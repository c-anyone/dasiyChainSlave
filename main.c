/*
 * main.c
 *
 *  Created on: 2016 Jul 12 17:06:11
 *  Author: faebsn
 */




#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "DaisyChain.h"

/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */
typedef struct {
	uint16_t identifier;
	uint16_t led1;		// zero equals off
	uint16_t led2;
	uint16_t led3;
} PWM_SETTINGS_t;

static uint8_t blinks = 0;

void packetHandler(uint8_t,uint8_t*);
void blinkNoTimes(uint8_t count);
void setPWM(PWM_SETTINGS_t);

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
	daisySetRxCallback(&packetHandler);

	blinkNoTimes(10);
	/* Placeholder for user application code. The while loop below can be replaced with user application code. */
	while(1U)
	{

	}
}
void blinkNoTimes(uint8_t count) {
	blinks = 2*count;
	TIMER_Start(&TIMER_0);
}

void setPWM(PWM_SETTINGS_t led) {
	PWM_CCU4_SetDutyCycle(&PWM_CCU4_0, led.led1);
	PWM_CCU4_SetDutyCycle(&PWM_CCU4_1, led.led2);
	PWM_CCU4_SetDutyCycle(&PWM_CCU4_2, led.led3);
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
