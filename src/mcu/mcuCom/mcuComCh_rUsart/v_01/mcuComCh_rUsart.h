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
 * mcuComCh_rUsart.h
 *
 *  Created on: Aug, 30th 2026  (Sun)
 *      Author: Marco Dau
 */


#ifndef MCU_COM_CH_R_USART_H
#define MCU_COM_CH_R_USART_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

#include <string>
#include <sys/ioctl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;


#include "hwComChIntfc.h"
using namespace fw2::fnct::base::hw;



class mmcuComCh_rUsart_t :  public hwComChIntfc_t
{
    public:

        mmcuComCh_rUsart_t  (char* p_strDevice);

        // general
            void    init                    (void);
            void    end                     (void);
            bool    chkInterruptsRaised     (void)            override;
        // transmit
            bool    tx_chkInterruptRaised   (void)            override;
            void    tx_eventBegin           (void)            override;
            void    tx_eventFirstData       (void)            override;
            void    tx_eventSendData        (uint8_t p_data)  override;
            void    tx_eventLastData        (void)            override;
            void    tx_eventEnd             (void)            override;

        // receive
            bool    rx_chkInterruptRaised   (void)            override;
            bool    rx_chkError_overrun     (void)            override;
            void    rx_eventBegin           (void)            override;
            uint8_t rx_eventReceiveData     (void)            override;
            void    rx_eventEnd             (void)            override;


    protected:
        char*   g_strDevice[50];
        uint8_t g_error;
        uint8_t g_error;
        int     g_fd;

private:


};


#endif 	// MCU_COM_CH_R_USART_H

