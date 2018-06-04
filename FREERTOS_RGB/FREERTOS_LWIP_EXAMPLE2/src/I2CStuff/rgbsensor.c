/*
 * rgbsensor.c
 *
 * Created: 11/05/2018 12:36:18
 *  Author: practiques
 */ 
#include "rgbsensor.h"

bool rgb_reset() {
	// Reset all registers
	uint8_t data = 0x00;
	uint8_t data_tmp = 0;
	// Reset registers
	write8(DEVICE_ID, 0x46);
	// Check reset
	read8(CONFIG_1, &data);
	read8(CONFIG_2, &data_tmp);
	data |= data_tmp;
	read8(CONFIG_3, &data_tmp);
	data |= data_tmp;
	read8(STATUS, &data_tmp);
	data |= data_tmp;
	if (data != 0x00)
	{
		return false;
	}
	return true;
}

bool rgb_config(uint8_t config1, uint8_t config2, uint8_t config3) {
	uint8_t data = 0x00;
	  
	// Set 1st configuration register
	write8(CONFIG_1, config1);
	// Set 2nd configuration register
	write8(CONFIG_2, config2);
	// Set 3rd configuration register
	write8(CONFIG_3, config3);
	
	read8(CONFIG_1, &data);
	
	if (data != config1)
	{
		return false;
	}
	read8(CONFIG_2, &data);
	if (data != config2)
	{
		return false;
	}
	read8(CONFIG_3, &data);
	if (data != config3)
	{
		return false;
	}
	return true;
}


bool rgb_init() {
	uint8_t data = 0;
	read8(DEVICE_ID, &data);
	if (data != 0x7D) return false;
	if (!rgb_reset()) return false;
	if (!rgb_config(CFG1_MODE_RGB | CFG1_10KLUX, CFG2_IR_ADJUST_HIGH, CFG_DEFAULT)) return false;
	return true;
}

void read_green(uint16_t *data) {
	read16(GREEN_L, data);
}

void read_blue(uint16_t *data) {
	read16(BLUE_L, data);
}

void read_red(uint16_t *data) {
	read16(RED_L, data);
}

void get_rgb(RGBPoint *data) {
	uint16_t r, g, b;
	read_red(&r);
	read_blue(&b);
	read_green(&g);
	data->r = r;
	data->g = g;
	data->b = b;
}