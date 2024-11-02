/*
 * RobotOrchestrator.cpp
 *
 *  Created on: Nov 2, 2024
 *      Author: Gabriel
 */

#include "RobotOrchestrator.hpp"

RobotOrchestrator::RobotOrchestrator(Queue<grSim_Robot_Command>* inQueue) :
	Executable(Log::Level::Debug, "RobotOrchestrator"),
	inQueue(inQueue)
{

}

RobotOrchestrator::~RobotOrchestrator() {

}

int32_t RobotOrchestrator::init() {
	return 0;
}

int32_t RobotOrchestrator::execute() {
	log(Log::Level::Informational, "Started execution");
	while(true){
		grSim_Robot_Command currentCommand;
		inQueue->receive(&currentCommand, -1);
		log(Log::Level::Debug, "grSim CMD: ID=%d", currentCommand.id);
	}
}
