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

#include "mcuBase.h"
#include "vhwProxIntfc.h"
#include "shmMcuUsart.h"
#include "mcuUsartRegister.h"


class mcuUsartEvents_t :   public comEventInterface_t
{
public:

    mcuUsartEvents_t  (mcuUsartRegister_t* p_register);


    void vhwInit (void)         override;
    void vhwLoop (void)         override;

    void    chEnable            (void);
    uint8_t check_read_write    (void);
    static void    tx_fifo_write       (void* p_ptrData, char c);
    static uint8_t rx_fifo_read        (void* p_ptrData);

    static callback_protocol_functions_t g_callback_protocol_functions;

private:

    uint8_t g_mcuId;
    k_mcuUsart_t    g_ch;



};


#endif 	// MCU_USART_H

