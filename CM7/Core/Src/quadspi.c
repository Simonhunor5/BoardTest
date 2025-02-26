/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    quadspi.c
  * @brief   This file provides code for the configuration
  *          of the QUADSPI instances.
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
/* Includes ------------------------------------------------------------------*/
#include "quadspi.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

QSPI_HandleTypeDef hqspi1;

/* QUADSPI init function */
void MX_QUADSPI_Init(void)
{

  /* USER CODE BEGIN QUADSPI_Init 0 */

  /* USER CODE END QUADSPI_Init 0 */

  /* USER CODE BEGIN QUADSPI_Init 1 */

  /* USER CODE END QUADSPI_Init 1 */
  hqspi1.Instance = QUADSPI;
  hqspi1.Init.ClockPrescaler = 255;
  hqspi1.Init.FifoThreshold = 1;
  hqspi1.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_NONE;
  hqspi1.Init.FlashSize = 25;
  hqspi1.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
  hqspi1.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi1.Init.FlashID = QSPI_FLASH_ID_1;
  hqspi1.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  if (HAL_QSPI_Init(&hqspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN QUADSPI_Init 2 */

  /* USER CODE END QUADSPI_Init 2 */

}

void HAL_QSPI_MspInit(QSPI_HandleTypeDef* qspiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspInit 0 */

  /* USER CODE END QUADSPI_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_QSPI;
    PeriphClkInitStruct.QspiClockSelection = RCC_QSPICLKSOURCE_D1HCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* QUADSPI clock enable */
    __HAL_RCC_QSPI_CLK_ENABLE();

    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**QUADSPI GPIO Configuration
    PF6     ------> QUADSPI_BK1_IO3
    PF7     ------> QUADSPI_BK1_IO2
    PF8     ------> QUADSPI_BK1_IO0
    PF9     ------> QUADSPI_BK1_IO1
    PF10     ------> QUADSPI_CLK
    PB10     ------> QUADSPI_BK1_NCS
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN QUADSPI_MspInit 1 */

  /* USER CODE END QUADSPI_MspInit 1 */
  }
}

void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef* qspiHandle)
{

  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspDeInit 0 */

  /* USER CODE END QUADSPI_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_QSPI_CLK_DISABLE();

    /**QUADSPI GPIO Configuration
    PF6     ------> QUADSPI_BK1_IO3
    PF7     ------> QUADSPI_BK1_IO2
    PF8     ------> QUADSPI_BK1_IO0
    PF9     ------> QUADSPI_BK1_IO1
    PF10     ------> QUADSPI_CLK
    PB10     ------> QUADSPI_BK1_NCS
    */
    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10);

  /* USER CODE BEGIN QUADSPI_MspDeInit 1 */

  /* USER CODE END QUADSPI_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

static uint8_t OWN_QSPI_WriteEnable(void){
    QSPI_CommandTypeDef sCommand;

    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.Instruction = WRITE_ENABLE_CMD;
    sCommand.AddressMode = QSPI_ADDRESS_NONE;
    sCommand.Address = 0;
    sCommand.DataMode = QSPI_DATA_NONE;
    sCommand.DummyCycles = 0;

    if (HAL_QSPI_Command(&hqspi1, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!= HAL_OK) {
        return HAL_ERROR;
    }

    return HAL_OK;
}

static uint8_t OWN_QSPI_AutoPollingMemReady(void){
    QSPI_CommandTypeDef sCommand;
    QSPI_AutoPollingTypeDef sConfig;

    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = READ_STATUS_REG_CMD;
    sCommand.AddressMode = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode = QSPI_DATA_1_LINE;
    sCommand.DummyCycles = 0;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    sConfig.Match = 0x00;
    sConfig.Mask = 0x01;
    sConfig.MatchMode = QSPI_MATCH_MODE_AND;
    sConfig.StatusBytesSize = 1;
    sConfig.Interval = 0x10;
    sConfig.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

    if (HAL_QSPI_AutoPolling(&hqspi1, &sCommand, &sConfig,HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return HAL_ERROR;
    }

    return HAL_OK;
}

static uint8_t OWN_QSPI_Configuration(void){
    QSPI_CommandTypeDef sCommand;
    uint8_t test_buffer = 0 ;

    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = READ_STATUS_REG_CMD;
    sCommand.AddressMode = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode = QSPI_DATA_1_LINE;
    sCommand.DummyCycles = 0;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.NbData = 1;

    if (HAL_QSPI_Command(&hqspi1, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!= HAL_OK) {
        return HAL_ERROR;
    }
    if (HAL_QSPI_Receive(&hqspi1, &test_buffer,HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return HAL_ERROR;
    }

    test_buffer |= 0x42;

    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = WRITE_STATUS_REG_CMD;
    sCommand.AddressMode = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode = QSPI_DATA_1_LINE;
    sCommand.DummyCycles = 0;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.NbData = 1;

    if (HAL_QSPI_Command(&hqspi1, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!= HAL_OK) {
        return HAL_ERROR;
    }

    if (HAL_QSPI_Transmit(&hqspi1, &test_buffer,HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        Error_Handler();
        return HAL_ERROR;
    }
    return HAL_OK;
}

static uint8_t OWN_QSPI_ResetChip(void){
    QSPI_CommandTypeDef sCommand;
    uint8_t temp = 0;

    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = RESET_ENABLE_CMD;
    sCommand.AddressMode = QSPI_ADDRESS_NONE;
    sCommand.DataMode = QSPI_DATA_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.DummyCycles = 0;

    if (HAL_QSPI_Command(&hqspi1, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!= HAL_OK) {
        return HAL_ERROR;
    }
    for (temp = 0; temp < 0x2f; temp++) {
        __NOP();
    }

    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = RESET_EXECUTE_CMD;
    sCommand.AddressMode = QSPI_ADDRESS_NONE;
    sCommand.DataMode = QSPI_DATA_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.DummyCycles = 0;

    if (HAL_QSPI_Command(&hqspi1, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)
        != HAL_OK) {
        return HAL_ERROR;
    }
    return HAL_OK;
}

uint8_t OWN_QSPI_Read_ID(uint8_t* mfID, uint16_t* chipSize){
    QSPI_CommandTypeDef sCommand;
    uint8_t test_buffer[3] = { 0 };

    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = READ_JEDEC_ID_CMD;
    sCommand.AddressMode = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode = QSPI_DATA_1_LINE;
    sCommand.DummyCycles = 0;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.NbData = 3;

    if (HAL_QSPI_Command(&hqspi1, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!= HAL_OK) {
        return HAL_ERROR;
    }
    if (HAL_QSPI_Receive(&hqspi1, test_buffer,HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return HAL_ERROR;
    }

    *mfID = test_buffer[0];
    *chipSize = ((uint16_t)(test_buffer[1]) << 8) | (uint16_t)(test_buffer[2]);

    if(test_buffer[0] == 0x9D && test_buffer[1] == 0x40 && test_buffer[2] == 0x12)
        return 0;
    return 0xFF;
}

uint8_t OWN_QSPI_Init(void){
    uint8_t status = 0;
    if (HAL_QSPI_DeInit(&hqspi1) != HAL_OK) {
        return HAL_ERROR;
    }
    MX_QUADSPI_Init();

    if (OWN_QSPI_ResetChip() != HAL_OK) {
        return HAL_ERROR;
    }

    HAL_Delay(1);

    if (OWN_QSPI_AutoPollingMemReady() != HAL_OK) {
        return HAL_ERROR;
    }

    if (OWN_QSPI_WriteEnable() != HAL_OK) {

        return HAL_ERROR;
    }

    OWN_QSPI_ReadStatus(&status);

    if (OWN_QSPI_Configuration() != HAL_OK) {
        return HAL_ERROR;
    }

    return HAL_OK;
}

uint8_t OWN_QSPI_EraseSector(uint32_t startAddr, uint32_t endAddr){
    QSPI_CommandTypeDef sCommand;

    startAddr = startAddr - startAddr % MEMORY_SECTOR_SIZE;

    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.DataMode = QSPI_DATA_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.Instruction = SECTOR_ERASE_CMD;
    sCommand.DummyCycles = 0;

    while (endAddr >= startAddr) {
        sCommand.Address = (startAddr & 0x0FFFFFFF);

        if (OWN_QSPI_WriteEnable() != HAL_OK) {
            return HAL_ERROR;
        }

        if (HAL_QSPI_Command(&hqspi1, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)
            != HAL_OK) {
            return HAL_ERROR;
        }
        startAddr += MEMORY_SECTOR_SIZE;

        if (OWN_QSPI_AutoPollingMemReady() != HAL_OK) {
            return HAL_ERROR;
        }
    }

    return HAL_OK;
}

uint8_t OWN_QSPI_Tester(void) {
    QSPI_CommandTypeDef sCommand;
    uint8_t status;
    uint8_t read_reg[64] = {0};
    uint8_t write_reg[64] = {0};

    UART_Send_Data("Starting QSPI Test...\r\n");

    // 1. Enable Write Operation
    if (OWN_QSPI_WriteEnable() != HAL_OK) {
        UART_Send_Data("ERROR: QSPI Write Enable Failed!\r\n");
        return HAL_ERROR;
    }
    UART_Send_Data("QSPI Write Enable Success!\r\n");

    // 2. Read and Verify Status Register
    if (OWN_QSPI_ReadStatus(&status) != HAL_OK) {
        UART_Send_Data("ERROR: QSPI Status Register Read Failed!\r\n");
        return HAL_ERROR;
    }
    UART_Send_Data("QSPI Status Register Read: 0x%02X\r\n", status);

    if ((status & 0x7E) != 0x42) {
        UART_Send_Data("ERROR: QSPI Status Incorrect! Expected 0x42, Got 0x%02X\r\n", status);
        return HAL_ERROR;
    }
    UART_Send_Data("QSPI Status Verified (WEL = 1, QE = 1, BPx = 0)\r\n");

    // 3. Erase a Sector (4kB)
    UART_Send_Data("Erasing QSPI Sector at Address: 0x00000000...\r\n");
    if (OWN_QSPI_EraseSector(0, 63) != HAL_OK) {
        UART_Send_Data("ERROR: QSPI Erase Failed!\r\n");
        return HAL_ERROR;
    }
    HAL_Delay(2);
    UART_Send_Data("QSPI Sector Erased Successfully!\r\n");

    // 4. Read Erased Memory
    UART_Send_Data("Reading Erased Data...\r\n");
    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = QUAD_OUT_FAST_READ_CMD;
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.Address = 0;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode = QSPI_DATA_4_LINES;
    sCommand.DummyCycles = 8;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.NbData = 64;

    if (HAL_QSPI_Command(&hqspi1, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        UART_Send_Data("ERROR: QSPI Read Command Failed!\r\n");
        return HAL_ERROR;
    }

    if (HAL_QSPI_Receive(&hqspi1, read_reg, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        UART_Send_Data("ERROR: QSPI Read Receive Failed!\r\n");
        return HAL_ERROR;
    }

    HAL_Delay(2);

    // Print First 16 Bytes of Read Data
    UART_Send_Data("QSPI Read Success! First 16 Bytes: ");
    for (uint8_t i = 0; i < 16; i++) {
        UART_Send_Data("0x%02X ", read_reg[i]);
    }
    UART_Send_Data("\r\n");

    // Check if Erased Successfully
    for (uint8_t i = 0; i < 64; ++i) {
        if (read_reg[i] != 0xFF) {
            UART_Send_Data("ERROR: Erase Verification Failed at Byte %d (Expected 0xFF, Got 0x%02X)\r\n", i, read_reg[i]);
            return HAL_ERROR;
        }
    }
    UART_Send_Data("Erased Verification Passed!\r\n");

    // 5. Write Dummy Data
    UART_Send_Data("Writing Dummy Data to Address: 0x00000000...\r\n");
    for (uint8_t i = 0; i < 64; ++i) {
        write_reg[i] = i;
    }

    if (OWN_QSPI_WriteMemory(write_reg, 0, 64) != HAL_OK) {
        UART_Send_Data("ERROR: QSPI Write Failed!\r\n");
        return HAL_ERROR;
    }

    HAL_Delay(2);
    UART_Send_Data("QSPI Write Success!\r\n");

    // 6. Read Back Data
    UART_Send_Data("Reading Back Written Data...\r\n");
    if (HAL_QSPI_Command(&hqspi1, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        UART_Send_Data("ERROR: QSPI Read Command Failed!\r\n");
        return HAL_ERROR;
    }

    if (HAL_QSPI_Receive(&hqspi1, read_reg, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        UART_Send_Data("ERROR: QSPI Read Receive Failed!\r\n");
        return HAL_ERROR;
    }

    HAL_Delay(2);

    // Print First 16 Bytes of Read Data
    UART_Send_Data("QSPI Read Success! First 16 Bytes: ");
    for (uint8_t i = 0; i < 16; i++) {
        UART_Send_Data("0x%02X ", read_reg[i]);
    }
    UART_Send_Data("\r\n");

    // Verify Data Match
    for (uint8_t i = 0; i < 64; ++i) {
        if (read_reg[i] != write_reg[i]) {
            UART_Send_Data("ERROR: Data Mismatch at Byte %d (Expected 0x%02X, Got 0x%02X)\r\n", i, write_reg[i], read_reg[i]);
            return HAL_ERROR;
        }
    }
    UART_Send_Data("QSPI Test Passed!\r\n");

    return HAL_OK;
}


uint8_t OWN_QSPI_WriteMemory(uint8_t* buffer, uint32_t addr, uint32_t buff_size){
    QSPI_CommandTypeDef sCommand;
    uint32_t end_addr, current_size, current_addr;

    /* Calculation of the size between the write address and the end of the page */
    current_addr = 0;


    //
    while (current_addr <= addr) {
        current_addr += MEMORY_PAGE_SIZE;
    }
    current_size = current_addr - addr;

    /* Check if the size of the data is less than the remaining place in the page */
    if (current_size > buff_size) {
        current_size = buff_size;
    }

    /* Initialize the adress variables */
    current_addr = addr;
    end_addr = addr + buff_size;

    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.Instruction = QUAD_READ_IO_CMD;
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.DataMode = QSPI_DATA_4_LINES;
    sCommand.NbData = buff_size;
    sCommand.Address = addr;
    sCommand.DummyCycles = 0;

    /* Perform the write page by page */
    do {
        sCommand.Address = current_addr;
        sCommand.NbData = current_size;

        if (current_size == 0) {
            return HAL_OK;
        }

        /* Enable write operations */
        if (OWN_QSPI_WriteEnable() != HAL_OK) {
            return HAL_ERROR;
        }

        /* Configure the command */
        if (HAL_QSPI_Command(&hqspi1, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!= HAL_OK) {
            return HAL_ERROR;
        }

        /* Transmission of the data */
        if (HAL_QSPI_Transmit(&hqspi1, buffer, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
            return HAL_ERROR;
        }

        /* Configure automatic polling mode to wait for end of program */
        if (OWN_QSPI_AutoPollingMemReady() != HAL_OK) {
            return HAL_ERROR;
        }

        /* Update the address and size variables for next page programming */
        current_addr += current_size;
        buffer += current_size;
        current_size =((current_addr + MEMORY_PAGE_SIZE) > end_addr) ?(end_addr - current_addr) : MEMORY_PAGE_SIZE;
    } while (current_addr <= end_addr);

    return HAL_OK;
}

uint8_t OWN_QSPI_EnableMemoryMappedMode(void){
    QSPI_CommandTypeDef sCommand;
    QSPI_MemoryMappedTypeDef sMemMappedCfg;

    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.DataMode = QSPI_DATA_4_LINES;
    sCommand.NbData = 0;
    sCommand.Address = 0;
    sCommand.Instruction = QUAD_OUT_FAST_READ_CMD;
    sCommand.DummyCycles = DUMMY_CLOCK_CYCLES_READ_QUAD;

    sMemMappedCfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;

    if (HAL_QSPI_MemoryMapped(&hqspi1, &sCommand, &sMemMappedCfg) != HAL_OK) {
        return HAL_ERROR;
    }
    return HAL_OK;
}

uint8_t OWN_QSPI_ReadStatus(uint8_t* statusReg){
    QSPI_CommandTypeDef sCommand;
    uint8_t test_buffer = 0;

    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = 0x05;
    sCommand.AddressMode = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode = QSPI_DATA_1_LINE;
    sCommand.DummyCycles = 0;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.NbData = 1;

    if (HAL_QSPI_Command(&hqspi1, &sCommand, HAL_QSPI_TIMEOUT_DEFAULT_VALUE)!= HAL_OK) {
        return HAL_ERROR;
    }
    if (HAL_QSPI_Receive(&hqspi1, &test_buffer,HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return HAL_ERROR;
    }

    *statusReg = test_buffer;
    return HAL_OK;
}



/* USER CODE END 1 */
