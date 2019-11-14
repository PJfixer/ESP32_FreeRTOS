
#ifndef SERIAL_H

#define SERIAL_H

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"

#define ECHO_TEST_TXD  (GPIO_NUM_26)
#define ECHO_TEST_RXD  (GPIO_NUM_25)
#define ECHO_TEST_RTS  (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS  (UART_PIN_NO_CHANGE)

#define BUF_SIZE (1024)



void init_uart();

#endif
