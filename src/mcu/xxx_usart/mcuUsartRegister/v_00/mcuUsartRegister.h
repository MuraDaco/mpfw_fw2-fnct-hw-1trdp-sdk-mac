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
 * mcuUsart.h
 *
 *  Created on: Jun, 27 2024
 *      Author: Marco Dau
 */


#ifndef MCU_USART_REGISTER_H
#define MCU_USART_REGISTER_H

#include "mcuBase.h"
#include "vhwProxIntfc.h"
#include "shmMcuUsart.h"
#include "comChannelInterface.h"


class mcuUsart_t :   public mcuBase_t
                    ,public vhwProxIntfc_t
                    ,public shmMcuUsart_t
                    ,public comChannelInterface_t
{
public:

    mcuUsart_t  (                   uint8_t p_mcuId, k_mcuUsart_t p_ch);
    mcuUsart_t  (uint8_t p_pid2,    uint8_t p_mcuId, k_mcuUsart_t p_ch);


    void vhwInit (void)         override;
    void vhwLoop (void)         override;

    void    chEnable            (void);
    uint8_t check_read_write    (void);
    static void    tx_fifo_write       (void* p_ptrData, char c);
    static uint8_t rx_fifo_read        (void* p_ptrData);

    // transmit
    void    tx_eventBegin           (void)                              override;
    void    tx_eventFirstData       (void)                              override;
    void    tx_eventSendData        (void* p_ptrData, uint8_t p_data)   override;
    void    tx_eventLastData        (void)                              override;
    void    tx_eventEnd             (void)                              override;

    // receive
    uint8_t rx_eventReceiveData     (void* p_PtrData)                   override;

private:

    uint8_t g_mcuId;
    k_mcuUsart_t    g_ch;



};


#endif 	// MCU_USART_H

