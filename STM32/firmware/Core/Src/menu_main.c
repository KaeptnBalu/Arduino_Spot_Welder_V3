/*
 * menu_main.c
 *
 *  Created on: 14-Nov-2019
 *      Author: medprime
 */

#include "menu_main.h"
#include "menu_page1.h"
#include "menu_page2.h"

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

static uint8_t Encoder_Clicks = 1;
static uint8_t Page_Screen = 1;
static uint8_t Elements_In_Page = 1;
static uint8_t Refresh_Screen = 0;

extern uint8_t Foot_Switchn_Flag;

void (*Show_Page)(uint8_t screen);
uint8_t (*Execute_Page_Element)(uint8_t screen , uint8_t button, int16_t count);

void Encoder_Button_Callback(uint8_t Clicked_Count)
    {
    Encoder_Clicks = Clicked_Count;
    }

void Change_Page(uint8_t page_no)
    {

    switch (page_no)
	{
    case 1:
	Show_Page = Show_Page1;
	Execute_Page_Element = Execute_Page1_Element;
	Page_Screen = 1;
	Elements_In_Page = 4;
	Refresh_Screen = 1;
	break;

    case 2:
	Show_Page = Show_Page2;
	Execute_Page_Element = Execute_Page2_Element;
	Page_Screen = 1;
	Elements_In_Page = 4;
	Refresh_Screen = 1;
	break;
	}

    }

void Init_Menu()
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

    Change_Page(1);
    Refresh_Screen = 0;
    }

void Handle_Menu()
    {

    static uint8_t call_again = 0;


    int16_t count = 0;
    count = Encoder_Get_Count(&Encoder);

    if (!call_again)
	{

	Foot_Switchn_Flag = 0;

	if (count < 0)
	    {
	    Encoder_Set_Count(&Encoder, 0);
	    Page_Screen++;
	    if(Page_Screen > Elements_In_Page)
		{
		Page_Screen = Elements_In_Page;
		}
	    Show_Page(Page_Screen);
	    }

	if (count > 0)
	    {
	    Encoder_Set_Count(&Encoder, 0);
	    Page_Screen--;
	    if(Page_Screen == 0)
		{
		Page_Screen = 1;
		}
	    Show_Page(Page_Screen);
	    }

	if (Encoder_Clicks == 1)
	    {
	    Encoder_Clicks = 0;
	    call_again = Execute_Page_Element(Page_Screen, 0, 0);
	    Encoder_Set_Count(&Encoder, 0);
	    }

	if(Refresh_Screen)
	    {
	    Refresh_Screen = 0;
	    Show_Page(Page_Screen);
	    }
	}
    else
	{

	if (Encoder_Clicks || count)
	    {
	    Foot_Switchn_Flag = 0;
	    call_again = Execute_Page_Element(Page_Screen, Encoder_Clicks, count);
	    Encoder_Set_Count(&Encoder, 0);
	    Encoder_Clicks = 0;
	    Refresh_Screen = 1;
	    }
	else
	    {
	    call_again = Execute_Page_Element(Page_Screen, Encoder_Clicks, count);
	    }

	}

    }
