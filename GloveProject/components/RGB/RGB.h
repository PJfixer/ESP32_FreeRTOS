
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

#define BLUE_FADE 0
#define GREEN_FADE 1
#define RED_FADE 2
#define YELLOW_FADE 3
#define PURPLE_FADE 4
#define CYAN_FADE 5
#define BLUE 6
#define GREEN 7
#define RED 8
#define CYAN 9
#define YELLOW 10
#define PURPLE 11
#define WHITE 12
#define OFF 13



#endif

