/**
  ******************************************************************************
  * @file    LibJPEG/LibJPEG_Decoding/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Jpeg includes component */
#include <stdint.h>
#include <string.h>
#include "jpeglib.h"

#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_sdram.h"

/* FatFs includes component */
#include "ff_gen_drv.h"
#include "usbh_diskio_dma.h"

#include "decode.h"

/* Exported types ------------------------------------------------------------*/
typedef struct RGB
{
  uint8_t B;
  uint8_t G;
  uint8_t R;
}RGB_typedef;

/* Exported constants --------------------------------------------------------*/
#define IMAGE_HEIGHT 320
#define IMAGE_WIDTH  240
#define LCD_BUFFER   0xD0000000

 #define USE_DMA2D 
 #define SWAP_RB 
/* #define DONT_USE_DMA2D */

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
