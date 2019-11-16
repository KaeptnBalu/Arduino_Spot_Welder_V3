/*
 * button.c
 *
 *  Created on: 17-Apr-2018
 *      Author: medprime
 */

#include "main.h"
#include "button.h"

#define MAX_BUTTONS 5

#define BUTTON_SCAN_TICK 10         // Button_Scan() called every BUTTON_SCAN_TICK

#define BUTTON_DEBOUNCE_DELAY      (50/BUTTON_SCAN_TICK)   //ticks
#define BUTTON_CLICKED_DELAY       (250/BUTTON_SCAN_TICK)  // confirm clicked in foreground after released for CLICKED_DELAY
#define BUTTON_REPRESSED_DELAY     (150/BUTTON_SCAN_TICK)  //ticks
#define BUTTON_LONG_PRESSED_DELAY  (1000/BUTTON_SCAN_TICK) //ticks

static Button_Struct_t *Button_Struct_PTR_Array[MAX_BUTTONS];

static uint8_t Attached_Buttons = 0;

uint8_t Button_Attach(Button_Struct_t *Button_Struct_PTR)
    {
    //init GPIOs as input
    if (Attached_Buttons < MAX_BUTTONS)
	{

	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE()
	;
	__HAL_RCC_GPIOD_CLK_ENABLE()
	;
	__HAL_RCC_GPIOA_CLK_ENABLE()
	;
	__HAL_RCC_GPIOB_CLK_ENABLE()
	;

	GPIO_InitStruct.Pin = Button_Struct_PTR->Button_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	if (Button_Struct_PTR->Button_Pressed_Logic == LOW)
	    {
	    GPIO_InitStruct.Pull = GPIO_PULLUP;
	    }
	else
	    {
	    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	    }
	HAL_GPIO_Init(Button_Struct_PTR->Button_Pin_Port, &GPIO_InitStruct);

	Button_Struct_PTR->Button_Clicked_Count = 0;
	Button_Struct_PTR->Button_Event = Button_Idle;
	Button_Struct_PTR->Button_Pressed_Ticks = 0;
	Button_Struct_PTR->Button_Released_Ticks = 0;

	Button_Struct_PTR_Array[Attached_Buttons] = Button_Struct_PTR;

	Attached_Buttons++;

	return (Attached_Buttons - 1); //return button ID

	}
    else
	{
	//error
	return (255); //return error
	}

    }

/*********************************************************
 *
 * called every tick (BUTTON_SCAN_TICK ?)
 *
 * should be called at least every 20ms?
 *
 *
 */
void Button_Scan()
    {

    static volatile uint32_t Button_Scan_Time_Stamp = 0;
    Button_Struct_t *PTR = NULL;

    if (HAL_GetTick() - Button_Scan_Time_Stamp > (BUTTON_SCAN_TICK - 1)) // excute this loop on every BUTTON_SCAN_TICK
	{
	Button_Scan_Time_Stamp = HAL_GetTick();

	for (uint8_t Index = 0; Index < Attached_Buttons; Index++)

	    {

	    PTR = Button_Struct_PTR_Array[Index];

	    if (HAL_GPIO_ReadPin(PTR->Button_Pin_Port, PTR->Button_Pin)
		    == PTR->Button_Pressed_Logic) //pressed detected

		{
		PTR->Button_Pressed_Ticks++;	//

		if (PTR->Button_Pressed_Ticks < BUTTON_LONG_PRESSED_DELAY)
		    {

		    if (PTR->Button_Released_Ticks //repressed detected
		    < BUTTON_REPRESSED_DELAY)
			{
			PTR->Button_Event = Button_Repressed;
			}
		    else
			{
			PTR->Button_Event = Button_Pressed;
			}

		    PTR->Button_Released_Ticks = 0;

		    }
		else if (PTR->Button_Event != Button_Long_Pressed)
		    {   //long pressed detected
		    PTR->Button_Event = Button_Long_Pressed;
		    PTR->Button_Clicked_Count = 0xFF; //0xFF for long press
		    if (PTR->Callback != NULL)
			{
			PTR->Callback(PTR->Button_Clicked_Count);
			PTR->Button_Clicked_Count = 0;
			}
		    }
		}
	    else   //released detected
		{
		PTR->Button_Released_Ticks++;

		if (PTR->Button_Pressed_Ticks > BUTTON_DEBOUNCE_DELAY) //if button was pressed for BUTTON_DEBOUNCE_DELAY
		    {
		    PTR->Button_Pressed_Ticks = 0;
		    if (PTR->Button_Event == Button_Repressed)
			{
			PTR->Button_Clicked_Count++;
			}
		    else if (PTR->Button_Event == Button_Pressed)
			{
			PTR->Button_Clicked_Count = 1;
			}
		    else if (PTR->Button_Event == Button_Long_Pressed)
			{
			PTR->Button_Event = Button_Idle;
			}
		    }

		if (PTR->Button_Released_Ticks > BUTTON_CLICKED_DELAY)
		    {
		    if (PTR->Callback != NULL
			    && PTR->Button_Event != Button_Idle)
			{
			PTR->Callback(PTR->Button_Clicked_Count);
			PTR->Button_Clicked_Count = 0;
			PTR->Button_Event = Button_Idle;

			}
		    }
		}
	    }
	}
    }

Button_Event_t Button_Get_Status(Button_Struct_t *PTR)
    {

    if (PTR != NULL)
	{
	return PTR->Button_Event;
	}
    else
	{
	//Error
	return 255;
	}
    }

uint8_t Button_Get_Clicked_Count(Button_Struct_t *PTR)
    {

    if (PTR != NULL)
	{
	return PTR->Button_Clicked_Count;
	}
    else
	{
	//Error
	return 0;
	}
    }

void Button_Reset_Count(Button_Struct_t *PTR)
    {

    if (PTR != NULL)
	{
	PTR->Button_Clicked_Count = 0;
	}
    else
	{
	//Error
	}

    }
