/*
 * spot_welder_main.c
 *
 *  Created on: Nov 12, 2019
 *      Author: medprime
 *
 *      menu imlementaion
 *      https://github.com/MaxTechTV/Tutorial_Sketches/blob/master/T14_SimpleMenuTutorial/T14_SimpleMenuTutorial.ino
 */

#include "spot_welder_main.h"


uint8_t Welder_Auto_Flag = 0;

int16_t  Main_Pulse_Duration = 1;
int16_t  Short_Pulse_Duration = 1;
int16_t  Auto_Pulse_Delay = 1000;

int16_t  Batt_Alarm = 11000; // in mv

uint8_t Foot_Switchn_Flag = 0;
uint8_t Welder_Enable_Flag = 1;

uint8_t Batt_Voltage = 0;


Soft_I2C_t Soft_I2C1;

#define SOFT_I2C_SDA_PIN		GPIO_PIN_10
#define SOFT_I2C_SDA_PORT		GPIOA

#define SOFT_I2C_SCL_PIN		GPIO_PIN_9
#define SOFT_I2C_SCL_PORT		GPIOA


void Systic_Callback()
    {
    Encoder_Scan();
    Button_Scan();
    }

void Set_Auto_Pulse_Delay(int16_t delay)
    {
    if (delay <= 500)
	{
	delay = 500;
	}
    if (delay > 10000)
	{
	delay = 10000;
	}
    Auto_Pulse_Delay = delay;
    }

uint16_t Get_Auto_Pulse_Delay()
    {
    return Auto_Pulse_Delay;
    }


void Set_Main_Pulse_Duration(int16_t duration)
    {
    if (duration <= 1)
	{
	duration = 1;
	}
    if (duration > 100)
	{
	duration = 100;
	}
    Main_Pulse_Duration = duration;
    }

uint16_t Get_Main_Pulse_Duration()
    {
    return Main_Pulse_Duration;
    }

void Set_Short_Pulse_Duration(int16_t duration)
    {
    if (duration <= 1)
	{
	duration = 1;
	}
    if (duration > 100)
	{
	duration = 100;
	}
    Short_Pulse_Duration = duration;
    }

uint16_t Get_Short_Pulse_Duration()
    {
    return Short_Pulse_Duration;
    }


void Set_Batt_Alarm(int16_t voltage)
    {
    if (voltage <= 10000)
	{
	voltage = 10000;
	}
    if (voltage > 13000)
	{
	voltage = 13000;
	}
    Batt_Alarm = voltage;
    }

uint16_t Get_Batt_Alarm()
    {
    return Batt_Alarm;
    }

void Disble_Welder()
    {
    Welder_Enable_Flag = 0;
    }

uint8_t Get_Welder_Status()
    {
    return Welder_Enable_Flag;
    }

void Disble_Auto_Welder()
    {
    Welder_Auto_Flag = 0;
    }

void Enable_Auto_Welder()
    {
    Welder_Auto_Flag = 1;
    }

uint8_t Get_Auto_Status()
    {
    return Welder_Auto_Flag;
    }

void Foot_Switch_Callback(uint8_t Clicked_Count)
    {

    if(Clicked_Count == 1)
	{
	Foot_Switchn_Flag = 1;
	}
    }

void Spot_Welder_Main()
    {

    Soft_I2C1.GPIO_SCL_Pin = SOFT_I2C_SCL_PIN;
    Soft_I2C1.GPIO_SCL_Port = SOFT_I2C_SCL_PORT;

    Soft_I2C1.GPIO_SDA_Pin = SOFT_I2C_SDA_PIN;
    Soft_I2C1.GPIO_SDA_Port = SOFT_I2C_SDA_PORT;

    Soft_I2C_Init(&Soft_I2C1);

    ssd1306_Init();

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString("  Arduino", Font_11x18, White);
    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString("Spot Welder", Font_11x18, White);
    ssd1306_SetCursor(0, 40);
    ssd1306_WriteString("    V3", Font_11x18, White);
    ssd1306_UpdateScreen();

    Foot_Switch.Button_Pin = Foot_Switch_Pin;
    Foot_Switch.Button_Pin_Port = Foot_Switch_GPIO_Port;
    Foot_Switch.Button_Pressed_Logic = LOW;
    Foot_Switch.Callback = Foot_Switch_Callback;
    Button_Attach(&Foot_Switch);



    Init_Menu();

    HAL_Delay(2000);

    while (1)
	{

	static uint32_t Scan_Time_Stamp = 0;

	if (HAL_GetTick() - Scan_Time_Stamp > (100 - 1))
	    {

	    Scan_Time_Stamp = HAL_GetTick();

	    Handle_Menu();
	    }

	}

    }
