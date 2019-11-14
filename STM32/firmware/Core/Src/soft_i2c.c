#include "stm32f0xx_hal.h"
#include "soft_i2c.h"
#include "delay_us.h"


void Soft_I2C_SDA_High(Soft_I2C_t* i2c_handle)
    {
    HAL_GPIO_WritePin(i2c_handle->GPIO_SDA_Port, i2c_handle->GPIO_SDA_Pin,
	    GPIO_PIN_SET);
    }

void Soft_I2C_SDA_Low(Soft_I2C_t* i2c_handle)
    {
    HAL_GPIO_WritePin(i2c_handle->GPIO_SDA_Port, i2c_handle->GPIO_SDA_Pin,
	    GPIO_PIN_RESET);
    }

uint8_t Soft_I2C_SDA_Read(Soft_I2C_t* i2c_handle)
    {
    return HAL_GPIO_ReadPin(i2c_handle->GPIO_SDA_Port, i2c_handle->GPIO_SDA_Pin);
    }

void Soft_I2C_SCL_High(Soft_I2C_t* i2c_handle)
    {
    HAL_GPIO_WritePin(i2c_handle->GPIO_SCL_Port, i2c_handle->GPIO_SCL_Pin,
	    GPIO_PIN_SET);
    }

void Soft_I2C_SCL_Low(Soft_I2C_t* i2c_handle)
    {
    HAL_GPIO_WritePin(i2c_handle->GPIO_SCL_Port, i2c_handle->GPIO_SCL_Pin,
	    GPIO_PIN_RESET);
    }

uint8_t Soft_I2C_SCL_Read(Soft_I2C_t* i2c_handle)
    {
    return HAL_GPIO_ReadPin(i2c_handle->GPIO_SCL_Port, i2c_handle->GPIO_SCL_Pin);
    }

void Soft_I2C_Init(Soft_I2C_t* i2c_handle)
    {

    GPIO_InitTypeDef GPIO_Init;

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE()
    ;
    __HAL_RCC_GPIOD_CLK_ENABLE()
    ;
    __HAL_RCC_GPIOA_CLK_ENABLE()
    ;
    __HAL_RCC_GPIOB_CLK_ENABLE()
    ;
    Soft_I2C_SDA_High(i2c_handle);
    Soft_I2C_SCL_High(i2c_handle);

    GPIO_Init.Mode  = GPIO_MODE_OUTPUT_OD;
    GPIO_Init.Pull  = GPIO_PULLUP;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;

    GPIO_Init.Pin = i2c_handle->GPIO_SDA_Pin;
    HAL_GPIO_Init(i2c_handle->GPIO_SDA_Port, &GPIO_Init);

    GPIO_Init.Pin = i2c_handle->GPIO_SCL_Pin;
    HAL_GPIO_Init(i2c_handle->GPIO_SCL_Port, &GPIO_Init);
    }

void Soft_I2C_Delay()
    {
    //Delay_Micros(1);
    asm("nop");
    }


/*generate start condition */

uint8_t Soft_I2C_Start(Soft_I2C_t* i2c_handle)
    {

    Soft_I2C_SCL_High(i2c_handle);
    Soft_I2C_SDA_Low(i2c_handle);

    Soft_I2C_Delay();

    if (Soft_I2C_SDA_Read(i2c_handle))
	{
	return SOFT_I2C_ERR;
	}

    return SOFT_I2C_OK;
    }

/*generate stop condition */

void Soft_I2C_Stop(Soft_I2C_t* i2c_handle)
    {
    Soft_I2C_SCL_Low(i2c_handle);
    Soft_I2C_SDA_Low(i2c_handle);
    Soft_I2C_SCL_High(i2c_handle);
    Soft_I2C_Delay();
    Soft_I2C_SDA_High(i2c_handle);
    }

uint8_t Soft_I2C_Wait_ACK(Soft_I2C_t* i2c_handle)
    {

    uint16_t timeOut = 5000;

    Soft_I2C_SCL_Low(i2c_handle);
    Soft_I2C_SDA_High(i2c_handle);
    Soft_I2C_SCL_High(i2c_handle);
    Soft_I2C_Delay();

    while (Soft_I2C_SDA_Read(i2c_handle))
	{
	timeOut--;
	if (timeOut == 0)
	    {
	    Soft_I2C_Stop(i2c_handle);
	    return SOFT_I2C_ERR;
	    }
	}

    Soft_I2C_SCL_Low(i2c_handle);

    return SOFT_I2C_OK;

    }

