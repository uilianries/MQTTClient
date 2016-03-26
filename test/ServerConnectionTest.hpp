//
// ServerConnectionTest.hpp
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

#ifndef HTTPREQUEST_SERVERCONNECTIONTEST_HPP
#define HTTPREQUEST_SERVERCONNECTIONTEST_HPP

#include <string>

namespace internet_connection {

static constexpr auto DEFAULT_SERVER_ADDRESS = "www.google.com";

bool test_connection(const std::string& url = DEFAULT_SERVER_ADDRESS);
}

#endif //HTTPREQUEST_SERVERCONNECTIONTEST_HPP
