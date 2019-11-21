/*
 * menu_main.h
 *
 *  Created on: 14-Nov-2019
 *      Author: medprime
 */

#include "stm32f0xx_hal.h"
#include "ssd1306.h"
#include "main.h"
#include "stdlib.h"
#include "rotary_encoder.h"
#include "button.h"
#include "spot_welder_main.h"

#ifndef INC_MENU_MAIN_H_
#define INC_MENU_MAIN_H_


extern const char STR_Back[]         ;
extern const char STR_Auto_Pulse[]   ;
extern const char STR_ON[]           ;
extern const char STR_OFF[]          ;
extern const char STR_Batt_Alarm[]  ;
extern const char STR_Shrt_Pulse[]   ;
extern const char STR_Auto[]         ;
extern const char STR_Space[]        ;
extern const char STR_2Space[]       ;
extern const char STR_3Space[]       ;
extern const char STR_4Space[]       ;

extern const char STR_Auto_Pulse_C[] ;
extern const char STR_Delay[]        ;
extern const char STR_Duration[]     ;
extern const char STR_Reset[]                ;


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
