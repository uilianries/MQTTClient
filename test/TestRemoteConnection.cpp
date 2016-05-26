//
// TestRemoteConnection.cpp
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

#include <chrono>
#include <gtest/gtest.h>
#include <Poco/Delegate.h>
#include <Poco/Process.h>

#include "ServerConnectionTest.hpp"
#include "IoT/MQTT/MQTTClient.h"
#include "IoT/MQTT/MQTTClientFactory.h"
#include "TargetEvent.hpp"

class TestRemoteConnection : public ::testing::Test
{
protected:
    void SetUp() override
    {
        auto servers_uri = { "test.mosquitto.org", "broker.hivemq.com" };
        auto connected = false;
        for (const auto& server_uri : servers_uri) {
            connected = internet_connection::test_connection(server_uri);
            if (connected) {
                mqtt_server_url_ = server_uri;
                break;
            }
        }

        ASSERT_TRUE(connected);
    }

    const std::string& get_mqtt_server_url() const noexcept
    {
        return mqtt_server_url_;
    }

private:
    std::string mqtt_server_url_;
};

TEST_F(TestRemoteConnection, ConnectToMQTTCloud)
{
    const auto& mqtt_server_url = "m10.cloudmqtt.com";

    std::string clientId = "TestIoTMQTTClient_" + std::to_string(Poco::Process::id());
    constexpr auto mqtt_server_port = 17460;
    std::ostringstream broker_path;
    broker_path << mqtt_server_url << ":" << mqtt_server_port;

    IoT::MQTT::MQTTConnectOptions connectOptions;
    connectOptions.username = "mqttclient";
    connectOptions.password = "mqttclient";

    using IoT::MQTT::MQTTClientFactory;

    auto client = MQTTClientFactory::CreateMQTTClient<MQTTClientFactory::ClientType::Paho>({broker_path.str(),
        clientId,
        connectOptions});

    TargetEvent targetEvent;
    client->connectionLost += Poco::delegate(&targetEvent, &TargetEvent::onConnectionLost);
    client->messageDelivered += Poco::delegate(&targetEvent, &TargetEvent::onMessageDelivered);
    client->messageArrived += Poco::delegate(&targetEvent, &TargetEvent::onMessageArrived);
    client->connectionDone +=  Poco::delegate(&targetEvent, &TargetEvent::onConnectionDone);

    const std::chrono::seconds timeout(10);
    constexpr auto topic = "foo/bar";

    ASSERT_TRUE(!client->connected());
    client->subscribe(topic, IoT::MQTT::QoS::AT_LEAST_ONCE);
    ASSERT_TRUE(TargetEvent::waitFor(targetEvent.connectionDoneEvents_, timeout));
    ASSERT_TRUE(client->connected());

    auto token = client->publish(topic, __FILE__, IoT::MQTT::QoS::AT_LEAST_ONCE);

    ASSERT_TRUE(TargetEvent::waitFor(targetEvent.messageDeliveredvents_, timeout));
    ASSERT_EQ(token, targetEvent.messageDeliveredvents_.back().token);

    ASSERT_TRUE(TargetEvent::waitFor(targetEvent.messageArrivedEvents_, timeout));
    auto& payload = targetEvent.messageArrivedEvents_.back().message.payload;
    ASSERT_EQ(__FILE__, payload);

    client->unsubscribe(topic);
    client->disconnect(10000);
    ASSERT_TRUE(!client->connected());
}