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
 * mcuPinPort2.cpp
 *
 *  Created on: Jul, 26 2024
 *      Author: Marco Dau
 */

#include <iostream>


#include "mcuPinPort2.h"


// mcuPinPort2_t::mcuPinPort2_t    (gpio_base_struct_t p_confPort) :
//      mcuPinPort_t   (p_confPort.mcuId, p_confPort.ptrPort, p_confPort.pin,  p_confPort.config)
//     ,g_pinPort2     {p_confPort.mcuId, p_confPort.ptrPort, p_confPort.pin,  p_confPort.config}
// {}

mcuPinPort2_t::mcuPinPort2_t    (gpio_base_struct_t p_confPort1, gpio_base_struct_t p_confPort2) :
     mcuPinPort_t   (p_confPort1.mcuId, p_confPort1.port, p_confPort1.pin,  p_confPort1.config)
    ,g_pinPort2     {p_confPort2.mcuId, p_confPort2.port, p_confPort2.pin,  p_confPort2.config}
{}



void mcuPinPort2_t::vhwInit (void) {

    mcuPinPort_t::vhwInit();
    g_pinPort2.vhwInit();
}

// void mcuPinPort2_t::vhwInit (uint8_t p_mcuId, uint8_t p_port,   uint8_t p_pin) {
//     mcuPinPort_t::vhwInit(p_mcuId, p_port, p_pin);
//     g_pinPort2.vhwInit(p_mcuId, p_port, p_pin);
// }
// 
// void mcuPinPort2_t::vhwInit (uint8_t p_mcuId,     uint8_t  p_port,   uint8_t p_pin, uint8_t p_pin2)    {
//     mcuPinPort_t::vhwInit(p_mcuId, p_port, p_pin);
//     g_pinPort2.vhwInit(p_mcuId, p_port, p_pin2);
// }


void mcuPinPort2_t::vhwLoop (void) {
    mcuPinPort_t::vhwLoop();
}

