#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>

#define F_CPU 16000000UL

#define makeSafe() {	\
    PORTB &= 0xF8;	\
    PORTD &= 0x7F;	\
    DDRB |= 0x07;	\
    DDRD |= 0x80;	\
    PORTB &= 0xF8;	\
    PORTD &= 0x7F;	\
    TCCR1A &= 0x0F;	\
    }

#endif /* __COMMON_H__ */
// vim:set tags+=/usr/avr/include/**/tags: //
