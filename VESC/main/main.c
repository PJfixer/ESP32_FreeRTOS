
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
	 setNunchuckValues();
	
}
