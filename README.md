# STM32_drivers_basic

Welcome to my implementation of basic peripheral drivers in STM32.
In this prject I have created drivers for:
            
            1}  GPIO
            2}  SPI
            3}  I2C
            4}  USART/UART

upcoming:

            1}  CAN
            2}  USB(Probably)

# Guide to this project

This project is based on STM32F446RE. Since ST's Nucleo boards are compatible across the family line
you may port this to your own board with very minor changes.

There are 3 folders of intrest to us here. Them being:
        
            1}  INC
            2}  Src
            3}  drivers/inc

The central MCU specific header file contains in drivers/inc folder name being : "stm32f446xx.h"
This is the core file and contains all the device specfic macros and structures.
IT IS THE LONGEST FILE OF ALL

The second important folder is Inc folder and Inc/src folder.
Actually this had to implemented separately as drivers/Inc && drivers/Src.
But due to some error in STM32CUBE IDE in Linux, it is not able to link the necessary file from the 
specified directories. So had to change the file path to ../Inc.

1}  In Inc folder we have our peripheral_drivers include files
2}  In Inc/Src folder we have our peripheral_drivers' source code

The application codes are kept at Src where the source codes are kept. These src codes test the 
driver layer and interact with the user

More updates coming soon 
:wq!
