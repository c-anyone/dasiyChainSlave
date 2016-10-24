/*
 * main.c
 *
 *  Created on: 2016 Jul 12 17:06:11
 *  Author: faebsn
 */




#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "./xmc_daisyChain/DaisyChain.h"
#include "i2c_handler.h"
#include "led_commands.h"

/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */


static uint8_t blinks = 0;

void packetHandler(uint8_t,uint8_t*);
void blinkNoTimes(uint8_t count);

//static PWM_SETTINGS_t led_settings = {.led1 = 0x00, .led2 = 0x00, .led3 = 0x00};
PWM_SETTINGS_t pwm_off = {.led1 = 0x00, .led2 = 0x00, .led3 = 0x00};
PWM_SETTINGS_t pwm_on = {.led1 = 0xFF, .led2 = 0xFF, .led3 = 0xFF};

static inline void setPWM(PWM_SETTINGS_t);
static inline void startPWM();
static inline void stopPWM();

int main(void)
{
	DAVE_STATUS_t status;

	status = DAVE_Init();           /* Initialization of DAVE APPs  */

	if(status == DAVE_STATUS_FAILURE)
	{
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");

		while(1U)
		{

		}
	}
	daisyInit(&UART_DAISY);

	readLedDataEeprom();

	blinkNoTimes(10);
	/* Placeholder for user application code. The while loop below can be replaced with user application code. */
	while(1U)
	{
		daisyWorker();
	}
}
void blinkNoTimes(uint8_t count) {
	blinks = 2*count;
	TIMER_Start(&TIMER_0);
}

#define CAST_TO_UINT32_T(x) (((uint32_t)(x))<<16)

static void setPWM(PWM_SETTINGS_t led) {
	uint32_t tmp = CAST_TO_UINT32_T(led.led1);
	PWM_CCU4_SetDutyCycle(&PWM_CCU4_0, CAST_TO_UINT32_T(led.led1));
	PWM_CCU4_SetDutyCycle(&PWM_CCU4_1, CAST_TO_UINT32_T(led.led2));
	PWM_CCU4_SetDutyCycle(&PWM_CCU4_2, CAST_TO_UINT32_T(led.led3));
}

static void startPWM() {
	setPWM(pwm_on);
/*	PWM_CCU4_Start(&PWM_CCU4_0);
	PWM_CCU4_Start(&PWM_CCU4_1);
	PWM_CCU4_Start(&PWM_CCU4_2);*/
}

static void stopPWM() {
	setPWM(pwm_off);
/*	PWM_CCU4_Stop(&PWM_CCU4_0);
	PWM_CCU4_Stop(&PWM_CCU4_1);
	PWM_CCU4_Stop(&PWM_CCU4_2); */
}


void daisyPacketReceived(uint8_t receive_address,uint8_t sender_address, uint8_t *buf, size_t length) {
	blinkNoTimes(buf[0]+1);
	switch((led_command_t)buf[0]) {
	case LED_COMMAND_ON:
		startPWM();
		break;
	case LED_COMMAND_OFF:
		stopPWM();
		break;
	case LED_COMMAND_SET:
		if(length-1 < sizeof(PWM_SETTINGS_t)) //not enough data in the struct
			return;
		setPWM((*(PWM_SETTINGS_t*)(buf+1)));	//+1 because buf[0] is the command identifier
		break;
	case LED_COMMAND_GET_TEMP:
		// should return the last read temperature to the sender,
		// but as I've got no access to a i2c temp sensor
		// this could not be tested
		break;
	case LED_COMMAND_GET_TYPES:
		// this should return the data read from eeprom defining the leds
		//
		break;
	}
}

void packetHandler(uint8_t length,uint8_t *buf){
	blinkNoTimes(3);
	if(length>0) {
		if (length == sizeof(PWM_SETTINGS_t)) {
			setPWM((*(PWM_SETTINGS_t*)buf));
		}
	}
}

void blinkIRQ() {
	if(blinks > 0) {
		--blinks;
		DIGITAL_IO_ToggleOutput(&LED_0);
	} else {
		TIMER_Stop(&TIMER_0);
	}
}
