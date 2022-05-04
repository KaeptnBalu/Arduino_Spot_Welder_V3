/*
 * delay_us.c
 *
 *  Created on: 05-May-2018
 *      Author: medprime
 */

#include "delay_us.h"

uint32_t Get_Micros(void)
{
	uint32_t usTicks = HAL_RCC_GetSysClockFreq() / 1000000;
	register uint32_t ms, cycle_cnt;
	do
	{
		ms = HAL_GetTick();
		cycle_cnt = SysTick->VAL;
	} while (ms != HAL_GetTick());
	return (ms * 1000) + (usTicks * 1000 - cycle_cnt) / usTicks;
}
void Delay_Micros(uint16_t micros)
{
	uint32_t start = Get_Micros();
	while (Get_Micros() - start < (uint32_t) micros)
	{
		asm("nop");
	}
}
