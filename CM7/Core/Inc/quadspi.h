/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    quadspi.h
  * @brief   This file contains all the function prototypes for
  *          the quadspi.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#ifndef __QUADSPI_H__
#define __QUADSPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"

/* USER CODE BEGIN Includes */
// IS25LP512M Memory Parameters
#define MEMORY_FLASH_SIZE   0x4000000
#define MEMORY_BLOCK_SIZE   0x10000
#define MEMORY_SECTOR_SIZE  0x1000
#define MEMORY_PAGE_SIZE    0x100

// IS25LP512M Flash Commands
#define WRITE_ENABLE_CMD        0x06
#define WRITE_DISABLE_CMD       0x04
#define READ_STATUS_REG_CMD     0x05
#define WRITE_STATUS_REG_CMD    0x01
#define READ_JEDEC_ID_CMD       0x9F
#define SECTOR_ERASE_CMD        0x20
#define BLOCK_ERASE_CMD         0xD8
#define CHIP_ERASE_CMD          0xC7
#define PAGE_PROGRAM_CMD        0x02
#define FAST_READ_CMD           0x0B
#define QUAD_OUT_FAST_READ_CMD  0x6B
#define QUAD_READ_IO_CMD        0xEB
#define RESET_ENABLE_CMD        0x66
#define RESET_EXECUTE_CMD       0x99
#define ENABLE_4BYTE_ADDR_CMD   0xB7
#define EXIT_4BYTE_ADDR_CMD     0x29

#define DUMMY_CLOCK_CYCLES_READ_QUAD 8
#define HAL_QPSI_TIMEOUT_DEFAULT_VALUE 5000
/* USER CODE END Includes */

extern QSPI_HandleTypeDef hqspi1;

/* USER CODE BEGIN Private defines */
uint8_t OWN_QSPI_Init(void);
uint8_t OWN_QSPI_EraseSector(uint32_t startAddr, uint32_t endAddr);
uint8_t OWN_QSPI_WriteMemory(uint8_t* buffer, uint32_t addr, uint32_t buff_size);
uint8_t OWN_QSPI_EnableMemoryMappedMode(void);

uint8_t OWN_QSPI_Read_ID(uint8_t* mfID, uint16_t* chipSize);
uint8_t OWN_QSPI_ReadStatus(uint8_t* statusReg);
uint8_t OWN_QSPI_Tester(void);

/* USER CODE END Private defines */

void MX_QUADSPI_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __QUADSPI_H__ */

