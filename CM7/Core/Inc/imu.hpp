/*
 * imu.hpp
 *
 *  Created on: Jun 10, 2023
 *      Author: Csurleny
 */

#pragma once

#include "main.h"

namespace driver{

	namespace settings{
		struct imu_config{
			I2C_HandleTypeDef* i2c;
			GPIO_TypeDef* gyro_drdy_port;
			uint16_t  gyro_drdy_pin;
		};

		constexpr uint8_t GYRO_ADDR = 0xD2;

		typedef enum{
			GYRO_WHO_AM_I		=	0x0F,
			GYRO_CTRL_REG1		=	0x20,
			GYRO_CTRL_REG2		=	0x21,
			GYRO_CTRL_REG3		=	0x22,
			GYRO_CTRL_REG4		=	0x23,
			GYRO_CTRL_REG5		=	0x24,
			GYRO_REFERENCE		=	0x25,
			GYRO_OUT_TEMP		=	0x26,
			GYRO_STATUS_REG 	=	0x27,
			GYRO_OUT_X_L		=	0x28,
			GYRO_OUT_X_H		=	0x29,
			GYRO_OUT_Y_L		=	0x2A,
			GYRO_OUT_Y_H		=	0x2B,
			GYRO_OUT_Z_L		=	0x2C,
			GYRO_OUT_Z_H		=	0x2D,
			GYRO_FIFO_CTRL_REG	=	0x2E,
			GYRO_FIFO_SRC_REG	=	0x2F,
			GYRO_INT1_CFG		= 	0x30,
			GYRO_INT1_SRC		= 	0x31,
			GYRO_INT1_TSH_XH	=	0x32,
			GYRO_INT1_TSH_XL	=	0x33,
			GYRO_INT1_TSH_YH	=	0x34,
			GYRO_INT1_TSH_YL	=	0x35,
			GYRO_INT1_TSH_ZH	=	0x36,
			GYRO_INT1_TSH_ZL	=	0x37,
			GYRO_INT1_DURATION	= 	0x38
		}GYRO_REG;

		typedef enum{
			GYRO_DR_95HZ	=	(0x00 << 6),
			GYRO_DR_190HZ	=	(0x01 << 6),
			GYRO_DR_380HZ	=	(0x02 << 6),
			GYRO_DR_760HZ   =	(0x03 << 6)
		}GYRO_DR;

		typedef enum{
			GYRO_BW_LOW		=	(0x00 << 4),
			GYRO_BW_LMID	=	(0x01 << 4),
			GYRO_BW_HMID	=	(0x02 << 4),
			GYRO_BW_HIGH	=	(0x03 << 4)
		}GYRO_BW;

		typedef enum{
			GYRO_AX_EN	=	(0x01 << 1),
			GYRO_AY_EN 	=	(0x01 << 0),
			GYRO_AZ_EN  = 	(0x01 << 2),
		}GYRO_AXIS_EN;

		constexpr uint8_t GYRO_PD_ON = (1 << 3);

		constexpr uint8_t GYRO_ID = 0xD4;

		constexpr uint8_t MAG_ADDR = 0x3C;

		typedef enum{
			MAG_CRA_REG		=	0x00,
			MAG_CRB_REG		=	0x01,
			MAG_MR_REG		=	0x02,
			MAG_OUT_X_H		=	0x03,
			MAG_OUT_X_L		=	0x04,
			MAG_OUT_Y_H		=	0x05,
			MAG_OUT_Y_L		=	0x06,
			MAG_OUT_Z_H		=	0x07,
			MAG_OUT_Z_L		=	0x08,
			MAG_SR_REG		=	0x09,
			MAG_IRA_REG		=	0x0A,
			MAG_IRB_REG		=	0x0B,
			MAG_IRC_REG		=	0x0C,
			MAG_TEMP_OUT_H	=	0x31,
			MAG_TMEP_OUT_L	=	0x32
		}MAG_REG;

		typedef enum{
			MAG_DR_0HZ75	=	(0x00 << 2),
			MAG_DR_1HZ5		=	(0x01 << 2),
			MAG_DR_3HZ		=	(0x02 << 2),
			MAG_DR_7HZ5   	=	(0x03 << 2),
			MAG_DR_15HZ		=	(0x04 << 2),
			MAG_DR_30HZ		=	(0x05 << 2),
			MAG_DR_75HZ		=	(0x06 << 2),
			MAG_DR_220HZ   	=	(0x07 << 2)
		}MAG_DR;

