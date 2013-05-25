#include <util/atomic.h>

//------------------------------------------------------------------------------

void T1PWMInit(void)
{
ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    // Power up timer 1

    PRR0 &= ~_BV(PRTIM1);    // Clear bit to enable

    // Ensure that all Timer 1 interrupts are DISABLED

    TIMSK1 = 0;     // Disable all timer 1 interrupts
    TCCR1B = 0;     // Stop counter until init done

    // When timer is set up for WGM mode 14 (Fast PWM, ICR sets PWM period),
    // the input capture register sets the terminal count for the timer.
    // Set it to 16-bit MAXINT for full 16-bit resolution.

    ICR1 = 0xFFFE;

    // Set compare values (PWM period) to minimum for now

    OCR1A = 0;
    OCR1B = 0;
    OCR1C = 0;

    // Configure timer 1 output mode - Timer 1 control register A (TCCR1A)
    // Reset counter and clear interrupt flags

    TCNT1 = 0;      // Reset counter
    TIFR1 = 0xFF;   // Clears all interrupt flags (writing 1's clears them)

    // COM1n1,COM1n0 = 1,0 to force output pin low on compare match.
    //   Set high when timer hits max count.
    // Set COM1n1,COM1n0 = 1,1 to set output HIGH on compare match and LOW
    //   at max count.
    // WGM1n1,WGM1n0 = 1,0 - these are the two low bits of the 4-bit timer mode.
    // Timer will use mode 14 (1110) to select Fast PWM using ICR1 to specify
    //   max count. 

    // "Blow" mode (high = ON): Output low on compare match
//  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(COM1C1) | _BV(WGM11);
    // "Suck" mode (low = ON): Output high on compare match (use with FETs)
    TCCR1A = _BV(COM1A1) | _BV(COM1A0) | _BV(COM1B1) | _BV(COM1B0) | _BV(COM1C1) | _BV(COM1C0) | _BV(WGM11);

    // Configure timer 1 counting mode - Timer 1 control register B (TCCR1B)
    // Waveform generation mode 14 (1110), Fast PWM with ICR1 setting max count
    //   WGM13,WGM12 = 11
    // Select maximum rate clock (clkio/1), CS12,CS11,CS10 = 001.
    //   Counter will start running when this register is set.
    // Input capture not used, ICNC1 = 0 and ICES1 = 0 

    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);

    // Timer 1 control register C (TCCR1C) is used to force ouotput compares
    // and is not used in PWM modes.

//  TCCR1C = 0;

    // Configure timer 1 compare pins as outputs

//  PORTB &= ~0xE0;	// "Blow" mode (high = ON): PB5,6,7 low
    PORTB |= 0xE0;  // "Suck" mode (low = ON):  PB5,6,7 high
    DDRB |= 0xE0;   // PB5/OC1A, PB6/OC1B, PB7/OC1C
} // End ATOMIC_BLOCK
}

//-----------------------------------------------------------------------------
// Set Timer 1 PWM pulse period

void SetPWM1Period(uint16_t period)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        ICR1 = period;
    }
}

//-----------------------------------------------------------------------------
// Set PWM pulse width for Timer 1 channel A

void SetPWM1A(uint16_t width)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        OCR1A = width;
    }
}
    
//-----------------------------------------------------------------------------
// Set PWM pulse width for Timer 1 channel B

void SetPWM1B(uint16_t width)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        OCR1B = width;
    }
}
    
//-----------------------------------------------------------------------------
// Set PWM pulse width for Timer 1 channel C

void SetPWM1C(uint16_t width)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        OCR1C = width;
    }
}
