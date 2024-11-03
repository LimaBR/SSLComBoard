/*
  ______                              _
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2016 Semtech

Description: Handling of the node configuration protocol

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis, Gregory Cristian and Matthieu Verdy
*/
#include "sx1280-hal.h"
#include <functional>
#include <FreeRTOS.h>
#include <task.h>
#include <cstring>

/*!
 * \brief Used to block execution waiting for low state on radio busy pin.
 *        Essentially used in SPI communications
 */
#define WaitOnBusy( )          for(uint8_t val=1; val; BUSY->read(&val));

// This code handles cases where assert_param is undefined
#ifndef assert_param
#define assert_param( ... )
#endif

SX1280Hal::SX1280Hal( SPI_Master* pSpiMaster, GPIO_Pin* pNssPin,
			GPIO_Pin* pBusyPin, GPIO_Pin* pIrqPin, GPIO_Pin* pRstPin,
			RadioCallbacks_t *callbacks ) :
			SX1280( callbacks ),
			RadioSpi(pSpiMaster),
			RadioNss( pNssPin ),
			RadioReset( pRstPin ),
			BUSY( pBusyPin ),
			DIO1( pIrqPin )
{

}

SX1280Hal::~SX1280Hal( void )
{

};

void SX1280Hal::SpiInit( void )
{
    RadioNss->set();
}

void SX1280Hal::IoIrqInit( DioIrqHandler irqHandler )
{
    assert_param( RadioSpi != NULL );
    SpiInit( );
    onIrqEventGroup = xEventGroupCreate();
    TaskHandle_t irqProcessTaskHandle;
    xTaskCreate(irqProcessTaskStatic, "irqProcess", 256, this, 25, &irqProcessTaskHandle);
	DIO1->registerExtiCallback(this);
}

void SX1280Hal::Reset( void )
{
	setDioIrqEnabled( false );
    vTaskDelay( 20 );
    RadioReset->reset();
    vTaskDelay( 50 );
    RadioReset->set();
    vTaskDelay( 20 );
    setDioIrqEnabled( true );
}

void SX1280Hal::Wakeup( void )
{
	setDioIrqEnabled( false );

    //Don't wait for BUSY here

    if( RadioSpi != NULL )
    {
    	RadioSpi->take(100);
        RadioNss->reset();
        uint8_t txBuffer[2] = {RADIO_GET_STATUS, 0};
        RadioSpi->transmit(txBuffer, 2);
        RadioNss->set();
        RadioSpi->give();
    }

    // Wait for chip to be ready.
    WaitOnBusy( );

    setDioIrqEnabled( true );
}

void SX1280Hal::WriteCommand( RadioCommands_t command, uint8_t *buffer, uint16_t size )
{
    WaitOnBusy( );

    if( RadioSpi != NULL )
    {
    	RadioSpi->take(100);
        RadioNss->reset();
        uint8_t txBuffer[size+1];
        txBuffer[0] = command;
        memcpy(txBuffer+1, buffer, size);
        RadioSpi->transmit(txBuffer, size+1);
        RadioNss->set();
        RadioSpi->give();
    }

    if( command != RADIO_SET_SLEEP )
    {
        WaitOnBusy( );
    }
}

void SX1280Hal::ReadCommand( RadioCommands_t command, uint8_t *buffer, uint16_t size )
{
    WaitOnBusy( );

    if( RadioSpi != NULL )
    {
    	RadioSpi->take(100);
        RadioNss->reset();
        if( command == RADIO_GET_STATUS )
        {
        	uint8_t txBuffer[3] = {RADIO_GET_STATUS, 0, 0};
        	uint8_t rxBuffer[3];
        	RadioSpi->trx(txBuffer, rxBuffer, 3);
        	buffer[0] = rxBuffer[0];
        }
        else
        {
        	uint8_t rxBuffer[size+2];
        	uint8_t txBuffer[size+2];
        	memset(txBuffer, 0, size+2);
        	txBuffer[0] = command;
        	RadioSpi->trx(txBuffer, rxBuffer, size+2);
        	memcpy(buffer, rxBuffer+2, size);
        }
        RadioNss->set();
        RadioSpi->give();
    }

    WaitOnBusy( );
}

