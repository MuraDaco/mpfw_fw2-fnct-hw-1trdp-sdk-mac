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
 * mcuPinPort.h
 *
 *  Created on: Jun, 27 2024
 *      Author: Marco Dau
 */


#ifndef MCU_PIN_PORT_H
#define MCU_PIN_PORT_H

#include "mcuBase.h"

#include "hw0GpioDgIntfc.h"

#include "sdkPortDef.h"
#include "shmMcuPinPort.h"


// ****************************************************
// section start **** MACRO DEFINEs *****

    #define mcuPinPort_t_DATA_TYPE_PTRS(name)      &pph_##name.g_dtyStatus

    #define pinSet          *g_ptrPort = *g_ptrPort | (1 << g_pin)
    #define pinClr          *g_ptrPort = *g_ptrPort & ~(1 << g_pin)
    #define pinTst          *g_ptrPort & (1 << g_pin)

    #define PIN_SET         g_ptrPortArray[g_port] = g_ptrPortArray[g_port] |  (1 << g_pin)
    #define PIN_CLR         g_ptrPortArray[g_port] = g_ptrPortArray[g_port] & ~(1 << g_pin)
    #define PIN_TST         g_ptrPortArray[g_port] & (1 << g_pin)

    // section end   **** ENUMs DEFINITIONs ***** 
    // ****************************************************
    // --------------------------


// ****************************************************
// section start **** CLASS DEFINITION *****

class mcuPinPort_t :     public     mcuBase_t           // (specific platform) - common to all virtual hardware components
                        ,public     shmMcuPinPort_t     // (specific platform) - low level sdk (mcu registers simnlation)
                        ,public     hw0GpioDgIntfc_t    // (all platforms)     - component interface
{

// ****************************************************
// section start **** CONSTRUCTOR *****
    public:

    mcuPinPort_t  (                   uint8_t  p_port,    uint8_t p_pin, uint8_t p_dir  );
    mcuPinPort_t  (uint8_t p_mcuId,   uint8_t  p_port,    uint8_t p_pin, const gpio_config_struct_t& p_config);

    // section end   **** CONSTRUCTOR ***** 
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** PIN PORT MANAGEMENT *****

    public:

        void        pinConfig   (uint8_t  p_Port,      uint8_t p_pin, gpio_config_struct_t& p_config) override;
        void        setHigh     (void) override;
        void        setLow      (void) override;
        void        tglPin      (void) override;
        void        setPin      (bool p_state) override;
        bool        getPin      (void) override;

    protected:
        uint8_t* g_ptrPort;
        uint8_t  g_status;
        gpio_config_struct_t g_config;
        static uint8_t* g_ptrPortArray;
        uint8_t  g_mcuIdOwner;
        uint8_t  g_mcuIdCurrent;

        uint8_t* g_ptrShmPort;
        static uint8_t* g_ptrShmPortArray;

        uint8_t g_port;
        uint8_t g_pin;
        uint8_t g_dir;
        uint8_t g_valuePinOld;
        bool    g_valueModified;
        
    private:

    // section end   **** PIN PORT MANAGEMENT *****
    // ****************************************************
    // --------------------------
    // ****************************************************
    // section start **** DISPLAY  *****

        public:
            enum kStatusColor_t  {
                 low =  kColor_t::red
                ,high = kColor_t::green
            };

            static fmt_str_t g_fmtStr;
            fmt_str_t* getPinStatusFormattedString(void);
            bool update (void);
            static const char* const messagesMatrix[][2];

        // section end   **** DISPLAY *****
        // ****************************************************
        // --------------------------



};


#endif 	// MCU_PIN_PORT_H
