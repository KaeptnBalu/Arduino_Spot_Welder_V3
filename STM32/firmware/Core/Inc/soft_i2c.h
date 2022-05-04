/*
* Soft_I2C.h
*
*  Created on: 10-Jul-2017
*      Author: medprime
*/

#include "stm32f0xx_hal.h"

#ifndef SOFT_I2C_H_
#define SOFT_I2C_H_

#define SOFT_I2C_OK		0
#define SOFT_I2C_ERR		1

typedef struct Soft_I2C_t
    {
	GPIO_TypeDef* GPIO_SCL_Port;
	uint16_t GPIO_SCL_Pin;

	GPIO_TypeDef* GPIO_SDA_Port;
	uint16_t GPIO_SDA_Pin;

    } Soft_I2C_t;


void Soft_I2C_Init(Soft_I2C_t* i2c_handle);

uint8_t Soft_I2C_Write_Byte(Soft_I2C_t* i2c_handle,
	                   uint8_t slave_address,
			   uint8_t register_address,
                           uint8_t *byte);

uint8_t Soft_I2C_Read_Byte(Soft_I2C_t* i2c_handle,
	                   uint8_t slave_address,
			   uint8_t register_address,
                           uint8_t *val);

uint8_t Soft_I2C_Write_Bytes(Soft_I2C_t* i2c_handle,
	                     uint8_t slave_address,
			     uint8_t register_address,
                             uint8_t *buf,
			     uint8_t num);

uint8_t Soft_I2C_Read_Bytes(Soft_I2C_t* i2c_handle,
	                    uint8_t slave_address,
	                    uint8_t register_address,
                            uint8_t *buf,
			    uint8_t num);

uint8_t Soft_I2C_Start(Soft_I2C_t* i2c_handle);

void Soft_I2C_Stop(Soft_I2C_t* i2c_handle);

uint8_t Soft_I2C_Wait_ACK(Soft_I2C_t* i2c_handle);

void Soft_I2C_ACK(Soft_I2C_t* i2c_handle);

void Soft_I2C_NACK(Soft_I2C_t* i2c_handle);

uint8_t Soft_I2C_Send_Byte(Soft_I2C_t* i2c_handle, uint8_t byte);

uint8_t Soft_I2C_Scan(Soft_I2C_t* i2c_handle, uint8_t slave_address);

uint8_t Soft_I2C_Devices(Soft_I2C_t* i2c_handle);

void Soft_I2C_Delay();


uint8_t Soft_I2C_Receive_Byte(Soft_I2C_t* i2c_handle);

#endif /* SOFT_I2C_H_ */
