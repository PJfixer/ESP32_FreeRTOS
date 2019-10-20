
#ifndef RGB_H_

#define RGB_H_

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "esp_task_wdt.h"

#include "driver/ledc.h"
void RGB_task(void *args);

#endif

