#include "BaseSerialNetwork.h"

BaseSerialNetwork::BaseSerialNetwork(SerialWrapper* dataLineSerial, SerialWrapper* debugLineSerial)
{
    this->dataLineSerial = dataLineSerial;
    this->debugLineSerial = debugLineSerial;
}

void BaseSerialNetwork::handleOutstandingPackets()
{
    if (dataLineSerial->available())
    {
        // Receive packet
        for (uint8_t stage = 0; stage < CONTROL_BYTES_COUNT; stage++)
        {
            if (!waitForBytes() || dataLineSerial->read() != CONTROL_DLE || 
                !handleNextTransmissionControlByte(stage))
            {
                debugLineSerial->print("Corrupt packet (stage = ");
                debugLineSerial->print(stage);
                debugLineSerial->println(")");
                discardPacket();
                return;
            }
        }
        // Process and discard packet
        processPacket();
        discardPacket();
    }
}

bool BaseSerialNetwork::handleNextTransmissionControlByte(const uint8_t stage)
{
    if (!waitForBytes()) return false;
    byte controlByte = dataLineSerial->read();
    if (transmissionControlOrder[stage] == controlByte)
    {
        if (!waitForBytes()) return false;
        switch (controlByte)
        {
        case CONTROL_SOH:
            transmissionPacket.code = dataLineSerial->read();
            return true;
        case CONTROL_STX:
            // get the body size
            transmissionPacket.bodySize = dataLineSerial->read();
            if (transmissionPacket.bodySize) // expect a body
            {
                transmissionPacket.bodyPtr = new byte[transmissionPacket.bodySize];   
                for (int i = 0; i < transmissionPacket.bodySize; i++)
                {
                    if (!waitForBytes()) return false;
                    transmissionPacket.bodyPtr[i] = dataLineSerial->read();
                }
            }
            return true;
        case CONTROL_ETX:
            return true;
        }
    }
    return false;
}

bool BaseSerialNetwork::waitForBytes()
{
    if (dataLineSerial->available())
        return true;
    unsigned long packetWaitStartTime = millis();
    while (!dataLineSerial->available())
    {
        if (millis() - packetWaitStartTime > PACKET_WAIT_TIMEOUT)
        {
            debugLineSerial->println("Packet wait timeout");
            discardPacket();
            return false;
        }
        delay(PACKET_WAIT_CYCLE);
    }
    return true;
}

void BaseSerialNetwork::discardPacket()
{
    if (transmissionPacket.bodyPtr != NULL)
    {
        delete[] transmissionPacket.bodyPtr;
    }
    transmissionPacket = {};
}

void BaseSerialNetwork::sendPacket(TransmissionPacket& packet)
{
    dataLineSerial->write(CONTROL_DLE);
    dataLineSerial->write(CONTROL_SOH);
    dataLineSerial->write(packet.code);
    dataLineSerial->write(CONTROL_DLE);
    dataLineSerial->write(CONTROL_STX);
    dataLineSerial->write(packet.bodySize);
    for (int i = 0; i < packet.bodySize; i++)
        dataLineSerial->write(packet.bodyPtr[i]);
    dataLineSerial->write(CONTROL_DLE);  
    dataLineSerial->write(CONTROL_ETX);  
}