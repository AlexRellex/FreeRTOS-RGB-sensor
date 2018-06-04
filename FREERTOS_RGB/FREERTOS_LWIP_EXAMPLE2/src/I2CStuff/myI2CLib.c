
#include "myI2CLib.h"

static const gpio_map_t TWI_GPIO_MAP =
{
	{AVR32_TWI_SDA_0_0_PIN, AVR32_TWI_SDA_0_0_FUNCTION},
	{AVR32_TWI_SCL_0_0_PIN, AVR32_TWI_SCL_0_0_FUNCTION}
};
twi_options_t opt;

static xSemaphoreHandle I2CMutex;

bool I2C_readRegister(uint8_t dev_addr, uint8_t reg_addr, uint8_t* data, size_t len) {

	int status;
	twi_package_t packet;
	
	packet.chip = dev_addr;
	packet.addr_length = 1;
	packet.length = len;
	packet.addr[0] = reg_addr;
	packet.buffer = data;

	xSemaphoreTake(I2CMutex, portMAX_DELAY);
	// perform a read access
	status = twi_master_read(&AVR32_TWI, &packet);
	
	xSemaphoreGive(I2CMutex);
	
	if (status == TWI_SUCCESS) {
		return true;
		} else {
		return false;
	}
}

bool read8(uint8_t reg_addr, uint8_t* data) {
	uint8_t dev_addr = RGB_SENSOR;
	return I2C_readRegister(dev_addr, reg_addr, data, 1);
}

bool read16(uint8_t reg_addr, uint16_t* data) {
	uint8_t dev_addr = RGB_SENSOR;
	return I2C_readRegister(dev_addr, reg_addr, (uint8_t*)data, 2);
}


bool I2C_writeRegister(uint8_t dev_addr, uint8_t reg_addr, uint8_t data) {
	int status;
	twi_package_t packet;
	
	packet.chip = dev_addr;
	packet.addr_length = 1;
	packet.length = 1;
	packet.addr[0] = reg_addr;
	packet.buffer = &data;

	xSemaphoreTake(I2CMutex, portMAX_DELAY);
	
	// perform a read access
	status = twi_master_write(&AVR32_TWI, &packet);
	
	xSemaphoreGive(I2CMutex);
	
	if (status == TWI_SUCCESS) {
		return true;
		} else {
		return false;
	}
}

bool write8(uint8_t reg_addr, uint8_t data) {
	uint8_t dev_addr = RGB_SENSOR;
	return I2C_writeRegister(dev_addr, reg_addr, data);
}

void I2C_Init() {
	int status;
	
	// TWI gpio pins configuration
	gpio_enable_module(TWI_GPIO_MAP, sizeof(TWI_GPIO_MAP) / sizeof(TWI_GPIO_MAP[0]));


	// options settings
	opt.pba_hz = FOSC0;
	opt.speed = TWI_SPEED;
	opt.chip = GESTURE_ADDR;
	status = twi_master_init(&AVR32_TWI, &opt);

	if (status == TWI_SUCCESS)
	{
		// display test result to user
		dip204_printf_string("TWI OK\r\n");
	}
	else
	{
		dip204_printf_string("TWI ERROR\r\n");
	}
	
	I2CMutex = xSemaphoreCreateMutex();
}