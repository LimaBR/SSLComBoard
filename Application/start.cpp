/*
 * start.cpp
 *
 *  Created on: Oct 31, 2024
 *      Author: Gabriel
 */

#include "start.h"
#include <cstdio>
#include "FreeRTOS.h"
#include "GPIO_Pin_STM32.hpp"
#include "BinLeds.hpp"
#include "LogDriver.hpp"
#include "PWM_Pin_STM32.hpp"
#include "UART_STM32.hpp"
#include "Queue_STM32.hpp"

#include "Components/ComputerComms_ESP8266/ComputerComms_ESP8266.hpp"
#include "Components/ProtobufDecode/ProtobufDecode.hpp"

GPIO_Pin_STM32 ledOrange(GPIOD, GPIO_PIN_13);
GPIO_Pin_STM32 ledGreen(GPIOD, GPIO_PIN_12);
GPIO_Pin_STM32 ledRed(GPIOD, GPIO_PIN_14);
GPIO_Pin_STM32 ledBlue(GPIOD, GPIO_PIN_15);
BinLeds discoveryLeds((GPIO_Pin*[]){&ledOrange, &ledGreen, &ledRed, &ledBlue}, 4);

extern UART_HandleTypeDef huart2;
UART_STM32 uart2(&huart2);

Queue_STM32<std::vector<uint8_t>, 4> computerPktQueue("computerPktQueue");
ComputerComms_ESP8266 componentReceiveFromComputer(&computerPktQueue, &uart2);
ProtobufDecode componentProtobufDecode(&computerPktQueue);

void executableDispatch(void* _executable){
	Executable* executable = static_cast<Executable*>(_executable);
	executable->execute();
	vTaskDelete(NULL);
}

void start(){
	discoveryLeds.set(1);
	printf("----------------INIT----------------\n");
	printf("X and Y: %lu\n", HAL_GetUIDw0());
	printf("Wafer number: %c\n", (uint8_t)HAL_GetUIDw1());
	printf("Lot number: %c%c%c%c%c%c%c\n",
			(uint8_t)(HAL_GetUIDw1()>>8),
			(uint8_t)(HAL_GetUIDw1()>>16),
			(uint8_t)(HAL_GetUIDw1()>>24),
			(uint8_t)(HAL_GetUIDw2()),
			(uint8_t)(HAL_GetUIDw2()>>8),
			(uint8_t)(HAL_GetUIDw2()>>16),
			(uint8_t)(HAL_GetUIDw2()>>24)
			);
	discoveryLeds.set(2);

	// Init log facility
	LogDriver::getInstance()->init();
	TaskHandle_t hTaskLogDriver;
	xTaskCreate(executableDispatch, "LogDriver", 256, LogDriver::getInstance(), 20, &hTaskLogDriver);

	// Init queues
	computerPktQueue.init();

	//Init components
	componentReceiveFromComputer.init();
	componentProtobufDecode.init();

	//Init tasks
	TaskHandle_t hTaskReceiveFromComputer;
	xTaskCreate(executableDispatch, "ReceiveFromComputer", 256, &componentReceiveFromComputer, 20, &hTaskReceiveFromComputer);

	TaskHandle_t hTaskProtobufDecode;
	xTaskCreate(executableDispatch, "ProtobufDecode", 256, &componentProtobufDecode, 20, &hTaskProtobufDecode);

	discoveryLeds.set(3);
	vTaskDelete(nullptr);
}
