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
    if(Get_Auto_Status())
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
    ssd1306_WriteString(":", Font_7x10, White);
    ssd1306_SetCursor(80, 20);
    if(Get_Auto_Status())
	{
	ssd1306_WriteString(STR_ON, Font_7x10, White);
	}
    else
	{
	ssd1306_WriteString(STR_OFF, Font_7x10, White);
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

uint8_t Enter_Page2_Screen1(uint8_t button, int16_t count)
{
Menu_Change_Page(1, 2);
return 0; // execution complete
}

uint8_t Enter_Page2_Screen2(uint8_t button, int16_t count)
{

static uint8_t toggle = 0;

if (toggle)
    {
    toggle = 0;
    Disable_Auto_Welder();
    }
else
    {
    toggle = 1;
    Enable_Auto_Welder();
    }
Show_Page2_Comman();
Show_Page2_Screen2();

return 0; // execution complete

}

uint8_t Enter_Page2_Screen3(uint8_t button, int16_t count)
{

uint8_t xreturn = 1;

Set_Auto_Pulse_Delay(count + Get_Auto_Pulse_Delay());

if (button == 1)
    {
    xreturn = 0;
    }

Show_Page2_Screen3();

return xreturn;

}

uint8_t Enter_Page2_Screen4(uint8_t button, int16_t count)
{

uint8_t xreturn = 1;

if (button == 1)
    {
    xreturn = 0;
    }

Set_Main_Pulse_Duration(count + Get_Main_Pulse_Duration());

Show_Page2_Screen4();

return xreturn;
}

uint8_t Enter_Page2_Screen(uint8_t screen, uint8_t button, int16_t count)
{

uint8_t xreturn = 0;

switch (screen)
    {
case 1:
    xreturn = Enter_Page2_Screen1(button, count);
    break;
case 2:
    xreturn = Enter_Page2_Screen2(button, count);
    break;
case 3:
    xreturn = Enter_Page2_Screen3(button, count);
    break;
case 4:
    xreturn = Enter_Page2_Screen4(button, count);
    break;
    }

return xreturn;
}
