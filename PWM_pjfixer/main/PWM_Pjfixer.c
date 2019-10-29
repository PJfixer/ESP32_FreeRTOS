/* i2c scanner
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





TaskHandle_t RGB_task_handle;


void app_main()
{
	
	
	xTaskCreate(RGB_task,"RGB_Fade",2048,NULL,configMAX_PRIORITIES-1,&RGB_task_handle);
	ESP_ERROR_CHECK(esp_task_wdt_add(RGB_task_handle));
	
}



