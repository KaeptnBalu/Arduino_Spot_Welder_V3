#include "at24cxx.h"
#include "soft_i2c.h"


extern Soft_I2C_t Soft_I2C1;

#define AT24C_I2C_Handle Soft_I2C1

void AT24CXX_Init()
    {
    //Soft_I2C_Init(Soft_I2C1);
    }

uint8_t AT24CXX_Write_Byte(uint16_t register_address, uint8_t data)
    {
    if (Soft_I2C_Start(&AT24C_I2C_Handle) == SOFT_I2C_ERR)/*generate star condition*/
	{
	Soft_I2C_Stop(&AT24C_I2C_Handle);
	return AT24CXX_ERR;
	}

    if (Soft_I2C_Send_Byte(&AT24C_I2C_Handle, AT24CXX_EEPROM_ADDR + 0) == SOFT_I2C_ERR)/*Send device address + write bit */
	{
	return AT24CXX_ERR;
	}

    if (AT24CXX_ADDRESS_WIDTH > 8)/* Only if address is 16 bit */
	{
	if (Soft_I2C_Send_Byte(&AT24C_I2C_Handle, (register_address >> 8)) == SOFT_I2C_ERR)
	    {
	    return AT24CXX_ERR;
	    }
	}

    if (Soft_I2C_Send_Byte(&AT24C_I2C_Handle, register_address) == SOFT_I2C_ERR)/*send register address to write*/
	{
	return AT24CXX_ERR;
	}

    if (Soft_I2C_Send_Byte(&AT24C_I2C_Handle, data) == SOFT_I2C_ERR)
	{
	return AT24CXX_ERR;
	}

    Soft_I2C_Stop(&AT24C_I2C_Handle);

    HAL_Delay(AT24CXX_WRITE_DELAY);/*Memory Programming Time approx 5ms*//*3ms for BL24CXX */

    return AT24CXX_OK;
    }

uint8_t AT24CXX_Read_Byte(uint16_t register_address, uint8_t* data)
    {

    if (Soft_I2C_Start(&AT24C_I2C_Handle) == SOFT_I2C_ERR)/*generate star condition*/
	{
	Soft_I2C_Stop(&AT24C_I2C_Handle);
	return AT24CXX_ERR;
	}

    if (Soft_I2C_Send_Byte(&AT24C_I2C_Handle, (AT24CXX_EEPROM_ADDR + 0)) == SOFT_I2C_ERR)/*Send device address + write bit */
	{
	return AT24CXX_ERR;
	}

    if (AT24CXX_ADDRESS_WIDTH > 8)/* Only if address is 16 bit */
	{
	if (Soft_I2C_Send_Byte(&AT24C_I2C_Handle, (register_address >> 8)) == SOFT_I2C_ERR)
	    {
	    return AT24CXX_ERR;
	    }
	}
    if (Soft_I2C_Send_Byte(&AT24C_I2C_Handle, register_address) == SOFT_I2C_ERR)/*send register address to write*/
	{
	return AT24CXX_ERR;
	}

    if (Soft_I2C_Start(&AT24C_I2C_Handle) == SOFT_I2C_ERR) //repeated start
	{
	Soft_I2C_Stop(&AT24C_I2C_Handle);
	return AT24CXX_ERR;
	}

    if (Soft_I2C_Send_Byte(&AT24C_I2C_Handle, (AT24CXX_EEPROM_ADDR + 1)) == SOFT_I2C_ERR)/*Send device address + read bit */
	{
	return AT24CXX_ERR;
	}

    *data = Soft_I2C_Receive_Byte(&AT24C_I2C_Handle);

    Soft_I2C_NACK(&AT24C_I2C_Handle);

    Soft_I2C_Stop(&AT24C_I2C_Handle);

    return AT24CXX_OK;
    }