void SX1280Hal::WriteRegister( uint16_t address, uint8_t *buffer, uint16_t size )
{
    WaitOnBusy( );

    if( RadioSpi != NULL )
    {
    	RadioSpi->take(100);
        RadioNss->reset();
        uint8_t txBuffer[size+3];
        txBuffer[0] = RADIO_WRITE_REGISTER;
        txBuffer[1] = ( address & 0xFF00 ) >> 8;
        txBuffer[2] = address & 0x00FF;
        memcpy(txBuffer+3, buffer, size);
        RadioSpi->transmit(txBuffer, size+3);
        RadioNss->set();
        RadioSpi->give();
    }

    WaitOnBusy( );
}

void SX1280Hal::WriteRegister( uint16_t address, uint8_t value )
{
    WriteRegister( address, &value, 1 );
}

void SX1280Hal::ReadRegister( uint16_t address, uint8_t *buffer, uint16_t size )
{
    WaitOnBusy( );

    if( RadioSpi != NULL )
    {
    	RadioSpi->take(100);
        RadioNss->reset();
        uint8_t txBuffer[size+4];
        uint8_t rxBuffer[size+4];
        txBuffer[0] = RADIO_READ_REGISTER;
        txBuffer[1] = ( address & 0xFF00 ) >> 8;
        txBuffer[2] = address & 0x00FF;
        memset(txBuffer+3, 0, size+1);
        RadioSpi->trx(txBuffer, rxBuffer, size+4);
        memcpy(buffer, rxBuffer+4, size);
        RadioNss->set();
        RadioSpi->give();
    }

    WaitOnBusy( );
}

uint8_t SX1280Hal::ReadRegister( uint16_t address )
{
    uint8_t data;

    ReadRegister( address, &data, 1 );
    return data;
}

void SX1280Hal::WriteBuffer( uint8_t offset, uint8_t *buffer, uint8_t size )
{
    WaitOnBusy( );

    if( RadioSpi != NULL )
    {
    	RadioSpi->take(100);
        RadioNss->reset();
        uint8_t txBuffer[size+2];
        txBuffer[0] = RADIO_WRITE_BUFFER;
        txBuffer[1] = offset;
        memcpy(txBuffer+2, buffer, size);
        RadioSpi->transmit(txBuffer, size+2);
        RadioNss->set();
        RadioSpi->give();
    }

    WaitOnBusy( );
}

void SX1280Hal::ReadBuffer( uint8_t offset, uint8_t *buffer, uint8_t size )
{
    WaitOnBusy( );

    if( RadioSpi != NULL )
    {
    	RadioSpi->take(100);
        RadioNss->reset();
        uint8_t txBuffer[size+3];
        uint8_t rxBuffer[size+3];
        txBuffer[0] = RADIO_READ_BUFFER;
        txBuffer[1] = offset;
        memset(txBuffer+2, 0, size+1);
        RadioSpi->trx(txBuffer, rxBuffer, size+3);
        memcpy(buffer, rxBuffer+3, size);
        RadioNss->set();
        RadioSpi->give();
    }

    WaitOnBusy( );
}

uint8_t SX1280Hal::GetDioStatus( void )
{
	uint8_t inter =0;
	uint8_t retval = 0;
	DIO1->read(&retval);
	retval = retval<<1;
	BUSY->read(&inter);
	retval += inter;
    return retval;
}

void SX1280Hal::setDioIrqEnabled(bool enabled) {
	dioIrqEnabled = enabled;
}

void SX1280Hal::irqHandler(InterruptReason *reason) {
	BaseType_t xHigherPriorityTaskWoken = false;
	if(reason == DIO1){
		xEventGroupSetBitsFromISR(onIrqEventGroup, 1<<0, &xHigherPriorityTaskWoken);
	}
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void SX1280Hal::irqProcessTaskStatic(void* object) {
	SX1280Hal* sx1280hal = static_cast<SX1280Hal*>(object);
	sx1280hal->irqProcessTask();
	vTaskDelete(NULL);
}

void SX1280Hal::irqProcessTask() {
	while(true){
		xEventGroupWaitBits(onIrqEventGroup, 1<<0, true, true, portMAX_DELAY);
		OnDioIrq();
	}
}