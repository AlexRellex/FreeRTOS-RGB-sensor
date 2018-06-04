/*
 * processingtask.c
 *
 * Created: 11/05/2018 12:13:24
 *  Author: practiques
 */

#include "processingtask.h"

void my_processing_task(void* p)
{
	RGBPoint point;
	
	while(1) {
		xQueueReceive(sensor_data, &point, portMAX_DELAY);
		
		point.r = (point.r >> 8) & 0xff;
		point.g = (point.g >> 8) & 0xff;
		point.b = (point.b >> 8) & 0xff;
		float lux = (point.r + point.g + point.b) / 3;
		processed_data_t pd;
		pd.lux = lux;
		pd.point = point;
		xQueueSend(processed_data, &pd, portMAX_DELAY);
	}
}