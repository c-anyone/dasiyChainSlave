/*
 * i2c_eeprom.h
 *
 *  Created on: Jun 22, 2016
 *      Author: Fabio Pungg
 *
 *      I2C handler using the Dave I2C Master App
 *      The App is assumed to be named I2C_MASTER_0
 *
 *		Both transmit and receive Interrupt Routines have to be set to i2c_callback_wrapper which
 *		handles calling the functions provided by the calling functions.
 */

#include <stddef.h>
#include <stdint.h>


typedef void (*i2c_rx_cb_t)(void);
typedef void (*i2c_tx_cb_t)(void);

typedef enum {
	I2C_STATE_IDLE,
	I2C_STATE_TX,
	I2C_STATE_RX,
	I2C_STATE_RX_END,
	I2C_STATE_TX_END
} I2C_STATE_t;

/**
 * Starts a write operation by first transmitting the memory pointer address to the
 * slave device.
 *
 * @param i2c_addr the 7 bit I2C address including write bit
 * @param buf pointer tobuffer containing the data to be written
 * @param len size of buf
 * @param ptr_addr ptr to byte array containing the addrLen bytes long memory address
 * @param addrLen size of the memory pointer
 */
void i2c_write_bytes(uint8_t i2c_addr, uint8_t *buf, size_t len, uint8_t* ptr_addr, size_t addrLen);
void i2c_read_bytes(uint8_t i2c_addr, uint8_t *buf, size_t len, uint8_t* address,size_t addrLen);

/**
 * set the receive callback
 */
void i2c_set_rx_callback(i2c_rx_cb_t);
void i2c_clear_rx_callback(void);

/**
 * set the transmit callback
 */
void i2c_set_tx_callback(i2c_tx_cb_t);
void i2c_clear_tx_callback(void);

/**
 *
 */
