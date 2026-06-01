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
 * shmMcuPinPort.h
 *
 *  Created on: Jul, 1st 2024
 *      Author: Marco Dau
 */


#ifndef SHM_MCU_PIN_PORT_H
#define SHM_MCU_PIN_PORT_H

#include <cstdint>

#include "shmBase.h"
#include "sdkPortDef.h"
#include "dtyTypesDefs.h"
using namespace dtyTypesDefs_t; 


class shmMcuPinPort_t: public shmBase_t  {

// ****************************************************
// section start **** MCU PIN PORTS SHARED MEMORY MANAGEMENT *****
    public:

        enum k_statusInit_t   {
             k_statusInit_RUN           // ("RUN - shared memory initialization is not yet completed\n")
            ,k_statusInit_ERR_OPEN      // ("ERROR - opening shared memory\n")
            ,k_statusInit_ERR_MMAP      // ("ERROR - memory map\n")
            ,k_statusInit_OK            // ("OK - shared memory initialization is completed\n")
            ,k_statusInit_UNLINK        // ("OK - shared memory unlink has been done\n")
        };

    public:
        static uint8_t* init                    (bool p_shm_reset);
        static void end                         (void);
        static bool getInitStatus               (void);
        static const char* getInitStatusString  (void);

        static uint8_t* getPtr      (uint8_t p_port);
        static uint8_t* getPtr      (void);

    private:
        typedef struct _shared_mem_struct
        {
            uint8_t portArray[SDK_MCU_PORT_NUM];
        } shared_mem_struct_t;

        //typedef uint8_t portArray_t[SDK_MCU_PORT_NUM];

        static shared_mem_struct_t* g_ptrShm;
        //static portArray_t* g_ptrShm;

        static int g_shmFd;
        static k_statusInit_t g_status;

    // section end   **** MCU PIN PORTS SHARED MEMORY MANAGEMENT ***** 
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** MESSAGEs MANAGEMENT *****

    static const char* const messagesMatrix[][2];

    // section end   **** MESSAGEs MANAGEMENT ***** 
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** DISPLAY  *****

    public:
        enum kStatusColor_t  {
             run =          kColor_t::yellow
            ,error_open =   kColor_t::red
            ,error_mmap =   kColor_t::red
            ,ok =           kColor_t::green
            ,unlink =       kColor_t::white
        };

        static fmt_str_t g_fmtStr;
        fmt_str_t* getInitStatusFormattedString(void);

    // section end   **** DISPLAY *****
    // ****************************************************
    // --------------------------

};


#endif 	// SHM_MCU_PIN_PORT_H
