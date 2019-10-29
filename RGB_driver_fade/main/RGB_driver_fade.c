/* PWM example
   This example code is in the Public Domain (or CC0 licensed, at your option.)

*/

#include <stdio.h>

#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_task_wdt.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"


#include "RGB.h"






QueueHandle_t RGB_task_queue;

void app_main()
{
	
	TaskHandle_t RGB_task_handle;
	RGB_task_queue = xQueueCreate(1,sizeof(uint8_t));
	xTaskCreate(RGB_task,"RGB_Fade",4096,&RGB_task_queue,configMAX_PRIORITIES-1,&RGB_task_handle);
	ESP_ERROR_CHECK(esp_task_wdt_add(RGB_task_handle));
	
	while(1)
	{
		uint8_t i;
		for(i=0;i<14;i++)
		{
			printf("i : %d \n",i);
			xQueueSend(RGB_task_queue,(void *)&i,0);
			vTaskDelay(3000 / portTICK_PERIOD_MS);
		}
	}
	
}



