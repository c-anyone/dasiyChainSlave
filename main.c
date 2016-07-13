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
static uint8_t blinks = 0;

void packetHandler(uint8_t,uint8_t*);
void blinkNoTimes(uint8_t count);

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
void packetHandler(uint8_t length,uint8_t *buf){
	if(length>0) {
		blinkNoTimes(buf[0]);
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
