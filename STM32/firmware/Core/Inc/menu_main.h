/*
 * menu_main.h
 *
 *  Created on: 14-Nov-2019
 *      Author: medprime
 */

#include "stm32f0xx_hal.h"


#ifndef INC_MENU_MAIN_H_
#define INC_MENU_MAIN_H_

typedef struct Menu_Event_t
    {
	int16_t Encoder_Count; // encoder value if any
	uint8_t Enter_Button_Clicks; // enter or select button

	uint8_t Up_Button_Clicks;   // if any
	uint8_t Down_Button_Clicks; // if any
	uint8_t Left_Button_Clicks; // if any
	uint8_t Right_Button_Clicks; // if any
    } Menu_Event_t;


void Menu_Init();
void Menu_Loop();
void Menu_Change_Page(uint8_t page_no, uint8_t page_screen);

#endif /* INC_MENU_MAIN_H_ */
