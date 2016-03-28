//
// subscribe.cpp
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

#include <cstdlib>
#include <tuple>
#include <iostream>

#include "Poco/Delegate.h"

#include "IoT/MQTT/MQTTConnectOptions.h"
#include "IoT/MQTT/MQTTClient.h"
#include "IoT/MQTT/MQTTClientFactory.h"

using IoT::MQTT::MQTTClientFactory;

/**
 * \brief Treat event from server
 */
class Target
{
    /** Wait for message from server */
    bool message_absent_ = true;
public:

    /**
     * \brief Delegated function to treat arrived messages
     * \param _sender Message provider
     * \param _event Event released from server
     */
    void OnMessageArrived(const void* _sender, const IoT::MQTT::MessageArrivedEvent& _event)
    {
        std::ignore = _sender;

        std::cout << __func__ << std::endl;
        std::cout << "Topic: " << _event.topic << std::endl;
        std::cout << "Payload: " << _event.message.payload << std::endl;
        std::cout << std::flush;

        message_absent_ = false;
    }

    /**
    * \brief Receive event from Connection lost
    * \param _sender Message provider
    * \param _event String error description
    */
    void OnConnectionLost(const void *_sender, const IoT::MQTT::ConnectionLostEvent& _event)
    {
        std::cerr << "Connection Lost: " << _event.cause << std::endl;
        std::cerr << std::flush;

        message_absent_ = false;
    }

    /**
     * \brief Get message status
     */
    bool messageArrived() const noexcept
    {
        return message_absent_;
    }
};

/**
 * \brief Main
 */
int main()
{
    MQTTClientFactory::FactoryArguments factoryArguments;
    factoryArguments.clientId = "IoTMQTTClientSampleSubscribe";
    factoryArguments.serverUri = "test.mosquitto.org";

    auto client = MQTTClientFactory::CreateMQTTClient<MQTTClientFactory::ClientType::Paho>(factoryArguments);

    Target target;
    client->connectionLost += Poco::delegate(&target, &Target::OnConnectionLost);
    client->messageArrived += Poco::delegate(&target, &Target::OnMessageArrived);

    client->subscribe("$SYS/broker/version", IoT::MQTT::QoS::AT_LEAST_ONCE);

    while (target.messageArrived());

    return EXIT_SUCCESS;
}