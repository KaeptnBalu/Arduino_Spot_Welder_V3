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

struct Welder_Dtata_t
    {
    int16_t Welder_Auto_Flag;
    int16_t Main_Pulse_Duration;
    int16_t Short_Pulse_Duration;
    int16_t Auto_Pulse_Delay;
    int16_t Batt_Alarm;
    int16_t Weld_Counter;
    }Welder_Data;

struct Welder_Dtata_t* Welder_Data_Handle = &Welder_Data;

static uint8_t Welder_Enable_Flag = 1;


Soft_I2C_t Soft_I2C1;

#define SOFT_I2C_SDA_PIN		GPIO_PIN_10
#define SOFT_I2C_SDA_PORT		GPIOA

#define SOFT_I2C_SCL_PIN		GPIO_PIN_9
#define SOFT_I2C_SCL_PORT		GPIOA

void Update_Data_In_EEPROM()
    {

    static uint32_t Update_Time_Stamp = 0;

    /* update only every 2000ms if data is changed*/
    if (HAL_GetTick() - Update_Time_Stamp > (2000 - 1))
	{
	uint8_t cmp_buffer[sizeof(Welder_Data)];
	uint8_t *data = (uint8_t*) Welder_Data_Handle;

	Update_Time_Stamp = HAL_GetTick();

	AT24CXX_Read_Buffer(0x00, cmp_buffer, sizeof(Welder_Data));

	for (uint8_t i = 0; i < sizeof(Welder_Data); i++)
	    {
	    if (cmp_buffer[i] != data[i])
		{
		AT24CXX_Write_Byte(i, data[i]);
		}
	    }
	HAL_Delay(AT24CXX_WRITE_DELAY);
	}

    }

void Read_Data_From_EEPROM()
    {
    AT24CXX_Read_Buffer(0x00, (uint8_t*)Welder_Data_Handle, sizeof(Welder_Data));
    }

void Set_Auto_Pulse_Delay(int16_t delay)
    {
    if (delay <= 500)
	{
	delay = 500;
	}
    if (delay > 5000)
	{
	delay = 5000;
	}
    Welder_Data_Handle->Auto_Pulse_Delay = delay;
    Update_Data_In_EEPROM();
    }

uint16_t Get_Auto_Pulse_Delay()
    {
    return Welder_Data_Handle->Auto_Pulse_Delay;
    }


void Set_Main_Pulse_Duration(int16_t duration)
    {
    if (duration <= 0)
	{
	duration = 0;
	}
    if (duration > 50)
	{
	duration = 50;
	}
    Welder_Data_Handle->Main_Pulse_Duration = duration;
    Update_Data_In_EEPROM();
    }

uint16_t Get_Main_Pulse_Duration()
    {
    return Welder_Data_Handle->Main_Pulse_Duration;
    }

void Set_Short_Pulse_Duration(int16_t duration)
    {
    if (duration <= 0)
	{
	duration = 0  ;
	}
    if (duration > 20)
	{
	duration = 20;
	}
    Welder_Data_Handle->Short_Pulse_Duration = duration;
    Update_Data_In_EEPROM();
    }

uint16_t Get_Short_Pulse_Duration()
    {
    return Welder_Data_Handle->Short_Pulse_Duration;
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
    Welder_Data_Handle->Batt_Alarm = voltage;
    Update_Data_In_EEPROM();
    }

uint16_t Get_Batt_Alarm()
    {
    return Welder_Data_Handle->Batt_Alarm;
    }

void Disable_Welder()
    {
    Welder_Enable_Flag = 0;
    }

uint8_t Get_Welder_Status()
    {
    return Welder_Enable_Flag;
    }

void Disable_Auto_Weld()
    {
    Welder_Data_Handle->Welder_Auto_Flag = 0;
    Update_Data_In_EEPROM();
    }

void Enable_Auto_Weld()
    {
    Welder_Data_Handle->Welder_Auto_Flag = 1;
    Update_Data_In_EEPROM();
    }

uint8_t Get_Auto_Weld_Status()
    {
    return Welder_Data_Handle->Welder_Auto_Flag;
    }

void Increment_Weld_Count()
    {
    Welder_Data_Handle->Weld_Counter++;
    Update_Data_In_EEPROM();
    }

uint16_t Get_Weld_Count()
    {
    return Welder_Data_Handle->Weld_Counter;
    }

uint8_t Get_Foot_Switch_Status()
    {
    if (!Get_Auto_Weld_Status()) // only active if Auto Weld is disabled.
	{
	return HAL_GPIO_ReadPin(Foot_Switch_GPIO_Port, Foot_Switch_Pin)?0:1;
	}
    return 0;
    }

uint8_t Get_Auto_Puse_In_Status()
    {
    if (Get_Auto_Weld_Status())
	{
	return HAL_GPIO_ReadPin(Auto_Pulse_In_GPIO_Port, Auto_Pulse_In_Pin);
	}
    return 0;
    }

void Reset_Welder_Data()
    {
    Set_Main_Pulse_Duration(3);
    Set_Short_Pulse_Duration(2);
    Set_Batt_Alarm(11000);
    Set_Auto_Pulse_Delay(1000);
    Disable_Auto_Weld();
    Update_Data_In_EEPROM();
    }

void Foot_Switch_Callback(uint8_t Clicked_Count)
    {

    if(Clicked_Count == 1)
	{
	}
    }

void Auto_Pulse_In_Callback(uint8_t Clicked_Count)
    {

    if(Clicked_Count == 1)
	{
	}
    }

void Spot_Welder_Main()
    {

    Soft_I2C1.GPIO_SCL_Pin = SOFT_I2C_SCL_PIN;
    Soft_I2C1.GPIO_SCL_Port = SOFT_I2C_SCL_PORT;

    Soft_I2C1.GPIO_SDA_Pin = SOFT_I2C_SDA_PIN;
    Soft_I2C1.GPIO_SDA_Port = SOFT_I2C_SDA_PORT;

    Soft_I2C_Init(&Soft_I2C1);

    Read_Data_From_EEPROM();

    Menu_Init();

    HAL_Delay(2000);

    while (1)
	{

	Menu_Loop();

	}

    }
