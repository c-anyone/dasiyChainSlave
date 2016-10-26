/*
 * led_eeprom_handler.c
 *
 *  Created on: Oct 24, 2016
 *      Author: Fabio Pungg
 */

#include "i2c_handler.h"

/**
 * so far not more than EEPROM_PAGESIZE bytes
 * are to be read from EEPROM or temperature sensor
 */
#define RX_BUF_SIZE	EEPROM_PAGESIZE
#define LED_DATA_STRUCTS	(3u)
/**
 * static variable definitions
 * as well as buffers
 */
static float last_temp = 0.0;
static uint8_t read_buf[RX_BUF_SIZE];
static uint8_t addr_ptr[2] = { 0, 0 };
//static ledtype_t led_data[3];
static ledtype_t *led_data = NULL;
static size_t led_size=0;


static int eeprom_read = -1;

/**
 * functions for evaluating data read from eeprom
 */
static inline void pack(uint8_t* buffer, ledtype_t* testboard);
static inline void unpack(uint8_t* DATA_READ);

static void SaveLedData() {
	eeprom_read = 0;
	unpack(read_buf);
}

static void tempConversion() {
	uint16_t temp_buffer = 0;
	temp_buffer = read_buf[1] | read_buf[0] << 8;
	temp_buffer >>= 3;
	last_temp = temp_buffer * 0.0625;
}

void readLedDataFromEeprom(ledtype_t *led_struct,size_t size) {
	led_data = led_struct;
	i2c_set_rx_callback(&SaveLedData);
	i2c_read_bytes(EEPROM_READ, read_buf, RX_BUF_SIZE, addr_ptr, 2);
}

size_t getLedData(ledtype_t *ptr,size_t size) {
	if (eeprom_read == 0) {
		memcpy(ptr,&led_data,sizeof(ledtype_t)*3);
		return LED_DATA_STRUCTS;
	} else {
		return 0;
	}
}

void readTemperature() {
	i2c_set_rx_callback(&tempConversion);
	i2c_read_bytes(TEMP_SENSOR_READ, read_buf, 2, addr_ptr, 1);
}

float getTemperature() {
	return last_temp;
}

/* pack converts LED-Data to uint8_t data*/
static inline void pack(uint8_t* buffer, ledtype_t* testboard) {
	for (int i = 0; i < 3; i++) {
		buffer[0 + i * 5] = (testboard[i].wavelength >> 8) & 0xFF;
		buffer[1 + i * 5] = (testboard[i].wavelength) & 0xFF;
		buffer[2 + i * 5] = (testboard[i].leds);
		buffer[3 + i * 5] = (testboard[i].amps >> 8) & 0xFF;
		buffer[4 + i * 5] = (testboard[i].amps) & 0xFF;
	}
}

/* converts data into right datatype*/
static inline void unpack(uint8_t* DATA_READ) {
	if (led_data == NULL)
		return;
	for (int i = 0, j = 0; i < 3; ++i, j += 5) {
		led_data[i].amps = ((uint16_t) (DATA_READ[0 + j] << 8))
				| ((uint16_t) (DATA_READ[1 + j]));
		led_data[i].leds = DATA_READ[2 + j];
		led_data[i].wavelength = ((uint16_t) (DATA_READ[3 + j] << 8))
				| ((uint16_t) (DATA_READ[4 + j]));
	}
}
