/*
 * led_eeprom_handler.h
 *
 *  Created on: Oct 24, 2016
 *      Author: Faebsn
 */

#include <stddef.h>
#include <stdint.h>

#ifndef I2C_HANDLER_H_
#define I2C_HANDLER_H_

#define EEPROM_WRITE (0xA0)
#define EEPROM_READ (0xA1)
#define EEPROM_PAGESIZE	(0x10)

#define TEMP_SENSOR_WRITE	(0x9E)
#define TEMP_SENSOR_READ	(0x9F)

typedef struct{
	uint16_t wavelength;
	uint8_t leds;
	uint16_t amps;
}ledtype_t;

void readLedDataEeprom(void);
void readTemperature(void);
float getTemperature();

#endif /* LED_EEPROM_HANDLER_H_ */
