/*
 * RobotOrchestrator.hpp
 *
 *  Created on: Nov 2, 2024
 *      Author: Gabriel
 */

#ifndef COMPONENTS_ROBOTORCHESTRATOR_ROBOTORCHESTRATOR_HPP_
#define COMPONENTS_ROBOTORCHESTRATOR_ROBOTORCHESTRATOR_HPP_

#include "Executable.hpp"
#include "Queue.hpp"
#include "Shared/SX1280Lib/sx1280-hal.h"
#include "Shared/nanopb/grSim_Commands.pb.h"

class RobotOrchestrator : public Executable  {
public:
	RobotOrchestrator(Queue<grSim_Robot_Command>* inQueue, SX1280Hal* txRadio);
	virtual ~RobotOrchestrator();
	int32_t init();
	int32_t execute();
private:
	Queue<grSim_Robot_Command>* inQueue;
	SX1280Hal* txRadio;
};

#endif /* COMPONENTS_ROBOTORCHESTRATOR_ROBOTORCHESTRATOR_HPP_ */