uint8_t AT24CXX_Write_Page(uint16_t start_address, const uint8_t *buf, uint16_t len)
    {

    if (len == 0)
	{
	return AT24CXX_OK;
	}

    if (Soft_I2C_Start(&AT24C_I2C_Handle) == SOFT_I2C_ERR)/*generate star condition*/
	{
	Soft_I2C_Stop(&AT24C_I2C_Handle);
	return AT24CXX_ERR;
	}

    if (Soft_I2C_Send_Byte(&AT24C_I2C_Handle, (AT24CXX_EEPROM_ADDR + 0)) == SOFT_I2C_ERR)/*Send device address + write bit */
	{
	return AT24CXX_ERR;
	}

    if (AT24CXX_ADDRESS_WIDTH > 8)/* Only if address is 16 bit */
	{
	if (Soft_I2C_Send_Byte(&AT24C_I2C_Handle, (start_address >> 8)) == SOFT_I2C_ERR)
	    {
	    return AT24CXX_ERR;
	    }
	}
    if (Soft_I2C_Send_Byte(&AT24C_I2C_Handle, start_address) == SOFT_I2C_ERR)/*send register address to write*/
	{
	return AT24CXX_ERR;
	}

    while (len--)
	{
	if (Soft_I2C_Send_Byte(&AT24C_I2C_Handle, *buf++) == SOFT_I2C_ERR)/*write data to address*/
	    {
	    return AT24CXX_ERR;
	    }
	}

    Soft_I2C_Stop(&AT24C_I2C_Handle);

    HAL_Delay(AT24CXX_WRITE_DELAY);/*Memory Programming Time approx 5ms*//*3ms for BL24CXX */

    return AT24CXX_OK;
    }

uint8_t AT24CXX_Read_Buffer(uint16_t start_address, uint8_t *buf, uint16_t len)
    {

    if (Soft_I2C_Start(&AT24C_I2C_Handle) == SOFT_I2C_ERR)/*generate star condition*/
	{
	Soft_I2C_Stop(&AT24C_I2C_Handle);
	return AT24CXX_ERR;
	}

    if (Soft_I2C_Send_Byte(&AT24C_I2C_Handle, (AT24CXX_EEPROM_ADDR + 0)) == SOFT_I2C_ERR)/*Send device address + write bit */
	{
	return AT24CXX_ERR;
	}

    if (AT24CXX_ADDRESS_WIDTH > 8)/* Only if address is 16 bit */
	{
	if (Soft_I2C_Send_Byte(&AT24C_I2C_Handle, (start_address >> 8)) == SOFT_I2C_ERR)
	    {
	    return AT24CXX_ERR;
	    }
	}

    if (Soft_I2C_Send_Byte(&AT24C_I2C_Handle, start_address) == SOFT_I2C_ERR)/*send register address to write*/
	{
	return AT24CXX_ERR;
	}

    if (Soft_I2C_Start(&AT24C_I2C_Handle) == SOFT_I2C_ERR) //repeated start
	{
	Soft_I2C_Stop(&AT24C_I2C_Handle);
	return AT24CXX_ERR;
	}

    if (Soft_I2C_Send_Byte(&AT24C_I2C_Handle, (AT24CXX_EEPROM_ADDR + 1)) == SOFT_I2C_ERR) //read bit
	{
	return AT24CXX_ERR;
	}

    while (len--)
	{
	*buf++ = Soft_I2C_Receive_Byte(&AT24C_I2C_Handle);

	if (len == 0)
	    {
	    Soft_I2C_NACK(&AT24C_I2C_Handle);
	    }
	else
	    {
	    Soft_I2C_ACK(&AT24C_I2C_Handle);
	    }
	}

    Soft_I2C_Stop(&AT24C_I2C_Handle);

    return AT24CXX_OK;

    }

/*this function can write any number of bytes from arbitrary location*/
uint8_t AT24CXX_Write_Buffer(uint16_t start_address, const uint8_t *buf, uint16_t len)
    {

    uint16_t index;
    uint16_t page_counter;
    uint16_t byte_counter;

    uint16_t eeprom_address;
    const    uint8_t* buffer_address;

    byte_counter =
	    (AT24CXX_PAGE_LENGTH - (start_address % AT24CXX_PAGE_LENGTH));

    if (len < byte_counter)
	{
	byte_counter = len;
	}

    page_counter = ((len - byte_counter) / AT24CXX_PAGE_LENGTH);

    eeprom_address = start_address;
    buffer_address = buf;
    if (AT24CXX_Write_Page(eeprom_address, buffer_address, byte_counter) == AT24CXX_ERR)
	{
	return AT24CXX_ERR;
	}

    eeprom_address += byte_counter;
    buffer_address += byte_counter;
    for (index = 0; index < (page_counter); index++)
	{
	if (AT24CXX_Write_Page(eeprom_address,
		               buffer_address,
	                       AT24CXX_PAGE_LENGTH) == AT24CXX_ERR)
	    {
	    return AT24CXX_ERR;
	    }

	eeprom_address += AT24CXX_PAGE_LENGTH;
	buffer_address += AT24CXX_PAGE_LENGTH;
	}

    if (AT24CXX_Write_Page(eeprom_address,
	                   buffer_address,
			   (len - (eeprom_address-start_address))) == AT24CXX_ERR)
	{
	return AT24CXX_ERR;
	}

    return AT24CXX_OK;
    }
