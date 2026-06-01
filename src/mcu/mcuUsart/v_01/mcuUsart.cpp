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

#define MCU_USART_STATUS__RX_NO_DATA    0xfff0



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
            init();
            chEnable();
        }



//        void mcuUsart_t::vhwLoop (void) {
//            check_read_write();
//        }


    // section end   **** PROCESS MANAGEMENT *****
    // ****************************************************
    // --------------------------


//void mcuUsart_t::vhwInit (void* p_ptrCh) {
//    // //g_shm = static_cast<shmMcuUsart_t*> (p_shm);
//    g_ch = *(static_cast<k_mcuUSART*> (p_ptrCh));
//}

void mcuUsart_t::chEnable       (void)  {
    shmMcuUsart_t::chEnable (g_ch);
}

bool mcuUsart_t::check_read_write(void)	{
	bool l_result = false;
	g_rx_data_new = false;

	// check data buffer status
    // check the "lock" status of the virtual serial comunication channel
    // only one process at time can write to
	if(shmMcuUsart_t::WriterPidGet())	{
        // INTERRUPT TRIGGER of "Send byte"/"Last byte phisically send" or "Receive byte"

		// write/read procedure is on
		if( 
            (shmMcuUsart_t::pidMatches())
         && (g_callback_protocol_functions.tx_status_get__running())
        )	{
			// the current process is the process that write/add data to packet buffer
			// all processes have read the data
			// therefore ...

            // check the trigger of the interrupt
            // there are two trigger
            // - send byte
            // - last byte physically send (usefull in rs-485 half-duplex comunication)
			if(tx_fifo_full())	{
                // INTERRUPT TRIGGER of "SEND BYTE" (therefore the "user buffer" is full) ...

                //  - to transfer the content of user bufer to usart peripheral register
				//      - for example:
                //          - current use case / virtual usart 
                //              - shmMcuUsart_t::setData(g_tx_data); 
                //              - N.B.: the above statement is called by the following instruction via g_callback_sdk_functions.reg_write() function
                g_callback_protocol_functions.tx_buffer_management(nullptr);
                // check the user buffer status
                if(g_callback_protocol_functions.tx_status_get__completed()) {
                    // INTERRUPT configuration: configurare i parametri di interrupt per attivarsi quando l'ultimo byte è stato fisicamente spedito
                    //  - N.B.: nel caso della usart virtuale questa condizione equivale a quella che tutti i processi abbiano letto il byte

                    // in the current use case of "virtual usart", ...
                    // do nothing
                }
				// empty the fifo
				tx_fifo_empty_out();
			} else {
                // INTERRUPT TRIGGER of "Last byte phisically send"

                // the "last byte" is completely physically send
                // in the current case of virtual usart this means that ...
                // ... the last byte has been read from all other processes, therefore ...

                // the tx procedure can be considered terminated
                // the following callback function is usually used to set the enable/disable rx/tx in RS-485 half-duplex comunication chnnel
                g_callback_protocol_functions.tx_status_set__last_byte_send();

				// release/unlock the virtual channel
			 	shmMcuUsart_t::WriterPidClr();
			}

		} else {
			// the current process is not the process that add data to packet buffer
			// therefore ...

			// check if there is a byte to read or a line conflict raised
			// N.B.: the line conflict happen when the current process want to send data but 
			// another process has already locked the channel
			if(tx_fifo_full())	{
				// there is a data to send
				// therefore there is a line conflict
				l_result = true;

				// empty the fifo
				tx_fifo_empty_out();
			} else {
				// there is a data to read
				// --- g_rx_data = shmMcuUsart_t::getData();
                g_callback_protocol_functions.rx_buffer_management(nullptr);
                if(g_callback_protocol_functions.rx_status_get__completed()) {
                    g_callback_protocol_functions.tx_status_set__last_byte_send();
                }
                g_rx_data_new = true;
			}

		}
	} else {
		// the channel is free
		// check if there is a data to send 
		if(tx_fifo_full())	{
			// there is a data to send

			// get/lock the channel & activate the tx interrupt
			shmMcuUsart_t::WriterPidSet();
			// write data
    		// --- shmMcuUsart_t::setData(g_tx_data);
            g_callback_protocol_functions.tx_buffer_management(nullptr);
			// empty the fifo
			tx_fifo_empty_out();
		}
	}

	return l_result;
}

bool mcuUsart_t::tx_fifo_full   (void)	{
	return g_tx_data_new;
}

bool mcuUsart_t::rx_fifo_full   (void)	{
	return g_rx_data_new;
}

void mcuUsart_t::tx_fifo_empty_out   (void)	{
	g_tx_data_new = false;
}

void mcuUsart_t::tx_fifo_write  (char c)	{
	g_tx_data = c;
	g_tx_data_new = true;
}

uint16_t mcuUsart_t::rx_fifo_read  (void)	{
	return g_rx_data;
}


uint16_t mcuUsart_t::read(void)	{
	return g_rx_data;
}

