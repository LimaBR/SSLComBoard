/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CS_I2C_SPI_Pin GPIO_PIN_3
#define CS_I2C_SPI_GPIO_Port GPIOE
#define PC14_OSC32_IN_Pin GPIO_PIN_14
#define PC14_OSC32_IN_GPIO_Port GPIOC
#define PC15_OSC32_OUT_Pin GPIO_PIN_15
#define PC15_OSC32_OUT_GPIO_Port GPIOC
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH
#define OTG_FS_PowerSwitchOn_Pin GPIO_PIN_0
#define OTG_FS_PowerSwitchOn_GPIO_Port GPIOC
#define PDM_OUT_Pin GPIO_PIN_3
#define PDM_OUT_GPIO_Port GPIOC
#define B1_Pin GPIO_PIN_0
#define B1_GPIO_Port GPIOA
#define B1_EXTI_IRQn EXTI0_IRQn
#define USART2_TX_Pin GPIO_PIN_2
#define USART2_TX_GPIO_Port GPIOA
#define USART2_RX_Pin GPIO_PIN_3
#define USART2_RX_GPIO_Port GPIOA
#define I2S3_WS_Pin GPIO_PIN_4
#define I2S3_WS_GPIO_Port GPIOA
#define SPI1_SCK_Pin GPIO_PIN_5
#define SPI1_SCK_GPIO_Port GPIOA
#define SPI1_MISO_Pin GPIO_PIN_6
#define SPI1_MISO_GPIO_Port GPIOA
#define SPI1_MOSI_Pin GPIO_PIN_7
#define SPI1_MOSI_GPIO_Port GPIOA
#define SX1280_A_BUSY_Pin GPIO_PIN_4
#define SX1280_A_BUSY_GPIO_Port GPIOC
#define SX1280_A_BUSY_EXTI_IRQn EXTI4_IRQn
#define SX1280_A_IRQ_Pin GPIO_PIN_5
#define SX1280_A_IRQ_GPIO_Port GPIOC
#define SX1280_A_IRQ_EXTI_IRQn EXTI9_5_IRQn
#define SX1280_A_NSS_Pin GPIO_PIN_0
#define SX1280_A_NSS_GPIO_Port GPIOB
#define SX1280_A_RST_Pin GPIO_PIN_1
#define SX1280_A_RST_GPIO_Port GPIOB
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define SX1280_A_RXEN_Pin GPIO_PIN_7
#define SX1280_A_RXEN_GPIO_Port GPIOE
#define SX1280_A_TXEN_Pin GPIO_PIN_8
#define SX1280_A_TXEN_GPIO_Port GPIOE
#define SX1280_B_BUSY_Pin GPIO_PIN_9
#define SX1280_B_BUSY_GPIO_Port GPIOE
#define SX1280_B_BUSY_EXTI_IRQn EXTI9_5_IRQn
#define SX1280_B_IRQ_Pin GPIO_PIN_10
#define SX1280_B_IRQ_GPIO_Port GPIOE
#define SX1280_B_IRQ_EXTI_IRQn EXTI15_10_IRQn
#define SX1280_B_NSS_Pin GPIO_PIN_11
#define SX1280_B_NSS_GPIO_Port GPIOE
#define SX1280_B_RST_Pin GPIO_PIN_12
#define SX1280_B_RST_GPIO_Port GPIOE
#define SX1280_B_RXEN_Pin GPIO_PIN_13
#define SX1280_B_RXEN_GPIO_Port GPIOE
#define SX1280_B_TXEN_Pin GPIO_PIN_14
#define SX1280_B_TXEN_GPIO_Port GPIOE
#define NRF24_A_IRQ_Pin GPIO_PIN_15
#define NRF24_A_IRQ_GPIO_Port GPIOE
#define NRF24_A_IRQ_EXTI_IRQn EXTI15_10_IRQn
#define CLK_IN_Pin GPIO_PIN_10
#define CLK_IN_GPIO_Port GPIOB
#define NRF24_A_NSS_Pin GPIO_PIN_11
#define NRF24_A_NSS_GPIO_Port GPIOB
#define NRF24_A_CE_Pin GPIO_PIN_12
#define NRF24_A_CE_GPIO_Port GPIOB
#define ESP8266_IRQ_Pin GPIO_PIN_8
#define ESP8266_IRQ_GPIO_Port GPIOD
#define ESP8266_IRQ_EXTI_IRQn EXTI9_5_IRQn
#define ESP8266_RST_Pin GPIO_PIN_9
#define ESP8266_RST_GPIO_Port GPIOD
#define LD4_Pin GPIO_PIN_12
#define LD4_GPIO_Port GPIOD
#define LD3_Pin GPIO_PIN_13
#define LD3_GPIO_Port GPIOD
#define LD5_Pin GPIO_PIN_14
#define LD5_GPIO_Port GPIOD
#define LD6_Pin GPIO_PIN_15
#define LD6_GPIO_Port GPIOD
#define NRF24_B_IRQ_Pin GPIO_PIN_6
#define NRF24_B_IRQ_GPIO_Port GPIOC
#define NRF24_B_IRQ_EXTI_IRQn EXTI9_5_IRQn
#define I2S3_MCK_Pin GPIO_PIN_7
#define I2S3_MCK_GPIO_Port GPIOC
#define NRF24_B_CE_Pin GPIO_PIN_9
#define NRF24_B_CE_GPIO_Port GPIOC
#define NRF24_B_NSS_Pin GPIO_PIN_8
#define NRF24_B_NSS_GPIO_Port GPIOA
#define VBUS_FS_Pin GPIO_PIN_9
#define VBUS_FS_GPIO_Port GPIOA
#define OTG_FS_ID_Pin GPIO_PIN_10
#define OTG_FS_ID_GPIO_Port GPIOA
#define OTG_FS_DM_Pin GPIO_PIN_11
#define OTG_FS_DM_GPIO_Port GPIOA
#define OTG_FS_DP_Pin GPIO_PIN_12
#define OTG_FS_DP_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define SPI2_NSS_Pin GPIO_PIN_15
#define SPI2_NSS_GPIO_Port GPIOA
#define I2S3_SCK_Pin GPIO_PIN_10
#define I2S3_SCK_GPIO_Port GPIOC
#define I2S3_SD_Pin GPIO_PIN_12
#define I2S3_SD_GPIO_Port GPIOC
#define Audio_RST_Pin GPIO_PIN_4
#define Audio_RST_GPIO_Port GPIOD
#define OTG_FS_OverCurrent_Pin GPIO_PIN_5
#define OTG_FS_OverCurrent_GPIO_Port GPIOD
#define TOUCH_NSS_Pin GPIO_PIN_6
#define TOUCH_NSS_GPIO_Port GPIOD
#define TOUCH_IRQ_Pin GPIO_PIN_7
#define TOUCH_IRQ_GPIO_Port GPIOD
#define TOUCH_IRQ_EXTI_IRQn EXTI9_5_IRQn
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define LCD_NSS_Pin GPIO_PIN_4
#define LCD_NSS_GPIO_Port GPIOB
#define LCD_RST_Pin GPIO_PIN_5
#define LCD_RST_GPIO_Port GPIOB
#define Audio_SCL_Pin GPIO_PIN_6
#define Audio_SCL_GPIO_Port GPIOB
#define LCD_DR_Pin GPIO_PIN_7
#define LCD_DR_GPIO_Port GPIOB
#define LCD_LED_Pin GPIO_PIN_8
#define LCD_LED_GPIO_Port GPIOB
#define Audio_SDA_Pin GPIO_PIN_9
#define Audio_SDA_GPIO_Port GPIOB
#define MEMS_INT2_Pin GPIO_PIN_1
#define MEMS_INT2_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
