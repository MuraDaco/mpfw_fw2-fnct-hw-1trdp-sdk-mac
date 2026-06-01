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


#ifndef MCU_USART_H
#define MCU_USART_H

#include "dtyCmmnHwGnrlAbst0Intfc.h"
#include "mcuBase.h"
#include "shmMcuUsart.h"


class mcuUsart_t :   public mcuBase_t
                    ,public dtyCmmnHwGnrlAbst0Intfc_t
                    ,public shmMcuUsart_t
{
public:

    mcuUsart_t  (                   uint8_t p_mcuId, k_mcuUsart_t p_ch);
    mcuUsart_t  (uint8_t p_pid2,    uint8_t p_mcuId, k_mcuUsart_t p_ch);


    void vhwInit (void)         override;
    //void vhwLoop (void)         override;

    bool tx_fifo_full           (void);
    bool rx_fifo_full           (void);
    void tx_fifo_empty_out      (void);
    void tx_fifo_write          (char c);
    uint16_t rx_fifo_read       (void);
    bool check_read_write       (void);
    uint16_t read               (void);
    void chEnable               (void);

private:

    uint8_t g_mcuId;
    // uint8_t g_channel;
    k_mcuUsart_t    g_ch;
    bool            g_tx_data_new;
    bool            g_rx_data_new;
    uint16_t        g_tx_data;
    uint16_t        g_rx_data;

};


#endif 	// MCU_USART_H
