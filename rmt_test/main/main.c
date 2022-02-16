/* IR protocols example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/rmt.h"

static const char *TAG = "RMT_TEST";

#define NEC_HEADER_MARK_US 9000
#define NEC_HEADER_SPACE_US 4500

#define NEC_BYTE_ONE_MARK_US 562
#define NEC_BYTE_ONE_SPACE_US 1687

#define NEC_BYTE_ZERO_MARK_US 562
#define NEC_BYTE_ZERO_SPACE_US 562

#define ONE 0   # ir demodulator output is in opendrain configuration
#define ZERO 1

static rmt_channel_t rx_channel = RMT_CHANNEL_0;



/* Converts the RMT level, duration into a positive or negative integer
 * Compatible with the ESP32-RMT-server application
 * Note: most IR receivers have active-low outputs, where the
 *   ESP32-RMT-server application has active-high oututs
 * This function inverts the RMT receive level so the text output is
 *   compatible with ESP32-RMT-server application
 */
int dur( uint32_t level, uint32_t duration ) {
	if ( level == 0 ) { return duration; }
	else { return -1.0 * duration; }
}

 int is_Between(uint16_t value,uint16_t reference, float tolerance)
{
	if(value >= (reference-(uint16_t)(reference*tolerance)) &&  value <= (uint16_t)(reference+(reference*tolerance)))
	{
		return 1;
	}
	return 0;
	
}

int Head_check(rmt_item32_t  first_item, float tolerance)
{

	if(first_item.level0 == ONE && is_Between(first_item.duration0,NEC_HEADER_MARK_US,tolerance) == 1 && first_item.level1 == ZERO && is_Between(first_item.duration1,NEC_HEADER_SPACE_US,tolerance) == 1 ) // if header look like NEC start (9,5 ms level 1  followed  4ms level 0 )
	{
		return 0;
	}
	
	return -1 ;
	
}

char Byte_check(rmt_item32_t  i_item, float tolerance)
{
	
	if(i_item.level0 == ONE && is_Between(i_item.duration0,NEC_BYTE_ONE_MARK_US,tolerance) == 1 && i_item.level1 == ZERO && is_Between(i_item.duration1,NEC_BYTE_ONE_SPACE_US,tolerance) == 1 ) // case pattern NEC logical 1
	{
		return 1;
	}
	else if(i_item.level0 == ONE && is_Between(i_item.duration0,NEC_BYTE_ZERO_MARK_US,tolerance) == 1 && i_item.level1 == ZERO && is_Between(i_item.duration1,NEC_BYTE_ZERO_SPACE_US,tolerance) == 1 )  // case pattern NEC logical 0
	{

		return 0;
	}
	return -1;
}

// char NEC_decode_byte(rmt_item32_t * i_item, float tolerance)
// {
	// if(first_item.level0 == 1 && is_Between(first_item.duration0,NEC_BYTE_ONE_MARK_US,0.10) == 1 && first_item.level1 == 0 && is_Between(first_item.duration1,NEC_BYTE_ONE_SPACE_US,0.10) == 1 ) // case pattern NEC logical 1
	// {
		// return 1;
	// }
	// else if(first_item.level0 == 1 && is_Between(first_item.duration0,NEC_BYTE_ZERO_MARK_US,0.10) == 1 && first_item.level1 == 0 && is_Between(first_item.duration1,NEC_BYTE_ZERO_SPACE_US,0.10) == 1 )  // case pattern NEC logical 0
	// {
		// return 0;
	// }
	// return -1;
// }


/**
 * @brief RMT Receive Task
 *
 */
static void ir_rx_task(void *arg)
{

    uint32_t rx_size = 0;
    RingbufHandle_t rb = NULL;
    rmt_item32_t *items = NULL;

   // rmt_config_t rmt_rx_config = RMT_DEFAULT_CONFIG_RX(CONFIG_EXAMPLE_RMT_RX_GPIO, rx_channel);
    rmt_config_t rmt_rx_config;
	rmt_rx_config.rmt_mode = RMT_MODE_RX;
	rmt_rx_config.channel = rx_channel;
	rmt_rx_config.gpio_num = GPIO_NUM_23;
	rmt_rx_config.clk_div = 80;
	rmt_rx_config.mem_block_num = 1;
	
	rmt_rx_config_t rx_conf;
	rx_conf.idle_threshold = 12000;
	rx_conf.filter_ticks_thresh = 100;
	rx_conf.filter_en = true;
	rmt_rx_config.rx_config = rx_conf;
	
    rmt_config(&rmt_rx_config);
    rmt_driver_install(rx_channel,1000, 0);

    // Start receive
    rmt_rx_start(rx_channel, true);
	for(;;)
	{
		// get the ring buffer handle
		rmt_get_ringbuf_handle(rx_channel, &rb);
		// get items, if there are any
		items = (rmt_item32_t*) xRingbufferReceive(rb, &rx_size, 10);
		if(items) 
		{

				
				// print the RMT received durations to the monitor
				printf( "received %i items\n",rx_size/4 );
				for (int i=0; i<rx_size/4; i++ ) {
					if ( i>0 ) { printf(","); }
					printf( "%i", dur( items[i].level0, items[i].duration0 ) );
					printf(",%i", dur( items[i].level1, items[i].duration1 ) );
					printf("|");
				}
				printf("\n");
				if(Head_check(items[0],0.10) == 0)
				{
					printf("NEC header catched \n");
				}
				else
				{
				
				printf("Header not catched \n");
				}
				Byte_check(items[1],0.15);

				
				// free up data space
				vRingbufferReturnItem(rb, (void*) items);
		}
		vTaskDelay( 100 / portTICK_PERIOD_MS );
	}

    rmt_driver_uninstall(rx_channel);
	
    vTaskDelete(NULL);
}



void app_main(void)
{
    xTaskCreate(ir_rx_task, "ir_rx_task", 2048, NULL, 10, NULL);
    
}
