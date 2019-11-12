/*
 * spot_welder_main.c
 *
 *  Created on: Nov 12, 2019
 *      Author: medprime
 */


#include "spot_welder_main.h"
#include "ssd1306.h"
#include "rotary_encoder.h"
#include "button.h"
#include "main.h"
#include "stdlib.h"

void Systic_Callback()
    {
    Encoder_Scan();
    Button_Scan();
    }

uint8_t Encoder_Buttorn_Clicks = 0;
uint8_t Spot_Welder_Enabled_Flag = 0;
uint8_t Spot_Welder_Auto_Flag = 0;
uint8_t Spot_Welder_Pulse_Time = 0;

void Encoder_Buttorn_Callback(uint8_t Clicked_Count)
    {
    Encoder_Buttorn_Clicks = Clicked_Count;
    }

void Spot_Welder_Give_Pusle(uint8_t milli_seconds)
    {
    HAL_GPIO_WritePin(Gate_Driver_GPIO_Port, Gate_Driver_Pin, GPIO_PIN_SET);
    HAL_Delay(milli_seconds);
    HAL_GPIO_WritePin(Gate_Driver_GPIO_Port, Gate_Driver_Pin, GPIO_PIN_RESET);
    HAL_Delay(milli_seconds);
    }

void Foot_Switch_Callback(uint8_t Clicked_Count)
    {

    if (Clicked_Count == 1 && Spot_Welder_Enabled_Flag)
	{
	Spot_Welder_Give_Pusle(Spot_Welder_Pulse_Time);
	}

    }

void Spot_Welder_Main()
    {

    ssd1306_Init();

    ssd1306_Init();

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString("  Arduino", Font_11x18, White);
    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString("Spot Welder", Font_11x18, White);
    ssd1306_SetCursor(0, 40);
    ssd1306_WriteString("    V3", Font_11x18, White);
    ssd1306_UpdateScreen();

    Encoder_Struct_t Encoder;
    Encoder.Encoder_Pin_0 = ENCDR_A_Pin;
    Encoder.Encoder_Pin_0_Port = ENCDR_A_GPIO_Port;
    Encoder.Encoder_Pin_1 = ENCDR_B_Pin;
    Encoder.Encoder_Pin_1_Port = ENCDR_B_GPIO_Port;
    Encoder_Attach(&Encoder);


    Button_Struct_t Encoder_Button;
    Encoder_Button.Button_Pin = ENCDR_Switch_Pin;
    Encoder_Button.Button_Pin_Port = ENCDR_Switch_GPIO_Port;
    Encoder_Button.Button_Pressed_Logic = LOW;
    Encoder_Button.Callback = Encoder_Buttorn_Callback;
    Button_Attach(&Encoder_Button);

    Button_Struct_t Foot_Switch;
    Foot_Switch.Button_Pin = Foot_Switch_Pin;
    Foot_Switch.Button_Pin_Port = Foot_Switch_GPIO_Port;
    Foot_Switch.Button_Pressed_Logic = LOW;
    Foot_Switch.Callback = Foot_Switch_Callback;
    Button_Attach(&Foot_Switch);

    HAL_Delay(2000);
    ssd1306_Fill(Black);


    while(1)
	{

	uint8_t in_loop_flag = 0;
	static volatile uint32_t Scan_Time_Stamp = 0;

	if (HAL_GetTick() - Scan_Time_Stamp > (100 - 1))
	    {

	    Scan_Time_Stamp = HAL_GetTick();

	    int16_t count = 0;
	    count = Encoder_Get_Count(&Encoder);
	    if(count < 0)
		{
		count = 0;
		Encoder_Set_Count(&Encoder, 0);
		}

	    if(count > 4)
		{
		count = 4;
		Encoder_Set_Count(&Encoder, 4);
		}


	    switch (count)
		{
	    case 0:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 20);
		ssd1306_WriteString(" AUTO:", Font_11x18, White);
		ssd1306_SetCursor(0, 40);
		ssd1306_WriteString(" PULSE:", Font_11x18, White);

		if (Encoder_Buttorn_Clicks == 1)
		    {
		    Encoder_Buttorn_Clicks = 0;
		    if (Spot_Welder_Enabled_Flag)
			{
			Spot_Welder_Enabled_Flag = 0;
			}
		    else
			{
			Spot_Welder_Enabled_Flag = 1;
			}

		    }

		ssd1306_SetCursor(0, 0);
		if(Spot_Welder_Enabled_Flag)
		    {
		    ssd1306_WriteString(">ENBL:ON", Font_11x18, White);
		    }
		else
		    {
		    ssd1306_WriteString(">ENBL:OFF", Font_11x18, White);
		    }

		ssd1306_UpdateScreen();
		break;

	    case 1:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString(" ENBL:", Font_11x18, White);
		ssd1306_SetCursor(0, 40);
		ssd1306_WriteString(" PULSE:", Font_11x18, White);

		if (Encoder_Buttorn_Clicks == 1)
		    {
		    Encoder_Buttorn_Clicks = 0;
		    if (Spot_Welder_Auto_Flag)
			{
			Spot_Welder_Auto_Flag = 0;
			}
		    else
			{
			Spot_Welder_Auto_Flag = 1;
			}

		    }

		ssd1306_SetCursor(0, 20);
		if(Spot_Welder_Auto_Flag)
		    {
		    ssd1306_WriteString(">AUTO:ON", Font_11x18, White);
		    }
		else
		    {
		    ssd1306_WriteString(">AUTO:OFF", Font_11x18, White);
		    }

		ssd1306_UpdateScreen();
		break;

	    case 2:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString(" ENBL:", Font_11x18, White);
		ssd1306_SetCursor(0, 20);
		ssd1306_WriteString(" AUTO:", Font_11x18, White);

		if (Encoder_Buttorn_Clicks == 1)
		    {
		    Encoder_Buttorn_Clicks = 0;
		    in_loop_flag = 1;
		    }

		do
		    {

		    if (Encoder_Buttorn_Clicks == 1)
			{
			Encoder_Buttorn_Clicks = 0;
			in_loop_flag = 0;
			}

		    int16_t count = 0;
		    char temp[10];
		    count = Encoder_Get_Count(&Encoder);
		    if (count < 0)
			{
			count = 0;
			Encoder_Set_Count(&Encoder, 0);
			}

		    if (count > 100)
			{
			count = 4;
			Encoder_Set_Count(&Encoder, 100);
			}
		    itoa(count,temp, 10);

		    ssd1306_SetCursor(0, 40);
		    ssd1306_WriteString(">PULSE:", Font_11x18, White);
		    ssd1306_WriteString(temp, Font_11x18, White);
		    ssd1306_UpdateScreen();
		    }
		while (in_loop_flag);
		Encoder_Set_Count(&Encoder, 2);

		break;

	    case 3:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString(" Auto:", Font_11x18, White);
		ssd1306_SetCursor(0, 20);
		ssd1306_WriteString(" Pulse:", Font_11x18, White);
		ssd1306_SetCursor(0, 40);
		ssd1306_WriteString(">Dely1:", Font_11x18, White);
		ssd1306_UpdateScreen();
		break;

	    case 4:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString(" Pulse:", Font_11x18, White);
		ssd1306_SetCursor(0, 20);
		ssd1306_WriteString(" Dely1:", Font_11x18, White);
		ssd1306_SetCursor(0, 40);
		ssd1306_WriteString(">Dely2:", Font_11x18, White);
		ssd1306_UpdateScreen();
		break;

	    default:
		break;

		}


	    }

	}

    }
