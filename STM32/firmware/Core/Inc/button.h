/*
 * button.h
 *
 *  Created on: 17-Apr-2018
 *      Author: medprime
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "stm32f0xx_hal.h"

#define HIGH 1
#define LOW  0

typedef enum Button_Event_t
{
	Button_Idle=0,
	Button_Pressed,  //still pressed
	Button_Repressed,//at least one clicked and still pressed
	Button_Long_Pressed
}Button_Event_t;



typedef struct Button_Struct_t
{
	uint16_t Button_Pin;  //gpio pin to which button is attached
	GPIO_TypeDef* Button_Pin_Port;  //gpio port to which button is attached
	uint8_t Button_Pressed_Logic; //gpio logic state after gpio is pressed HIGH /  LOW
	Button_Event_t Button_Event;
	uint32_t Button_Pressed_Ticks;
	uint32_t Button_Released_Ticks;
	uint8_t Button_Clicked_Count;
	void (*Callback)(uint8_t Button_Clicked_Count); //callback function ptr

} Button_Struct_t;

void Button_Scan();
uint8_t Button_Get_Clicked_Count(Button_Struct_t* PTR);
Button_Event_t Button_Get_Status(Button_Struct_t* PTR);
void Button_Reset(Button_Struct_t* PTR);
uint8_t Button_Attach(Button_Struct_t*  Button_Struct_t_PTR);





#endif /* BUTTON_H_ */
