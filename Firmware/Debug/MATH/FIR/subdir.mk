################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MATH/FIR/FIR.c 

OBJS += \
./MATH/FIR/FIR.o 

C_DEPS += \
./MATH/FIR/FIR.d 


# Each subdirectory must supply rules for building sources it contributes
MATH/FIR/%.o MATH/FIR/%.su MATH/FIR/%.cyclo: ../MATH/FIR/%.c MATH/FIR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MATH-2f-FIR

clean-MATH-2f-FIR:
	-$(RM) ./MATH/FIR/FIR.cyclo ./MATH/FIR/FIR.d ./MATH/FIR/FIR.o ./MATH/FIR/FIR.su

.PHONY: clean-MATH-2f-FIR

