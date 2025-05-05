/*
 * delay_us.h
 *
 *  Created on: 05-May-2018
 *      Author: medprime
 */

#ifndef DELAY_US_H_
#define DELAY_US_H_

#include "stm32f0xx_hal.h"

uint32_t Get_Micros(void);
void Delay_Micros(uint16_t micros);


#endif /* DELAY_US_H_ */
