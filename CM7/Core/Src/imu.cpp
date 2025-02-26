#include "imu.hpp"
#include <stdio.h>

namespace driver{

imu::imu(I2C_HandleTypeDef *i2c, GPIO_TypeDef* gyro_drdy_port, uint16_t gyro_drdy_pin){
	uint8_t temp_reg;
	imu_conf.i2c = i2c;
	imu_conf.gyro_drdy_port = gyro_drdy_port;
	imu_conf.gyro_drdy_pin = gyro_drdy_pin;

	// Gyro setup
	uint8_t value;
	value = i2c_readData(settings::GYRO_ADDR, settings::GYRO_WHO_AM_I);
	// Highpass filter - Normal mode, 0.09Hz
	i2c_writeData(settings::GYRO_ADDR, settings::GYRO_CTRL_REG2, 0x09);
	// Disable interrupts, enable data ready flag
	i2c_writeData(settings::GYRO_ADDR, settings::GYRO_CTRL_REG3, 0x08);
	// Scale selection 500dps, block data update until data is read
	i2c_writeData(settings::GYRO_ADDR, settings::GYRO_CTRL_REG4, 0x90);
	// No FIFO, no mem reboot, enable high-pass filter
	// LP1 0b00, LP1+HP 0b01, LP1+HP+LP2 0b10/0b11
	i2c_writeData(settings::GYRO_ADDR, settings::GYRO_CTRL_REG5, 0x13);
	// Set data rate, bandwidth, and enable channels
	temp_reg = settings::GYRO_DR_760HZ | settings::GYRO_BW_HIGH | settings::GYRO_PD_ON
			| settings::GYRO_AX_EN | settings::GYRO_AY_EN | settings::GYRO_AZ_EN;
	i2c_writeData(settings::GYRO_ADDR, settings::GYRO_CTRL_REG1, temp_reg);

	// Mag setup
	// temperature sensor on, 220Hz data rate
	temp_reg = settings::MAG_DR_220HZ | 0x80;
	i2c_writeData(settings::MAG_ADDR, settings::MAG_CRA_REG, temp_reg);
	// gain settings
	temp_reg = settings::MAG_GN_1G3;
	i2c_writeData(settings::MAG_ADDR, settings::MAG_CRB_REG, temp_reg);
	// enable continuous conversion
	i2c_writeData(settings::MAG_ADDR, settings::MAG_MR_REG, 0);
	// read dummy addr
	value = i2c_readData(settings::MAG_ADDR, settings::MAG_IRA_REG);
	value = i2c_readData(settings::MAG_ADDR, settings::MAG_IRB_REG);
	value = i2c_readData(settings::MAG_ADDR, settings::MAG_IRC_REG);

	// Accel setup
	temp_reg = settings::ACCEL_DR_100HZ | settings::ACCEL_AX_EN | settings::ACCEL_AY_EN | settings::ACCEL_AZ_EN;
	i2c_writeData(settings::ACCEL_ADDR, settings::ACCEL_CTRL_REG1, temp_reg);
	i2c_writeData(settings::ACCEL_ADDR, settings::ACCEL_CTRL_REG2, 0);
	// Set DRDY1 source to INT1
	i2c_writeData(settings::ACCEL_ADDR, settings::ACCEL_CTRL_REG3, 0x10);
	// 0x00 Set Hi-res mode off -- 0x08 Hi-res mode on
	i2c_writeData(settings::ACCEL_ADDR, settings::ACCEL_CTRL_REG4, 0x88);
	i2c_writeData(settings::ACCEL_ADDR, settings::ACCEL_CTRL_REG5, 0);
	i2c_writeData(settings::ACCEL_ADDR, settings::ACCEL_CTRL_REG6, 0);

}

imu::~imu(){
	// Shut down gyro
	i2c_writeData(settings::GYRO_ADDR, settings::GYRO_CTRL_REG1, 0);
	// Shut down magneto
	i2c_writeData(settings::MAG_ADDR, settings::MAG_CRA_REG, 0);
	i2c_writeData(settings::MAG_ADDR, settings::MAG_MR_REG, 0x03);
	//Shut down Accel
	i2c_writeData(settings::ACCEL_ADDR, settings::ACCEL_CTRL_REG1, 0);
}

uint8_t imu::i2c_readData(uint16_t addr, uint8_t reg){
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t value = 0;
	status = HAL_I2C_Mem_Read(imu_conf.i2c, addr, reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 0x10000);
	if(status != HAL_OK)
		__asm("NOP");
	return value;
}

void imu::i2c_writeData(uint16_t addr, uint8_t reg, uint8_t val){
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Write(imu_conf.i2c, addr, (uint16_t) reg, I2C_MEMADD_SIZE_8BIT, &val, 1, 0x1000);
	if(status != HAL_OK)
		__asm("NOP");
}

uint8_t imu::getTemperature(){
	uint8_t temp_reg;
	temp_reg = i2c_readData(settings::GYRO_ADDR, settings::GYRO_OUT_TEMP);
	return temp_reg;
}

void imu::getAccel(int16_t *resV){
	uint8_t temp_reg[6];
	int16_t raw_data[3];

	temp_reg[0] = i2c_readData(settings::ACCEL_ADDR, settings::ACCEL_OUT_X_L);
	temp_reg[1] = i2c_readData(settings::ACCEL_ADDR, settings::ACCEL_OUT_X_H);
	temp_reg[2] = i2c_readData(settings::ACCEL_ADDR, settings::ACCEL_OUT_Y_L);
	temp_reg[3] = i2c_readData(settings::ACCEL_ADDR, settings::ACCEL_OUT_Y_H);
	temp_reg[4] = i2c_readData(settings::ACCEL_ADDR, settings::ACCEL_OUT_Z_L);
	temp_reg[5] = i2c_readData(settings::ACCEL_ADDR, settings::ACCEL_OUT_Z_H);

	raw_data[0] = (int16_t)(((uint16_t)temp_reg[1] << 8) + temp_reg[0]);
	raw_data[1] = (int16_t)(((uint16_t)temp_reg[3] << 8) + temp_reg[2]);
	raw_data[2] = (int16_t)(((uint16_t)temp_reg[5] << 8) + temp_reg[4]);

	resV[0] = raw_data[0];
	resV[1] = raw_data[1];
	resV[2] = raw_data[2];
}

void imu::getGyro(int16_t *resV){
	uint8_t temp_reg[6];
	int16_t raw_data[3];

	temp_reg[0] = i2c_readData(settings::GYRO_ADDR, settings::GYRO_OUT_X_L);
	temp_reg[1] = i2c_readData(settings::GYRO_ADDR, settings::GYRO_OUT_X_H);
	temp_reg[2] = i2c_readData(settings::GYRO_ADDR, settings::GYRO_OUT_Y_L);
	temp_reg[3] = i2c_readData(settings::GYRO_ADDR, settings::GYRO_OUT_Y_H);
	temp_reg[4] = i2c_readData(settings::GYRO_ADDR, settings::GYRO_OUT_Z_L);
	temp_reg[5] = i2c_readData(settings::GYRO_ADDR, settings::GYRO_OUT_Z_H);

	raw_data[0] = (int16_t)(((uint16_t)temp_reg[1] << 8) + temp_reg[0]);
	raw_data[1] = (int16_t)(((uint16_t)temp_reg[3] << 8) + temp_reg[2]);
	raw_data[2] = (int16_t)(((uint16_t)temp_reg[5] << 8) + temp_reg[4]);

	resV[0] = raw_data[0];
	resV[1] = raw_data[1];
	resV[2] = raw_data[2];
}

uint8_t imu::readRefGyro(void){
	uint8_t temp;
	temp = i2c_readData(settings::GYRO_ADDR, settings::GYRO_REFERENCE);
	return temp;
}

void imu::getMag(int16_t *resV){
	uint8_t temp_reg[6];
	temp_reg[0] = i2c_readData(settings::MAG_ADDR, settings::MAG_OUT_X_H);
	temp_reg[1] = i2c_readData(settings::MAG_ADDR, settings::MAG_OUT_X_L);
	temp_reg[2] = i2c_readData(settings::MAG_ADDR, settings::MAG_OUT_Y_H);
	temp_reg[3] = i2c_readData(settings::MAG_ADDR, settings::MAG_OUT_Y_L);
	temp_reg[4] = i2c_readData(settings::MAG_ADDR, settings::MAG_OUT_Z_H);
	temp_reg[5] = i2c_readData(settings::MAG_ADDR, settings::MAG_OUT_Z_L);

	resV[0] = (int16_t)(((uint16_t)temp_reg[0] << 8) + temp_reg[1]);
	resV[1] = (int16_t)(((uint16_t)temp_reg[2] << 8) + temp_reg[3]);
	resV[2] = (int16_t)(((uint16_t)temp_reg[4] << 8) + temp_reg[5]);
}

}
