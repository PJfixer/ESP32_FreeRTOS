
#ifndef ADC_H_

#define ADC_H_

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "esp_task_wdt.h"

#include "driver/adc.h"

void ADC_task(void *args);

#endif

