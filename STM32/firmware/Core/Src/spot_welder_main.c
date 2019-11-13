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

const char STR_Back[]         = "Back";
const char STR_Auto_Pulse[]   = "Auto Pulse";
const char STR_ON[]           = "ON";
const char STR_OFF[]          = "OFF";
const char STR_Batt_Alarm[]   = "Batt Alarm";
const char STR_Shrt_Pulse[]   = "Shrt Pulse";
const char STR_Auto[]         = "Auto:";
const char STR_Space[]        = " ";
const char STR_2Space[]       = "  ";
const char STR_3Space[]       = "   ";
const char STR_4Space[]       = "    ";

const char STR_Auto_Pulse_C[] = "Auto Pulse:";
const char STR_Delay[]        = "Delay:";
const char STR_Duration[]     = "Duration:";

const char* STR_Auto_Value = STR_OFF;



void Systic_Callback()
    {
    Encoder_Scan();
    Button_Scan();
    }

Encoder_Struct_t Encoder;
Button_Struct_t Encoder_Button;
Button_Struct_t Foot_Switch;

uint8_t Encoder_Buttorn_Clicks = 0;
uint8_t Spot_Welder_Enabled_Flag = 0;
uint8_t Spot_Welder_Auto_Flag = 0;

int16_t  Spot_Welder_Pulse_Time = 1;
int16_t  Auto_Pulse_Delay = 1000;

float Batt_Alarm = 11.0;

uint8_t Menu = 1;
uint8_t Page = 1;
uint8_t Refresh_Menu_Flag = 0;


void (*Show_Current_Page)(void);
void (*Execute_Current_Menu)(void);


void Page1_Menus();
void Page2_Menus();

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


void Set_Pulse_Duration(int16_t duration)
    {
    if (duration <= 1)
	{
	duration = 1;
	}
    if (duration > 100)
	{
	duration = 100;
	}
    Spot_Welder_Pulse_Time = duration;
    }

uint16_t Get_Pulse_Duration()
    {
    return Spot_Welder_Pulse_Time;
    }


void Set_Batt_Alarm(float voltage)
    {
    if (voltage <= 10.0)
	{
	voltage = 10.0;
	}
    if (voltage > 13.0)
	{
	voltage = 13.0;
	}
    Batt_Alarm = voltage;
    }

uint16_t Get_Batt_Alarm()
    {
    return Batt_Alarm;
    }


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


    }

void Show_Page1_Menu1()
    {
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(STR_Back, Font_11x18, Black);
    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(STR_Auto_Pulse, Font_11x18, White);
    ssd1306_SetCursor(0, 40);
    ssd1306_WriteString(STR_Batt_Alarm, Font_11x18, White);
    ssd1306_UpdateScreen();
    }


void Show_Page1_Menu2()
    {
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(STR_Back, Font_11x18, White);
    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(STR_Auto_Pulse, Font_11x18, Black);
    ssd1306_SetCursor(0, 40);
    ssd1306_WriteString(STR_Batt_Alarm, Font_11x18, White);
    ssd1306_UpdateScreen();
    }

void Show_Page1_Menu3()
    {

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(STR_Back, Font_11x18, White);
    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(STR_Auto_Pulse, Font_11x18, White);
    ssd1306_SetCursor(0, 40);
    ssd1306_WriteString(STR_Batt_Alarm, Font_11x18, Black);
    ssd1306_UpdateScreen();

    }

void Show_Page1_Menu4()
    {

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(STR_Auto_Pulse, Font_11x18, White);
    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(STR_Batt_Alarm, Font_11x18, White);
    ssd1306_SetCursor(0, 40);
    ssd1306_WriteString(STR_Shrt_Pulse, Font_11x18, Black);
    ssd1306_UpdateScreen();

    }

void Show_Page1_Menu5()
    {

    }

void Show_Page2_Comman()
    {

    char temp[10];

    ssd1306_Fill(Black);

    ssd1306_SetCursor(0, 5);
    ssd1306_WriteString(STR_Back, Font_7x10, White);


    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(STR_Auto_Pulse_C, Font_7x10, White);
    ssd1306_SetCursor(80, 20);
    ssd1306_WriteString(STR_Auto_Value, Font_7x10, White);

    ssd1306_SetCursor(0, 35);
    ssd1306_WriteString(STR_Delay, Font_7x10, White);
    ssd1306_SetCursor(80, 35);
    itoa(Get_Auto_Pulse_Delay(), temp, 10);
    ssd1306_WriteString(temp, Font_7x10, White);

    ssd1306_SetCursor(0, 50);
    ssd1306_WriteString(STR_Duration, Font_7x10, White);
    ssd1306_SetCursor(80, 50);
    itoa(Get_Pulse_Duration(), temp, 10);
    ssd1306_WriteString(temp, Font_7x10, White);

    ssd1306_UpdateScreen();
    }


