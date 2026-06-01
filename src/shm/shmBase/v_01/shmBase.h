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
 * shmBase.h
 *
 *  Created on: Jan, 7th 2025 (tue)
 *      Author: Marco Dau
 */


#ifndef SHM_BASE_H
#define SHM_BASE_H

#include <cstdint>


class shmBase_t {

// ****************************************************
// section start **** INITIALIZATION MANAGEMENT *****
    public:

        enum k_statusInit_t   {
             k_statusInit_RUN       // ("RUN - shared memory initialization is not yet completed\n")
            ,k_statusInit_ERR_PROCESS_BUF       // ("ERROR - opening shared memory\n")
            ,k_statusInit_FULL      // ("FULL - processes buffer is full\n")
            ,k_statusInit_OK        // ("OK - shared memory initialization is completed\n")
            ,k_statusInit_UNLINK    // ("OK - shared memory unlink has been done\n")
            ,k_statusInit_NUM
        };

        static k_statusInit_t g_status;

        static int32_t g_pid;

    // section end   **** INITIALIZATION MANAGEMENT ***** 
    // ****************************************************
    // --------------------------


};


#endif 	// SHM_BASE_H
