#ifndef BASE_SERIAL_NETWORK_H
#define BASE_SERIAL_NETWORK_H

class BaseSerialNetwork;

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
    SerialWrapper* debugLineSerialRx = NULL;
    SerialWrapper* debugLineSerialTx = NULL;
    void discardPacket();
    bool handleNextTransmissionControlByte(const uint8_t stage);
    bool waitForBytes();

protected:
    BaseSerialNetwork(SerialWrapper* dataLineSerial, SerialWrapper* debugLineSerialRx, SerialWrapper* debugLineSerialTx);
    TransmissionPacket transmissionPacket = {};
    virtual void sendPacket(TransmissionPacket& packet);
    virtual void processPacket() = 0;

public:
    void handleOutstandingPackets();
    template<typename T>
    void send(T* t, uint8_t code);
};

template<typename T>
void BaseSerialNetwork::send(T* t, uint8_t code)
{
    byte* buffer = new byte[sizeof(T)];
    memcpy(buffer, t, sizeof(T));
    TransmissionPacket packet =
    {
        code, sizeof(T), buffer
    };
    sendPacket(packet);
    delete[] buffer;
}

#endif