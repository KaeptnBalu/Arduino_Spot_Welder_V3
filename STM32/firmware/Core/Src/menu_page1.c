/*
 * menu_page1.c
 *
 *  Created on: 14-Nov-2019
 *      Author: medprime
 */

#include "menu_main.h"

void Show_Page1_Screen1()
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

void Show_Page1_Screen2()
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

void Show_Page1_Screen3()
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

void Show_Page1_Screen4()
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

void Show_Page1_Screen5()
    {

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(STR_Batt_Alarm, Font_11x18, White);
    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(STR_Shrt_Pulse, Font_11x18, White);
    ssd1306_SetCursor(0, 40);
    ssd1306_WriteString(STR_Reset, Font_11x18, Black);
    ssd1306_UpdateScreen();

    }

void Show_Page1(uint8_t screen)
    {

    switch (screen)
	{
    case 1:
	Show_Page1_Screen1();
	break;
    case 2:
	Show_Page1_Screen2();
	break;
    case 3:
	Show_Page1_Screen3();
	break;
    case 4:
	Show_Page1_Screen4();
	break;
    case 5:
	Show_Page1_Screen5();
	break;

	}
    }

uint8_t Page1_Screen1_Loop(Menu_Event_t *event)
    {

    uint8_t xreturn = 1;
    char temp[10];

    int16_t bat_voltage;

    if (event->Enter_Button_Clicks == 1)
	{
	xreturn = 0; // exit loop
	}

    Set_Main_Pulse_Duration(event->Encoder_Count + Get_Main_Pulse_Duration());

    HAL_ADC_PollForConversion(&hadc, 10);
    bat_voltage = HAL_ADC_GetValue(&hadc) * 13;

    if (bat_voltage < Get_Batt_Alarm())
	{
	Disable_Welder();
	}

    if (Get_Foot_Switch_Status() || Get_Auto_Puse_In_Status())
	{

	if (Get_Welder_Status())
	    {

	    HAL_Delay(Get_Auto_Pulse_Delay());

	    ssd1306_Fill(Black);
	    ssd1306_SetCursor(0, 0);
	    ssd1306_WriteString("Pulse:", Font_11x18, White);
	    itoa(Get_Main_Pulse_Duration(), temp, 10);
	    ssd1306_WriteString(temp, Font_11x18, White);
	    ssd1306_WriteString("ms", Font_11x18, White);
	    ssd1306_UpdateScreen();

	    /*short pulse*/
	    HAL_GPIO_WritePin(Gate_Driver_GPIO_Port, Gate_Driver_Pin,
		    GPIO_PIN_SET);
	    HAL_Delay(Get_Short_Pulse_Duration());
	    HAL_GPIO_WritePin(Gate_Driver_GPIO_Port, Gate_Driver_Pin,
		    GPIO_PIN_RESET);
	    /*short pulse*/

	    /*main pulse*/
	    HAL_Delay(Get_Main_Pulse_Duration());
	    HAL_GPIO_WritePin(Gate_Driver_GPIO_Port, Gate_Driver_Pin,
		    GPIO_PIN_SET);
	    HAL_Delay(Get_Main_Pulse_Duration());
	    HAL_GPIO_WritePin(Gate_Driver_GPIO_Port, Gate_Driver_Pin,
		    GPIO_PIN_RESET);
	    /*main pulse*/

	    HAL_Delay(100);

	    Increment_Weld_Count();

	    while (Get_Auto_Puse_In_Status())
		{
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("Disconnect", Font_7x10, White);
		ssd1306_SetCursor(0, 15);
		ssd1306_WriteString("Now", Font_7x10, White);
		ssd1306_UpdateScreen();
		}

	    while (Get_Foot_Switch_Status())
		{
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("Release", Font_7x10, White);
		ssd1306_SetCursor(0, 15);
		ssd1306_WriteString("Foot SW", Font_7x10, White);
		ssd1306_UpdateScreen();
		}
	    }
	else
	    {
	    ssd1306_Fill(Black);
	    ssd1306_SetCursor(0, 0);
	    ssd1306_WriteString("Battery Low", Font_7x10, White);
	    ssd1306_SetCursor(0, 15);
	    ssd1306_WriteString("Under Voltage", Font_7x10, White);
	    ssd1306_SetCursor(0, 30);
	    ssd1306_WriteString("Lock Out", Font_7x10, White);
	    ssd1306_SetCursor(0, 45);
	    ssd1306_WriteString("Reboot Welder", Font_7x10, White);
	    ssd1306_UpdateScreen();
	    HAL_Delay(2000);
	    }

	}

    ssd1306_Fill(Black);

    ssd1306_SetCursor(45, 0);
    itoa(Get_Main_Pulse_Duration(), temp, 10);
    ssd1306_WriteString(temp, Font_11x18, White);
    ssd1306_WriteString("ms", Font_11x18, White);

    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString("Battery:", Font_7x10, White);
    ssd1306_SetCursor(75, 20);
    itoa(bat_voltage, temp, 10);
    ssd1306_WriteString(temp, Font_7x10, White);
    ssd1306_WriteString("mV", Font_7x10, White);

    ssd1306_SetCursor(0, 35);
    ssd1306_WriteString("Tot Welds:", Font_7x10, White);
    ssd1306_SetCursor(75, 35);
    itoa(Get_Weld_Count(), temp, 10);
    ssd1306_WriteString(temp, Font_7x10, White);

    ssd1306_SetCursor(0, 50);
    ssd1306_WriteString(STR_Auto, Font_7x10, White);
    ssd1306_WriteString(" ", Font_7x10, White);
    if (Get_Auto_Weld_Status())
	{
	ssd1306_WriteString(STR_ON, Font_7x10, White);
	}
    else
	{
	ssd1306_WriteString(STR_OFF, Font_7x10, White);
	}
    ssd1306_SetCursor(100, 50);
    ssd1306_WriteString(">>", Font_7x10, White);

    ssd1306_UpdateScreen();

    return xreturn;
    }

