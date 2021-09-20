/**
  ******************************************************************************
  * @file    FLASH/FLASH_WriteProtection/Src/main.c
  * @author  MCD Application Team
  * @brief   This example provides a description of how to erase and program the
  *          STM32F4xx FLASH.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup FLASH_WriteProtection
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define FLASH_WRP_SECTORS   (OB_WRP_SECTOR_6 | OB_WRP_SECTOR_7) /* sectors 6 and 7  */
#define LTDC_BACKGROUND_LAYER   0
#define LTDC_FOREGROUND_LAYER   1

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FLASH_OBProgramInitTypeDef OBInit;
__IO uint32_t SectorsWRPStatus = 0xFFF;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  uint8_t  lcd_status = LCD_OK;

  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization: global MSP (MCU Support Package) initialization
     */
  HAL_Init();

  /* Configure the system clock to 180 MHz */
  SystemClock_Config();

  /* Configure Tamper push-button */
  BSP_PB_Init(BUTTON_TAMPER, BUTTON_MODE_GPIO);

  /*##-1- Initialize the LCD #################################################*/
  /* Initialize the SDRAM */
  if (BSP_SDRAM_Init() != SDRAM_OK)
  {
    /* User can add here some code to deal with this error */
    while (1)
    {
    }
  }

  /* Initialize DSI LCD */
  lcd_status = BSP_LCD_Init();
  if (lcd_status != LCD_OK)
  {
    /* User can add here some code to deal with this error */
    while (1)
    {
    }
  }

  /* Set LCD Foreground Layer  */
  BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
  BSP_LCD_SelectLayer(0);

  /* Set LCD font */
  BSP_LCD_SetFont(&Font20);

  /*##-2- Display messages on LCD ############################################*/
  /* Clear the LCD */
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  /* Set the LCD Text Color */
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);

  /* Display test name on LCD */
  BSP_LCD_DisplayStringAt(0, LINE(8),  (uint8_t *)"Flash Write", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, LINE(9),  (uint8_t *)"protection test", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *)"Press User", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, LINE(11), (uint8_t *)"Tamper-button", CENTER_MODE);

  while (1)
  {
    /* Wait for Tamper push-button to be pushed */
    while (BSP_PB_GetState(BUTTON_TAMPER) != RESET)
    {
    }

    /* Wait for Tamper push-button to be released */
    while (BSP_PB_GetState(BUTTON_TAMPER) != SET)
    {
    }

    /* Get FLASH_WRP_SECTORS write protection status */
    HAL_FLASHEx_OBGetConfig(&OBInit);
    SectorsWRPStatus = OBInit.WRPSector & FLASH_WRP_SECTORS;

    if (SectorsWRPStatus == 0)
    {
      /* If FLASH_WRP_SECTORS are write protected, disable the write protection */

      /* Allow Access to option bytes sector */
      HAL_FLASH_OB_Unlock();

      /* Allow Access to Flash control registers and user Flash */
      HAL_FLASH_Unlock();

      /* Disable FLASH_WRP_SECTORS write protection */
      OBInit.OptionType = OPTIONBYTE_WRP;
      OBInit.WRPState   = OB_WRPSTATE_DISABLE;
      OBInit.WRPSector  = FLASH_WRP_SECTORS;
      HAL_FLASHEx_OBProgram(&OBInit);

      /* Start the Option Bytes programming process */
      if (HAL_FLASH_OB_Launch() != HAL_OK)
      {
        /* User can add here some code to deal with this error */
        while (1)
        {
        }
      }

      /* Prevent Access to option bytes sector */
      HAL_FLASH_OB_Lock();

      /* Disable the Flash option control register access (recommended to protect
      the option Bytes against possible unwanted operations) */
      HAL_FLASH_Lock();

      /* Get FLASH_WRP_SECTORS write protection status */
      HAL_FLASHEx_OBGetConfig(&OBInit);
      SectorsWRPStatus = OBInit.WRPSector & FLASH_WRP_SECTORS;

      /* Check if FLASH_WRP_SECTORS write protection is disabled */
      if (SectorsWRPStatus == FLASH_WRP_SECTORS)
      {
        /* Set the LCD Text Color */
        BSP_LCD_SetTextColor(LCD_COLOR_GREEN);

        BSP_LCD_DisplayStringAt(0, LINE(13), (uint8_t *)"Write", CENTER_MODE);
        BSP_LCD_DisplayStringAt(0, LINE(14), (uint8_t *)"protection is", CENTER_MODE);
        BSP_LCD_DisplayStringAt(0, LINE(15), (uint8_t *)"disabled", CENTER_MODE);
      }
      else
      {
        /* Set the LCD Text Color */
        BSP_LCD_SetTextColor(LCD_COLOR_RED);

        BSP_LCD_DisplayStringAt(0, LINE(13), (uint8_t *)"Write", CENTER_MODE);
        BSP_LCD_DisplayStringAt(0, LINE(14), (uint8_t *)"protection is", CENTER_MODE);
        BSP_LCD_DisplayStringAt(0, LINE(15), (uint8_t *)"not disabled", CENTER_MODE);
      }
    }
    else
    {
      /* If FLASH_WRP_SECTORS are not write protected, enable the write protection */

      /* Allow Access to option bytes sector */
      HAL_FLASH_OB_Unlock();

      /* Allow Access to Flash control registers and user Flash */
      HAL_FLASH_Unlock();

      /* Enable FLASH_WRP_SECTORS write protection */
      OBInit.OptionType = OPTIONBYTE_WRP;
      OBInit.WRPState   = OB_WRPSTATE_ENABLE;
      OBInit.WRPSector  = FLASH_WRP_SECTORS;
      HAL_FLASHEx_OBProgram(&OBInit);

      /* Start the Option Bytes programming process */
      if (HAL_FLASH_OB_Launch() != HAL_OK)
      {
        /* User can add here some code to deal with this error */
        while (1)
        {
        }
      }

      /* Prevent Access to option bytes sector */
      HAL_FLASH_OB_Lock();

      /* Disable the Flash option control register access (recommended to protect
      the option Bytes against possible unwanted operations) */
      HAL_FLASH_Lock();

      /* Get FLASH_WRP_SECTORS write protection status */
      HAL_FLASHEx_OBGetConfig(&OBInit);
      SectorsWRPStatus = OBInit.WRPSector & FLASH_WRP_SECTORS;

      /* Check if FLASH_WRP_SECTORS are write protected */
      if (SectorsWRPStatus == 0)
      {
        /* Set the LCD Text Color */
        BSP_LCD_SetTextColor(LCD_COLOR_GREEN);

        BSP_LCD_DisplayStringAt(0, LINE(13), (uint8_t *)"Write", CENTER_MODE);
        BSP_LCD_DisplayStringAt(0, LINE(14), (uint8_t *)"protection is", CENTER_MODE);
        BSP_LCD_DisplayStringAt(0, LINE(15), (uint8_t *)" enabled ", CENTER_MODE);
      }
      else
      {
        /* Set the LCD Text Color */
        BSP_LCD_SetTextColor(LCD_COLOR_RED);

        BSP_LCD_DisplayStringAt(0, LINE(13), (uint8_t *)"Write", CENTER_MODE);
        BSP_LCD_DisplayStringAt(0, LINE(14), (uint8_t *)"protection is", CENTER_MODE);
        BSP_LCD_DisplayStringAt(0, LINE(15), (uint8_t *)"not enabled", CENTER_MODE);
      }
    }
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            PLL_R                          = 6
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  RCC_OscInitStruct.PLL.PLLR = 6;
  
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* Activate the OverDrive to reach the 180 MHz Frequency */  
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/