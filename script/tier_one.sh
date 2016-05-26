#!/bin/bash

cd build
test/TestIoTMQTT
if [ $? -ne 0 ]; then
    exit 1
fi
exit 0
