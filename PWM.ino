#include "T1PWM.h"

void setup(void)
{
    T1PWMInit();
    SetPWM1Period(0x3FFF);
}

void loop(void)
{
    uint16_t i;

    for (i = 0; i < 0x4000; i += 0x04) {
        SetPWM1A(i);
        SetPWM1B(i);
        SetPWM1C(i);
        delay(1);
    }
}
