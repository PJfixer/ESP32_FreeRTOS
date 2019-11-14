
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "serial.h"
#include "vesc.h"


extern dataPackage data; 
extern nunchuckPackage nunchuck; 

void app_main()
{
	init_uart();
	while(1)
	{
		getVescValues();
		printf("tachometer 1 : %ld ",data.tachometer);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		getVescValuesfwd(90);
		printf("tachometer 2 : %ld ",data.tachometer);
		vTaskDelay(4000 / portTICK_PERIOD_MS);
	}
}
