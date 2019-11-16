/*
 * rotary_encoder.h
 *
 *  Created on: 11-Apr-2018
 *      Author: medprime
 */

#ifndef ROTARY_ENCODER_H_
#define ROTARY_ENCODER_H_

#include "stm32f0xx_hal.h"

#define HIGH 1
#define LOW  0

typedef enum Enoder_State_t
{
	Enoder_State_00=0,
	Enoder_State_01,
	Enoder_State_10,
	Enoder_State_11
}Enoder_State_t;

typedef struct Encoder_Struct_t
{
	uint16_t Encoder_Pin_0;
	uint16_t Encoder_Pin_1;
	GPIO_TypeDef* Encoder_Pin_0_Port;
	GPIO_TypeDef* Encoder_Pin_1_Port;
	uint8_t Encoder_Pin_0__State;
	uint8_t Encoder_Pin_1__State;
	uint32_t Encoder_Time_Stamp;
	int16_t Encoder_Count;

} Encoder_Struct_t;

int16_t Encoder_Get_Count(Encoder_Struct_t* PTR);
void Encoder_Scan();
void Encoder_Reset_Count(Encoder_Struct_t *PTR);
//void Encoder_Set_Count(Encoder_Struct_t* PTR, int16_t count);

uint8_t Encoder_Attach(Encoder_Struct_t*  Encoder_Struct_PTR);



#endif /* ROTARY_ENCODER_H_ */
