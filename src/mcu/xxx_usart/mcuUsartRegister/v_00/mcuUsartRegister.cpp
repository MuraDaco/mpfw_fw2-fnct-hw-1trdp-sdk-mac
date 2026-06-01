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
 * mcuUsartRegister.cpp
 *
 *  Created on: Feb, 12th 2026  (Thu)
 *      Author: Marco Dau
 */

// #include <iostream>

#include "mcuUsartRegister.h"

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
    void    tx_eventBegin           (void)                              {
        // 1. enable tx interrupt (only about "real" case )
        // 2. clear  rx-enable pin (only about "real" case )

    }

    void    tx_eventFirstData       (void)                              {
        // enable channel
        //  2.a. "virtual" case                     -> set [writerPid] parameter
        //  2.b. "real" case (rs485 half-duplex)    -> set tx-enable pin

    }

    void    tx_eventSendData        (void* p_ptrData, uint8_t p_data)   {

    }

    void    tx_eventLastData        (void)                              {

        // 2. the tx interrupt has to be configured to raise when the last byte is phisically and completely sent
    }

    void    tx_eventEnd             (void)                              {

        // disable tx interrupt; clr enable_tx pin / set enable_rx pin
    }


    // receive
    uint8_t rx_eventReceiveData     (void* p_PtrData)                   {

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

#ifdef      DEBUG_DEF_MCU_USART_CPP
    {
        static bool l_once = true;
        if(l_once)  {
            char l_str[] = "debug - check_read_write";
            sysDebug_t::msg(4,4, l_str);
            l_once = false;
        }
    }
#endif  //  DEBUG_DEF_MCU_USART_CPP

	// check data buffer status
    // check the "lock" status of the virtual serial comunication channel
    // only one process at time can write to
	if(shmMcuUsart_t::WriterPidGet())	{
        // INTERRUPT TRIGGER of "Receive byte" or "Send byte"/"Last byte phisically send"

#ifdef      DEBUG_DEF_MCU_USART_CPP
    {
        static bool l_once = true;
        if(l_once)  {
            char l_str[] = "debug - INTERRUPT TRIGGER";
            sysDebug_t::msg(4,4, l_str);
            l_once = false;
        }
    }
#endif  //  DEBUG_DEF_MCU_USART_CPP

		// write/read procedure is on
		if(shmMcuUsart_t::pidMatches()) {
			// the current process is the process that write/add data to packet buffer
			// all processes have read the data
			// therefore ...

#ifdef      DEBUG_DEF_MCU_USART_CPP
    {
        static bool l_once = true;
        if(l_once)  {
            char l_str[] = "debug - interrupt write/read procedure is on";
            sysDebug_t::msg(4,4, l_str);
            l_once = false;
        }
    }
#endif  //  DEBUG_DEF_MCU_USART_CPP

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

#ifdef      DEBUG_DEF_MCU_USART_CPP
                char l_str[] = "debug - tx completed";
                sysDebug_t::msg(4,4, l_str);
                // sysDebug_t::msg(4,4, " test debug message "); // warning compiler: "ISO C++11 does not allow conversion from string literal to 'char *' [-Wwritable-strings]"
                // sysDebug_t::exit();
#endif  //  DEBUG_DEF_MCU_USART_CPP

  				// release/unlock the virtual channel
       		 	shmMcuUsart_t::WriterPidClr();
            }

		} else {
			// the current process is not the process that add data to packet buffer
			// therefore ...
    		// there is a data to read

			// check if there is a line conflict raised
			// N.B.: the line conflict happen when the current process want to send data but 
			// another process has already locked the channel
			if(g_callback_protocol_functions.tx_status_get__running())	{
				// there is a data to send
				// therefore there is a line conflict
				l_result = TX_FAIL_LINE_CONFLICT;

			} else {
                // // check status rxBuffer then read data
                // if(g_callback_protocol_functions.rx_status_get__waiting_packets()) {
                //     g_callback_protocol_functions.rx_status_set__running();
                // }

                if(g_callback_protocol_functions.rx_status_get__running()) {
    				// --- g_rx_data = shmMcuUsart_t::getData();
                    g_callback_protocol_functions.rx_buffer_management(nullptr);
                    if(g_callback_protocol_functions.rx_status_get__completed()) {
                        // do nothing ...
                    }
    			}

            }

		}
	} else {
		// the channel is free
		
        // // reset rx status if it is set to "running"
        // if(g_callback_protocol_functions.rx_status_get__running()) {
        //     g_callback_protocol_functions.rx_status_set__free();
        // }

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

