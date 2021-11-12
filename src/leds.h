#ifndef __LEDS_H__
#define __LEDS_H__

#include <stdint.h>
#include <stdbool.h>

void LedsCreate(uint16_t *puerto);

void LedsOn(int led);

void LedsOff(int led);

void LedsAllOn(void);

void LedsAllOff(void);

bool LedsIsOn(int led);

#endif /* __LEDS_H__ */