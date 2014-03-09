#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "common.h"

#include <stdint.h>

void setupADC(void);
void setupPWM(void);
void enableHighSwitches(void);

#define PWM_CARRIER	12000UL

/* Current limit is scaled by resitstor value.  Valid entries are
 * [-512,511]. */
#define AMPS_TO_ADC(i)	((int16_t)((i)/2000.0*33.0/2.0/5.0*1024))
#define CURRENT_LIMIT	AMPS_TO_ADC(100.0)


#define PWM_TOP (uint16_t)(F_CPU / PWM_CARRIER)


#endif /* __AUDIO_H__ */
// vim:set tags+=/usr/avr/include/**/tags: //
