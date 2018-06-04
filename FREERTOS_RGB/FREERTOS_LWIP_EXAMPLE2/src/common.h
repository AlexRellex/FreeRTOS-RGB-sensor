/*
 * common.h
 *
 * Created: 11/05/2018 11:41:07
 *  Author: practiques
 */ 

#ifndef COMMON_H_
#define COMMON_H_


/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Random important (or not) stuff */
#include "dip204.h"
#include "intc.h"
#include "gpio.h"
#include "pm.h"
#include "delay.h"
#include "spi.h"
#include "conf_clock.h"

/* Priority definitions for most of the tasks in the demo application. */
#define mainLED_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1 )
#define mainETH_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1 )

#define mainLCDTEST_PERIOD          ( ( portTickType ) 100 / portTICK_RATE_MS  )

typedef struct {
	uint16_t r, g, b;
}RGBPoint;
	
typedef struct {
	RGBPoint point;
	float lux;
}processed_data_t;

xQueueHandle sensor_data;
xQueueHandle processed_data;

void display_init(U32);

#endif /* COMMON_H_ */