#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "common.h"

#include <stdint.h>

void setupADC(void);
void setupPWM(void);
void enableHighSwitches(void);

#define PWM_CARRIER 12000UL

#define PWM_TOP (uint16_t)(F_CPU / PWM_CARRIER)


#endif /* __AUDIO_H__ */
// vim:set tags+=/usr/avr/include/**/tags: //
