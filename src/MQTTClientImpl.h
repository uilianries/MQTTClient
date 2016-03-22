//
// MQTTClientImpl.h
//
// $Id$
//
// Library: IoT/MQTT
// Package: MQTTClient
// Module:  MQTTClientImpl
//
// Definition of the MQTTClientImpl class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_MQTT_MQTTClientImpl_INCLUDED
#define IoT_MQTT_MQTTClientImpl_INCLUDED


#include "IoT/MQTT/MQTTClient.h"
#include "IoT/MQTT/MQTTConnectOptions.h"
#include "Poco/Util/Timer.h"
#include "Poco/Logger.h"
#include "Poco/Mutex.h"
#include <map>


extern "C" {
#include "MQTTClient.h"
}


namespace IoT {
namespace MQTT {


class IoTMQTT_API MQTTClientImpl: public IoT::MQTT::MQTTClient
	/// The default implementation of MQTTClient based on paho.
{
public:
	typedef Poco::SharedPtr<MQTTClientImpl> Ptr;

	
	enum Persistence
	{
		MQTT_PERSISTENCE_NONE = 0,     /// In-memory persistence.
		MQTT_PERSISTENCE_FILE = 1,     /// File-based persistence.
		MQTT_PERSISTENCE_DATABASE = 2  /// Database-based persistence.
	};
	
	MQTTClientImpl(const std::string& serverAddr, const std::string& clientId, Persistence persistence, const std::string& persistencePath, const MQTTConnectOptions& connectOptions);
		/// Creates the MQTTClientImpl with the given server URI, client ID, persistence, persistence path
		/// and connect options.
		///
		/// For File-based persistence, the path should specify a directory.
		/// For SQLite-based persistence, the path should specify a SQLite database file.

	~MQTTClientImpl();
		/// Destroys the MQTTClientImpl.
		
	void connect();
		/// Connects to the MQTT server, if not yet connected.
		///
		/// Throws a Poco::IOException if the connection cannot be established.
		
	void disconnect(int timeout);
		/// This function attempts to disconnect the client from the MQTT server. 
		/// In order to allow the client time to complete handling of messages that are 
		/// in-flight when this function is called, a timeout period is specified. 
		/// When the timeout period has expired, the client disconnects even if there 
		/// are still outstanding message acknowledgements. The next time the client 
		/// connects to the same server, any QoS 1 or 2 messages which have not completed 
		/// will be retried depending on the clean session settings for both the previous 
		/// and the new connection.
	
	// MQTTClient
	const std::string& id() const;
	const std::string& serverURI() const;
	bool connected() const;
	std::vector<TopicQoS> subscribedTopics() const;
	Statistics statistics() const;
	int publish(const std::string& topic, const std::string& payload, int qos);
	int publishMessage(const std::string& topic, const Message& message);
	void subscribe(const std::string& topic, int qos);
	void unsubscribe(const std::string& topic);
	void subscribeMany(const std::vector<TopicQoS>& topicsAndQoS);
	void unsubscribeMany(const std::vector<std::string>& topics);
	
protected:
	enum 
	{
		INITIAL_RECONNECT_DELAY = 1000,
		MAXIMUM_RECONNECT_DELAY = 32000
	};
	
	void reconnect();
	void connectImpl(const MQTTConnectOptions& options);
	void resubscribe();

	static std::string errorMessage(int code);
	static void onConnectionLost(void* context, char* cause);
	static void onMessageDelivered(void* context, int token);
	static int onMessageArrived(void* context, char* topicName, int topicLen, MQTTClient_message* message);
	
private:
	std::string _clientId;
	std::string _serverURI;
	MQTTConnectOptions _options;
	long _reconnectDelay;
	std::map<std::string, int> _subscribedTopics;
	std::map<std::string, int> _receivedMessages;
	std::map<std::string, int> _publishedMessages;
	::MQTTClient _mqttClient;
	Poco::Util::Timer _timer;
	Poco::Logger& _logger;
	mutable Poco::Mutex _mutex;
	
	friend class ReconnectTask;
};


} } // namespace IoT::MQTT


#endif // IoT_MQTT_MQTTClientImpl_INCLUDED
