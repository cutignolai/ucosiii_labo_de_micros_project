################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/drivers/SysTick.c \
../source/drivers/button.c \
../source/drivers/card_reader.c \
../source/drivers/display.c \
../source/drivers/encoder.c \
../source/drivers/fifo.c \
../source/drivers/gpio.c \
../source/drivers/led.c \
../source/drivers/leds.c \
../source/drivers/message.c \
../source/drivers/timer.c \
../source/drivers/uart.c 

OBJS += \
./source/drivers/SysTick.o \
./source/drivers/button.o \
./source/drivers/card_reader.o \
./source/drivers/display.o \
./source/drivers/encoder.o \
./source/drivers/fifo.o \
./source/drivers/gpio.o \
./source/drivers/led.o \
./source/drivers/leds.o \
./source/drivers/message.o \
./source/drivers/timer.o \
./source/drivers/uart.o 

C_DEPS += \
./source/drivers/SysTick.d \
./source/drivers/button.d \
./source/drivers/card_reader.d \
./source/drivers/display.d \
./source/drivers/encoder.d \
./source/drivers/fifo.d \
./source/drivers/gpio.d \
./source/drivers/led.d \
./source/drivers/leds.d \
./source/drivers/message.d \
./source/drivers/timer.d \
./source/drivers/uart.d 


# Each subdirectory must supply rules for building sources it contributes
source/drivers/%.o: ../source/drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -D__USE_CMSIS -DDEBUG -I"C:\00 - Ignacio\Facultad\Laboratorio de Microprocesadores - 22.99\TPs\04 - TP4\ucosiii_labo_de_micros_project\source\ucosiii_config" -I"C:\00 - Ignacio\Facultad\Laboratorio de Microprocesadores - 22.99\TPs\04 - TP4\ucosiii_labo_de_micros_project\source\rtos\uCOSIII\src\uC-CPU\ARM-Cortex-M4\GNU" -I"C:\00 - Ignacio\Facultad\Laboratorio de Microprocesadores - 22.99\TPs\04 - TP4\ucosiii_labo_de_micros_project\source\rtos\uCOSIII\src\uC-CPU" -I"C:\00 - Ignacio\Facultad\Laboratorio de Microprocesadores - 22.99\TPs\04 - TP4\ucosiii_labo_de_micros_project\source\rtos\uCOSIII\src\uC-LIB" -I"C:\00 - Ignacio\Facultad\Laboratorio de Microprocesadores - 22.99\TPs\04 - TP4\ucosiii_labo_de_micros_project\source\rtos\uCOSIII\src\uCOS-III\Ports\ARM-Cortex-M4\Generic\GNU" -I"C:\00 - Ignacio\Facultad\Laboratorio de Microprocesadores - 22.99\TPs\04 - TP4\ucosiii_labo_de_micros_project\source\rtos\uCOSIII\src\uCOS-III\Source" -I../source -I../ -I../SDK/CMSIS -I../SDK/startup -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


