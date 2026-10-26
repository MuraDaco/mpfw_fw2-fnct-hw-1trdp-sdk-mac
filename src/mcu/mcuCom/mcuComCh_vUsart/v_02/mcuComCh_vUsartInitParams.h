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
 * mcuComCh_vUsartInitParams.cpp
 *
 *  Created on: Sep, 1st 2026 (Tue)
  *      Author: Marco Dau
 */


#ifndef     MCU_COM_CH_V_USART_INIT_PARAMS_H_
#define     MCU_COM_CH_V_USART_INIT_PARAMS_H_

#include "hw0ConfigUsart.h"


struct  mcuComCh_vUsartInitParams_t {

    uint8_t         pid2;
    k_hw0Usart_t    ch;
};


#endif  //  MCU_COM_CH_V_USART_INIT_PARAMS_H_