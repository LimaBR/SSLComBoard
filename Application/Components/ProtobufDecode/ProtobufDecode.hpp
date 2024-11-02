/*
 * ProtobufDecode.hpp
 *
 *  Created on: Oct 30, 2024
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_PROTOBUFDECODE_HPP_
#define SRC_COMPONENTS_PROTOBUFDECODE_HPP_

#include "Executable.hpp"
#include "Queue.hpp"
#include <vector>
#include "Shared/nanopb/grSim_Commands.pb.h"

class ProtobufDecode : public Executable {
public:
	ProtobufDecode(Queue<std::vector<uint8_t>>* inQueue, Queue<grSim_Robot_Command>* outQueue);
	virtual ~ProtobufDecode();
	int32_t init();
	int32_t execute();
private:
	Queue<std::vector<uint8_t>>* inQueue;
	Queue<grSim_Robot_Command>* outQueue;
	char printPktBuffer[192];
};

#endif /* SRC_COMPONENTS_PROTOBUFDECODE_HPP_ */
