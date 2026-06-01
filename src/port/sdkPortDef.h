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
 * sdkPortDef.h
 *
 *  Created on: Jan, 6th 2025
 *      Author: Marco Dau
 */


#ifndef SDK_PORT_DEF_H
#define SDK_PORT_DEF_H

#include <cstdint>

#define SDK_MCU_PORT_A          0
#define SDK_MCU_PORT_B          1
#define SDK_MCU_PORT_C          2
#define SDK_MCU_PORT_D          3
#define SDK_MCU_PORT_E          4
#define SDK_MCU_PORT_F          5
#define SDK_MCU_PORT_G          6
#define SDK_MCU_PORT_H          7
#define SDK_MCU_PORT_NUM        8

#define SDK_MCU_PORT_A_PTR      &sdkPortDef_t::Port[SDK_MCU_PORT_A]
#define SDK_MCU_PORT_B_PTR      &sdkPortDef_t::Port[SDK_MCU_PORT_B]
#define SDK_MCU_PORT_C_PTR      &sdkPortDef_t::Port[SDK_MCU_PORT_C]
#define SDK_MCU_PORT_D_PTR      &sdkPortDef_t::Port[SDK_MCU_PORT_D]
#define SDK_MCU_PORT_E_PTR      &sdkPortDef_t::Port[SDK_MCU_PORT_E]
#define SDK_MCU_PORT_F_PTR      &sdkPortDef_t::Port[SDK_MCU_PORT_F]
#define SDK_MCU_PORT_G_PTR      &sdkPortDef_t::Port[SDK_MCU_PORT_G]
#define SDK_MCU_PORT_H_PTR      &sdkPortDef_t::Port[SDK_MCU_PORT_H]

class sdkPortDef_t {

public:

    static uint8_t      Port[];

};


#endif 	// SDK_PORT_DEF_H
