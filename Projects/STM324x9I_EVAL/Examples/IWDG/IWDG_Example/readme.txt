/**
  @page IWDG_Example Independent Watchdog example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    IWDG/IWDG_Example/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the Independent Watchdog example.
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics. All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
   @endverbatim

@par Example Description 

How to handle the IWDG reload counter and simulate a software fault that generates 
an MCU IWDG reset after a preset laps of time.

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 180 MHz.

The IWDG peripheral configuration is ensured by the HAL_IWDG_Init() function.
This later is calling the HAL_IWDG_MspInit()function which core is implementing
the configuration of the needed IWDG resources according to the used hardware (CLOCK, 
GPIO, DMA and NVIC). You may update this function to change IWDG configuration.

The IWDG timeout is set to 250 ms (the timeout may vary due to LSI frequency 
dispersion).

First, the TIM5 timer is configured to measure the LSI frequency as the 
LSI is internally connected to TIM5 CH4, in order to adjust the IWDG clock.

The LSI measurement using the TIM5 is described below:
  - Configure the TIM5 to remap internally the TIM5 CH4 Input Capture to the LSI
    clock output.
  - Enable the TIM5 Input Capture interrupt: after one cycle of LSI clock, the
    period value is stored in a variable and compared to the HCLK clock to get
    its real value. 

Then, the IWDG reload counter is configured as below to obtain 250 ms according 
to the measured LSI frequency after setting the prescaler value:
  
    IWDG counter clock Frequency = LSI Frequency / Prescaler value

The IWDG reload counter is refreshed each 240 ms in the main program infinite 
loop to prevent a IWDG reset.
  
LED2 is also toggled each 240 ms indicating that the program is running.

An EXTI Line is connected to a GPIO pin, and configured to generate an interrupt
on the rising edge of the signal.

The EXTI Line is used to simulate a software failure: once the EXTI Line event 
occurs, by pressing the Key/Tamper push-button(PC.13), the corresponding interrupt  
is served. 

In the ISR, a write to invalid address generates a Hardfault exception 
containing an infinite loop and preventing to return to main program (the IWDG 
reload counter is not refreshed).
As a result, when the IWDG counter reaches 00h, the IWDG reset occurs.
  
If the IWDG reset is generated, after the system resumes from reset, LED1 turns ON.
If the EXTI Line event does not occur, the IWDG counter is indefinitely refreshed
in the main program infinite loop, and there is no IWDG reset.

LED3 will turn ON, if any error is occurred.


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Keywords

System, IWDG, Timeout, Reload Counter, MCU Reset, Downcounter, LSI, Timer, Measure Frequency

@par Directory contents 
 
  - IWDG/IWDG_Example/Inc/stm32f4xx_hal_conf.h    HAL configuration file
  - IWDG/IWDG_Example/Inc/stm32f4xx_it.h          Interrupt handlers header file
  - IWDG/IWDG_Example/Inc/main.h                  Main program header file
  - IWDG/IWDG_Example/Src/stm32f4xx_it.c          Interrupt handlers
  - IWDG/IWDG_Example/Src/main.c                  Main program
  - IWDG/IWDG_Example/Src/stm32f4xx_hal_msp.c     HAL MSP module 
  - IWDG/IWDG_Example/Src/system_stm32f4xx.c      STM32F4xx system clock configuration file

     
@par Hardware and Software environment

  - This example runs on STM32F42xxx/STM32F43xxx devices.
    
  - This example has been tested with STM324x9I-EVAL RevB evaluation board and can be
    easily tailored to any other supported device and development board.   


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
 