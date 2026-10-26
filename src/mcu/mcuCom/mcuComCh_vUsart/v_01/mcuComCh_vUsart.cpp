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
 * mcuComCh_vUsart.cpp
 *
 *  Created on: Aug, 30th 2026  (Sun)
 *      Author: Marco Dau
 */

#include "mcuComCh_vUsart.h"

// ****************************************************
// section start **** CONSTRUCTOR *****

    mcuComCh_vUsart_t::mcuComCh_vUsart_t(mcuComUsartInitParams_t* p_pConfig) :
         shmMcuUsart_t      {p_pConfig->pid2}
        ,g_ch               {p_pConfig->ch}
    {}

    // section end   **** CONSTRUCTOR ***** 
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** EVENTS *****

    // public:
        void mcuComCh_vUsart_t::init (void) {
            shmMcuUsart_t::init();
            chEnable();
        }

        bool    mcuComCh_vUsart_t::chkInterruptsRaised     (void)             {
            // return shmMcuUsart_t::WriterPidGet();
            return WriterPidGet();  // derived from shmMcuUsart_t
        }

        bool    mcuComCh_vUsart_t::tx_chkInterruptRaised    (void)             {
            // return shmMcuUsart_t::pidMatches();
            return pidMatches();    // derived from shmMcuUsart_t
        }


        void    mcuComCh_vUsart_t::tx_eventBegin           (void)                              {
            // "virtual" case:  do nothing
            // "real" case:     1. enable tx interrupt
            //                  2. set tx-enable pin (automatically clear rx-enable pin)
            // g_pConfig->setTxEnablePin();
        }

        void    mcuComCh_vUsart_t::tx_eventFirstData       (void)                              {
            //  "virtual" case: lock the channel setting [writerPid] parameter
            //  "real" case:    do nothing
			shmMcuUsart_t::WriterPidSet();
        }

        void mcuComCh_vUsart_t::tx_eventSendData          (uint8_t p_data)	{
            shmMcuUsart_t::setData(p_data); 
        }

        void    mcuComCh_vUsart_t::tx_eventLastData        (void)                              {
            // "virtual" case:    do nothing
            // "real" case:       the tx interrupt has to be configured to raise when the last byte is phisically and completely sent
        }

        void    mcuComCh_vUsart_t::tx_eventEnd             (void)                              {
            // "virtual" case:    un-lock the channel clearing [writerPid] parameter
            // "real" case:       1. disable tx interrupt
            //                    2. clear tx-enable pin (automatically set rx-enable pin)
            shmMcuUsart_t::WriterPidClr();
//                #include "mcuUsartRs485_dbgToken_exit.h"
            // g_pConfig->clrTxEnablePin();
        }


    // receive
        bool    mcuComCh_vUsart_t::rx_chkInterruptRaised    (void)             {
            // return !shmMcuUsart_t::pidMatches();
            return !pidMatches();    // derived from shmMcuUsart_t
        }

        bool    mcuComCh_vUsart_t::rx_chkError_overrun   (void)                         {
            return false;
        }

        // It is called in an "application thread/routine" when the user makes ready to receive a packet 
        // therefore when the buffer status is set to "waiting to receive a packet"
        void    mcuComCh_vUsart_t::rx_eventBegin           (void)                         {
            // "virtual" case:  
            //      . do nothing
            //      . it is not necessary to enable the "rx interrupt" because the "interrupt thread/routine" is always performed
            // "real" case:     
            //      1. enable rx interrupt
            //      2. set rx-enable pin (automatically clear tx-enable pin)
            // Enable receiver interrupt.
        }

        // It is called in an "interrupt thread/routine" when the buffer status is "rx running"
        uint8_t    mcuComCh_vUsart_t::rx_eventReceiveData     (void)                         {
            //  "virtual" case: 
            //      . read from the shared memory buffer, the buffer that is shared with other processes (N.B.: not threads but processes)) 
            //  "real" case: 
            //      . read from the mcu usart register
           	return shmMcuUsart_t::getData();
        }

        // It is called in an "interrupt thread/routine" when the "last byte has been received" or error is detected
        // when the last byte is received the buffer status is set to "rx completed" 
        // when error is detected the buffer status is set to "rx error"
        // 
        void    mcuComCh_vUsart_t::rx_eventEnd             (void)                         {
            // "virtual" case:
            //      . do nothing
            // "real" case:     
            //      1. DIS-able rx interrupt
        }


        void mcuComCh_vUsart_t::chEnable       (void)  {
            shmMcuUsart_t::chEnable (g_ch);
        }

    // section end   **** EVENTS *****
    // ****************************************************
    // --------------------------





