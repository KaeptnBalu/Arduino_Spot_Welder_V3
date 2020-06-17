/*
 * menu_main.c
 *
 *  Created on: 14-Nov-2019
 *      Author: medprime
 */

#include "menu_main.h"
#include "button.h"
#include "rotary_encoder.h"
#include "main.h"

#include "ssd1306.h"
#include "menu_page1.h"
#include "menu_page2.h"

static uint8_t Current_Page_Screen;
static uint8_t Screens_In_Current_Page;
static uint8_t Refresh_Flag;

static Encoder_Struct_t Encoder;
static Button_Struct_t Encoder_Button;

static void (*Show_Page_Screen)(uint8_t screen);
static uint8_t (*Enter_Page_Screen)(uint8_t screen, Menu_Event_t *event);

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

    switch (page_no)
	{
    case 1:
	Show_Page_Screen = &Show_Page1_Screen;
	Enter_Page_Screen = &Enter_Page1_Screen;

	Current_Page_Screen = page_screen;
	Screens_In_Current_Page = 5; // 5 screens in page 1
	break;

    case 2:
	Show_Page_Screen = &Show_Page2_Screen;
	Enter_Page_Screen = &Enter_Page2_Screen;

	Current_Page_Screen = page_screen;
	Screens_In_Current_Page = 4; // 4 screens in page 2
	break;
	}

    if (Current_Page_Screen == 0)
	{
	Current_Page_Screen = 1;
	}

    Refresh_Flag = 1;

    }

void Menu_Init()
    {

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
    Encoder_Button.Callback = Encoder_Button_Callback;
    Button_Attach(&Encoder_Button);

    Menu_Change_Page(1, 1); // by default show page1 screen1.
    Refresh_Flag = 0; // do not refresh for first time
    }

void Menu_Loop()
    {

    static uint8_t in_page_loop = 1; // by default enter page1 screen1 (Home Screen).

    static uint32_t Scan_Time_Stamp = 0;

    Menu_Event_t menu_event;

    if (HAL_GetTick() - Scan_Time_Stamp > (100 - 1))
	{

	Scan_Time_Stamp = HAL_GetTick();

	menu_event.Encoder_Count = Encoder_Get_Count(&Encoder);

	menu_event.Enter_Button_Clicks = Button_Get_Clicked_Count(
		&Encoder_Button);

	if (!in_page_loop)
	    {

	    if (menu_event.Encoder_Count < 0) // or down button
		{
		Current_Page_Screen++;
		if (Current_Page_Screen > Screens_In_Current_Page)
		    {
		    Current_Page_Screen = Screens_In_Current_Page;
		    }
		Show_Page_Screen(Current_Page_Screen);
		}

	    if (menu_event.Encoder_Count > 0) // or up button
		{
		Current_Page_Screen--;
		if (Current_Page_Screen == 0)
		    {
		    Current_Page_Screen = 1;
		    }
		Show_Page_Screen(Current_Page_Screen);
		}

	    if (menu_event.Enter_Button_Clicks == 1) // enter or select button
		{
		menu_event.Enter_Button_Clicks = 0;  // click and count does not belong to page loop so reset theme.
		menu_event.Encoder_Count = 0;
		in_page_loop = Enter_Page_Screen(Current_Page_Screen,
			&menu_event);
		}

	    if (Refresh_Flag == 1)
		{
		Refresh_Flag = 0;
		Show_Page_Screen(Current_Page_Screen);
		}

	    }
	else
	    {

	    in_page_loop = Enter_Page_Screen(Current_Page_Screen, &menu_event);

	    if (!in_page_loop)
		{
		Refresh_Flag = 1;
		}

	    }

	}

    }
