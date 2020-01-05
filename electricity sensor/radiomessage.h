#ifndef RADIO_MESSAGE
#define RADIO_MESSAGE

#include "common.h"
#include <algorithm>

class RadioMessage
{
public:
    uint8_t payload[MAX_PAYLOAD_SIZE];
    uint8_t len;

    RadioMessage(uint8_t payloadParam[], int lenParam)
    {
        len = std::min(MAX_PAYLOAD_SIZE, lenParam);
        memcpy(payload, payloadParam, len);
    }

};

#endif
