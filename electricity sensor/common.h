#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <vector>
#include <stdint.h>
#include <math.h>
#include <time.h>

#define LEVEL (1)

#define TRANSMISSION_CONSUMPTION_COST (8)
#define MAX_PAYLOAD_SIZE (16)

#if LEVEL == 1
#endif

#if (LEVEL == 2) || (LEVEL == 4)
#define MESSAGE_LOSS_PROBABILITY (6) /* 1 message on 6 is lost */
#endif

#if (LEVEL == 3) || (LEVEL == 4)
#define BIT_TOGGLE_PROBABILITY (20) /* 1 bit on 20 is toggled */
#endif

class UnitConverter
{
public:
    static double periodInMsToPowerInWatts(uint16_t period);
    static std::vector<double> periodInMsToPowerInWatts(uint16_t period[], uint16_t len);
};

double computeRootMeanSquareError(std::vector<double> v1, std::vector<double> v2);
void toggleSomeBitsRandomly(uint8_t payload[], uint8_t len, uint8_t probability);

#endif
