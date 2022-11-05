/*
 * button.c
 *
 *  Created on: Nov 5, 2022
 *      Author: ASUS
 */

#include "button.h"

int buttonN_flag[3] = { 0, 0, 0 };
int buttonN_PIN[3] = {GPIO_PIN_13 , GPIO_PIN_14 , GPIO_PIN_15 };

int KeyReg0[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg1[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg2[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg3[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};

int TimerForKeyPress[3] = {300, 300, 300};

int isButtonNPressed(int index) {
	if (buttonN_flag[index] == 1) {
		buttonN_flag[index] = 0;
		return 1;
	}
	return 0;
}
void subKeyProcess(int index) {
	buttonN_flag[index] = 1;
}

void getKeyInput() {
	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		KeyReg0[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg2[i];
		KeyReg2[i] = HAL_GPIO_ReadPin(GPIOA, buttonN_PIN[i]);

		if ((KeyReg0[i] == KeyReg1[i]) && (KeyReg1[i] == KeyReg2[i]))
		{
			if (KeyReg3[i] != KeyReg2[i])
			{
				KeyReg3[i] = KeyReg2[i];
				if (KeyReg2[i] == PRESSED_STATE)
				{
					subKeyProcess(i);
					TimerForKeyPress[i] = 300;
				}
			}
			else
			{
				TimerForKeyPress[i]--;
				if (TimerForKeyPress[i] == 0)
				{
					if(KeyReg2[i] == PRESSED_STATE)
						subKeyProcess(i);

					TimerForKeyPress[i] = 100;
				}
			}
		}
	}
}
