#ifndef LOCAL_CONTRACT_H
#define LOCAL_CONTRACT_H

/**
 * Serial transmission packet structure
 * ************************************
 * 0x10 - Data link escape (DLE)
 * 0x01 - Start of heading (SOH)
 * CODE (1 byte)
 * 0x10 - Data link escape (DLE)
 * 0x02 - Start of text (STX)
 * BODY_SIZE (1 byte)
 * BODY (BODY_SIZE bytes)
 * 0x10 - Data link escape (DLE)
 * 0x03 - End of text (ETX)
 */

#define CONTROL_SOH 0x01
#define CONTROL_STX 0x02
#define CONTROL_ETX 0x03
#define CONTROL_DLE 0x10

#define CONTROL_BYTES_COUNT 3
const byte transmissionControlOrder[CONTROL_BYTES_COUNT] =
{
    CONTROL_SOH,
    CONTROL_STX,
    CONTROL_ETX
};

#define LOCAL_CONTRACT_CODE_REQUEST_INIT_DATA 0x30
#define LOCAL_CONTRACT_CODE_RESPONSE_INIT_DATA 0x31
#define LOCAL_CONTRACT_CODE_RESPONSE_STATE 0x32
#define LOCAL_CONTRACT_CODE_RESPONSE_TEMPERATURES 0x33
#define LOCAL_CONTRACT_CODE_HR_MODE_AUTO 0x34
#define LOCAL_CONTRACT_CODE_HR_MODE_MANUAL 0x35

#endif