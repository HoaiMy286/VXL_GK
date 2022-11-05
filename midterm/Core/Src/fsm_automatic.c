/*
 * fsm_automatic.c
 *
 *  Created on: Nov 5, 2022
 *      Author: ASUS
 */

#include "fsm_automatic.h"

int counter = 0;
int timeout10s = 0;

void checkCounter()
{
	if(counter > 9)
		counter = 0;

	if(counter < 0)
		counter = 9;

	display7SEG(counter);
}

void fsm_simple_buttons_run()
{
	switch (status)
	{
	case INIT:
		timer2_flag = 1;
		timer3_flag = 1;

		status = NORMAL_PRESS;
		display7SEG(0);
		break;
	case NORMAL_PRESS:
		if(timer2_flag == 1)	// no press
		{
			setTimer2(1000);
			timeout10s++;

			if(timeout10s == 11)
			{
				timeout10s = 0;
				status = NO_PRESS;
			}
		}

		if(isButtonNPressed(0) == 1)		// reset counter
		{
			counter = 0;
			display7SEG(0);

			timeout10s = 0;
		}
		if(isButtonNPressed(1) == 1)		// increase counter
		{
			counter++;
			checkCounter();

			timeout10s = 0;
		}
		if(isButtonNPressed(2) == 1)		// decrease counter
		{
			counter--;
			checkCounter();

			timeout10s = 0;
		}
		break;
	case LONG_PRESS:
		break;
	case NO_PRESS:
		if(timer3_flag == 1)
		{
			setTimer3(1000);

			if(counter > 0)
				counter--;
			display7SEG(counter);
		}

		if(isButtonNPressed(1) == 1)	// INC PRESS
		{
			counter++;
			checkCounter();

			status = NORMAL_PRESS;
		}

		if(isButtonNPressed(2) == 1)		// DEC PRESS
		{
			counter--;
			checkCounter();

			status = NORMAL_PRESS;
		}
		break;
	default:
		break;
	}
}

