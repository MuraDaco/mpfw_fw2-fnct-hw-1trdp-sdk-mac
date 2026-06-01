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

// #include <iostream>

#include "mcuUsart.h"

#include "sysDebugModuleDefine.h"
#ifdef      DEBUG_DEF_MCU_USART_CPP
    #include "sysDebug.h"
#endif  //  DEBUG_DEF_MCU_USART_CPP


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

void mcuUsart_t::check_read_write(void)	{


	// check data buffer status
    // check the "lock" status of the virtual serial comunication channel
    // only one process at time can write to
	// if(shmMcuUsart_t::WriterPidGet())	{
	if(g_channel->chkInterruptsRaised())	{
        // INTERRUPT TRIGGER of "Receive byte" or "Send byte"/"Last byte phisically send"

		// write/read procedure is on
		// if(shmMcuUsart_t::pidMatches()) {
    	if(g_channel->chkTxInterruptRaised())	{
			// the current process is the process that write/add data to packet buffer
			// all processes have read the data
			// therefore ...

            g_buffer->tx_interrupt_buffer_management();

		} else {
			// the current process is not the process that add data to packet buffer
			// therefore ...
    		// there is a data to read

            g_buffer->rx_interrupt_buffer_management();

		}
	} else {
		// the channel is free
		
        g_buffer->tx_interrupt_buffer_management();

	}
}

void mcuUsart_t::tx_fifo_write(void* p_ptrData, char c)	{
    UNUSED(p_ptrData);
    shmMcuUsart_t::setData(c); 
}


uint8_t mcuUsart_t::rx_fifo_read  (void* p_ptrData)	{
    UNUSED(p_ptrData);
	return shmMcuUsart_t::getData();
}

