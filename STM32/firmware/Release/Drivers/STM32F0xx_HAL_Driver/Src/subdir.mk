################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.c \
../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc.c \
../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc_ex.c \
../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cortex.c \
../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dma.c \
../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_exti.c \
../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash.c \
../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash_ex.c \
../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_gpio.c \
../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c.c \
../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c_ex.c \
../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr.c \
../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr_ex.c \
../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc.c \
../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc_ex.c \
../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim.c \
../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim_ex.c 

OBJS += \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.o \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc.o \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc_ex.o \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cortex.o \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dma.o \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_exti.o \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash.o \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash_ex.o \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_gpio.o \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c.o \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c_ex.o \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr.o \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr_ex.o \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc.o \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc_ex.o \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim.o \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim_ex.o 

C_DEPS += \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.d \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc.d \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc_ex.d \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cortex.d \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dma.d \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_exti.d \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash.d \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash_ex.d \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_gpio.d \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c.d \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c_ex.d \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr.d \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr_ex.d \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc.d \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc_ex.d \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim.d \
./Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim_ex.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc_ex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc_ex.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cortex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cortex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cortex.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dma.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dma.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dma.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_exti.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_exti.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_exti.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash_ex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash_ex.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_gpio.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_gpio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c_ex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c_ex.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr_ex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr_ex.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc_ex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc_ex.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim_ex.o: ../Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim_ex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim_ex.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