void Show_Page2_Menu1()
    {

    ssd1306_SetCursor(0, 5);
    ssd1306_WriteString(STR_Back, Font_7x10, Black);

    ssd1306_UpdateScreen();
    }


void Show_Page2_Menu2()
    {

    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(STR_Auto_Pulse_C, Font_7x10, Black);
    ssd1306_SetCursor(80, 20);
    ssd1306_WriteString(STR_Auto_Value, Font_7x10, Black);

    ssd1306_UpdateScreen();
    }

void Show_Page2_Menu3()
    {

    char temp[10];
    itoa(Get_Auto_Pulse_Delay(), temp, 10);

    ssd1306_SetCursor(0, 35);
    ssd1306_WriteString(STR_Delay, Font_7x10, Black);
    ssd1306_SetCursor(80, 35);
    ssd1306_WriteString(temp, Font_7x10, Black);

    ssd1306_UpdateScreen();

    }

void Show_Page2_Menu4()
    {

    char temp[10];
    itoa(Get_Pulse_Duration(), temp, 10);

    ssd1306_SetCursor(0, 50);
    ssd1306_WriteString(STR_Duration, Font_7x10, Black);
    ssd1306_SetCursor(80, 50);
    ssd1306_WriteString(temp, Font_7x10, Black);

    ssd1306_UpdateScreen();
    }

void Page1()
    {

    switch (Menu)
	{
    case 0:
	Menu = 1;
	break;
    case 1:
	Show_Page1_Menu1();
	break;
    case 2:
	Show_Page1_Menu2();
	break;
    case 3:
	Show_Page1_Menu3();
	break;
    case 4:
	Show_Page1_Menu4();
	break;
    case 5:
	Show_Page1_Menu5();
	break;
    case 6:
    	Menu = 5;
    	break;
	}
    }

void Page2()
    {

    switch (Menu)
	{
    case 0:
	Menu = 1;
	break;
    case 1:
	Show_Page2_Comman();
	Show_Page2_Menu1();
	break;
    case 2:
	Show_Page2_Comman();
	Show_Page2_Menu2();
	break;
    case 3:
	Show_Page2_Comman();
	Show_Page2_Menu3();
	break;
    case 4:
	Show_Page2_Comman();
	Show_Page2_Menu4();
	break;
    case 5:
	Menu = 4;
	break;
	}
    }

void Execute_Page1_Menu1()
    {

    char temp[10];
    uint8_t in_menu_loop_flag = 1;

    do
	{

	int16_t count = 0;
	count = Encoder_Get_Count(&Encoder);

	Encoder_Set_Count(&Encoder, 0);

	Set_Pulse_Duration(count + Get_Pulse_Duration());

	if (Encoder_Buttorn_Clicks == 1)
	    {
	    Encoder_Buttorn_Clicks = 0;
	    Encoder_Set_Count(&Encoder, 0);
	    in_menu_loop_flag = 0;
	    Refresh_Menu_Flag = 1;
	    }

	itoa(Get_Pulse_Duration(), temp, 10);
	ssd1306_Fill(Black);

	ssd1306_SetCursor(45, 0);
	ssd1306_WriteString(temp, Font_11x18, White);
	ssd1306_WriteString("ms", Font_11x18, White);

	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString("Battery:", Font_7x10, White);
	ssd1306_SetCursor(75, 20);
	ssd1306_WriteString("13.4V  ", Font_7x10, White);

	ssd1306_SetCursor(0, 35);
	ssd1306_WriteString("Tot Welds:", Font_7x10, White);
	ssd1306_SetCursor(75, 35);
	ssd1306_WriteString("125", Font_7x10, White);

	ssd1306_SetCursor(0, 50);
	ssd1306_WriteString(STR_Auto, Font_7x10, White);
	ssd1306_WriteString(STR_Space, Font_7x10, White);
	ssd1306_WriteString(STR_Auto_Value, Font_7x10, White);

	ssd1306_SetCursor(100, 50);
	ssd1306_WriteString(">>", Font_7x10, White);

	ssd1306_UpdateScreen();
	}
    while (in_menu_loop_flag);
    }

void Execute_Page1_Menu2()
    {
    Menu = 1;
    Show_Current_Page = Page2;
    Execute_Current_Menu = Page2_Menus;
    }

void Execute_Page1_Menu3()
    {

    uint8_t in_menu_loop_flag = 1;

    do
	{

	int16_t count = 0;
	count = Encoder_Get_Count(&Encoder);

	Encoder_Set_Count(&Encoder, 0);

	//Set_Batt_Alarm(Get_Batt_Alarm() + (count/10));


	if (Encoder_Buttorn_Clicks == 1)
	    {
	    Encoder_Buttorn_Clicks = 0;
	    Encoder_Set_Count(&Encoder, 0);
	    in_menu_loop_flag = 0;
	    }

	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(STR_Batt_Alarm, Font_11x18, White);
	ssd1306_UpdateScreen();

	}
    while (in_menu_loop_flag);

    }

