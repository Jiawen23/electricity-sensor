#include "electricitysensor.h"

void ElectricitySensor::u16ToByteArray(uint16_t u16, uint8_t byteArray[2])
{
    for (int i = 0; i < 2; i++)
    {
        byteArray[i] = (u16 >> (8 * i)) & 0xff;
    }
}

uint16_t ElectricitySensor::byteArrayTo_u16(uint8_t byteArray[2])
{
    uint16_t ret = 0;
    for (int i = 0; i < 2; i++)
    {
        ret |= ((uint16_t)byteArray[i]) << (8 * i);
    }
    return ret;
}

ElectricitySensor::ElectricitySensor()
{
    
}

ElectricitySensor &ElectricitySensor::instance()
{
    static ElectricitySensor i;
    return i;
}

void ElectricitySensor::notify(uint16_t period)
{
    
    uint8_t periodInBytes[2];
    u16ToByteArray(period, periodInBytes);
    memcpy(payload, periodInBytes, 2);
}

bool ElectricitySensor::isReadyToTransmit( )
{
   uint8_t* payload;
   this-> getPayload(payload);
   if(sizeof(payload)==16*sizeof(uint8_t))
   return true;
   else
   return false;
}

uint8_t ElectricitySensor::getPayload(uint8_t *payload)
{
    memcpy(payload, this->payload, 2);
    return 2;
}

std::vector<double> ElectricitySensor::powersPerMillisFromRadioMessages(std::vector<RadioMessage> &messages)
{

    /*
    * This method takes a vector of Messages as input
    * It should return a vector of instant power consumption to the millisecond
    *
    * Each entry of the returned vector must represent 1 millisecond of power consumption
    *
    */

    uint16_t *periods = new uint16_t[messages.size()];

    for (uint16_t i = 0; i < messages.size(); i++)
    {
        periods[i] = byteArrayTo_u16(messages[i].payload);
    }
    return UnitConverter::periodInMsToPowerInWatts(periods, messages.size());
}
