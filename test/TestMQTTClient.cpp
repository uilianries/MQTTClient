//
// TestMQTTClient.cpp
//
// $Id$
//
// Library: IoT/MQTT
// Package: MQTTClient
// Module:  MQTTClient
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//

#include <vector>
#include <chrono>
#include <thread>

#include <gtest/gtest.h>

#include <Poco/Process.h>
#include <Poco/Environment.h>
#include <Poco/Path.h>
#include <Poco/PipeStream.h>
#include <Poco/Delegate.h>
#include <Poco/Any.h>

#include "IoT/MQTT/MQTTClientFactory.h"
#include "TargetEvent.hpp"

/** Manages Mosquitto Process */
class MosquittoProcess {
public:
    /** Default port for broker listen */
    static constexpr auto MOSQUITTO_PORT = 1883;

    /**
     * \brief Start Mosquitto Broker on local machine
     */
    MosquittoProcess()
    {
        auto path = Poco::Environment::get("PATH");
        Poco::Path mosquittoPath;

        if (!Poco::Path::find(path, "mosquitto", mosquittoPath)) {
            throw std::runtime_error("Could not found mosquitto in PATH");
        }

        std::vector<std::string> process_args;
        std::string mosquittPortArg = " -p " + std::to_string(MOSQUITTO_PORT);

        auto handle = Poco::Process::launch(mosquittoPath.absolute().toString() + mosquittPortArg, process_args, nullptr, &outPipe_, nullptr);
        if (handle.id() == -1) {
            throw std::runtime_error("Could not launch mosquitto process");
        }

        std::clog << "TRACE: Mosquitto started with pid " << handle.id() << std::endl;

        mosquittoPid_ = handle.id();
    }

    ~MosquittoProcess()
    {
        Poco::Process::kill(mosquittoPid_);
    }

private:
    Poco::Process::PID mosquittoPid_;
    Poco::Pipe outPipe_;
};

class TestMQTTClient : public testing::Test {
public:
    void SetUp() override
    {

        std::string mosquittoUri = "127.0.0.1:" + std::to_string(MosquittoProcess::MOSQUITTO_PORT);
        std::string clientId = "TestMQTTClient";
        IoT::MQTT::MQTTConnectOptions connectOptions;

        using IoT::MQTT::MQTTClientFactory;

        mqttClient_ = MQTTClientFactory::CreateMQTTClient<MQTTClientFactory::ClientType::Paho>(mosquittoUri,
            clientId,
            connectOptions);
    }

protected:
    std::unique_ptr<IoT::MQTT::MQTTClient> mqttClient_;

private:
    std::unique_ptr<MosquittoProcess> mosquittoProcess_;
};

TEST_F(TestMQTTClient, ConnectedOnMosquitto)
{
}

TEST_F(TestMQTTClient, SubscribeOnMosquitto)
{
    constexpr auto qos = IoT::MQTT::QoS::AT_LEAST_ONCE;
    const std::string topic{ "$SYS/#" };
    mqttClient_->subscribe(topic, qos);
}

TEST_F(TestMQTTClient, Loopback)
{
    TargetEvent targetEvent;

    mqttClient_->messageArrived += Poco::delegate(&targetEvent, &TargetEvent::onMessageArrived);
    mqttClient_->messageDelivered += Poco::delegate(&targetEvent, &TargetEvent::onMessageDelivered);
    mqttClient_->connectionLost += Poco::delegate(&targetEvent, &TargetEvent::onConnectionLost);

    constexpr auto qos = IoT::MQTT::QoS::AT_LEAST_ONCE;
    const std::string topic{ "test/IoTMQTTClient/foobar" };
    mqttClient_->subscribe(topic, qos);

    const std::string message{ "C0U$&" };
    auto pulishToken = mqttClient_->publish(topic, message, qos);

    ASSERT_TRUE(TargetEvent::waitFor(targetEvent.messageDeliveredvents_, std::chrono::seconds(3)));
    ASSERT_EQ(pulishToken, targetEvent.messageDeliveredvents_.front().token);

    ASSERT_TRUE(TargetEvent::waitFor(targetEvent.messageArrivedEvents_, std::chrono::seconds(3)));
    ASSERT_EQ(topic, targetEvent.messageArrivedEvents_.front().topic);
    ASSERT_EQ(message, targetEvent.messageArrivedEvents_.front().message.payload);
    ASSERT_EQ(1, targetEvent.messageArrivedEvents_.front().message.qos);

    mqttClient_->unsubscribe(topic);
}