void Soft_I2C_ACK(Soft_I2C_t* i2c_handle)
    {

    Soft_I2C_SCL_Low(i2c_handle);
    Soft_I2C_SDA_Low(i2c_handle);
    Soft_I2C_SCL_High(i2c_handle);
    Soft_I2C_Delay();
    Soft_I2C_SCL_Low(i2c_handle);
    Soft_I2C_Delay();

    }

void Soft_I2C_NACK(Soft_I2C_t* i2c_handle)
    {

    Soft_I2C_SCL_Low(i2c_handle);
    Soft_I2C_SDA_High(i2c_handle);
    Soft_I2C_SCL_High(i2c_handle);
    Soft_I2C_Delay();
    Soft_I2C_SCL_Low(i2c_handle);
    Soft_I2C_Delay();

    }

uint8_t Soft_I2C_Send_Byte(Soft_I2C_t* i2c_handle, uint8_t byte)
    {

    uint8_t count = 8;

    Soft_I2C_SCL_Low(i2c_handle);

    while (count--)
	{
	if (byte & 0x80)
	    {
	    Soft_I2C_SDA_High(i2c_handle);
	    }
	else
	    {
	    Soft_I2C_SDA_Low(i2c_handle);
	    }

	byte <<= 1;

	Soft_I2C_SCL_High(i2c_handle);
	Soft_I2C_Delay();
	Soft_I2C_SCL_Low(i2c_handle);
	Soft_I2C_Delay();
	}
    if (Soft_I2C_Wait_ACK(i2c_handle) == SOFT_I2C_ERR)
	{
	return SOFT_I2C_ERR;
	}
    return SOFT_I2C_OK;
    }

uint8_t Soft_I2C_Receive_Byte(Soft_I2C_t* i2c_handle)
    {

    uint8_t i = 8;
    uint8_t ReceivedByte = 0;

    Soft_I2C_SDA_High(i2c_handle);
    while (i--)
	{
	ReceivedByte <<= 1;
	Soft_I2C_SCL_Low(i2c_handle);
	Soft_I2C_Delay();
	Soft_I2C_SCL_High(i2c_handle);
	Soft_I2C_Delay();
	if (Soft_I2C_SDA_Read(i2c_handle))
	    {
	    ReceivedByte |= 0x01;
	    }
	}
    Soft_I2C_SCL_Low(i2c_handle);
    return ReceivedByte;

    }

uint8_t Soft_I2C_Write_Byte(Soft_I2C_t* i2c_handle,
	                    uint8_t     slave_address,
	                    uint8_t     register_address,
			    uint8_t     *byte)
    {

    if (Soft_I2C_Start(i2c_handle) == SOFT_I2C_ERR)
	{
	Soft_I2C_Stop(i2c_handle);
	return SOFT_I2C_ERR;
	}

    if (Soft_I2C_Send_Byte(i2c_handle, slave_address) == SOFT_I2C_ERR)
	{
	return SOFT_I2C_ERR;
	}
    if (Soft_I2C_Send_Byte(i2c_handle, register_address) == SOFT_I2C_ERR)
	{
	return SOFT_I2C_ERR;
	}

    if (byte)
	{
	if (Soft_I2C_Send_Byte(i2c_handle, *byte) == SOFT_I2C_ERR)
	    {
	    return SOFT_I2C_ERR;
	    }
	}

    Soft_I2C_Stop(i2c_handle);

    return SOFT_I2C_OK;

    }

