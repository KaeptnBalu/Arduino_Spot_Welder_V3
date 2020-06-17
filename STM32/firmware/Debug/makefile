################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F0xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Spot_Welder.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Spot_Welder.list \


# All Target
all: Spot_Welder.elf secondary-outputs

# Tool invocations
Spot_Welder.elf: $(OBJS) $(USER_OBJS) /home/medprime/Documents/Projects/alsaad/Arduino_Spot_Welder_V3/STM32/firmware/STM32F030F4PX_FLASH.ld
	arm-none-eabi-gcc -o "Spot_Welder.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"/home/medprime/Documents/Projects/alsaad/Arduino_Spot_Welder_V3/STM32/firmware/STM32F030F4PX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Spot_Welder.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Spot_Welder.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Spot_Welder.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
