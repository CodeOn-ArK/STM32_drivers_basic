################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/001ToggleLed.c \
../Src/002led_button.c \
../Src/003led_button_ext.c \
../Src/004Interrupt.c \
../Src/005spi_Tx_only.c \
../Src/006spi_TxOnly_ArduinoSlave.c \
../Src/007spi_cmd_handling.c \
../Src/008I2C_master_Tx_test.c \
../Src/009I2C_master_Rx_test.c \
../Src/010I2C_master_Rx_test_IT.c \
../Src/011I2C_Slave_Tx_string.c \
../Src/sysmem.c 

OBJS += \
./Src/001ToggleLed.o \
./Src/002led_button.o \
./Src/003led_button_ext.o \
./Src/004Interrupt.o \
./Src/005spi_Tx_only.o \
./Src/006spi_TxOnly_ArduinoSlave.o \
./Src/007spi_cmd_handling.o \
./Src/008I2C_master_Tx_test.o \
./Src/009I2C_master_Rx_test.o \
./Src/010I2C_master_Rx_test_IT.o \
./Src/011I2C_Slave_Tx_string.o \
./Src/sysmem.o 

C_DEPS += \
./Src/001ToggleLed.d \
./Src/002led_button.d \
./Src/003led_button_ext.d \
./Src/004Interrupt.d \
./Src/005spi_Tx_only.d \
./Src/006spi_TxOnly_ArduinoSlave.d \
./Src/007spi_cmd_handling.d \
./Src/008I2C_master_Tx_test.d \
./Src/009I2C_master_Rx_test.d \
./Src/010I2C_master_Rx_test_IT.d \
./Src/011I2C_Slave_Tx_string.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/001ToggleLed.o: ../Src/001ToggleLed.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/inc" -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/src" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/001ToggleLed.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/002led_button.o: ../Src/002led_button.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/src" -I../Inc -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/002led_button.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/003led_button_ext.o: ../Src/003led_button_ext.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/src" -I../Inc -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/003led_button_ext.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/004Interrupt.o: ../Src/004Interrupt.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/src" -I../Inc -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/004Interrupt.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/005spi_Tx_only.o: ../Src/005spi_Tx_only.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/src" -I../Inc -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/005spi_Tx_only.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/006spi_TxOnly_ArduinoSlave.o: ../Src/006spi_TxOnly_ArduinoSlave.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/src" -I../Inc -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/006spi_TxOnly_ArduinoSlave.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/007spi_cmd_handling.o: ../Src/007spi_cmd_handling.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/src" -I../Inc -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/007spi_cmd_handling.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/008I2C_master_Tx_test.o: ../Src/008I2C_master_Tx_test.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/src" -I../Inc -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/008I2C_master_Tx_test.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/009I2C_master_Rx_test.o: ../Src/009I2C_master_Rx_test.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/src" -I../Inc -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/009I2C_master_Rx_test.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/010I2C_master_Rx_test_IT.o: ../Src/010I2C_master_Rx_test_IT.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/src" -I../Inc -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/010I2C_master_Rx_test_IT.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/011I2C_Slave_Tx_string.o: ../Src/011I2C_Slave_Tx_string.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/src" -I../Inc -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/011I2C_Slave_Tx_string.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/src" -I../Inc -I"/home/ark/st/working_space/stm32f446xx_drivers/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

