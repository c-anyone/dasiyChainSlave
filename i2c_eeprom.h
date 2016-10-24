/*
 * Addresses:
 * 	Write	Read
 * 	0xA0	0xA1
 * 	0xA2	0xA3
 */

#include <stddef.h>
#include <stdint.h>


typedef void (*i2c_rx_cb_t)(void);
typedef void (*i2c_tx_cb_t)(void);

void i2c_write_bytes(uint8_t i2c_addr, uint8_t *buf, size_t len, uint8_t* ptr_addr, size_t addrLen);
void i2c_read_bytes(uint8_t i2c_addr, uint8_t *buf, size_t len, uint8_t* address,size_t addrLen);

void i2c_set_rx_callback(i2c_rx_cb_t);
void i2c_clear_rx_callback(void);

void i2c_set_tx_callback(i2c_tx_cb_t);
void i2c_clear_tx_callback(void);

typedef enum {
	I2C_STATE_IDLE,
	I2C_STATE_TX,
	I2C_STATE_RX,
	I2C_STATE_RX_END,
	I2C_STATE_TX_END
} I2C_STATE;
