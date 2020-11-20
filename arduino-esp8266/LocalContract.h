#ifndef LOCAL_CONTRACT_H
#define LOCAL_CONTRACT_H

/**
 * Serial transmission packet structure
 * ************************************
 * 0x01 - Start of heading (SOH)
 * ... heading ...
 * 0x02 - Start of text (STX)
 * ... payload ...
 * 0x03 - End of text (ETX)
 */

#define CONTROL_SOH 0x01
#define CONTROL_STX 0x02
#define CONTROL_ETX 0x03

#define LOCAL_CONTRACT_REQUEST_STATE 0x30
#define LOCAL_CONTRACT_RESPONSE_STATE 0x31

#endif