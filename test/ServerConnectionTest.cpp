//
// ServerConnectionTest.cpp
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

#include "ServerConnectionTest.hpp"

#include <Poco/URI.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPBasicCredentials.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/NetException.h>

namespace internet_connection {

bool test_connection(const std::string& url)
{
    auto result = false;
    Poco::Net::HTTPClientSession session(url);
    Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET);
    try {
        session.sendRequest(req);
        result = true;
    }
    catch (const Poco::Net::HostNotFoundException&) {
    }

    return result;
}
}
