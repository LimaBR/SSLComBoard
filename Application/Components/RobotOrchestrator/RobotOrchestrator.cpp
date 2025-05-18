/*
 * RobotOrchestrator.cpp
 *
 *  Created on: Nov 2, 2024
 *      Author: Gabriel
 */

#include "RobotOrchestrator.hpp"

RobotOrchestrator::RobotOrchestrator(Queue<grSim_Robot_Command>* inQueue, SX1280* txRadio) :
	Executable(Log::Level::Debug, "RobotOrchestrator"),
	inQueue(inQueue),
	txRadio(txRadio)
{

}

RobotOrchestrator::~RobotOrchestrator() {

}

int32_t RobotOrchestrator::init() {
	txRadio->Init();
	txRadio->SetRegulatorMode( USE_DCDC );
	RadioStatus_t status = txRadio->GetStatus();
	if(status.Fields.ChipMode != 0x02 || status.Fields.CmdStatus != 0x01){
		log(Log::Level::Error, "Failed to initialize radio status %d", status.Value);
		return -1;
	}

	PacketParams_t packetParams;
	ModulationParams_t modulationParams;

    modulationParams.PacketType                    = PACKET_TYPE_FLRC;
    modulationParams.Params.Flrc.BitrateBandwidth  = FLRC_BR_0_260_BW_0_3;
    modulationParams.Params.Flrc.CodingRate        = FLRC_CR_1_2;
    modulationParams.Params.Flrc.ModulationShaping = RADIO_MOD_SHAPING_BT_1_0;

    packetParams.PacketType                 = PACKET_TYPE_FLRC;
    packetParams.Params.Flrc.PreambleLength = PREAMBLE_LENGTH_32_BITS;
    packetParams.Params.Flrc.SyncWordLength = FLRC_SYNCWORD_LENGTH_4_BYTE;
    packetParams.Params.Flrc.SyncWordMatch  = RADIO_RX_MATCH_SYNCWORD_1;
    packetParams.Params.Flrc.HeaderType     = RADIO_PACKET_VARIABLE_LENGTH;
    packetParams.Params.Flrc.PayloadLength  = 15;
    packetParams.Params.Flrc.CrcLength      = RADIO_CRC_3_BYTES;
    packetParams.Params.Flrc.Whitening      = RADIO_WHITENING_OFF;

    txRadio->SetStandby( STDBY_RC );
    txRadio->SetPacketType( modulationParams.PacketType );
    txRadio->SetModulationParams( &modulationParams );
    txRadio->SetPacketParams( &packetParams );

    txRadio->SetRfFrequency( 2395000000UL );
    txRadio->SetBufferBaseAddresses( 0x00, 0x00 );
    txRadio->SetTxParams( 12, RADIO_RAMP_20_US );
    //uint16_t RxIrqMask = IRQ_RX_DONE | IRQ_RX_TX_TIMEOUT;
    //txRadio->SetDioIrqParams( RxIrqMask, RxIrqMask, IRQ_RADIO_NONE, IRQ_RADIO_NONE );
    //txRadio->SetRx( ( TickTime_t ) { RADIO_TICK_SIZE_1000_US, 100 } );
    uint16_t TxIrqMask = IRQ_TX_DONE | IRQ_RX_TX_TIMEOUT;
    txRadio->SetDioIrqParams( TxIrqMask, TxIrqMask, IRQ_RADIO_NONE, IRQ_RADIO_NONE );
    PacketStatus_t packetStatus;
    txRadio->GetPacketStatus(&packetStatus);
    while(true){
    	txRadio->SendPayload( (uint8_t*)"Hello World", 12, ( TickTime_t ){ RADIO_TICK_SIZE_1000_US, 100 } );
    	txRadio->WaitForEvent();
    }
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
