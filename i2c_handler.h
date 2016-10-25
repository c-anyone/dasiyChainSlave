/*
 * led_eeprom_handler.h
 *
 *  Created on: Oct 24, 2016
 *      Author: Fabio Pungg
 *
 * Module for reading setup data from EEPROM or temperature data
 * from a MAX6634 digital temperature sensor. Contains no setup code, addresses
 * of the devices are hardcoded via defines
 */

#ifndef I2C_HANDLER_H_
#define I2C_HANDLER_H_

#include <stddef.h>
#include <stdint.h>

#include "i2c_eeprom.h"

/**
 * Addresses of the EEPROM chip
 */
#define EEPROM_WRITE (0xA0)
#define EEPROM_READ (0xA1)
#define EEPROM_PAGESIZE	(0x10)

#define TEMP_SENSOR_WRITE	(0x9E)
#define TEMP_SENSOR_READ	(0x9F)


/**
 * struct to hold the LED information stored on the EEPROM
 */
typedef struct{
	uint16_t wavelength;
	uint8_t leds;
	uint16_t amps;
}ledtype_t;

/**
 * starts a read from the eeprom
 */
void readLedDataFromEeprom(void);

/**
 * starts a temperature read, supposed to be called periodically
 */
void readTemperature(void);

/**
 * @return last the last read Temperature or NaN if readTemperature has
 * never been called
 */
float getTemperature();

#endif /* LED_EEPROM_HANDLER_H_ */
