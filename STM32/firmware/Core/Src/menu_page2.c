/*
 * menu_page2.c
 *
 *  Created on: 14-Nov-2019
 *      Author: medprime
 */

#include "menu_main.h"

void Show_Page2_Comman()
    {

    char temp[10];

    ssd1306_Fill(Black);

    ssd1306_SetCursor(0, 5);
    ssd1306_WriteString(STR_Back, Font_7x10, White);

    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(STR_Auto_Pulse, Font_7x10, White);
    ssd1306_WriteString(":", Font_7x10, White);
    ssd1306_SetCursor(80, 20);
    if (Get_Auto_Weld_Status())
	{
	ssd1306_WriteString(STR_ON, Font_7x10, White);
	}
    else
	{
	ssd1306_WriteString(STR_OFF, Font_7x10, White);
	}

    ssd1306_SetCursor(0, 35);
    ssd1306_WriteString(STR_Delay, Font_7x10, White);
    ssd1306_SetCursor(80, 35);
    itoa(Get_Auto_Pulse_Delay(), temp, 10);
    ssd1306_WriteString(temp, Font_7x10, White);

    ssd1306_SetCursor(0, 50);
    ssd1306_WriteString(STR_Duration, Font_7x10, White);
    ssd1306_SetCursor(80, 50);
    itoa(Get_Main_Pulse_Duration(), temp, 10);
    ssd1306_WriteString(temp, Font_7x10, White);

    ssd1306_UpdateScreen();
    }

void Show_Page2_Screen1()
    {

    ssd1306_SetCursor(0, 5);
    ssd1306_WriteString(STR_Back, Font_7x10, Black);

    ssd1306_UpdateScreen();
    }

void Show_Page2_Screen2()
    {

    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(STR_Auto_Pulse, Font_7x10, Black);
    ssd1306_WriteString(":", Font_7x10, Black);
    ssd1306_SetCursor(80, 20);
    if (Get_Auto_Weld_Status())
	{
	ssd1306_WriteString(STR_ON, Font_7x10, Black);
	}
    else
	{
	ssd1306_WriteString(STR_OFF, Font_7x10, Black);
	}
    ssd1306_UpdateScreen();
    }

void Show_Page2_Screen3()
    {

    char temp[10];
    itoa(Get_Auto_Pulse_Delay(), temp, 10);

    ssd1306_SetCursor(0, 35);
    ssd1306_WriteString(STR_Delay, Font_7x10, Black);
    ssd1306_SetCursor(80, 35);
    ssd1306_WriteString(temp, Font_7x10, Black);

    ssd1306_UpdateScreen();

    }

void Show_Page2_Screen4()
    {

    char temp[10];
    itoa(Get_Main_Pulse_Duration(), temp, 10);

    ssd1306_SetCursor(0, 50);
    ssd1306_WriteString(STR_Duration, Font_7x10, Black);
    ssd1306_SetCursor(80, 50);
    ssd1306_WriteString(temp, Font_7x10, Black);

    ssd1306_UpdateScreen();
    }

void Show_Page2(uint8_t screen)
    {

    switch (screen)
	{
    break;
case 1:
    Show_Page2_Comman();
    Show_Page2_Screen1();
    break;
case 2:
    Show_Page2_Comman();
    Show_Page2_Screen2();
    break;
case 3:
    Show_Page2_Comman();
    Show_Page2_Screen3();
    break;
case 4:
    Show_Page2_Comman();
    Show_Page2_Screen4();
    break;
    }
}

uint8_t Page2_Screen1_Loop(Menu_Event_t *event)
{
Menu_Change_Page(1, 2); // change page to page1 screen2
return 0; // exit loop
}

uint8_t Page2_Screen2_Loop(Menu_Event_t *event)
{

if (Get_Auto_Weld_Status())
    {
    Disable_Auto_Weld();
    }
else
    {
    Enable_Auto_Weld();
    }

Show_Page2_Comman();
Show_Page2_Screen2();

return 0; // exit loop

}

uint8_t Page2_Screen3_Loop(Menu_Event_t *event)
{

uint8_t xreturn = 1;

Set_Auto_Pulse_Delay(event->Encoder_Count + Get_Auto_Pulse_Delay());

if (event->Enter_Button_Clicks == 1)
    {
    xreturn = 0;  // exit loop
    }

Show_Page2_Screen3();

return xreturn;

}

uint8_t Page2_Screen4_Loop(Menu_Event_t *event)
{

uint8_t xreturn = 1;

if (event->Enter_Button_Clicks == 1)
    {
    xreturn = 0;  // exit loop
    }

Set_Main_Pulse_Duration(event->Encoder_Count + Get_Main_Pulse_Duration());

Show_Page2_Screen4();

return xreturn;
}

uint8_t Enter_Page2_Screen(uint8_t screen, Menu_Event_t *event)
{

uint8_t xreturn = 0;

switch (screen)
    {
case 1:
    xreturn = Page2_Screen1_Loop(event);
    break;
case 2:
    xreturn = Page2_Screen2_Loop(event);
    break;
case 3:
    xreturn = Page2_Screen3_Loop(event);
    break;
case 4:
    xreturn = Page2_Screen4_Loop(event);
    break;
    }

return xreturn;
}
