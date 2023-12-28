################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/exti.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/systick.c \
../Src/timers.c 

OBJS += \
./Src/adc.o \
./Src/exti.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/systick.o \
./Src/timers.o 

C_DEPS += \
./Src/adc.d \
./Src/exti.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/systick.d \
./Src/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G0 -DNUCLEO_G0B1RE -DSTM32G0B1RETx -DSTM32G0B1xx -c -I../Inc -I/home/ebenezer/STM32CubeIDE/workspace_1.13.2/chip_headers/CMSIS/Device/ST/STM32G0xx/Include -I/home/ebenezer/STM32CubeIDE/workspace_1.13.2/chip_headers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adc.cyclo ./Src/adc.d ./Src/adc.o ./Src/adc.su ./Src/exti.cyclo ./Src/exti.d ./Src/exti.o ./Src/exti.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/systick.cyclo ./Src/systick.d ./Src/systick.o ./Src/systick.su ./Src/timers.cyclo ./Src/timers.d ./Src/timers.o ./Src/timers.su

.PHONY: clean-Src

