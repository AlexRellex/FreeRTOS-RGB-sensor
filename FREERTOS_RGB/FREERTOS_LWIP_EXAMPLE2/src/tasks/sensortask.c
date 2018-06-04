/*
 * sensortask.c
 *
 * Created: 11/05/2018 11:33:37
 *  Author: practiques
 */ 

#include "sensortask.h"
#include "rgbsensor.h"

void mysensortask(void *p)
{
	uint8_t i = 0;
	uint8_t status;
	
	display_init(FOSC0*8);
	//display_init(configCPU_CLOCK_HZ);
	
	
	I2C_Init();
	if (!rgb_init()) {
		dip204_printf_string("ERROR RGB INIT");
		while(1) ;
	}
	
	
	
	while (1) {
		uint8_t data = i++;
		RGBPoint point;
		get_rgb(&point);
		
		if (i % 100000) xQueueSend(sensor_data, &point, portMAX_DELAY);
		vTaskDelay(mainLCDTEST_PERIOD);
	}
}