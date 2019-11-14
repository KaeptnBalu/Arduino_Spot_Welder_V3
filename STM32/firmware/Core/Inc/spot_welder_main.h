/*
 * spot_welder_main.h
 *
 *  Created on: Nov 12, 2019
 *      Author: medprime
 */

#ifndef INC_SPOT_WELDER_MAIN_H_
#define INC_SPOT_WELDER_MAIN_H_

#include "ssd1306.h"
#include "rotary_encoder.h"
#include "stm32f0xx_hal.h"
#include "adc.h"
#include "button.h"
#include "main.h"
#include "stdlib.h"
#include "menu_main.h"


Button_Struct_t Foot_Switch;
Button_Struct_t Auto_Pulse;


void Spot_Welder_Main();

void Set_Auto_Pulse_Delay(int16_t delay);
uint16_t Get_Auto_Pulse_Delay();
void Set_Main_Pulse_Duration(int16_t duration);
uint16_t Get_Main_Pulse_Duration();
void Set_Short_Pulse_Duration(int16_t duration);
uint16_t Get_Short_Pulse_Duration();
void Set_Batt_Alarm(int16_t voltage);
uint16_t Get_Batt_Alarm();

void Disble_Welder();
uint8_t Get_Welder_Status();

void Disble_Auto_Welder();
void Enable_Auto_Welder();
uint8_t Get_Auto_Status();


#endif /* INC_SPOT_WELDER_MAIN_H_ */
