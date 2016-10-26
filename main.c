/*
 * main.c
 *
 *  Created on: 2016 Jul 12 17:06:11
 *  Author: Fabio Pungg
 *
 *  Daisy Chain Slave Device
 *
 *
 */

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "xmc_daisyChain/DaisyChain.h"
#include "i2c_handler.h"
#include "led_commands.h"

#define ONEMSEC		(1000u)
#define	ONESEC		(1000*ONEMSEC)

/**

 * @brief main() - Application entry point
 *
 *
 *
 */

extern uint8_t daisy_address;

static uint8_t blinks = 0;

/**
 * function used to indicate reception of frames
 */
void blinkNoTimes(uint8_t count);

#define PWM_ALL_OFF {.led1 = 0, .led2 = 0, .led3 = 0}
#define PWM_ALL_ON	{.led1 = 10000, .led2 = 10000, .led3 = 10000}

static PWM_SETTINGS_t pwm_current = { .led1 = 0, .led2 = 0, .led3 = 0 };
static uint8_t packet[DAISY_MAX_PACKET_SIZE];
ledtype_t led_data_buffer[3];

/**
 * Sets PWM duty cycle to values provided by led
 * @param led pointer to the struct containing the settings for the PWM duty cycle
 */
void setPWM(PWM_SETTINGS_t *led);

/**
 * Sets PWM to MAX, only for evaluation with the onboard LED's
 */
static void startPWM();

/**
 * Sets PWM Duty Cycle to 0 for every setup PWM
 */
static void stopPWM();

int main(void) {
	DAVE_STATUS_t status;
	//uint32_t temp_read_timer;

	status = DAVE_Init(); /* Initialization of DAVE APPs  */

	if (status == DAVE_STATUS_FAILURE) {
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");

		while (1U) {

		}
	}
	daisyInit(&UART_DAISY);
	/*
	 * only tested offline
	 *
	readLedDataFromEeprom(led_data_buffer, 3);
	temp_read_timer = SYSTIMER_CreateTimer(60 * ONESEC, SYSTIMER_MODE_PERIODIC,
			(void*) &readTemperature, NULL);
	SYSTIMER_StartTimer(temp_read_timer);
	*/

	blinkNoTimes(3);
	/* Placeholder for user application code. The while loop below can be replaced with user application code. */
	while (1U) {
		daisyWorker();
	}
}
void blinkNoTimes(uint8_t count) {
	blinks = 2 * count;
	TIMER_Start(&TIMER_0);
}

void setPWM(PWM_SETTINGS_t *led) {
	memcpy(&pwm_current, led, sizeof(PWM_SETTINGS_t));
	PWM_CCU4_SetDutyCycle(&PWM_CCU4_0,
			pwm_current.led1 < 10000 ? pwm_current.led1 : 10000);
	PWM_CCU4_SetDutyCycle(&PWM_CCU4_1,
			pwm_current.led2 < 10000 ? pwm_current.led2 : 10000);
	PWM_CCU4_SetDutyCycle(&PWM_CCU4_2,
			pwm_current.led3 < 10000 ? pwm_current.led3 : 10000);
}

static void startPWM() {
	PWM_SETTINGS_t pwm_on = { .led1 = 10000, .led2 = 10000, .led3 = 10000 };
	setPWM(&pwm_on);

}

static void stopPWM() {
	PWM_SETTINGS_t pwm_off = { .led1 = 0x00, .led2 = 0x00, .led3 = 0x00 };
	setPWM(&pwm_off);
}

/**
 * Implementation of a
 */
void daisyPacketReceived(uint8_t receive_address, uint8_t sender_address,
		uint8_t *buf, size_t length) {

	led_command_t cmd;
//	float temp;
	cmd = (led_command_t) buf[0];
	blinkNoTimes(buf[0] + 1);
	memcpy(packet, buf, length);
	switch (cmd) {
	case LED_COMMAND_ON:
		startPWM();
		break;
	case LED_COMMAND_OFF:
		stopPWM();
		break;
	case LED_COMMAND_SET:
		if (length - 1 != sizeof(PWM_SETTINGS_t)) //not enough data in the struct
			return;
		setPWM((PWM_SETTINGS_t*) ((&packet[1])));//packet[1] because packet[0] is the command identifier
		break;
	case LED_COMMAND_GET_TEMP:
		/**
		 * Tested only without daisy chain, needs more testing in daisy
		 * before beeing usable
		 */
		/*
		 packet[0] = (uint8_t) cmd;
		 float temp = getTemperature();
		 memcpy(packet+1,&temp,sizeof(float));
		 daisySendData(DAISY_ADDR_MASTER,daisyGetAddress(),packet,sizeof(float)+1);
		 */
		break;
	case LED_COMMAND_GET_TYPES:
		/**
		 * Tested only without daisy chain, needs more testing in daisy
		 * before beeing usable
		 */
		/*
		 packet[0] = (uint8_t) cmd;
		 memcpy(packet+1,led_data_buffer,sizeof(ledtype_t)*3);
		 daisySendData(DAISY_ADDR_MASTER,daisyGetAddress(),packet,(sizeof(ledtype_t)*3)+1);
		 */
		break;

	case LED_COMMAND_GET_PWM_SETTINGS:
		/**
		 * 	send the PWM settings back to Master for evaluation
		 * 	sender contains our specified address
		 */
		packet[0] = (uint8_t) LED_COMMAND_GET_PWM_SETTINGS;
		memcpy(packet + 1, &pwm_current, sizeof(PWM_SETTINGS_t));
		daisySendData(DAISY_ADDR_MASTER, daisyGetAddress(), packet,
				sizeof(PWM_SETTINGS_t) + 1);
		break;
	}
}

void blinkIRQ() {
	if (blinks > 0) {
		--blinks;
		DIGITAL_IO_ToggleOutput(&LED_0);
	} else {
		TIMER_Stop(&TIMER_0);
	}
}
