#include "common.h"
#include "audio.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


/*FUSES = {
    .low = 0xEE,
    .high = 0x99,
    .extended = 0xFF,
};*/

int main(void) {
    int16_t count;

    /* Intitialize the LED so we can blink */
    DDRB = 1<<5;
    PORTB = 0;

    makeSafe();

    /* Wait for 5s to let the power come on */
    for(count = 300; count--; count){
	_delay_ms(100.0);
        PORTB ^= 1<<5;
    }	

    /* Setup the I/O for everything */
    setupADC();
    setupPWM();

    DDRD |= 1<<6;
    enableHighSwitches();
    sei();
    while(42) {
        _delay_ms(500.0);
    //    if((x++)&0x10) tuneUp();
      //  else tuneDown();
        PORTB ^= 1<<5;
	sei();
    }
}

ISR(BADISR_vect) {
    makeSafe();
    DDRB |= 1<<5;
    while(42) {
        _delay_ms(100.0);
        PORTB ^= 1<<5;
    }
}   

ISR(TIMER1_OVF_vect) {
    return;
}
// vim:set tags+=/usr/avr/include/**/tags: //
