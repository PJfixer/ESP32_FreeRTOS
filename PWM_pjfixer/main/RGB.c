

#include "RGB.h"



void RGB_task(void *args) {
	(void)args;
	//gpio_pad_select_gpio(25);
	/*gpio_pad_select_gpio(26);
	gpio_pad_select_gpio(27);
    	 Set the GPIO as a push/pull output*/
   	//gpio_set_direction(25, GPIO_MODE_OUTPUT);
	/*gpio_set_direction(26, GPIO_MODE_OUTPUT);
	gpio_set_direction(27, GPIO_MODE_OUTPUT);*/
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
	
	
	
	for(;;)
	{
		int i;
		uint8_t r = 0;
		uint8_t g = 0;
		uint8_t b = 0;
		for(i=0;i<255;i++) 
		{	

			r++;
			b++ ;
			if(i < 128)
			{
				g+=2;
			}
			else
			{
				g-=2;
			}
			ledc_set_duty(LEDC_HIGH_SPEED_MODE,LEDC_CHANNEL_0,r);
			ledc_set_duty(LEDC_HIGH_SPEED_MODE,LEDC_CHANNEL_1,b);
			ledc_set_duty(LEDC_HIGH_SPEED_MODE,LEDC_CHANNEL_2,g);
			
			ledc_update_duty(LEDC_HIGH_SPEED_MODE,LEDC_CHANNEL_0);
			ledc_update_duty(LEDC_HIGH_SPEED_MODE,LEDC_CHANNEL_1);
			ledc_update_duty(LEDC_HIGH_SPEED_MODE,LEDC_CHANNEL_2);
			vTaskDelay(100 / portTICK_PERIOD_MS);
			esp_task_wdt_reset();
		}
        	
	}
	
	
}
