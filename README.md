# MQTTClient
MQTTClient based/forked from Macchina.io 

The Project Macchina.io provides a sweet MQTT Client (Paho based), with Poco libraries.

# Dependencies
- Poco libraries (pocoproject.org);
- Paho dependencies:
    - SSL library;
    - Crypto library;
    - Posix Thread (pthread) library;
- Google Test libraries.

# How to install

- make build
- cd build
- cmake ..
- make
- sudo make install

The library and headers are moved to /usr/local.

[![Build Status](https://travis-ci.org/uilianries/MQTTClient.svg?branch=master)](https://travis-ci.org/uilianries/MQTTClient)
