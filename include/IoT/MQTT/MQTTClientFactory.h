//
// MQTTClientFactory.h
//
// $Id$
//
// Library: IoT/MQTT
// Package: MQTTClient
// Module:  MQTTClient
//
// Definition of the MQTTClient interface.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_MQTT_MQTTClientFactory_INCLUDED
#define IoT_MQTT_MQTTClientFactory_INCLUDED

#include <string>
#include <memory>

#include "Poco/AutoPtr.h"

#include "IoT/MQTT/MQTTClient.h"
#include "IoT/MQTT/MQTTConnectOptions.h"

namespace IoT {
namespace MQTT {

    /**
     * \brief Provide MQTTClient creation
     */
    class MQTTClientFactory {
        public:

    /**
     * \brief Type to instance by factory
     */
    enum class ClientType {
        Paho
    };

    template <ClientType>
    /**
     * \brief Create a MQTT client, based on some sub-client.
     *        For now, the only supported is Paho.
     * \param serverURI Broker address
     * \param clientId Unique identifier to broker register
     * \param options Connections Options
     * \return A MQTTClient instance
     */
    static std::unique_ptr<MQTTClient> CreateMQTTClient(const std::string& serverUri,
            const std::string& clientId, const MQTTConnectOptions& options);

    };


} } // namespace IoT::MQTT


#endif // IoT_MQTT_MQTTClientFactory_INCLUDED
