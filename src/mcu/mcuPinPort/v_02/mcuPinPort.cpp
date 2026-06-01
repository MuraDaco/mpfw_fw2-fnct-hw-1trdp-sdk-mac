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
 * mcuPinPort.cpp
 *
 *  Created on: Jun, 27 2024
 *      Author: Marco Dau
 */

#include "mcuPinPort.h"

#include <iostream>

#include "mcuDeviceConfig.h"

// ****************************************************
// section start **** CONSTRUCTOR *****

    mcuPinPort_t::mcuPinPort_t(                 uint8_t  p_port, uint8_t p_pin, const gpio_config_struct_t& p_config) :
         g_ptrPort      {&g_ptrPortArray[p_port]}
        ,g_config       {p_config}
        ,g_mcuIdOwner   {MCU_DEVICE_DEFAULT}
        ,g_ptrShmPort   {nullptr}
        ,g_port         {p_port}
        ,g_pin          {p_pin}
        // ,g_dtyStatus    {&g_status}
    {}

    mcuPinPort_t::mcuPinPort_t(uint8_t p_mcuId, uint8_t  p_port, uint8_t p_pin, const gpio_config_struct_t& p_config) :
         g_ptrPort      {&g_ptrPortArray[p_port]}
        ,g_config       {p_config}
        ,g_mcuIdOwner   {p_mcuId}
        ,g_ptrShmPort   {nullptr}
        ,g_port         {p_port}
        ,g_pin          {p_pin}
        // ,g_dtyStatus    {&g_status}
    {}

    // section end   **** CONSTRUCTOR ***** 
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** PIN PORT MANAGEMENT *****

    // private:
        uint8_t* mcuPinPort_t::g_ptrPortArray = sdkPortDef_t::Port;
        uint8_t* mcuPinPort_t::g_ptrShmPortArray = nullptr;
        // uint8_t  mcuPinPort_t::g_mcuIdOwner = MCU_DEVICE_DEFAULT;

    // private:

    // public:
        uint32_t hw0GpioDgIntfc_t::pinRead   ([[maybe_unused]] uint8_t p_port,      [[maybe_unused]] uint32_t p_pin)    {
            return 0;
        }

        void hw0GpioDgIntfc_t::pinWrite  ([[maybe_unused]] uint8_t  p_Port,      [[maybe_unused]] uint32_t p_pin, [[maybe_unused]] uint8_t p_status) {

        }

        void mcuPinPort_t::pinConfig ([[maybe_unused]] uint8_t  p_Port,      [[maybe_unused]] uint8_t p_pin, gpio_config_struct_t& p_config)    {
            g_config.type = p_config.type;
            g_config.mode = p_config.mode;
        }

        void mcuPinPort_t::setHigh        (void)    {
            if(
                (
                    (MCU_DEVICE_DEFAULT == g_mcuIdOwner) ||
                    (g_mcuIdCurrent     == g_mcuIdOwner)
                ) &&
                (k_modePort_output == g_config.mode)
            ) pinSet;
        }

        void mcuPinPort_t::setLow         (void)    {
            if(
                (
                    (MCU_DEVICE_DEFAULT == g_mcuIdOwner) ||
                    (g_mcuIdCurrent     == g_mcuIdOwner)
                ) &&
                (k_modePort_output == g_config.mode)
            ) pinClr;
        }

        void mcuPinPort_t::tglPin       (void)  {
            if(pinTst)  {
                pinClr;
                g_valuePinOld = 0;
            }
            else    {
                pinSet;
                g_valuePinOld = 1;
            }
            g_valueModified = true;
        }

        void mcuPinPort_t::setPin       (bool p_state)  {
            if(p_state) {
                pinSet;
                g_valuePinOld = 1;
            }
            else    {
                pinClr;
                g_valuePinOld = 0;
            }
        }

        bool mcuPinPort_t::getPin       (void)    {
            g_valuePinOld = pinTst;
            if(pinTst)  {
                g_valuePinOld = 1;
            }
            else    {
                g_valuePinOld = 0;
            }
            return pinTst;
        }

    // section end   **** PIN PORT MANAGEMENT *****
    // ****************************************************
    // --------------------------
    // ****************************************************
    // section start **** DISPLAY  *****

            const char* const mcuPinPort_t::messagesMatrix[][2] = {
                 {"low " ,"pressed"     }
                ,{"high" ,"released"    }
                ,{nullptr}
            };

            fmt_str_t mcuPinPort_t::g_fmtStr;

            fmt_str_t* mcuPinPort_t::getPinStatusFormattedString(void)  {
                uint8_t l_pinStatus = getPin();
                if(l_pinStatus) {
                    g_fmtStr.color = kColor_t::blue;
                } else {
                    g_fmtStr.color = kColor_t::red;
                }

                g_fmtStr.str = messagesMatrix[l_pinStatus][0];
                return &g_fmtStr;
            }

            bool mcuPinPort_t::update       (void)    {
                bool l_result = false;
                if(pinTst)  {
                    l_result = (g_valuePinOld == 0);
                } else {
                    l_result = (g_valuePinOld == 1);
                }
                return l_result;
                //return false;
            }

        // section end   **** DISPLAY *****
        // ****************************************************
        // --------------------------

