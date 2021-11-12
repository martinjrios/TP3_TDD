#include "leds.h"
#include "errores.h"

#define LEDS_ALL_OFF        0x0000
#define LEDS_ALL_ON         0xFFFF
#define LEDS_OFFSET         1
#define LED_ON_STATE        1
#define FIRST_LED           1
#define LAST_LED            16
#define LED_TO_MASK(x)      (LED_ON_STATE << (x - LEDS_OFFSET))
#define IS_VALID_LED(x)     ((x >= FIRST_LED) && (x <= LAST_LED)? true : false)
#define ERROR_INVALID_LED   "Numero de led invalido"

static uint16_t * puerto;

void LedsCreate(uint16_t * direccion) {
    puerto = direccion;
    *puerto = LEDS_ALL_OFF;
}

void LedsOn(int led) {
    if( IS_VALID_LED(led) ) {
        *puerto |= LED_TO_MASK(led);
    }
    else {
        RegistrarMensaje(0, __FUNCTION__, __LINE__, ERROR_INVALID_LED);
    }
}

void LedsOff(int led) {
    if( IS_VALID_LED(led) ) {
        *puerto &= ~LED_TO_MASK(led);
    }
    else {
        RegistrarMensaje(0, __FUNCTION__, __LINE__, ERROR_INVALID_LED);
    }    
}

void LedsAllOn(void) {
    *puerto = LEDS_ALL_ON;
}

void LedsAllOff(void) {
    *puerto = LEDS_ALL_OFF;
}

bool LedsIsOn(int led) {
    if( IS_VALID_LED(led) ) {
        return((*puerto & LED_TO_MASK(led))>>(led - LEDS_OFFSET));
    }
    else {
        RegistrarMensaje(0, __FUNCTION__, __LINE__, ERROR_INVALID_LED);
        return false;
    }          
}
