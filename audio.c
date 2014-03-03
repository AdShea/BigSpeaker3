#include "common.h"
#include "audio.h"

#include <avr/io.h>
#include <avr/interrupt.h>

void setupADC(void) {
    /* Setup Channel A only, External Rail reference, right aligned */
    ADMUX = 0x40;

    /* Set the ADC clock to 125kHz (16MHz / 128) */
    ADCSRA = 0x07;

    /* Disable the DIO on ADC0 */
    DIDR0 = 0x01;
    
    /* Enable power to the ADC */
    PRR &= ~_BV(PRADC);

    /* Turn on the ADC */
    ADCSRA |= _BV(ADEN);

    /* Start a conversion to get things running, then wait for completion.
     * Finally, setup auto-trigger mode and enable the interrupt. */
    ADCSRA |= _BV(ADSC) | _BV(ADIF);
    
    loop_until_bit_is_set(ADCSRA,ADIF);
    ADCSRA |= _BV(ADIF);

    ADCSRB = 0x06;
    ADCSRA |= _BV(ADIF) | _BV(ADIE);
    ADCSRA |= _BV(ADATE);

    return;
}

void setupPWM(void) {
    makeSafe();

    /* Setup for FastPWM, ICR1 for TOP, Reverse sense for both outputs. */
    TCCR1A = _BV(COM1A1) | _BV(COM1A0) | _BV(COM1B1) | _BV(COM1B0) | _BV(WGM11);
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);

    TIMSK1 = _BV(TOIE1);

    ICR1 = PWM_TOP;

    return;
}

void enableHighSwitches(void) {
    PORTD |= 0x80;
    PORTB |= 0x01;
}

ISR(ADC_vect) {
    int16_t half;
    int16_t input;

    /* Process the ADC value and put it into the PWM output. This function
     * implements 1.25 gain right now, uses offset PWM. */
    input = (int16_t)(ADC) - (1<<9);
    half = input;
    input += input;
    
    OCR1A = PWM_TOP/2 + half;
    OCR1B = PWM_TOP/2 + half - input;
    
    ADCSRA |= _BV(ADIF);
    
}

// vim:set tags+=/usr/avr/include/**/tags: //
