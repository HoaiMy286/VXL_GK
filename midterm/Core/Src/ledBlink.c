/*
 * ledBlink.c
 *
 *  Created on: Nov 5, 2022
 *      Author: ASUS
 */

#include "ledBlink.h"

void ledBlink()
{
	if(timer1_flag == 1)
	{
		setTimer1(1000);
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	}
}
