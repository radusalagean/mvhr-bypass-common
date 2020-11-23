#ifndef BASE_SERIAL_NETWORK_H
#define BASE_SERIAL_NETWORK_H

#include <Arduino.h>
#include <string.h>
#include "LocalContract.h"
#include "State.h"
#include "TransmissionPacket.h"
#include "SerialWrapper.h"

#define PACKET_WAIT_TIMEOUT 2000
#define PACKET_WAIT_CYCLE 100

class BaseSerialNetwork
{
private:
    SerialWrapper* dataLineSerial = NULL;
    SerialWrapper* debugLineSerial = NULL;
    void discardPacket();
    bool handleNextTransmissionControlByte(const uint8_t stage);
    bool waitForBytes();

protected:
    BaseSerialNetwork(SerialWrapper* dataLineSerial, SerialWrapper* debugLineSerial);
    TransmissionPacket transmissionPacket = {};
    virtual void processPacket() = 0;

public:
    void handleOutstandingPackets();
    virtual void sendPacket(TransmissionPacket& packet);
};

#endif