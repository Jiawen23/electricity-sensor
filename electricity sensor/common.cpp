#include "common.h"
#include <stdlib.h>

double UnitConverter::periodInMsToPowerInWatts(uint16_t period)
{
    double power = 0;
    power = (3600.0 * 1000.0) / ((double)period);
    return power;
}

std::vector<double> UnitConverter::periodInMsToPowerInWatts(uint16_t period[], uint16_t len)
{
    std::vector<double> powerArray; //this vector will be returned

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < period[i]; j++)
        {
            powerArray.push_back(periodInMsToPowerInWatts(period[i]));
        }
    }
    return powerArray;
}

double computeRootMeanSquareError(std::vector<double> v1, std::vector<double> v2)
{
    double total_sum = 0;
    for (unsigned i = 0; i < v2.size(); i++)
    {
        double diff;
        if (i >= v1.size())
        {
            diff = v2[i];
        }
        else
        {
            diff = (v1[i] - v2[i]);
        }
        double diff_squared = diff * diff;
        total_sum += diff_squared / v2.size();
    }
    return sqrt(total_sum);
}

void toggleSomeBitsRandomly(uint8_t payload[], uint8_t len, uint8_t probability)
{
    for (uint16_t i = 0; i < len; i++)
    {
        for (uint8_t j = 0; j < 8; j++)
        {
            if ((rand() % probability) == 0)
            {
                payload[i] ^= 1 << j;
            }
        }
    }
}
