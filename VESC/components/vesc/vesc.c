

#include "vesc.h"

dataPackage data; 
nunchuckPackage nunchuck; 
extern SemaphoreHandle_t UART1_mut;



int packSendPayload(uint8_t * payload, int lenPay) {

	uint16_t crcPayload = crc16(payload, lenPay);
	int count = 0;
	uint8_t messageSend[256];

	if (lenPay <= 256)
	{
		messageSend[count++] = 2;
		messageSend[count++] = lenPay;
	}
	else
	{
		messageSend[count++] = 3;
		messageSend[count++] = (uint8_t)(lenPay >> 8);
		messageSend[count++] = (uint8_t)(lenPay & 0xFF);
	}

	memcpy(&messageSend[count], payload, lenPay);

	count += lenPay;
	messageSend[count++] = (uint8_t)(crcPayload >> 8);
	messageSend[count++] = (uint8_t)(crcPayload & 0xFF);
	messageSend[count++] = 3;
	messageSend[count] = '\0';

	

	// Sending package
	//serialPort->write(messageSend, count);
	uart_tx_chars(UART_NUM_1,(const char *)messageSend,count);
	// Returns number of send bytes
	return count;
}


bool processReadPacket(uint8_t * message) {

	COMM_PACKET_ID packetId;
	int32_t ind = 0;

	packetId = (COMM_PACKET_ID)message[0];
	message++; // Removes the packetId from the actual message (payload)

	switch (packetId){
		case COMM_GET_VALUES: // Structure defined here: https://github.com/vedderb/bldc/blob/43c3bbaf91f5052a35b75c2ff17b5fe99fad94d1/commands.c#L164
			printf("process COMM_GET_VALUES data \n ");
			ind = 4; // Skip the first 4 bytes 
			data.avgMotorCurrent 	= buffer_get_float32(message, 100.0, &ind);
			data.avgInputCurrent 	= buffer_get_float32(message, 100.0, &ind);
			ind += 8; // Skip the next 8 bytes
			data.dutyCycleNow 		= buffer_get_float16(message, 1000.0, &ind);
			data.rpm 				= buffer_get_int32(message, &ind);
			data.inpVoltage 		= buffer_get_float16(message, 10.0, &ind);
			data.ampHours 			= buffer_get_float32(message, 10000.0, &ind);
			data.ampHoursCharged 	= buffer_get_float32(message, 10000.0, &ind);
			ind += 8; // Skip the next 8 bytes 
			data.tachometer 		= buffer_get_int32(message, &ind);
			data.tachometerAbs 		= buffer_get_int32(message, &ind);
			return true;

		break;

		default:
			return false;
		break;
	}
}

bool getVescValues(void) {

	uint8_t command[1] = { COMM_GET_VALUES };
	uint8_t payload[256];

	packSendPayload(command, 1);
	// delay(1); //needed, otherwise data is not read

	size_t lenPayload;
	uart_get_buffered_data_len(UART_NUM_1, &lenPayload);

	if (lenPayload > 55) {
		uart_read_bytes(UART_NUM_1,payload, lenPayload, 100);
		bool read = processReadPacket(payload); //returns true if sucessful
		return read;
	}
	else
	{
		return false;
	}
}

bool getVescValuesfwd(uint8_t canID ) {
	uint8_t index = 0;
	uint8_t command[3];
	//command[0] = ;
	uint8_t payload[256];
	 command[index++] =  COMM_FORWARD_CAN ; //Forwarding CAN 
	 command[index++] = canID;                //Sending CAN id
	 command[index++] =  COMM_GET_VALUES ;  //Requesting Values

	packSendPayload(command,3);
	// delay(1); //needed, otherwise data is not read

	size_t lenPayload;
	uart_get_buffered_data_len(UART_NUM_1, &lenPayload);

	if (lenPayload > 55) {
		uart_read_bytes(UART_NUM_1,payload, lenPayload, 100);
		bool read = processReadPacket(payload); //returns true if sucessful
		return read;
	}
	else
	{
		return false;
	}
}

void setNunchuckValues() {
	int32_t ind = 0;
	uint8_t payload[11];

	
	payload[ind++] = COMM_SET_CHUCK_DATA;
	payload[ind++] = nunchuck.valueX;
	payload[ind++] = nunchuck.valueY;
	buffer_append_bool(payload, nunchuck.lowerButton, &ind);
	buffer_append_bool(payload, nunchuck.upperButton, &ind);
	
	// Acceleration Data. Not used, Int16 (2 byte)
	payload[ind++] = 0;
	payload[ind++] = 0;
	payload[ind++] = 0;
	payload[ind++] = 0;
	payload[ind++] = 0;
	payload[ind++] = 0;

	

	packSendPayload(payload, 11);
}






