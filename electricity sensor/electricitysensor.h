#ifndef ELECTRICITY_SENSOR
#define ELECTRICITY_SENSOR

#include "common.h"
#include <string.h>
#include "radiomessage.h"

class ElectricitySensor
{
    static void u16ToByteArray(uint16_t u16, uint8_t byteArray[2]);
    static uint16_t byteArrayTo_u16(uint8_t byteArray[2]);

    uint8_t payload[MAX_PAYLOAD_SIZE];

public:
    ElectricitySensor();
    static ElectricitySensor &instance();
    void notify(uint16_t period);
    bool isReadyToTransmit();
    uint8_t getPayload(uint8_t *payload);
    static std::vector<double> powersPerMillisFromRadioMessages(std::vector<RadioMessage> &messages);
};

#endif // ELECTRICITY_SENSOR
