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
 * mcuUsartRs485.h
 *
 *  Created on: Feb, 13th 2026  (Fri)
 *      Author: Marco Dau
 */


#ifndef MCU_USART_H
#define MCU_USART_H

#include "mcuBase.h"
#include "shmMcuUsart.h"
#include "hw0UsartIntfc.h"
using namespace fw2::fnct::base::hw;

// using namespace fw2::fnct::base;

class mcuUsartRs485_t :  public mcuBase_t
                        ,public shmMcuUsart_t
                        ,public hw0UsartIntfc_t
{
    public:

        mcuUsartRs485_t  (                   k_hw0Usart_t p_ch);
        mcuUsartRs485_t  (uint8_t p_pid2,    k_hw0Usart_t p_ch);

        // general
            void    init                    (void);
            bool    chkInterruptsRaised     (void)            override;
        // transmit
            bool    tx_chkInterruptRaised   (void)            override;
            void    tx_eventBegin           (void)            override;
            void    tx_eventFirstData       (void)            override;
            void    tx_eventSendData        (uint8_t p_data)  override;
            void    tx_eventLastData        (void)            override;
            void    tx_eventEnd             (void)            override;

        // receive
            bool    rx_chkError_overrun     (void)            override;
            void    rx_eventBegin           (void)            override;
            uint8_t rx_eventReceiveData     (void)            override;
            void    rx_eventEnd             (void)            override;


    protected:
        void    chEnable            (void);

private:

    // comConfigRs485Interface_t*  g_pConfig;
    // uint8_t                     g_mcuId;
    k_hw0Usart_t                g_ch;



};


#endif 	// MCU_USART_H

