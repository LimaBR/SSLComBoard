/*
 * ReceiveFromComputer.cpp
 *
 *  Created on: Oct 16, 2024
 *      Author: Gabriel
 */

#include "FreeRTOS.h"
#include "task.h"
#include <cstring>
#include "ComputerComms_ESP8266.hpp"

ComputerComms_ESP8266::ComputerComms_ESP8266(Queue<std::vector<uint8_t>>* outQueue, UART* computerUart) :
	Executable(Log::Level::Informational, "ReceiveFromComputer"),
	outQueue(outQueue),
	computerUart(computerUart)
{

}

ComputerComms_ESP8266::~ComputerComms_ESP8266() {

}

int32_t ComputerComms_ESP8266::init() {
	int32_t errors = 0;
	log(Log::Level::Informational, "Init");
	errors += computerUart->init();
	return errors;
}

int32_t ComputerComms_ESP8266::execute() {
	log(Log::Level::Informational, "Started execution, taking UART mutex");
	if(computerUart->take(100) < 0){
		log(Log::Level::Error, "UART mutex take error");
	}
	while(true){
		int32_t count = computerUart->receiveUntilLineIdle(pktBuffer, maxPktSizeBytes);
		if(count>0){
			log(Log::Level::Debug, "Packet of %ld bytes RX", count);
			std::vector<uint8_t> pkt(pktBuffer, pktBuffer+count);
			if(outQueue->send(pkt, queueSendTimeoutMs) < 0){
				log(Log::Level::Error, "%s send error", outQueue->getName());
			}
		}else{
			log(Log::Level::Error, "Packet RX error %ld, sleeping for 100ms before retry", count);
			vTaskDelay(100);
		}
	}
}
