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
 * mcuPinPort2.h
 *
 *  Created on: Jul, 26 2024
 *      Author: Marco Dau
 */


#ifndef MCU_PIN_PORT_2_H
#define MCU_PIN_PORT_2_H

#include "mcuPinPort.h"

//#define DEF_MCU_PIN_PORT2_DEVICE_CONFIG(name, id1, config1, id2, config2)           \
//            mcuPinPort2_t mcu_##id1##_##id2##_##name                            (   \
//                {id1, MCU_##id1##_##name##_##config1##_PORT_PTR, MCU_##id1##_##name##_##config1##_PIN, mcuPinPort_t::config1},  \
//                {id2, MCU_##id2##_##name##_##config2##_PORT_PTR, MCU_##id2##_##name##_##config2##_PIN, mcuPinPort_t::config2}   \
//            );
                
// #define mcuPinPort2_t_DATA_TYPE_PTRS(name)      &pph_##name.g_dtyStatus, &pph_##name.g_pinPort2.g_dtyStatus


class mcuPinPort2_t : public mcuPinPort_t {


public:


    //mcuPinPort2_t(uint8_t p_mcuId,   uint8_t* p_ptrPort,   uint8_t p_pin,                        const gpio_config_struct_t& p_config);
//    mcuPinPort2_t(gpio_base_struct_t p_confPort);
    mcuPinPort2_t(gpio_base_struct_t p_confPort1, gpio_base_struct_t p_confPort2);
    //mcuPinPort2_t(uint8_t p_mcuId,   uint8_t* p_ptrPort,   uint8_t p_pin,                        const gpio_config_struct_t& p_config);
    //mcuPinPort2_t(                   uint8_t* p_ptrPort,   uint8_t p_pin, void (*p_func)(void),  const gpio_config_struct_t& p_config );
    //mcuPinPort2_t(uint8_t p_mcuId,   uint8_t* p_ptrPort,   uint8_t p_pin, void (*p_func)(void),  const gpio_config_struct_t& p_config );

    // void vhwInit            (uint8_t p_mcuId,     uint8_t  p_port,   uint8_t p_pin)    override;
    // virtual void vhwInit    (uint8_t p_mcuId,     uint8_t  p_port,   uint8_t p_pin, uint8_t p_pin2);
    void vhwInit (void)    override;
    void vhwLoop (void)        override;

    // 
    mcuPinPort_t  g_pinPort2;

};


#endif 	// MCU_PIN_PORT_2_H
