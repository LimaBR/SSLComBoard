/*
  ______                              _
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2015 Semtech

Description: Handling of the node configuration protocol

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#ifndef __SX1280_HAL_H__
#define __SX1280_HAL_H__

#include <GPIO_Pin.hpp>
#include <SPI_Master.hpp>
#include <FreeRTOS.h>
#include <event_groups.h>
#include <Shared/SX1280Lib/SX1280.hpp>

/*!
 * \brief Actual implementation of a SX1280 radio
 */
class SX1280_FreeRTOS : public SX1280, private Interruptible
{
public:
    /*!
     * \brief Constructor for SX1280Hal with SPI support
     *
     * Represents the physical connectivity with the radio and set callback functions on radio interrupts
     */
    SX1280_FreeRTOS( SPI_Master* pSpiMaster, GPIO_Pin* pNssPin,
			GPIO_Pin* pBusyPin, GPIO_Pin* pIrqPin, GPIO_Pin* pRstPin);

    /*!
     * \brief Destructor for SX1280Hal with UART support
     *
     * Take care of the correct destruction of the communication objects
     */
    virtual ~SX1280_FreeRTOS( void );

    /*!
     * \brief Soft resets the radio
     */
    virtual void Reset( void );

    /*!
     * \brief Wakes up the radio
     */
    virtual void Wakeup( void );

    /*!
     * \brief Send a command that write data to the radio
     *
     * \param [in]  opcode        Opcode of the command
     * \param [in]  buffer        Buffer to be send to the radio
     * \param [in]  size          Size of the buffer to send
     */
    virtual void WriteCommand( RadioCommands_t opcode, uint8_t *buffer, uint16_t size );

    /*!
     * \brief Send a command that read data from the radio
     *
     * \param [in]  opcode        Opcode of the command
     * \param [out] buffer        Buffer holding data from the radio
     * \param [in]  size          Size of the buffer
     */
    virtual void ReadCommand( RadioCommands_t opcode, uint8_t *buffer, uint16_t size );

    /*!
     * \brief Write data to the radio memory
     *
     * \param [in]  address       The address of the first byte to write in the radio
     * \param [in]  buffer        The data to be written in radio's memory
     * \param [in]  size          The number of bytes to write in radio's memory
     */
    virtual void WriteRegister( uint16_t address, uint8_t *buffer, uint16_t size );

    /*!
     * \brief Write a single byte of data to the radio memory
     *
     * \param [in]  address       The address of the first byte to write in the radio
     * \param [in]  value         The data to be written in radio's memory
     */
    virtual void WriteRegister( uint16_t address, uint8_t value );

    /*!
     * \brief Read data from the radio memory
     *
     * \param [in]  address       The address of the first byte to read from the radio
     * \param [out] buffer        The buffer that holds data read from radio
     * \param [in]  size          The number of bytes to read from radio's memory
     */
    virtual void ReadRegister( uint16_t address, uint8_t *buffer, uint16_t size );

    /*!
     * \brief Read a single byte of data from the radio memory
     *
     * \param [in]  address       The address of the first byte to write in the
     *                            radio
     *
     * \retval      value         The value of the byte at the given address in
     *                            radio's memory
     */
    virtual uint8_t ReadRegister( uint16_t address );

    /*!
     * \brief Write data to the buffer holding the payload in the radio
     *
     * \param [in]  offset        The offset to start writing the payload
     * \param [in]  buffer        The data to be written (the payload)
     * \param [in]  size          The number of byte to be written
     */
    virtual void WriteBuffer( uint8_t offset, uint8_t *buffer, uint8_t size );

    /*!
     * \brief Read data from the buffer holding the payload in the radio
     *
     * \param [in]  offset        The offset to start reading the payload
     * \param [out] buffer        A pointer to a buffer holding the data from the radio
     * \param [in]  size          The number of byte to be read
     */
    virtual void ReadBuffer( uint8_t offset, uint8_t *buffer, uint8_t size );

    /*!
     * \brief Returns the status of DIOs pins
     *
     * \retval      dioStatus     A byte where each bit represents a DIO state:
     *                            [ DIO3 | DIO2 | DIO1 | BUSY ]
     */
    virtual uint8_t GetDioStatus( void );

    virtual Event WaitForEvent();

protected:

    SPI_Master* RadioSpi;	//!< The SPI object used to communicate with the radio
    GPIO_Pin* RadioNss;		//!< The pin connected to Radio chip select (active low)
    GPIO_Pin* RadioReset;	//!< The reset pin connected to the radio
    GPIO_Pin* BUSY;			//!< The pin connected to BUSY
    GPIO_Pin* DIO1;			//!< The pin connected to DIO1
    GPIO_Pin* DIO2;			//!< The pin connected to DIO2
    GPIO_Pin* DIO3;			//!< The pin connected to DIO3

    // TODO Comments
    void HardwareInit( );
    void onEvent(Event event);

private:
    bool dioIrqEnabled = false;
    EventGroupHandle_t onIrqEventGroup;
    QueueHandle_t eventQueue;
    void setDioIrqEnabled(bool enabled);
    void irqHandler(InterruptReason* reason);
    static void irqProcessTaskStatic(void* object);
    void irqProcessTask();
};

#endif // __SX1280_HAL_H__
