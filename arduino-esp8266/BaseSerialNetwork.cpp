#include "BaseSerialNetwork.h"

void BaseSerialNetwork::handleOutstandingPackets()
{
    if (DataLineSerial.available())
    {
        // Receive packet
        for (uint8_t stage = 0; stage < CONTROL_BYTES_COUNT; stage++)
        {
            if (!waitForBytes() || DataLineSerial.read() != CONTROL_DLE || 
                !handleNextTransmissionControlByte(stage))
            {
                DebugLineSerial.print("Corrupt packet (stage = ");
                DebugLineSerial.print(stage);
                DebugLineSerial.println(")");
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
    byte controlByte = DataLineSerial.read();
    if (transmissionControlOrder[stage] == controlByte)
    {
        if (!waitForBytes()) return false;
        switch (controlByte)
        {
        case CONTROL_SOH:
            transmissionPacket.code = DataLineSerial.read();
            return true;
        case CONTROL_STX:
            // get the body size
            transmissionPacket.bodySize = DataLineSerial.read();
            if (transmissionPacket.bodySize) // expect a body
            {
                transmissionPacket.bodyPtr = new byte[transmissionPacket.bodySize];   
                for (int i = 0; i < transmissionPacket.bodySize; i++)
                {
                    if (!waitForBytes()) return false;
                    transmissionPacket.bodyPtr[i] = DataLineSerial.read();
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
    if (DataLineSerial.available())
        return true;
    unsigned long packetWaitStartTime = millis();
    while (!DataLineSerial.available())
    {
        if (millis() - packetWaitStartTime > PACKET_WAIT_TIMEOUT)
        {
            DebugLineSerial.println("Packet wait timeout");
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
    DataLineSerial.write(CONTROL_DLE);
    DataLineSerial.write(CONTROL_SOH);
    DataLineSerial.write(packet.code);
    DataLineSerial.write(CONTROL_DLE);
    DataLineSerial.write(CONTROL_STX);
    DataLineSerial.write(packet.bodySize);
    for (int i = 0; i < packet.bodySize; i++)
        DataLineSerial.write(packet.bodyPtr[i]);
    DataLineSerial.write(CONTROL_DLE);  
    DataLineSerial.write(CONTROL_ETX);  
}