//
// MQTTClientOption.h
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


#ifndef IoT_MQTT_MQTTClientOption_INCLUDED
#define IoT_MQTT_MQTTClientOption_INCLUDED

#include <vector>
#include <string>

namespace IoT {
namespace MQTT {

	enum QoS {
		AT_MOST_ONCE ,
		AT_LEAST_ONCE,
		EXACTLY_ONCE
	};

	enum Version {
		DEFAULT,
		V_3_1 = 3,
		V_3_1_1
	};

	struct MQTTConnectOptions
	{
		int keepAliveInterval = 20;
			/// Keep-alive interval in seconds.
	
		int retryInterval = 10;
			/// Retry interval in seconds.
		
		int connectTimeout = 10;
			/// Connect timeout in seconds.

		bool cleanSession = true;
			/// Start with a clean session.
			
		bool reliable = false;
			/// If set to true, only one message at a time can be "in flight".

		std::string username;
			/// Username for MQTT v3.1.

		std::string password;
			/// Password for MQTT v3.1.
	
		std::string willTopic;
			/// Last will topic name.
	
		std::string willMessage;
			/// Last will message.

		bool willRetained = false;
			/// Retained flag for will message.
	
		QoS willQoS = IoT::MQTT::QoS::AT_MOST_ONCE;
			/// Quality of Service level for will message (0-2).
	
		std::vector<std::string> serverURIs;
			/// Optional list of server URIs.

		Version mqttVersion = Version::DEFAULT;
			/// Sets the version of MQTT to be used on the connect. Valid values are
			/// 0, 3 and 4.
			///   * 0 = default: start with 3.1.1, and if that fails, fall back to 3.1 
			///   * 3 = only try version 3.1  
			///   * 4 = only try version 3.1.1
			
		std::string sslTrustStore;
			/// The file in PEM format containing the public digital certificates trusted by the client.
		
		std::string sslKeyStore;
			/// The file in PEM format containing the public certificate chain of the client. 
			/// It may also include the client's private key.
			
		std::string sslPrivateKey;
			/// If not included in the sslKeyStore, this setting points to the file in PEM 
			/// format containing the client's private key.
			
		std::string sslPrivateKeyPassword;
			/// The password to load the client's privateKey if encrypted.
			
		std::string sslEnabledCipherSuites;
			/// The list of cipher suites that the client will present to the server 
			/// during the SSL handshake. For a full explanation of the cipher list 
			/// format, please see the OpenSSL on-line documentation: 
			/// http://www.openssl.org/docs/apps/ciphers.html#CIPHER_LIST_FORMAT 
			/// If this setting is ommitted, its default value will be "ALL", that is, 
			/// all the cipher suites -excluding those offering no encryption- will be 
			/// considered. This setting can be used to set an SSL anonymous connection 
			/// ("aNULL" string value, for instance).
			
		bool sslEnableServerCertAuth = false;
			/// Enable or disable verification of the server certificate.
	};

} } // namespace IoT::MQTT

#endif // IoT_MQTT_MQTTClientOption_INCLUDED
