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

#include "dtyCmmnHwPortAbst1Intfc.h"

#include "sdkPortDef.h"
//#include "dtyUint8.h"
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

class mcuPinPort_t :     public     mcuBase_t
                        ,public     dtyCmmnHwPortAbst1Intfc_t
                        ,public     shmMcuPinPort_t 
{

//// ****************************************************
//// section start **** ENUMs DEFINITIONs *****
//    public:
//
//        enum k_typePort_t   {
//             k_typePort_digital
//            ,k_typePort_analog
//            ,k_typePort_usart
//            ,k_typePort_spi
//            ,k_typePort_i2c
//        };
//
//        enum k_modePort_t   {
//             k_modePort_input
//            ,k_modePort_output
//            ,k_modePort_data
//            ,k_modePort_clck
//        };
//
//    // section end   **** ENUMs DEFINITIONs ***** 
//    // ****************************************************
//    // --------------------------
//// ****************************************************
//// section start **** TYPEs DEFINITIONs *****
//    public:
//
//        typedef struct gpio_config_struct
//        {
//            k_typePort_t type;
//            k_modePort_t mode;
//        } gpio_config_struct_t;
//
//        typedef struct gpio_base_struct
//        {
//            uint8_t     mcuId;
//            uint8_t     port;
//            uint8_t     pin;
//            const gpio_config_struct_t& config;
//        } gpio_base_struct_t;
//
//        typedef struct gpio_conf2_struct
//        {
//            uint8_t*    ptrPort;
//            uint8_t     pin;
//        } gpio_config2_struct_t;
//
//        typedef struct gpio_conf3_struct
//        {
//            uint8_t     mcuId;
//            uint8_t     port;
//            uint8_t     pin;
//        } gpio_config3_struct_t;
//
//    // section end   **** TYPEs DEFINITIONs ***** 
//    // ****************************************************
//    // --------------------------
// ****************************************************
// section start **** CONSTANTs DEFINITIONs *****
    public:

        static constexpr gpio_config_struct_t din       = {k_typePort_digital ,k_modePort_input  };
        static constexpr gpio_config_struct_t dout      = {k_typePort_digital ,k_modePort_output };
        static constexpr gpio_config_struct_t ain       = {k_typePort_analog  ,k_modePort_input  };
        static constexpr gpio_config_struct_t aout      = {k_typePort_analog  ,k_modePort_output };

        static constexpr gpio_config_struct_t usart_rx  = {k_typePort_usart   ,k_modePort_input  };
        static constexpr gpio_config_struct_t usart_tx  = {k_typePort_usart   ,k_modePort_output };
        static constexpr gpio_config_struct_t spi_data  = {k_typePort_spi     ,k_modePort_data };
        static constexpr gpio_config_struct_t spi_clck  = {k_typePort_spi     ,k_modePort_clck };
        static constexpr gpio_config_struct_t i2c_data  = {k_typePort_i2c     ,k_modePort_data };
        static constexpr gpio_config_struct_t i2c_clck  = {k_typePort_i2c     ,k_modePort_clck };

    // section end   **** CONSTANTs DEFINITIONs ***** 
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** CONSTRUCTOR *****
    public:

    mcuPinPort_t  (uint8_t p_mcuId,   uint8_t  p_port,    uint8_t p_pin, const gpio_config_struct_t& p_config);

    // section end   **** CONSTRUCTOR ***** 
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** PROCESS MANAGEMENT *****

    public:
        //void vhwInit   	            (uint8_t p_mcuId,  uint8_t  p_Port,    uint8_t p_pin) override;
        void vhwInit                (void) override;
        void vhwLoop   	            (void) override;
        // bool loopChildren           (tuiGraphicUnit_t* p_this) override;
        // void end       	            (tuiGraphicUnit_t* p_this) override;
        // void endChildren            (tuiGraphicUnit_t* p_this) override;

    // section end   **** PROCESS MANAGEMENT *****
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** PIN PORT MANAGEMENT *****

    private:
        uint8_t* g_ptrPort;
        uint8_t  g_status;
        gpio_config_struct_t g_config;
        static uint8_t* g_ptrPortArray;
    //protected:
        uint8_t  g_mcuId;

        uint8_t* g_ptrShmPort;
        static uint8_t* g_ptrShmPortArray;

    protected:
        uint8_t  g_port;
        uint8_t  g_pin;
        uint8_t     g_valuePinOld;
        //bool     g_valueChanged;
        bool    g_valueModified;
        
    public:
        // dtyUint8_t g_dtyStatus;

        uint16_t pinRead        (uint8_t  p_port,      uint8_t p_pin) override;
        void     pinWrite       (uint8_t  p_Port,      uint8_t p_pin, uint16_t p_status) override;
        void     pinConfig      (uint8_t  p_Port,      uint8_t p_pin, gpio_config_struct_t& p_config) override;
        void setHigh        (uint8_t p_mcuId)   override;
        void setLow         (uint8_t p_mcuId)   override;
        void vhwSetHigh     (uint8_t p_mcuId)   override;
        void vhwSetLow      (uint8_t p_mcuId)   override;
        void tglPin          (void) override;
        void setPin          (bool p_state) override;
        bool getPin          (void) override;

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
        fmt_str_t* getPinStatusFormattedString(void) override;
        bool update (void) override;
        static const char* const messagesMatrix[][2];

    // section end   **** DISPLAY *****
    // ****************************************************
    // --------------------------



};


#endif 	// MCU_PIN_PORT_H
