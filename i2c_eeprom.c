/*
 * i2c_eeprom.c
 *
 *  Created on: Jun 22, 2016
 *      Author: Fabio Pungg
 */

#include <DAVE.h>
#include "i2c_eeprom.h"

static i2c_rx_cb_t rx_cb_fun;
static i2c_tx_cb_t tx_cb_fun;
static I2C_STATE_t state;
static uint8_t* txBuf;
static uint8_t* rxBuf;
static size_t txlen;
static size_t rxlen;

static uint8_t device_addr = 0;


void i2c_write_bytes(uint8_t i2c_addr, uint8_t *buf, size_t len, uint8_t* ptr_addr, size_t addrLen) {
	// set up for followup transmit (address is transmitted first)

	/*
	 * if (len > EEPROM_PAGESIZE) {
	 * 	setup bulk write code if implemented. needs to use
	 * 	a timer to allow the EEPROM to store the page in between
	 * 	writes
	 * }
	 *
	 */
	state = I2C_STATE_TX;
	txBuf = buf;
	txlen = len;
	device_addr = i2c_addr;

	// Transmit the internal memory address
	I2C_MASTER_Transmit(&I2C_MASTER_0, true, device_addr, ptr_addr, addrLen,
	false);
}

void i2c_read_bytes(uint8_t i2c_addr, uint8_t *rBuf, size_t len, uint8_t* ptr_addr, size_t addrLen) {
	state = I2C_STATE_RX;
	rxBuf = rBuf;
	rxlen = len;

	device_addr = i2c_addr;
	// Transmit the internal memory ptr_addr
	I2C_MASTER_Transmit(&I2C_MASTER_0, true, device_addr-1, ptr_addr, addrLen,
	false);
}

void i2c_set_rx_callback(i2c_rx_cb_t cb_fun_ptr) {
	rx_cb_fun = cb_fun_ptr;
}

void i2c_clear_rx_callback(void) {
	rx_cb_fun = NULL;
}

void i2c_set_tx_callback(i2c_tx_cb_t cb_fun_ptr) {
	tx_cb_fun = cb_fun_ptr;
}

void i2c_clear_tx_callback(void) {
	tx_cb_fun = NULL;
}

void i2c_callback_wrapper(void) {
	if (state == I2C_STATE_TX) {
		state = I2C_STATE_TX_END;
		I2C_MASTER_Transmit(&I2C_MASTER_0, false, device_addr, txBuf, txlen,
		true);
	} else if (state == I2C_STATE_RX) {
		state = I2C_STATE_RX_END;
		I2C_MASTER_Receive(&I2C_MASTER_0, true, device_addr, rxBuf, rxlen, true,
		false);
	} else if (state == I2C_STATE_RX_END) {
		state = I2C_STATE_IDLE;
		if (rx_cb_fun != NULL) {
			(*rx_cb_fun)();
		}
	} else if (state == I2C_STATE_TX_END) {
		state = I2C_STATE_IDLE;
		if (tx_cb_fun != NULL) {
			(*tx_cb_fun)();
		}
	}
}

