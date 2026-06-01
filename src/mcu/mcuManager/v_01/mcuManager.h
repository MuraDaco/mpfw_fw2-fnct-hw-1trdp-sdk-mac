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
 * mcuManager.h
 *
 *  Created on: Dec, 20th 2024
 *      Author: Marco Dau
 */


#ifndef MCU_MANAGER_H
#define MCU_MANAGER_H

#include "dtyCmmnHwGnrlAbst0Intfc.h"

#include <cstdint>
#include "mcuBase.h"
#include "shmManager.h"

#define GET_PTR_BUFFER_PROX_FUNC        reinterpret_cast<void*>(shmManager_t::getpBufferProx)


class mcuManager_t:  protected   mcuBase_t
                    ,public     dtyCmmnHwGnrlAbst0Intfc_t
                    ,public      shmManager_t
{

public:
    static void init                        (init_params_t* p_initParams);

};


#endif 	// MCU_MANAGER_H