		typedef enum{
			MAG_GN_1G3		=	(0x01 << 5),	// +-1.3Gauss, Gain 1100
			MAG_GN_1G9		=	(0x02 << 5),	// +-1.9Gauss, Gain 855
			MAG_GN_2G5   	=	(0x03 << 5),	// +-2.5Gauss, Gain 670
			MAG_GN_4G0		=	(0x04 << 5),	// +-4.0Gauss, Gain 450
			MAG_GN_4G7		=	(0x05 << 5),	// +-4.7Gauss, Gain 400
			MAG_GN_5G6		=	(0x06 << 5),	// +-5.6Gauss, Gain 330
			MAG_GN_8G1   	=	(0x07 << 5)		// +-8.1Gauss, Gain 230
		}MAG_GN;

		constexpr uint8_t ACCEL_ADDR = 0x32;

		typedef enum{
			ACCEL_CTRL_REG1	=	0x20,
			ACCEL_CTRL_REG2	=	0x21,
			ACCEL_CTRL_REG3	=	0x22,
			ACCEL_CTRL_REG4	=	0x23,
			ACCEL_CTRL_REG5	=	0x24,
			ACCEL_CTRL_REG6	=	0x25,
			ACCEL_REFERENCE = 	0x26,
			ACCEL_STATUS	=	0x27,
			ACCEL_OUT_X_L	=	0x28,
			ACCEL_OUT_X_H	=	0x29,
			ACCEL_OUT_Y_L	=	0x2A,
			ACCEL_OUT_Y_H	=	0x2B,
			ACCEL_OUT_Z_L	=	0x2C,
			ACCEL_OUT_Z_H	=	0x2D,
			ACCEL_FIFO_CTRL	=	0x2E,
			ACCEL_FIFO_SRC	= 	0x2F,
			ACCEL_INT1_CFG	=	0x30,
			ACCEL_INT1_SRC	=	0x31,
			ACCEL_INT1_THS 	=	0x32,
			ACCEL_INT1_DUR	=	0x33,
			ACCEL_INT2_CFG	=	0x34,
			ACCEL_INT2_SRC	=	0x35,
			ACCEL_INT2_THS 	=	0x36,
			ACCEL_INT2_DUR	=	0x37,
			ACCEL_CLICK_CFG =	0x38,
			ACCEL_CLICK_SRC	=	0x39,
			ACCEL_CLICK_THS	=	0x3A
		}ACCEL_REG;

		typedef enum{
			ACCEL_DR_PDN   			=	(0x00 << 4),
			ACCEL_DR_1HZ			=	(0x01 << 4),
			ACCEL_DR_10HZ			=	(0x02 << 4),
			ACCEL_DR_25HZ			=	(0x03 << 4),
			ACCEL_DR_50HZ   		=	(0x04 << 4),
			ACCEL_DR_100HZ			=	(0x05 << 4),
			ACCEL_DR_200HZ			=	(0x06 << 4),
			ACCEL_DR_400HZ			=	(0x07 << 4),
			ACCEL_DR_1620HZ   		=	(0x08 << 4),
			ACCEL_DR_1344_5376HZ	=	(0x09 << 4)
		}ACCEL_DR;

		constexpr uint8_t ACCEL_LP_EN = 0x01 << 3;

		typedef enum{
			ACCEL_AX_EN	=	(0x01 << 0),
			ACCEL_AY_EN =	(0x01 << 1),
			ACCEL_AZ_EN  = 	(0x01 << 2)
		}ACCEL_AXIS_EN;
	}

	class imu{

	public:
		imu(I2C_HandleTypeDef *i2c, GPIO_TypeDef* gyro_drdy_port, uint16_t gyro_drdy_pin);
		~imu();
		uint8_t getTemperature();
		void getGyro(int16_t *resV);
		void getMag(int16_t *resV);
		void getAccel(int16_t *resV);
		uint8_t readRefGyro(void);
	private:
		settings::imu_config imu_conf;

		uint8_t i2c_readData(uint16_t addr, uint8_t reg);
		void i2c_writeData(uint16_t addr, uint8_t reg, uint8_t val);
	};
}
