/*
 * ProtobufDecode.cpp
 *
 *  Created on: Oct 30, 2024
 *      Author: Gabriel
 */

#include "ProtobufDecode.hpp"
#include "Utilities.hpp"

ProtobufDecode::ProtobufDecode(Queue<std::vector<uint8_t>>* inQueue) :
	Executable(Log::Level::Debug, "ProtobufDecode"),
	inQueue(inQueue)
{

}

ProtobufDecode::~ProtobufDecode() {

}

int32_t ProtobufDecode::init() {
	int32_t errors = 0;
	log(Log::Level::Informational, "Init");
	return errors;
}

int32_t ProtobufDecode::execute() {
	log(Log::Level::Informational, "Started execution");
	while(true){
		std::vector<uint8_t> pkt;
		inQueue->receive(&pkt, -1);
		log(Log::Level::Debug, "Packet RX %s", pkt.data());
	}
}
