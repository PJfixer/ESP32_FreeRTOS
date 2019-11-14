

#include "adc.h"

uint16_t Flexsensor = 0;
extern SemaphoreHandle_t Flexsensor_mut;


void ADC_task(void *args) {
	(void)args;
	
	adc1_config_width(ADC_WIDTH_BIT_10);
	adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_11);   //gpio 36 3.3v
	for(;;)
	{
		xSemaphoreTake(Flexsensor_mut,0);
		Flexsensor = adc1_get_raw(ADC1_CHANNEL_0);
		xSemaphoreGive(Flexsensor_mut);
		vTaskDelay(200 / portTICK_PERIOD_MS);
		esp_task_wdt_reset();
	}
}