void Execute_Page1_Menu4()
    {

    }

void Execute_Page1_Menu5()
    {

    }


void Execute_Page2_Menu1()
    {
    Show_Current_Page = Page1;
    Execute_Current_Menu = Page1_Menus;
    }

void Execute_Page2_Menu2()
    {

    if (Spot_Welder_Auto_Flag)
	{
	Spot_Welder_Auto_Flag = 0;
	STR_Auto_Value = STR_OFF;
	}
    else
	{
	Spot_Welder_Auto_Flag = 1;
	STR_Auto_Value = STR_ON;
	}

    }

void Execute_Page2_Menu3()
    {

    uint8_t in_menu_loop_flag = 1;

    do
	{

	int16_t count = 0;
	count = Encoder_Get_Count(&Encoder);

	Encoder_Set_Count(&Encoder, 0);

	Set_Auto_Pulse_Delay(count + Get_Auto_Pulse_Delay());

	if (Encoder_Buttorn_Clicks == 1)
	    {
	    Encoder_Buttorn_Clicks = 0;
	    Encoder_Set_Count(&Encoder, 0);
	    in_menu_loop_flag = 0;
	    }

	Show_Page2_Menu3();

	}
    while (in_menu_loop_flag);

    }

void Execute_Page2_Menu4()
    {

    uint8_t in_menu_loop_flag = 1;

    do
	{

	int16_t count = 0;
	count = Encoder_Get_Count(&Encoder);

	Encoder_Set_Count(&Encoder, 0);

	Set_Pulse_Duration(count + Get_Pulse_Duration());

	if (Encoder_Buttorn_Clicks == 1)
	    {
	    Encoder_Buttorn_Clicks = 0;
	    Encoder_Set_Count(&Encoder, 0);
	    in_menu_loop_flag = 0;
	    }

	Show_Page2_Menu4();

	}
    while (in_menu_loop_flag);

    }


void Page1_Menus()
    {
    switch (Menu)
	{
    case 1:
	Execute_Page1_Menu1();
	break;
    case 2:
	Execute_Page1_Menu2();
	break;
    case 3:
	Execute_Page1_Menu3();
	break;
    case 4:
	Execute_Page1_Menu4();
	break;
    case 5:
    	Execute_Page1_Menu5();
    	break;
	}
    }

void Page2_Menus()
    {
    switch (Menu)
	{
    case 1:
	Execute_Page2_Menu1();
	break;
    case 2:
	Execute_Page2_Menu2();
	break;
    case 3:
	Execute_Page2_Menu3();
	break;
    case 4:
	Execute_Page2_Menu4();
	break;
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

    Encoder.Encoder_Pin_0 = ENCDR_B_Pin;
    Encoder.Encoder_Pin_0_Port = ENCDR_B_GPIO_Port;
    Encoder.Encoder_Pin_1 = ENCDR_A_Pin;
    Encoder.Encoder_Pin_1_Port = ENCDR_A_GPIO_Port;
    Encoder_Attach(&Encoder);

    Encoder_Button.Button_Pin = ENCDR_Switch_Pin;
    Encoder_Button.Button_Pin_Port = ENCDR_Switch_GPIO_Port;
    Encoder_Button.Button_Pressed_Logic = LOW;
    Encoder_Button.Callback = Encoder_Buttorn_Callback;
    Button_Attach(&Encoder_Button);

    Foot_Switch.Button_Pin = Foot_Switch_Pin;
    Foot_Switch.Button_Pin_Port = Foot_Switch_GPIO_Port;
    Foot_Switch.Button_Pressed_Logic = LOW;
    Foot_Switch.Callback = Foot_Switch_Callback;
    Button_Attach(&Foot_Switch);

    HAL_Delay(2000);

    Show_Current_Page = Page1;
    Execute_Current_Menu = Page1_Menus;

    Execute_Current_Menu();

    while (1)
	{

	static uint32_t Scan_Time_Stamp = 0;

	if (HAL_GetTick() - Scan_Time_Stamp > (10 - 1))
	    {

	    Scan_Time_Stamp = HAL_GetTick();

	    int16_t count = 0;
	    count = Encoder_Get_Count(&Encoder);
	    if (count < 0)
		{
		count = 0;
		Menu++;
		Show_Current_Page();
		Encoder_Set_Count(&Encoder, 0);
		}

	    if (count > 0)
		{
		count = 0;
		Menu--;
		Show_Current_Page();
		Encoder_Set_Count(&Encoder, 0);
		}

	    if (Encoder_Buttorn_Clicks == 1)
		{
		Encoder_Buttorn_Clicks = 0;
		Execute_Current_Menu();
		Show_Current_Page();
		Encoder_Set_Count(&Encoder, 0);
		}

	    if (Refresh_Menu_Flag)
		{
		Refresh_Menu_Flag = 0;
		Show_Current_Page();
		Encoder_Set_Count(&Encoder, 0);
		}

	    }

	}

    }
