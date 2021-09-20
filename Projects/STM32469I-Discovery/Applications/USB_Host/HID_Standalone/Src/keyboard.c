/**
  ******************************************************************************
  * @file    USB_Host/HID_Standalone/Src/keyboard.c 
  * @author  MCD Application Team
  * @brief   This file implements the HID keyboard functions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define KYBRD_FIRST_COLUMN               (uint16_t)7
#define KYBRD_LAST_COLUMN                (uint16_t)479
#define KYBRD_FIRST_LINE                 (uint8_t) 90
#define SMALL_FONT_COLUMN_WIDTH                    8
#define SMALL_FONT_LINE_WIDTH                      15
#define KYBRD_LAST_LINE                  (uint16_t)200

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern HID_DEMO_StateMachine hid_demo;
uint8_t KeybrdCharXpos = 0;
uint16_t KeybrdCharYpos = 0;

/* Private function prototypes -----------------------------------------------*/
static void USR_KEYBRD_Init(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Manages Keyboard Menu Process.  
  * @param  None
  * @retval None
  */
void HID_KeyboardMenuProcess(void)
{
  USR_KEYBRD_Init();   
}

/**
  * @brief  Init Keyboard window.     
  * @param  None
  * @retval None
  */
static void USR_KEYBRD_Init(void)
{
  LCD_LOG_ClearTextZone();
  BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
  
  BSP_LCD_DisplayStringAtLine(4, (uint8_t *)"Use Keyboard to tape characters:                                                            ");
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  
  KeybrdCharXpos = KYBRD_FIRST_LINE;
  KeybrdCharYpos = KYBRD_FIRST_COLUMN;
}

/**
  * @brief  Processes Keyboard data.
  * @param  data: Keyboard data to be displayed
  * @retval None
  */
void USR_KEYBRD_ProcessData(uint8_t data)
{
  if(data == '\n')
  {
    KeybrdCharYpos = KYBRD_FIRST_COLUMN;
    
    /* Increment char X position */
    KeybrdCharXpos += SMALL_FONT_LINE_WIDTH;
    
    if(KeybrdCharXpos > KYBRD_LAST_LINE)
    {
      LCD_LOG_ClearTextZone();
      KeybrdCharXpos = KYBRD_FIRST_LINE;
      KeybrdCharYpos = KYBRD_FIRST_COLUMN;
    }
  }
   else if(data == '\r')
  {
    /* Manage deletion of character and update cursor location */
    if( KeybrdCharYpos == KYBRD_FIRST_COLUMN) 
    {
      /* First character of first line to be deleted */
      if(KeybrdCharXpos == KYBRD_FIRST_LINE)
      { 
        KeybrdCharYpos = KYBRD_FIRST_COLUMN; 
      }
      else
      {
        KeybrdCharXpos -= SMALL_FONT_LINE_WIDTH;
        KeybrdCharYpos = (KYBRD_LAST_COLUMN - SMALL_FONT_COLUMN_WIDTH); 
      }
    }
    else
    {
      KeybrdCharYpos -= SMALL_FONT_COLUMN_WIDTH; 
    } 
    BSP_LCD_DisplayChar(KeybrdCharYpos, KeybrdCharXpos, ' '); 
  }
  else
  {
    /* Update the cursor position on LCD */
    BSP_LCD_DisplayChar(KeybrdCharYpos, KeybrdCharXpos, data);  
    
    /* Increment char Y position */
    KeybrdCharYpos += SMALL_FONT_COLUMN_WIDTH;
    
    /* Check if the Y position has reached the last column */
    if(KeybrdCharYpos == KYBRD_LAST_COLUMN)
    {
      KeybrdCharYpos = KYBRD_FIRST_COLUMN;
      
      /* Increment char X position */
      KeybrdCharXpos += SMALL_FONT_LINE_WIDTH;
    }
    
    if(KeybrdCharXpos > KYBRD_LAST_LINE)
    {
      LCD_LOG_ClearTextZone();
      KeybrdCharXpos = KYBRD_FIRST_LINE;
      /* Start New Display of the cursor position on LCD */
      BSP_LCD_DisplayChar(KeybrdCharYpos,KeybrdCharXpos, data);  
    }
  }
}               

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
