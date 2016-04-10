//
// TargetEvent.hpp
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

#ifndef MACCHINAIOMQTTCLIENT_TARGETEVENT_HPP
#define MACCHINAIOMQTTCLIENT_TARGETEVENT_HPP

#include <chrono>
#include <thread>

#include "IoT/MQTT/MQTTClient.h"

/**
 * \brief Receive events from MQTT client
 */
struct TargetEvent {
    /**
     * \brief Push any message fired by client
     * \param sender Client instance
     * \param event Message fired
     */
    void onMessageArrived(const void* sender, const IoT::MQTT::MessageArrivedEvent& event)
    {
        (void)sender;
        messageArrivedEvents_.push_back(event);
    }

    void onMessageDelivered(const void* sender, const IoT::MQTT::MessageDeliveredEvent& event)
    {
        (void)sender;
        messageDeliveredvents_.push_back(event);
    }

    void onConnectionLost(const void* sender, const IoT::MQTT::ConnectionLostEvent& event)
    {
        (void)sender;
        connectionLostEvents_.push_back(event);
    }

    void onConnectionDone(const void* sender, const IoT::MQTT::ConnectionDoneEvent& event)
    {
        (void)sender;
        connectionDoneEvents_.push_back(event);
    }

    template <typename T>
    /**
     * \brief Wait for vector is not empty, within the duration
     * \param any vector to be observed
     * \param duration time limit to check
     * \return true if the vector is not empty. Otherwise, false
     */
    static bool waitFor(const std::vector<T>& any, const std::chrono::seconds& duration)
    {
        const std::chrono::milliseconds interval{ 250 };
        const auto timeout = std::chrono::steady_clock::now() + duration;

        while (timeout >= std::chrono::steady_clock::now()) {
            if (!any.empty()) {
                return true;
            }
            std::this_thread::sleep_for(interval);
        }
        return false;
    }

    std::vector<IoT::MQTT::MessageArrivedEvent> messageArrivedEvents_;
    std::vector<IoT::MQTT::MessageDeliveredEvent> messageDeliveredvents_;
    std::vector<IoT::MQTT::ConnectionLostEvent> connectionLostEvents_;
    std::vector<IoT::MQTT::ConnectionDoneEvent> connectionDoneEvents_;

};

#endif //MACCHINAIOMQTTCLIENT_TARGETEVENT_HPP
