#ifndef _T1PWM
#define _T1PWM

// Initialize Timer 1 for variable resolution "Fast PWM" mode
extern void T1PWMInit(void);

// Set PWM period for Timer 1
extern void SetPWM1Period(uint16_t period);

// Set PWM pulse width for Timer 1 channel A - OCR1A
extern void SetPWM1A(uint16_t width);

// Set PWM pulse width for Timer 1 channel B - OCR1B
extern void SetPWM1B(uint16_t width);

// Set PWM pulse width for Timer 1 channel C - OCR1C
extern void SetPWM1C(uint16_t width);

#endif
