#ifndef TRANSMISSION_PACKET_H
#define TRANSMISSION_PACKET_H

typedef struct
{
    byte code;
    uint8_t bodySize;
    byte* bodyPtr;
    // TODO add checksum support
} TransmissionPacket;

#endif