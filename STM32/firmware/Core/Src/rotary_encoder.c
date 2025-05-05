/*
 * rotary_encoder.c
 *
 *  Created on: 11-Apr-2018
 *      Author: medprime
 */

#include "rotary_encoder.h"
#include "main.h"

// multi encoder code with speed up values adapted for STM32-arduino by Matthias Diro
// no caps for encoder Pins needed: gives back wrong acc values
// using gpio_read_bit instead of digitalRead gives about 4x more speed http://forums.leaflabs.com/topic.php?id=1107
#define MAX_ENCODERS 2

static Encoder_Struct_t *Encoder_Struct_PTR_Array[MAX_ENCODERS];

static uint8_t Attached_Encoders = 0;

uint8_t Encoder_Attach(Encoder_Struct_t *Encoder_Struct_PTR)
    {
    //init GPIOs as input

    GPIO_InitTypeDef GPIO_InitStruct;

    if (Attached_Encoders < MAX_ENCODERS)
	{

	/* GPIO Ports Clock Enable
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	*/


	GPIO_InitStruct.Pin = Encoder_Struct_PTR->Encoder_Pin_0;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(Encoder_Struct_PTR->Encoder_Pin_0_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = Encoder_Struct_PTR->Encoder_Pin_1;
	HAL_GPIO_Init(Encoder_Struct_PTR->Encoder_Pin_1_Port, &GPIO_InitStruct);

	Encoder_Struct_PTR->Encoder_Time_Stamp = 0;
	Encoder_Struct_PTR->Encoder_Count = 0;

	Encoder_Struct_PTR->Encoder_Pin_0_State = HAL_GPIO_ReadPin(
		Encoder_Struct_PTR->Encoder_Pin_0_Port,
		Encoder_Struct_PTR->Encoder_Pin_0);

	Encoder_Struct_PTR->Encoder_Pin_1_State = HAL_GPIO_ReadPin(
		Encoder_Struct_PTR->Encoder_Pin_1_Port,
		Encoder_Struct_PTR->Encoder_Pin_1);

	Encoder_Struct_PTR_Array[Attached_Encoders] = Encoder_Struct_PTR;
	Attached_Encoders++;

	return (Attached_Encoders - 1); //return encoder ID
	}
    else
	{
	//Error
	return (255); //return error
	}

    }

/* call in millis callback or systick callback */
void Encoder_Scan()
    {

    Encoder_Struct_t *PTR = NULL;

    for (uint8_t Index = 0; Index < Attached_Encoders; Index++)
	{

	PTR = Encoder_Struct_PTR_Array[Index];

	if (HAL_GPIO_ReadPin(PTR->Encoder_Pin_0_Port, PTR->Encoder_Pin_0)
		!= PTR->Encoder_Pin_0_State)
	    {
	    PTR->Encoder_Pin_0_State = !PTR->Encoder_Pin_0_State;
	    if (PTR->Encoder_Pin_0_State && !PTR->Encoder_Pin_1_State)
		{
		if (HAL_GetTick() - PTR->Encoder_Time_Stamp > 10)
		    {
		    PTR->Encoder_Count += 1;
		    }
		else if (HAL_GetTick() - PTR->Encoder_Time_Stamp > 5)
		    {
		    PTR->Encoder_Count += 10;
		    }
		else
		    {
		    PTR->Encoder_Count += 50;
		    }

		PTR->Encoder_Time_Stamp = HAL_GetTick();
		}
	    }
	if (HAL_GPIO_ReadPin(PTR->Encoder_Pin_1_Port, PTR->Encoder_Pin_1)
		!= PTR->Encoder_Pin_1_State)
	    {
	    PTR->Encoder_Pin_1_State = !PTR->Encoder_Pin_1_State;
	    if (PTR->Encoder_Pin_1_State && !PTR->Encoder_Pin_0_State)
		{
		if (HAL_GetTick() - PTR->Encoder_Time_Stamp > 10)
		    {
		    PTR->Encoder_Count -= 1;
		    }
		else if (HAL_GetTick() - PTR->Encoder_Time_Stamp > 5)
		    {
		    PTR->Encoder_Count -= 10;
		    }
		else
		    {
		    PTR->Encoder_Count -= 50;
		    }
		PTR->Encoder_Time_Stamp = HAL_GetTick();
		}
	    }
	}

    }

int16_t Encoder_Get_Count(Encoder_Struct_t *PTR)
    {

    int16_t count = 0;

    if (PTR != NULL)
	{

	/*reset encoder count after 500ms of inactivity*/
	if (HAL_GetTick() - PTR->Encoder_Time_Stamp > 500)
	    {
	    PTR->Encoder_Count = 0;
	    }

	count = PTR->Encoder_Count;
	PTR->Encoder_Count = 0;

	}
    else
	{
	//Error
	}

    return count;

    }

/* to reset*/
void Encoder_Reset_Count(Encoder_Struct_t *PTR)
    {

    if (PTR != NULL)
	{
	PTR->Encoder_Count = 0;
	}
    else
	{
	//Error
	}
    }

void Encoder_Set_Count(Encoder_Struct_t *PTR, int16_t count)
    {

    if (PTR != NULL)
	{
	PTR->Encoder_Count = count;
	}
    else
	{
	//Error
	}
    }

