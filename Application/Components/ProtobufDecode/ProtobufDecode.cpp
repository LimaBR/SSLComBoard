/*
 * ProtobufDecode.cpp
 *
 *  Created on: Oct 30, 2024
 *      Author: Gabriel
 */

#include "ProtobufDecode.hpp"
#include "Utilities.hpp"
#include "Shared/nanopb/pb_decode.h"

ProtobufDecode::ProtobufDecode(Queue<std::vector<uint8_t>>* inQueue, Queue<grSim_Robot_Command>* outQueue) :
	Executable(Log::Level::Debug, "ProtobufDecode"),
	inQueue(inQueue),
	outQueue(outQueue)
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
		pb_istream_t stream = pb_istream_from_buffer(pkt.data(), pkt.size());
		grSim_Robot_Command receivedPacket;
		bool decodeStatus = pb_decode(&stream, grSim_Robot_Command_fields, &receivedPacket);
		if(decodeStatus){
			log(Log::Level::Debug, "Decode status OK, sending to queue");
			int32_t sendStatus = outQueue->send(receivedPacket, 100);
			if(sendStatus < 0){
				log(Log::Level::Error, "Error sending to queue, dropping");
			}
		}else{
			log(Log::Level::Error, "Error decoding packet, dropping");
		}
	}
}
