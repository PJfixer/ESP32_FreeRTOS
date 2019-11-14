
#ifndef BT_SPP_H 

#define BT_SPP_H

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "nvs.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"
#include "esp_bt_device.h"
#include "esp_spp_api.h"


#define SPP_TAG "SPP_INITIATOR_DEMO"
#define EXCAMPLE_DEVICE_NAME "ESP_SPP_INITIATOR"

#define SPP_SHOW_DATA 0
#define SPP_SHOW_SPEED 1
#define SPP_SHOW_MODE SPP_SHOW_DATA  /*Choose show mode: show data or speed*/

void  init_bt(void);


#endif