uint8_t Page1_Screen2_Loop(Menu_Event_t *event)
    {
    Menu_Change_Page(2, 1); // change page to page2 screen1
    return 0; // exit loop
    }

uint8_t Page1_Screen3_Loop(Menu_Event_t *event)
    {

    uint8_t xreturn = 1;
    char temp[10];

    if (event->Enter_Button_Clicks == 1)
	{
	xreturn = 0; // exit loop
	}

    Set_Batt_Alarm(Get_Batt_Alarm() + (event->Encoder_Count * 10));

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(STR_Batt_Alarm, Font_11x18, White);

    ssd1306_SetCursor(0, 20);
    itoa(Get_Batt_Alarm(), temp, 10);
    ssd1306_WriteString(temp, Font_11x18, White);
    ssd1306_WriteString(" mV", Font_11x18, White);
    ssd1306_UpdateScreen();

    return xreturn;
    }

uint8_t Page1_Screen4_Loop(Menu_Event_t *event)
    {

    uint8_t xreturn = 1;
    char temp[10];

    Set_Short_Pulse_Duration(
	    Get_Short_Pulse_Duration() + (event->Encoder_Count));

    if (event->Enter_Button_Clicks == 1)
	{
	xreturn = 0; // exit loop
	}

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(STR_Shrt_Pulse, Font_11x18, White);

    ssd1306_SetCursor(0, 20);
    itoa(Get_Short_Pulse_Duration(), temp, 10);
    ssd1306_WriteString(temp, Font_11x18, White);
    ssd1306_WriteString(" ms ", Font_11x18, White);
    ssd1306_UpdateScreen();

    return xreturn;
    }

uint8_t Page1_Screen5_Loop(Menu_Event_t *event)
    {

    uint8_t xreturn = 1;

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(STR_Reset, Font_11x18, White);
    ssd1306_WriteString("?", Font_11x18, White);

    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString("long press", Font_7x10, White);
    ssd1306_SetCursor(0, 35);
    ssd1306_WriteString("to RESET", Font_7x10, White);

    ssd1306_UpdateScreen();

    if (event->Enter_Button_Clicks == 1)
	{
	xreturn = 0; // exit loop
	}

    if (event->Enter_Button_Clicks == 255) //255 is for long press
	{
	xreturn = 0; // exit loop
	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("RESETTING..", Font_7x10, White);
	ssd1306_UpdateScreen();
	HAL_Delay(2000);
	Reset_Welder_Data();
	}

    return xreturn;
    }

uint8_t Enter_Page1_Screen(uint8_t screen, Menu_Event_t *event)
    {

    uint8_t xreturn = 0;

    switch (screen)
	{
    case 1:
	xreturn = Page1_Screen1_Loop(event);
	break;
    case 2:
	xreturn = Page1_Screen2_Loop(event);
	break;
    case 3:
	xreturn = Page1_Screen3_Loop(event);
	break;
    case 4:
	xreturn = Page1_Screen4_Loop(event);
	break;
    case 5:
	xreturn = Page1_Screen5_Loop(event);
	break;
	}

    return xreturn;
    }
