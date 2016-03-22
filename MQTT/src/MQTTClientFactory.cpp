//
// MQTTClientFactory.cpp
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

#include "IoT/MQTT/MQTTClientFactory.h"
#include "MQTTClientImpl.h"

namespace IoT {
namespace MQTT {

    template <>
    std::unique_ptr<MQTTClient> MQTTClientFactory::CreateMQTTClient<MQTTClientFactory::ClientType::Paho>(const std::string& serverUri,
        const std::string& clientId, const MQTTConnectOptions& options)
    {
        return std::unique_ptr<MQTTClient>(new MQTTClientImpl(serverUri, clientId, MQTTClientImpl::MQTT_PERSISTENCE_FILE, "/tmp", options));
    }
}
} // namespace IoT::MQTT
