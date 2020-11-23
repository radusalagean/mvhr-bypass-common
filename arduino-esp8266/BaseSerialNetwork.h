#ifndef BASE_SERIAL_NETWORK_H
#define BASE_SERIAL_NETWORK_H

#include <Arduino.h>
#include <string.h>
#include "LocalContract.h"
#include "State.h"
#include "TransmissionPacket.h"

#define PACKET_WAIT_TIMEOUT 2000
#define PACKET_WAIT_CYCLE 100

#if defined(__AVR__)

// TODO

#elif defined(ESP8266)

#define DataLineSerial Serial
#define DebugLineSerial Serial1

#endif

class BaseSerialNetwork
{
private:
    void discardPacket();
    bool handleNextTransmissionControlByte(const uint8_t stage);
    bool waitForBytes();

protected:
    TransmissionPacket transmissionPacket = {};
    virtual void processPacket() = 0;

public:
    void handleOutstandingPackets();
    void sendPacket(TransmissionPacket& packet);
};

#endif