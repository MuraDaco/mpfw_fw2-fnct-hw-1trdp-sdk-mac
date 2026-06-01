//  *******************************************************************************
//  
//  mpfw / fw2 - Multi Platform FirmWare FrameWork
//  Copyright (C) (2023) Marco Dau
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published
//  by the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//  
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//  
//  You can contact me by the following email address
//  marco <d o t> ing <d o t> dau <a t> gmail <d o t> com
//  
//  *******************************************************************************

/*
 * mcuUSART.cpp
 *
 *  Created on: Jun, 27 2024
 *      Author: Marco Dau

    Description:
    - the code flow is the following:
        1) create an instance at compile time in tbl.cpp file
            1.1) no parameter are available
                1.1.1) the uniq parameter is "g_msg_ptr" the pointer to shared memory
                    - this parameter is set after that the shared memory is created
        2) start device
        3) init procedure
            3.1) vhwManager module execute the init procedure
                3.1.1) create shared memory 
                3.1.2) call init function of mcuUSART module


 */

#include <iostream>

#include "mcuUsart.h"

// ****************************************************
// section start **** CONSTRUCTOR *****

    mcuUsart_t::mcuUsart_t(uint8_t p_mcuId, k_mcuUsart_t  p_ch) :
         shmMcuUsart_t      {0}
        ,g_mcuId            {p_mcuId}
        ,g_ch               {p_ch}
    {}

    mcuUsart_t::mcuUsart_t(uint8_t p_pid2,  uint8_t p_mcuId, k_mcuUsart_t  p_ch) :
         shmMcuUsart_t      {p_pid2}
        ,g_mcuId            {p_mcuId}
        ,g_ch               {p_ch}
    {}

    // section end   **** CONSTRUCTOR ***** 
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** PROCESS MANAGEMENT *****

    // public:
        void mcuUsart_t::vhwInit (void) {
            shmMcuUsart_t::init();
            chEnable();
        }



        void mcuUsart_t::vhwLoop (void) {
            check_read_write();
        }


    // section end   **** PROCESS MANAGEMENT *****
    // ****************************************************
    // --------------------------


//void mcuUsart_t::vhwInit (void* p_ptrCh) {
//    // //g_shm = static_cast<shmMcuUsart_t*> (p_shm);
//    g_ch = *(static_cast<k_mcuUSART*> (p_ptrCh));
//}

#define UNUSED(X) (void)X      // To avoid gcc/g++ warnings

void mcuUsart_t::chEnable       (void)  {
    UNUSED(g_mcuId);
    shmMcuUsart_t::chEnable (g_ch);
}

#define TX_OK                   0
#define TX_FAIL_LINE_CONFLICT   1

uint8_t mcuUsart_t::check_read_write(void)	{
	uint8_t l_result = TX_OK;

	// check data buffer status
    // check the "lock" status of the virtual serial comunication channel
    // only one process at time can write to
	if(shmMcuUsart_t::WriterPidGet())	{
        // INTERRUPT TRIGGER of "Receive byte" or "Send byte"/"Last byte phisically send"

		// write/read procedure is on
		if(shmMcuUsart_t::pidMatches()) {
			// the current process is the process that write/add data to packet buffer
			// all processes have read the data
			// therefore ...

            // check the trigger of the interrupt
            // there are two trigger
            // - send byte
            // - last byte physically send (usefull in rs-485 half-duplex comunication)
			if(g_callback_protocol_functions.tx_status_get__running())	{
                // INTERRUPT TRIGGER of "SEND BYTE" (therefore the "user buffer" is full) ...

                //  - to transfer the content of user bufer to usart peripheral register
				//      - for example:
                //          - current use case / virtual usart 
                //              - shmMcuUsart_t::setData(g_tx_data); 
                //              - N.B.: the above statement is called by the following instruction via g_callback_sdk_functions.reg_write() function
                g_callback_protocol_functions.tx_buffer_management(nullptr);
			}
            // check the user buffer status
            if(g_callback_protocol_functions.tx_status_get__waiting_last_byte_send()) {
                // INTERRUPT TRIGGER of "Last byte phisically send"

                // the "last byte" is completely physically send
                // in the current case of virtual usart this means that ...
                // ... the last byte has been read from all other processes, therefore ...

                // the tx procedure can be considered terminated
                // the following callback function is usually used to set the enable/disable rx/tx in RS-485 half-duplex comunication chnnel
                g_callback_protocol_functions.tx_status_set__completed();

  				// release/unlock the virtual channel
       		 	shmMcuUsart_t::WriterPidClr();
            }

		} else {
			// the current process is not the process that add data to packet buffer
			// therefore ...

			// check if there is a byte to read or a line conflict raised
			// N.B.: the line conflict happen when the current process want to send data but 
			// another process has already locked the channel
            if(g_callback_protocol_functions.rx_status_get__running()) {
				// there is a data to read
				// --- g_rx_data = shmMcuUsart_t::getData();
                g_callback_protocol_functions.rx_buffer_management(nullptr);
                if(g_callback_protocol_functions.rx_status_get__completed()) {
                    // to do
                }
			}

			if(g_callback_protocol_functions.tx_status_get__running())	{
				// there is a data to send
				// therefore there is a line conflict
				l_result = TX_FAIL_LINE_CONFLICT;

			}

		}
	} else {
		// the channel is free
		// check if there is a data to send 
    	if(g_callback_protocol_functions.tx_status_get__running())	{
			// there is a data to send

			// get/lock the channel & activate the tx interrupt
			shmMcuUsart_t::WriterPidSet();
			// write data
    		// --- shmMcuUsart_t::setData(g_tx_data);
            g_callback_protocol_functions.tx_buffer_management(nullptr);
		}
	}

	return l_result;
}

void mcuUsart_t::tx_fifo_write(void* p_ptrData, char c)	{
    UNUSED(p_ptrData);
    shmMcuUsart_t::setData(c); 
}


uint8_t mcuUsart_t::rx_fifo_read  (void* p_ptrData)	{
    UNUSED(p_ptrData);
	return shmMcuUsart_t::getData();
}

