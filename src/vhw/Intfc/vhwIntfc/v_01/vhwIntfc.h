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
 * dtyCmmnHwGnrlAbst0Intfc.h
 *
 *  Created on: Apr,  6th 2025 (Sun)
 *      Author: Marco Dau
 */


#ifndef     VHW_INFC_H
#define     VHW_INFC_H

#include <cstdint>

#include "vhwData.h"
using namespace vhwData_t;
// ****************************************************
// section start **** CLASS DEFINITION *****

class vhwIntfc_t
{

// ****************************************************
// section start **** PROCESS MANAGEMENT *****

    public:
        virtual void vhwInit ([[maybe_unused]] uint8_t p_mcuId, [[maybe_unused]] uint8_t* p_ptrPort, [[maybe_unused]] uint8_t p_pin) {};
        virtual void vhwInit ([[maybe_unused]] uint8_t p_mcuId, [[maybe_unused]] uint8_t  p_Port,    [[maybe_unused]] uint8_t p_pin) {};
        virtual void vhwInit (uint8_t*) {};
        virtual void vhwInit (void*) {};
        virtual void vhwInit (void) {};
        virtual void vhwInit ([[maybe_unused]] vhwData_t::init_params_t* p_initParams) {};

        virtual void vhwLoop (void) {};
        virtual void vhwLoop ([[maybe_unused]]uint8_t p_mcuId) {};

        virtual void vhwEnd (void) {};

    // section end   **** PROCESS MANAGEMENT *****
    // ****************************************************
    // --------------------------


};



#endif  //  VHW_INFC_H
