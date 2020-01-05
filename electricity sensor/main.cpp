#include "common.h"
#include "electricitysensor.h"
#include "radiomessage.h"

/* This data is an example of what we will test your implementation with */
uint16_t periods[] = {1000, 1000, 3000, 4000,
                      4000, 500, 200, 200, 200,
                      200, 5000, 5000, 5000, 5600, 5005, 2001, 2003, 2004, 585, 698, 1999, 2398, 9348, 384, 987, 989, 709, 985, 912, 912,
                      456, 564, 566, 546, 567, 456,456, 456,654,543,453, 1279,1297,1578,1986,1287,7623,7895, 8214,8122,
                                            200, 5000, 5000, 5000, 5600, 5005, 2001, 2003, 2004, 585, 698, 1999, 2398, 9348, 384, 987, 989, 709, 985, 912, 912,
                  456, 564, 566, 546, 567, 456,456, 456,654,543,453, 1279,1297,1578,1986,1287,7623,7895, 8214,8122,
                                            200, 5000, 5000, 5000, 5600, 5005, 2001, 2003, 2004, 585, 698, 1999, 2398, 9348, 384, 987, 989, 709, 985, 912, 912,
                      456, 564, 566, 546, 567, 456,456, 456,654,543,453, 1279,1297,1578,1986,1287,7623,7895, 8214,8122};
                      
                      
/* This `main()` is how we will test your implementation */
int main()
{
    srand(time(NULL));

    uint32_t totalConsumption = 0;
    std::vector<RadioMessage> messages;

    const uint16_t periodCount = sizeof(periods) / sizeof(*periods);

    for (uint16_t i = 0; i < periodCount; i++)
    {
        // `ElectricitySensor` is notified of an incoming blink that way:
        ElectricitySensor::instance().notify(periods[i]);
        static int flag=0;

        // We check if ElectricitySensor want to transmit a radio message
        if (ElectricitySensor::instance().isReadyToTransmit())
        {
           
            uint8_t payload[MAX_PAYLOAD_SIZE] = {0};

            // Let's get your mocked radio message
            uint8_t len = ElectricitySensor::instance().getPayload(payload);

#if (LEVEL == 2) || (LEVEL == 4)
            if (rand() % MESSAGE_LOSS_PROBABILITY) // Only record ~ 5 messages on 6

            {

#if (LEVEL == 3) || (LEVEL == 4){
                uint8_t payload_t[len];
                memcpy(payload_t,payload,MAX_PAYLOAD_SIZE);
                toggleSomeBitsRandomly(payload, len, BIT_TOGGLE_PROBABILITY);
                if（flag==3)
                {
                    flag=0;
                    continue;
                }
                for(int j=0;j<len;j++)
                if(payload[i]!=payload_t[i])
                {
                    flag++;
                    i--;
                    break;
                }
                

}
               
                
                

#endif

                messages.push_back(RadioMessage(payload, len));
            }
            else
            {
                if (flag==0){
                    i--;
                    flag++;
                }
                else if (flag==3)
                {
                    flag=0；
                    continue;
                }
                
  
            }
#endif
            // Anyway you decided to transmit data, it will cost you some battery ;)
            totalConsumption += len + TRANSMISSION_CONSUMPTION_COST;
        }
    }

    

    /* We use YOUR implementation to transform the maybe corrupted RadioMessages into powerData */
    std::vector<double> powerArrayAfterRadio = ElectricitySensor::powersPerMillisFromRadioMessages(messages); // <-- you need to implement the content of that method
    std::vector<double> powerArrayTrue = UnitConverter::periodInMsToPowerInWatts(periods, periodCount);

    double rmse = computeRootMeanSquareError(powerArrayAfterRadio, powerArrayTrue);

    printf("Consumption is : %d  (the lower the better)\n", totalConsumption);
    printf("Error is :       %f  (the lower the better)\n", rmse);

    return 0;
}
