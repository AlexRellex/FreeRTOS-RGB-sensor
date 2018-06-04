/*
 * ledtask.c
 *
 * Created: 11/05/2018 12:02:47
 *  Author: els alumnes més macos del mon :3
 */ 

#include "ledtask.h"

void myLEDtask(void* p)
{
	processed_data_t pd;

	
	while(1) {
		xQueueReceive(processed_data, &pd, portMAX_DELAY);
		RGBPoint point = pd.point;
		dip204_set_cursor_position(1, 1);
		dip204_printf_string("R: %03hu", point.r);
		dip204_set_cursor_position(1, 2);
		dip204_printf_string("G: %03hu", point.g);
		dip204_set_cursor_position(1, 3);
		dip204_printf_string("B: %03hu", point.b);
		
		float lux = pd.lux;
		LED_Off(LED0 | LED1 | LED2 | LED3 | LED5 | LED6 | LED7);
		float chunk = 256 / 6;
		if (lux > chunk*6) {
			LED_On(LED7);
		}
		if (lux > chunk*5) {
			LED_On(LED6);
		}
		if (lux > chunk*4) {
			LED_On(LED5);
		}
		if (lux > chunk*3) {
			LED_On(LED3);
		}
		if (lux > chunk*2) {
			LED_On(LED2);
		}
		if (lux > chunk) {
			LED_On(LED1);
		}		
	}
}