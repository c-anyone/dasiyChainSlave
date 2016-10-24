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


extern uint8_t daisy_address;

static uint8_t blinks = 0;

void blinkNoTimes(uint8_t count);

#define PWM_ALL_OFF {.led1 = 0, .led2 = 0, .led3 = 0}
#define PWM_ALL_ON	{.led1 = 10000, .led2 = 10000, .led3 = 10000}

//static PWM_SETTINGS_t led_settings = {.led1 = 0x00, .led2 = 0x00, .led3 = 0x00};


PWM_SETTINGS_t pwm_current = {.led1 = 0,.led2 = 0,.led3 = 0};

void setPWM(PWM_SETTINGS_t);
static void startPWM();
static void stopPWM();

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

	blinkNoTimes(3);
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

#define SET_PWM_TO_MAX(x)  ((x) < 10000 ? (x) : 10000)

void setPWM(PWM_SETTINGS_t led) {
	pwm_current.led1 = SET_PWM_TO_MAX(led.led1);
	pwm_current.led2 = SET_PWM_TO_MAX(led.led2);
	pwm_current.led3 = SET_PWM_TO_MAX(led.led3);
	PWM_CCU4_SetDutyCycle(&PWM_CCU4_0, pwm_current.led1);
	PWM_CCU4_SetDutyCycle(&PWM_CCU4_1, pwm_current.led2);
	PWM_CCU4_SetDutyCycle(&PWM_CCU4_2, pwm_current.led3);
}

static void startPWM() {
	PWM_SETTINGS_t pwm_on = {.led1 = 10000, .led2 = 10000, .led3 = 10000};
	setPWM(pwm_on);
/*	PWM_CCU4_Start(&PWM_CCU4_0);
	PWM_CCU4_Start(&PWM_CCU4_1);
	PWM_CCU4_Start(&PWM_CCU4_2);*/
}

static void stopPWM() {
	PWM_SETTINGS_t pwm_off = {.led1 = 0x00, .led2 = 0x00, .led3 = 0x00};
	setPWM(pwm_off);
/*	PWM_CCU4_Stop(&PWM_CCU4_0);
	PWM_CCU4_Stop(&PWM_CCU4_1);
	PWM_CCU4_Stop(&PWM_CCU4_2); */
}


void daisyPacketReceived(uint8_t receive_address,uint8_t sender_address, uint8_t *buf, size_t length) {
	uint8_t packet[DAISY_MAX_PACKET_SIZE];
	led_command_t cmd;

	cmd = (led_command_t)buf[0];
	blinkNoTimes(buf[0]+1);
	memcpy(packet,buf,length);
	switch(cmd) {
	case LED_COMMAND_ON:
		startPWM();
		break;
	case LED_COMMAND_OFF:
		stopPWM();
		break;
	case LED_COMMAND_SET:
		if(length-1 < sizeof(PWM_SETTINGS_t)) //not enough data in the struct
			return;
		setPWM(*((PWM_SETTINGS_t*)(packet+1)));	//+1 because buf[0] is the command identifier
		break;
	case LED_COMMAND_GET_TEMP:
		// should return the last read temperature to the sender,
		// but concurrent sending/message queueing is not yet implemented on
		// neither the daisy chain layer nor the uart layer
		break;
	case LED_COMMAND_GET_TYPES:
		// this should return the data read from eeprom defining the leds
		// same as above
		break;
	case LED_COMMAND_GET_PWM_SETTINGS:
		//	this should return the pwm settings
		// same as above
		packet[0] = (uint8_t)LED_COMMAND_GET_PWM_SETTINGS;
		memcpy(packet+1,&pwm_current,sizeof(PWM_SETTINGS_t));
		daisySendData(DAISY_ADDR_MASTER,daisy_address,packet,sizeof(PWM_SETTINGS_t)+1);
		break;
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
