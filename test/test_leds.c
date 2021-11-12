/*
 * Despues de la configuracion todos los leds deben quedar apagados
 * Prender un led cualquiera
 * Apagar un led cualquiera
 * Prender y apagar algunos leds
 * Prender todos los leds juntos
 * Apagar todos los leds juntos
 * Consultar el estado de un led encendido
 * Revisar los valores limites de los parametros
 * Probar valores invalidos para los parametros 
*/
#include "unity.h"
#include "leds.h"
#include "mock_errores.h"

#define LED             3
#define LED_BIT(x)     (1 << (x-1))
#define PRIMER_LED      1
#define ULTIMO_LED      16

static uint16_t puertoVirtual;

void setUp(void) {
    LedsCreate(&puertoVirtual);
}

/* Despues de la configuracion todos los leds deben quedar apagados */
void test_todos_los_leds_inician_apagados(void) {
    uint16_t puertoVirtual = 0xFFFF;
    LedsCreate(&puertoVirtual);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puertoVirtual);
}

/* Prender un led cualquiera */
void test_prender_led(void) {
    LedsOn(LED);
    TEST_ASSERT_EQUAL_HEX16(LED_BIT(LED), puertoVirtual);
}

/* Apagar un led cualquiera */
void test_apagar_led(void) {
    LedsOn(LED);
    LedsOff(LED);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puertoVirtual);    
}

/* Prender y apagar algunos leds */
void test_prender_y_apagar_varios_leds(void) {
    LedsOn(LED);
    LedsOn(LED+3);
    LedsOff(LED);
    TEST_ASSERT_EQUAL_HEX16(LED_BIT(LED+3), puertoVirtual); 
}

/* Prender todos los leds juntos */
void test_prender_todos_los_leds(void) {
    LedsAllOn();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, puertoVirtual); 
}

 /* Apagar todos los leds juntos */
 void test_apagar_todos_los_leds_juntos(void) {
    LedsAllOn(); 
    LedsAllOff();
    TEST_ASSERT_EQUAL_HEX16(0x0000, puertoVirtual); 
 }

 /* Consultar el estado de un led encendido */
 void test_consulta_estado_led_encendido(void) {
     LedsOn(LED);
     bool estadoLed = LedsIsOn(LED);
     TEST_ASSERT_EQUAL(true, estadoLed);
     LedsOff(LED);
     estadoLed = LedsIsOn(LED);
     TEST_ASSERT_EQUAL(false, estadoLed);     
 }
 
 /* Revisar los valores limites de los parametros */
void test_error_en_parametro_encender_led(void) {
    RegistrarMensaje_Expect(0, "LedsOn", 0, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedsOn(PRIMER_LED-1);
    RegistrarMensaje_Expect(0, "LedsOn", 0, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedsOn(ULTIMO_LED+1);    
}

void test_error_en_parametro_apagar_led(void) {
    RegistrarMensaje_Expect(0, "LedsOff", 0, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedsOff(PRIMER_LED-1);    
    RegistrarMensaje_Expect(0, "LedsOff", 0, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedsOff(ULTIMO_LED+1);
}

void test_error_en_parametro_consultar_led_encendido(void) {
    RegistrarMensaje_Expect(0, "LedsIsOn", 0, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedsIsOn(PRIMER_LED-1);
    RegistrarMensaje_Expect(0, "LedsIsOn", 0, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedsIsOn(ULTIMO_LED+1);    
}

 /* Probar valores invalidos para los parametros */
 void test_error_parametro_invalido_encender_led(void) {
    RegistrarMensaje_Expect(0, "LedsOn", 0, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedsOn(-1);
    RegistrarMensaje_Expect(0, "LedsOn", 0, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedsOn(150);    
}

void test_error_parametro_invalido_apagar_led(void) {
    RegistrarMensaje_Expect(0, "LedsOff", 0, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedsOff(0xff1a);    
    RegistrarMensaje_Expect(0, "LedsOff", 0, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedsOff('a');
}

 void test_error_parametro_invalido_consultar_led_encendido(void) {
    RegistrarMensaje_Expect(0, "LedsIsOn", 0, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedsIsOn(-1);
    RegistrarMensaje_Expect(0, "LedsIsOn", 0, "Numero de led invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedsIsOn(150);    
}