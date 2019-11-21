/*
 * menu_main.c
 *
 *  Created on: 14-Nov-2019
 *      Author: medprime
 */

#include "menu_main.h"
#include "menu_page1.h"
#include "menu_page2.h"

const char STR_Back[] = "Back";
const char STR_Auto_Pulse[] = "Auto Pulse";
const char STR_ON[] = "ON";
const char STR_OFF[] = "OFF";
const char STR_Batt_Alarm[] = "Batt Alarm";
const char STR_Shrt_Pulse[] = "Shrt Pulse";
const char STR_Auto[] = "Auto:";

const char STR_Delay[] = "Delay:";
const char STR_Duration[] = "Duration:";

const char STR_Reset[] = "Reset";

static uint8_t Current_Page_Screen = 1;
static uint8_t Screens_In_Page = 0;
static uint8_t Refresh_Screen = 0;

Encoder_Struct_t Encoder;
Button_Struct_t Encoder_Button;

void (*Show_Page)(uint8_t screen);
uint8_t (*Enter_Page_Screen)(uint8_t screen, Menu_Event_t* event);

void Systic_Callback()
    {
    Encoder_Scan();
    Button_Scan();
    }

void Encoder_Button_Callback(uint8_t Clicked_Count)
    {

    }

void Menu_Change_Page(uint8_t page_no, uint8_t page_screen)
    {

    Refresh_Screen = 1;

    if (Current_Page_Screen == 0)
	{
	Current_Page_Screen = 1;
	}

    switch (page_no)
	{
    case 1:
	Show_Page = Show_Page1;
	Enter_Page_Screen = Enter_Page1_Screen;
	Current_Page_Screen = page_screen;
	Screens_In_Page = 5; // 5 screens in page 1
	break;

    case 2:
	Show_Page = Show_Page2;
	Enter_Page_Screen = Enter_Page2_Screen;
	Current_Page_Screen = page_screen;
	Screens_In_Page = 4; // 4 screens in page 2
	break;
	}

    }

void Menu_Init()
    {
    Encoder.Encoder_Pin_0 = ENCDR_B_Pin;
    Encoder.Encoder_Pin_0_Port = ENCDR_B_GPIO_Port;
    Encoder.Encoder_Pin_1 = ENCDR_A_Pin;
    Encoder.Encoder_Pin_1_Port = ENCDR_A_GPIO_Port;
    Encoder_Attach(&Encoder);

    Encoder_Button.Button_Pin = ENCDR_Switch_Pin;
    Encoder_Button.Button_Pin_Port = ENCDR_Switch_GPIO_Port;
    Encoder_Button.Button_Pressed_Logic = LOW;
    Encoder_Button.Callback = Encoder_Button_Callback;
    Button_Attach(&Encoder_Button);

    Menu_Change_Page(1,1);
    Refresh_Screen = 0;
    }


void Menu_Loop()
    {

    static uint8_t in_screen = 1;

    static uint32_t Scan_Time_Stamp = 0;

    Menu_Event_t menu_event;

    if (HAL_GetTick() - Scan_Time_Stamp > (100 - 1))
	{

	Scan_Time_Stamp = HAL_GetTick();

	menu_event.Encoder_Count = Encoder_Get_Count(&Encoder);

	menu_event.Enter_Button_Clicks = Button_Get_Clicked_Count(&Encoder_Button);

	if (!in_screen)
	    {

	    if (menu_event.Encoder_Count < 0)// or down button
		{
		Current_Page_Screen++;
		if (Current_Page_Screen > Screens_In_Page)
		    {
		    Current_Page_Screen = Screens_In_Page;
		    }
		Show_Page(Current_Page_Screen);
		}

	    if (menu_event.Encoder_Count > 0)// or up button
		{
		Current_Page_Screen--;
		if (Current_Page_Screen == 0)
		    {
		    Current_Page_Screen = 1;
		    }
		Show_Page(Current_Page_Screen);
		}

	    if (menu_event.Enter_Button_Clicks == 1)
		{
		menu_event.Enter_Button_Clicks = 0;
		menu_event.Encoder_Count = 0;
		in_screen = Enter_Page_Screen(Current_Page_Screen, &menu_event);
		}

	    if (Refresh_Screen)
		{
		Refresh_Screen = 0;
		Show_Page(Current_Page_Screen);
		}

	    }
	else
	    {

	    in_screen = Enter_Page_Screen(Current_Page_Screen, &menu_event);

	    if(!in_screen)
		{
		Refresh_Screen = 1;
		}

	    }

	}

    }