uint8_t Soft_I2C_Read_Byte(Soft_I2C_t* i2c_handle,
	                   uint8_t     slave_address,
	                   uint8_t     register_address,
			   uint8_t     *val)
    {

    if (Soft_I2C_Start(i2c_handle) == SOFT_I2C_ERR)
	{
	Soft_I2C_Stop(i2c_handle);
	return SOFT_I2C_ERR;
	}

    if (Soft_I2C_Send_Byte(i2c_handle, slave_address) == SOFT_I2C_ERR)
	{
	return SOFT_I2C_ERR;
	}

    if (Soft_I2C_Send_Byte(i2c_handle, register_address) == SOFT_I2C_ERR)
	{
	return SOFT_I2C_ERR;
	}

    if (Soft_I2C_Start(i2c_handle) == SOFT_I2C_ERR) //repeated start
	{
	return SOFT_I2C_ERR;
	}

    if (Soft_I2C_Send_Byte(i2c_handle, slave_address + 1) == SOFT_I2C_ERR) //read bit
	{
	return SOFT_I2C_ERR;
	}

    *val = Soft_I2C_Receive_Byte(i2c_handle);
    Soft_I2C_NACK(i2c_handle);

    Soft_I2C_Stop(i2c_handle);

    return SOFT_I2C_OK;

    }

uint8_t Soft_I2C_Write_Bytes(Soft_I2C_t* i2c_handle,
	                     uint8_t     slave_address,
	                     uint8_t     register_address,
			     uint8_t     *buf,
			     uint8_t     num)
    {

    if (Soft_I2C_Start(i2c_handle) == SOFT_I2C_ERR)
	{
	Soft_I2C_Stop(i2c_handle);
	return SOFT_I2C_ERR;
	}

    if (Soft_I2C_Send_Byte(i2c_handle, slave_address) == SOFT_I2C_ERR)
	{
	return SOFT_I2C_ERR;
	}

    if (Soft_I2C_Send_Byte(i2c_handle, register_address) == SOFT_I2C_ERR)
	{
	return SOFT_I2C_ERR;
	}

    while (num--)
	{
	if (Soft_I2C_Send_Byte(i2c_handle, *buf++) == SOFT_I2C_ERR)
	    {
	    return SOFT_I2C_ERR;
	    }

	}

    Soft_I2C_Stop(i2c_handle);

    return SOFT_I2C_OK;

    }

uint8_t Soft_I2C_Read_Bytes(Soft_I2C_t* i2c_handle,
	                    uint8_t     slave_address,
	                    uint8_t     register_address,
			    uint8_t     *buf,
			    uint8_t     num)
    {

    if (Soft_I2C_Start(i2c_handle) == SOFT_I2C_ERR)
	{
	Soft_I2C_Stop(i2c_handle);
	return SOFT_I2C_ERR;
	}

    if (Soft_I2C_Send_Byte(i2c_handle, slave_address) == SOFT_I2C_ERR)
	{
	return SOFT_I2C_ERR;
	}

    if (Soft_I2C_Send_Byte(i2c_handle, register_address) == SOFT_I2C_ERR)
	{
	return SOFT_I2C_ERR;
	}

    if (Soft_I2C_Start(i2c_handle) == SOFT_I2C_ERR) //repeated start
	{
	Soft_I2C_Stop(i2c_handle);
	return SOFT_I2C_ERR;
	}

    if (Soft_I2C_Send_Byte(i2c_handle, slave_address + 1) == SOFT_I2C_ERR) //read bit
	{
	return SOFT_I2C_ERR;
	}

    while (num--)
	{
	*buf++ = Soft_I2C_Receive_Byte(i2c_handle);

	if (num == 0)
	    {
	    Soft_I2C_NACK(i2c_handle);
	    }
	else
	    {
	    Soft_I2C_ACK(i2c_handle);
	    }
	}

    Soft_I2C_Stop(i2c_handle);

    return SOFT_I2C_OK;

    }

uint8_t Soft_I2C_Scan(Soft_I2C_t* i2c_handle, uint8_t slave_address)
    {

    if (Soft_I2C_Start(i2c_handle) == SOFT_I2C_ERR)
	{
	Soft_I2C_Stop(i2c_handle);
	return SOFT_I2C_ERR;
	}

    if (Soft_I2C_Send_Byte(i2c_handle, slave_address) == SOFT_I2C_ERR)
	{
	return SOFT_I2C_ERR;
	}

    Soft_I2C_Stop(i2c_handle);

    return SOFT_I2C_OK;

    }

uint8_t Soft_I2C_Devices(Soft_I2C_t* i2c_handle)
    {
    uint8_t status = 0;
    uint8_t count = 0;

    for (uint8_t i = 0; i < 128; i++)
	{

	status = Soft_I2C_Scan(i2c_handle, i << 1);

	if (status == SOFT_I2C_OK)
	    {
	    count++;
	    }
	}

    return count;
    }
