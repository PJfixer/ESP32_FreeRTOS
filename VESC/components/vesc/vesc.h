
#ifndef VESC_H

#define VESC_H

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "buffer.h"
#include "crc.h"
#include "datatypes.h"
/** Struct to store the telemetry data returned by the VESC */
	typedef struct  {
		float avgMotorCurrent;
		float avgInputCurrent;
		float dutyCycleNow;
		long rpm;
		float inpVoltage;
		float ampHours;
		float ampHoursCharged;
		long tachometer;
		long tachometerAbs;
	}dataPackage;

	/** Struct to hold the nunchuck values to send over UART */
		typedef struct  {
		int	valueX;
		int	valueY;
		bool upperButton; // valUpperButton
		bool lowerButton; // valLowerButton
	}nunchuckPackage;
	
int packSendPayload(uint8_t * payload, int lenPay);
bool processReadPacket(uint8_t * message);
bool getVescValues(void);
bool getVescValuesfwd(uint8_t canID );
void setNunchuckValues();
#endif
