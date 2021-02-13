################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/src/stm32f446xx_gpio.c \
../Inc/src/stm32f446xx_i2c.c \
../Inc/src/stm32f446xx_rcc.c \
../Inc/src/stm32f446xx_spi.c \
../Inc/src/stm32f446xx_usart.c 

OBJS += \
./Inc/src/stm32f446xx_gpio.o \
./Inc/src/stm32f446xx_i2c.o \
./Inc/src/stm32f446xx_rcc.o \
./Inc/src/stm32f446xx_spi.o \
./Inc/src/stm32f446xx_usart.o 

C_DEPS += \
./Inc/src/stm32f446xx_gpio.d \
./Inc/src/stm32f446xx_i2c.d \
./Inc/src/stm32f446xx_rcc.d \
./Inc/src/stm32f446xx_spi.d \
./Inc/src/stm32f446xx_usart.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/src/stm32f446xx_gpio.o: ../Inc/src/stm32f446xx_gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I../Inc -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/inc" -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/src/stm32f446xx_gpio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/src/stm32f446xx_i2c.o: ../Inc/src/stm32f446xx_i2c.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/src" -I../Inc -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/src/stm32f446xx_i2c.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/src/stm32f446xx_rcc.o: ../Inc/src/stm32f446xx_rcc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/src" -I../Inc -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/src/stm32f446xx_rcc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/src/stm32f446xx_spi.o: ../Inc/src/stm32f446xx_spi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/src" -I../Inc -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/src/stm32f446xx_spi.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/src/stm32f446xx_usart.o: ../Inc/src/stm32f446xx_usart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/src" -I../Inc -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/src/stm32f446xx_usart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

