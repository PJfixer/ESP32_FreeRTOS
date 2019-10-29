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
#include "adc.h"
#include "bt_spp.h"




extern uint16_t Flexsensor;

SemaphoreHandle_t Flexsensor_mut;

QueueHandle_t RGB_task_queue;



void app_main()
{
	 esp_err_t ret = nvs_flash_init();
    	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    	}
    	ESP_ERROR_CHECK( ret );
	
	init_bt();

	Flexsensor_mut = xSemaphoreCreateMutex() ;
	
	TaskHandle_t RGB_task_handle;
	TaskHandle_t ADC_task_handle;
	
	
	
	RGB_task_queue = xQueueCreate(1,sizeof(uint8_t));
	xTaskCreate(RGB_task,"RGB_Fade",4096,NULL,configMAX_PRIORITIES-3,&RGB_task_handle);
	ESP_ERROR_CHECK(esp_task_wdt_add(RGB_task_handle));
	
	xTaskCreate(ADC_task,"ADC_sample",1024,NULL,configMAX_PRIORITIES-2,&ADC_task_handle);
	ESP_ERROR_CHECK(esp_task_wdt_add(ADC_task_handle));
	
	

	
	
	uint8_t i = 2;
	xQueueSend(RGB_task_queue,(void *)&i,0);
	
	

}



