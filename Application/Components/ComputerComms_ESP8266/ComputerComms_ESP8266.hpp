/*
 * ReceiveFromComputer.hpp
 *
 *  Created on: Oct 16, 2024
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_RECEIVEFROMCOMPUTER_HPP_
#define SRC_COMPONENTS_RECEIVEFROMCOMPUTER_HPP_

#include "Executable.hpp"
#include "Queue.hpp"
#include "UART.hpp"
#include <vector>

class ComputerComms_ESP8266 : public Executable {
public:
	ComputerComms_ESP8266(Queue<std::vector<uint8_t>>* outQueue, UART* computerUart);
	virtual ~ComputerComms_ESP8266();
	int32_t init();
	int32_t execute();
private:
	Queue<std::vector<uint8_t>>* outQueue;
	UART* computerUart;
	static constexpr uint32_t maxPktSizeBytes = 256;
	static constexpr uint32_t queueSendTimeoutMs = 100;
	uint8_t pktBuffer[maxPktSizeBytes];
};

#endif /* SRC_COMPONENTS_RECEIVEFROMCOMPUTER_HPP_ */
