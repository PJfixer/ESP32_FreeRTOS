/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "esp_task_wdt.h"




static esp_err_t i2c_master_init()
{
    int i2c_master_port = I2C_NUM_0; // I2C0
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = GPIO_NUM_33;// SCL on GPIO 33
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = GPIO_NUM_32; //SDA on GPIO 34
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 400000;
    i2c_param_config(i2c_master_port, &conf);
    return i2c_driver_install(i2c_master_port, conf.mode,0, 0, 0); // no buffer needed in master mode + interupt disabled
}


static void
I2C_scan(void *args) {
	(void)args;
	
	ESP_ERROR_CHECK(i2c_master_init());
	uint8_t i ;
	
		
	for (;;) {
		
		printf("start I2c scan \n ");
		for(i=0;i<128;i++)
		{
			i2c_cmd_handle_t cmd = i2c_cmd_link_create();
			i2c_master_start(cmd);
	   		i2c_master_write_byte(cmd,(i<<1),true);
			i2c_master_stop(cmd);
			esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    		i2c_cmd_link_delete(cmd);
			if(ret == ESP_OK)
			{
			   printf("found a slave at  %#02x !! \n",i);

			}
			else if(ret == ESP_FAIL)
			{
			   //printf("nothing at %#02x \n",i);
			}
		}
		printf("end of scan  \n ");
		vTaskDelay(4000 / portTICK_PERIOD_MS);
		esp_task_wdt_reset();
		
				
		
	}
}



TaskHandle_t I2C_scan_handle;


void app_main()
{
	
	
	xTaskCreate(I2C_scan,"I2C_scanner",2048,NULL,configMAX_PRIORITIES-1,&I2C_scan_handle);
	ESP_ERROR_CHECK(esp_task_wdt_add(I2C_scan_handle)); // suscribe I2C scan to watchdog
	
}



