#ifndef _T1PWM
#define _T1PWM

#include <stdint.h>

// Initialize Timer 1 for variable resolution "Fast PWM" mode
void T1PWMInit(void);

// Set PWM period for Timer 1
void SetPWM1Period(uint16_t period);

// Set PWM pulse width for Timer 1 channel A - OCR1A
void SetPWM1A(uint16_t width);

// Set PWM pulse width for Timer 1 channel B - OCR1B
void SetPWM1B(uint16_t width);

// Set PWM pulse width for Timer 1 channel C - OCR1C
void SetPWM1C(uint16_t width);

#endif
