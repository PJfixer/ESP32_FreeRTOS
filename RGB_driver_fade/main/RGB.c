

#include "RGB.h"



extern QueueHandle_t RGB_task_queue;

void RGB_task(void *args) {
	(void)args;
	
	ledc_timer_config_t conf_timer;
	conf_timer.speed_mode = LEDC_HIGH_SPEED_MODE;
	conf_timer.duty_resolution = LEDC_TIMER_8_BIT;
	conf_timer.timer_num = LEDC_TIMER_0;
	conf_timer.freq_hz = 1000 ;
	//conf_timer.clk_cfg = LEDC_AUTO_CLK;
	if(ledc_timer_config(&conf_timer) == ESP_OK)
	{
		printf("led driver inited \n");
	}
	else
	{
		printf("led driver init failed \n");
	}
	ledc_channel_config_t chan1; //red
	chan1.gpio_num = 25;
	chan1.speed_mode = LEDC_HIGH_SPEED_MODE;
	chan1.channel = LEDC_CHANNEL_0;
	chan1.intr_type = LEDC_INTR_DISABLE;
	chan1.timer_sel = LEDC_TIMER_0;
	chan1.duty = 0 ;
	chan1.hpoint = 0;
	ledc_channel_config_t chan2; // blue
	chan2.gpio_num = 26;
	chan2.speed_mode = LEDC_HIGH_SPEED_MODE;
	chan2.channel = LEDC_CHANNEL_1;
	chan2.intr_type = LEDC_INTR_DISABLE;
	chan2.timer_sel = LEDC_TIMER_0;
	chan2.duty = 0 ;
	chan2.hpoint = 0;
	ledc_channel_config_t chan3; // green
	chan3.gpio_num = 27;
	chan3.speed_mode = LEDC_HIGH_SPEED_MODE;
	chan3.channel = LEDC_CHANNEL_2;
	chan3.intr_type = LEDC_INTR_DISABLE;
	chan3.timer_sel = LEDC_TIMER_0;
	chan3.duty = 0 ;
	chan3.hpoint = 0;
	if(ledc_channel_config(&chan1) == ESP_FAIL)
	{
		printf("led channel 1 failed \n");
	}
	if(ledc_channel_config(&chan2) == ESP_FAIL)
	{
		printf("led channel 2 failed \n");
	}
	if(ledc_channel_config(&chan3) == ESP_FAIL)
	{
		printf("led channel 3 failed \n");
	}
	
	ledc_fade_func_install(0);
	
	uint8_t buf ; 

	for(;;)
	{
			xQueueReceive(RGB_task_queue,&buf,0);
			
			switch(buf)
			{
				case BLUE_FADE:
					ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE,1,255,1000);
					ledc_fade_start(LEDC_HIGH_SPEED_MODE,1,1);
					ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE,1,0,1000);
					ledc_fade_start(LEDC_HIGH_SPEED_MODE,1,1);
					vTaskDelay(10 / portTICK_PERIOD_MS);
					esp_task_wdt_reset();
				break;
				case GREEN_FADE:
					ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE,2,255,1000);
					ledc_fade_start(LEDC_HIGH_SPEED_MODE,2,1);
					ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE,2,0,1000);
					ledc_fade_start(LEDC_HIGH_SPEED_MODE,2,1);
					vTaskDelay(10 / portTICK_PERIOD_MS);
					esp_task_wdt_reset();
				break;
				case RED_FADE:
					ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE,0,255,1000);
					ledc_fade_start(LEDC_HIGH_SPEED_MODE,0,1);
					ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE,0,0,1000);
					ledc_fade_start(LEDC_HIGH_SPEED_MODE,0,1);
					vTaskDelay(10 / portTICK_PERIOD_MS);
					esp_task_wdt_reset();
				case YELLOW_FADE:
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,1,0);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,1);
					ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE,0,255,1000);
					ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE,2,255,1000);
					ledc_fade_start(LEDC_HIGH_SPEED_MODE,0,0);
					ledc_fade_start(LEDC_HIGH_SPEED_MODE,2,1);
					ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE,0,0,1000);
					ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE,2,0,1000);
					ledc_fade_start(LEDC_HIGH_SPEED_MODE,0,0);
					ledc_fade_start(LEDC_HIGH_SPEED_MODE,2,1);
					vTaskDelay(10 / portTICK_PERIOD_MS);
					esp_task_wdt_reset();
				break;
				case PURPLE_FADE:
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,2,0);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,2);
					ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE,0,255,1000);
					ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE,1,255,1000);
					ledc_fade_start(LEDC_HIGH_SPEED_MODE,0,0);
					ledc_fade_start(LEDC_HIGH_SPEED_MODE,1,1);
					ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE,0,0,1000);
					ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE,1,0,1000);
					ledc_fade_start(LEDC_HIGH_SPEED_MODE,0,0);
					ledc_fade_start(LEDC_HIGH_SPEED_MODE,1,1);
					vTaskDelay(10 / portTICK_PERIOD_MS);
					esp_task_wdt_reset();
				break;
				case CYAN_FADE:
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,0,0);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,0);
					ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE,2,255,1000);
					ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE,1,255,1000);
					ledc_fade_start(LEDC_HIGH_SPEED_MODE,2,0);
					ledc_fade_start(LEDC_HIGH_SPEED_MODE,1,1);
					ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE,2,0,1000);
					ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE,1,0,1000);
					ledc_fade_start(LEDC_HIGH_SPEED_MODE,2,0);
					ledc_fade_start(LEDC_HIGH_SPEED_MODE,1,1);
					vTaskDelay(10 / portTICK_PERIOD_MS);
					esp_task_wdt_reset();
				break;
				case BLUE:
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,1,255);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,1);
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,0,0);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,0);
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,2,0);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,2);
					vTaskDelay(10 / portTICK_PERIOD_MS);
					esp_task_wdt_reset();
					break;
				case GREEN:
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,2,255);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,2);
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,1,0);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,1);
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,0,0);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,0);
					vTaskDelay(10 / portTICK_PERIOD_MS);
					esp_task_wdt_reset();
				break;
				case RED:
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,0,255);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,0);
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,1,0);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,1);
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,2,0);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,2);
					vTaskDelay(10 / portTICK_PERIOD_MS);
					esp_task_wdt_reset();
				break;
				case CYAN:
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,1,255);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,1);
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,2,255);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,2);
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,0,0);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,0);
					vTaskDelay(10 / portTICK_PERIOD_MS);
					esp_task_wdt_reset();
				break;
				case YELLOW:
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,1,0);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,1);
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,2,255);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,2);
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,0,255);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,0);
					vTaskDelay(10 / portTICK_PERIOD_MS);
					esp_task_wdt_reset();
				break;
				case PURPLE:
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,1,255);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,1);
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,0,255);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,0);
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,2,0);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,2);
					vTaskDelay(10 / portTICK_PERIOD_MS);
					esp_task_wdt_reset();
				break;
				case WHITE:
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,1,255);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,1);
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,0,255);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,0);
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,2,255);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,2);
					vTaskDelay(10 / portTICK_PERIOD_MS);
					esp_task_wdt_reset();
				break;
				case OFF:
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,1,0);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,1);
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,0,0);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,0);
					ledc_set_duty(LEDC_HIGH_SPEED_MODE,2,0);
					ledc_update_duty(LEDC_HIGH_SPEED_MODE,2);
					vTaskDelay(10 / portTICK_PERIOD_MS);
					esp_task_wdt_reset();
				break;
				default:
					vTaskDelay(10 / portTICK_PERIOD_MS);
					esp_task_wdt_reset();
				break;
			}
			
			
	}
	
	
}
