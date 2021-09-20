/**
  ******************************************************************************
  * @file    Templates_LL/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/

/* LL drivers common to all LL examples */
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_adc.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_crc.h"
#include "stm32f4xx_ll_dac.h"
#include "stm32f4xx_ll_dma.h"
#include "stm32f4xx_ll_dma2d.h"
#include "stm32f4xx_ll_i2c.h"
#include "stm32f4xx_ll_iwdg.h"
#include "stm32f4xx_ll_rtc.h"
#include "stm32f4xx_ll_spi.h"
#include "stm32f4xx_ll_tim.h"
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_wwdg.h"
#include "stm32f4xx_ll_rng.h"
#include "stm32f4xx_ll_lptim.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* ==============   BOARD SPECIFIC CONFIGURATION CODE BEGIN    ============== */
/**
  * @brief LED1 
  */

#define LED1_PIN                           LL_GPIO_PIN_0
#define LED1_GPIO_PORT                     GPIOE
#define LED1_GPIO_CLK_ENABLE()             LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE)

/**
  * @brief LED2 
  */

#define LED2_PIN                           LL_GPIO_PIN_1
#define LED2_GPIO_PORT                     GPIOE
#define LED2_GPIO_CLK_ENABLE()             LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE)

/**
  * @brief LED3 
  */

#define LED3_PIN                           LL_GPIO_PIN_2
#define LED3_GPIO_PORT                     GPIOE
#define LED3_GPIO_CLK_ENABLE()             LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE)

/**
  * @brief LED4 
  */

#define LED4_PIN                           LL_GPIO_PIN_3
#define LED4_GPIO_PORT                     GPIOE
#define LED4_GPIO_CLK_ENABLE()             LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE)

/**
  * @brief JOY SEL-button
  */
#define SEL_JOY_PIN                         LL_GPIO_PIN_0
#define SEL_JOY_GPIO_PORT                   GPIOA
#define SEL_JOY_GPIO_CLK_ENABLE()           LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)   
#define SEL_JOY_EXTI_LINE                   LL_EXTI_LINE_0
#define SEL_JOY_EXTI_IRQn                   EXTI0_IRQn
#define SEL_JOY_EXTI_LINE_ENABLE()          LL_EXTI_EnableIT_0_31(SEL_JOY_EXTI_LINE)   
#define SEL_JOY_EXTI_FALLING_TRIG_ENABLE()  LL_EXTI_EnableFallingTrig_0_31(SEL_JOY_EXTI_LINE)   
#define SEL_JOY_SYSCFG_SET_EXTI()           do {                                                                     \
                                                LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);                \
                                                LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE0); \
                                            } while(0)
#define SEL_JOY_IRQHANDLER                  EXTI0_IRQHandler

/**
  * @brief JOY LEFT-button
  */
#define LEFT_JOY_PIN                         LL_GPIO_PIN_15
#define LEFT_JOY_GPIO_PORT                   GPIOF
#define LEFT_JOY_GPIO_CLK_ENABLE()           LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF)   
#define LEFT_JOY_EXTI_LINE                   LL_EXTI_LINE_15
#define LEFT_JOY_EXTI_IRQn                   EXTI15_10_IRQn
#define LEFT_JOY_EXTI_LINE_ENABLE()          LL_EXTI_EnableIT_0_31(LEFT_JOY_EXTI_LINE)   
#define LEFT_JOY_EXTI_FALLING_TRIG_ENABLE()  LL_EXTI_EnableFallingTrig_0_31(LEFT_JOY_EXTI_LINE)   
#define LEFT_JOY_SYSCFG_SET_EXTI()           do {                                                                     \
                                                LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);                 \
                                                LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTF, LL_SYSCFG_EXTI_LINE15); \
                                            } while(0)
#define LEFT_JOY_IRQHANDLER                  EXTI15_10_IRQHandler

/**
  * @brief JOY UP-button
  */
#define UP_JOY_PIN                         LL_GPIO_PIN_0
#define UP_JOY_GPIO_PORT                   GPIOG
#define UP_JOY_GPIO_CLK_ENABLE()           LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOG)   
#define UP_JOY_EXTI_LINE                   LL_EXTI_LINE_0
#define UP_JOY_EXTI_IRQn                   EXTI0_IRQn
#define UP_JOY_EXTI_LINE_ENABLE()          LL_EXTI_EnableIT_0_31(UP_JOY_EXTI_LINE)   
#define UP_JOY_EXTI_FALLING_TRIG_ENABLE()  LL_EXTI_EnableFallingTrig_0_31(UP_JOY_EXTI_LINE)   
#define UP_JOY_SYSCFG_SET_EXTI()           do {                                                                      \
                                                LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);                \
                                                LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTG, LL_SYSCFG_EXTI_LINE0); \
                                            } while(0)
#define UP_JOY_IRQHANDLER                  EXTI0_IRQHandler

/**
  * @brief JOY RIGHT-button
  */
#define RIGHT_JOY_PIN                         LL_GPIO_PIN_14
#define RIGHT_JOY_GPIO_PORT                   GPIOF
#define RIGHT_JOY_GPIO_CLK_ENABLE()           LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF)   
#define RIGHT_JOY_EXTI_LINE                   LL_EXTI_LINE_14
#define RIGHT_JOY_EXTI_IRQn                   EXTI15_10_IRQn
#define RIGHT_JOY_EXTI_LINE_ENABLE()          LL_EXTI_EnableIT_0_31(RIGHT_JOY_EXTI_LINE)   
#define RIGHT_JOY_EXTI_FALLING_TRIG_ENABLE()  LL_EXTI_EnableFallingTrig_0_31(RIGHT_JOY_EXTI_LINE)   
#define RIGHT_JOY_SYSCFG_SET_EXTI()           do {                                                                    \
                                                LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);                 \
                                                LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTF, LL_SYSCFG_EXTI_LINE14); \
                                            } while(0)
#define RIGHT_JOY_IRQHANDLER                  EXTI15_10_IRQHandler

/**
  * @brief JOY DOWN-button
  */
#define DOWN_JOY_PIN                         LL_GPIO_PIN_1
#define DOWN_JOY_GPIO_PORT                   GPIOG
#define DOWN_JOY_GPIO_CLK_ENABLE()           LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOG)   
#define DOWN_JOY_EXTI_LINE                   LL_EXTI_LINE_1
#define DOWN_JOY_EXTI_IRQn                   EXTI1_IRQn
#define DOWN_JOY_EXTI_LINE_ENABLE()          LL_EXTI_EnableIT_0_31(DOWN_JOY_EXTI_LINE)   
#define DOWN_JOY_EXTI_FALLING_TRIG_ENABLE()  LL_EXTI_EnableFallingTrig_0_31(DOWN_JOY_EXTI_LINE)   
#define DOWN_JOY_SYSCFG_SET_EXTI()           do {                                                                    \
                                                LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);                \
                                                LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTG, LL_SYSCFG_EXTI_LINE1); \
                                            } while(0)
#define DOWN_JOY_IRQHANDLER                  EXTI1_IRQHandler


/* ==============   BOARD SPECIFIC CONFIGURATION CODE END      ============== */

/**
  * @brief Toggle periods for various blinking modes
  */
#define LED_BLINK_FAST  200
#define LED_BLINK_SLOW  500
#define LED_BLINK_ERROR 1000
  
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
