/*
 * led_eeprom_handler.c
 *
 *  Created on: Oct 24, 2016
 *      Author: Faebsn
 */

#include "i2c_handler.h"
#include "i2c_eeprom.h"

#define RX_BUF_SIZE	(16u)

static float last_temp = 0.0;
static uint8_t readBuf[RX_BUF_SIZE];
static uint8_t addr_ptr[2] = { 0, 0 };
static ledtype_t ledData[3];

static inline void pack(uint8_t* buffer, ledtype_t* testboard);
static inline void unpack(uint8_t* DATA_READ);

static void save_led_data() {
	unpack(readBuf);
}

static void temp_conversion() {
	uint16_t temp_buffer = 0;
	temp_buffer = readBuf[1] | readBuf[0] << 8;
	temp_buffer >>= 3;
	last_temp = temp_buffer * 0.0625;
}

void eeprom_handler_init() {

}

void readLedDataEeprom() {
	i2c_set_rx_callback(&save_led_data);
	i2c_read_bytes(EEPROM_READ, readBuf, RX_BUF_SIZE, addr_ptr, 2);
}

void readTemperature() {
	i2c_set_rx_callback(&temp_conversion);
	i2c_read_bytes(TEMP_SENSOR_READ, readBuf, 2, addr_ptr, 1);
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
	for (int i = 0, j = 0; i < 3; ++i, j += 5) {
		ledData[i].amps = ((uint16_t) (DATA_READ[0 + j] << 8))
				| ((uint16_t) (DATA_READ[1 + j]));
		ledData[i].leds = DATA_READ[2 + j];
		ledData[i].wavelength = ((uint16_t) (DATA_READ[3 + j] << 8))
				| ((uint16_t) (DATA_READ[4 + j]));
	}
}
