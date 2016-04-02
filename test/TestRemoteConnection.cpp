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

#include "ServerConnectionTest.hpp"
#include "IoT/MQTT/MQTTClient.h"
#include "IoT/MQTT/MQTTClientFactory.h"
#include "TargetEvent.hpp"

class TestRemoteConnection : public ::testing::Test
{
protected:
    void SetUp() override
    {
        auto servers_uri = { "test.mosquitto.org",  "broker.hivemq.com" };
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
    const auto& mqtt_server_url = get_mqtt_server_url();

    std::string clientId = "TestIoTMQTTClient";
    constexpr auto mqtt_server_port = 1883;
    std::ostringstream broker_path;
    broker_path << mqtt_server_url << ":" << mqtt_server_port;

    IoT::MQTT::MQTTConnectOptions connectOptions;

    using IoT::MQTT::MQTTClientFactory;

    auto client = MQTTClientFactory::CreateMQTTClient<MQTTClientFactory::ClientType::Paho>({broker_path.str(),
        clientId,
        connectOptions});

    TargetEvent targetEvent;
    client->connectionLost += Poco::delegate(&targetEvent, &TargetEvent::onConnectionLost);
    client->messageDelivered += Poco::delegate(&targetEvent, &TargetEvent::onMessageDelivered);
    client->messageArrived += Poco::delegate(&targetEvent, &TargetEvent::onMessageArrived);

    const std::chrono::seconds timeout(10);
    constexpr auto topic = "test/iot/mqtt/foo/bar";
    constexpr auto message = "couse";

    client->subscribe(topic, IoT::MQTT::QoS::AT_LEAST_ONCE);
    auto token = client->publish(topic, message, IoT::MQTT::QoS::AT_LEAST_ONCE);

    ASSERT_TRUE(TargetEvent::waitFor(targetEvent.messageDeliveredvents_, timeout));
    ASSERT_EQ(token, targetEvent.messageDeliveredvents_.back().token);

    ASSERT_TRUE(TargetEvent::waitFor(targetEvent.messageArrivedEvents_, timeout));
    auto& payload = targetEvent.messageArrivedEvents_.back().message.payload;
    ASSERT_EQ(message, payload);

    client->unsubscribe(topic);
}