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
 * shmManager.h
 *
 *  Created on: Jun, 27 2024
 *      Author: Marco Dau
 */


#ifndef SHM_MANAGER_H
#define SHM_MANAGER_H

#include <string>
#include <atomic>
#include <cstdint>

#include "shmBase.h"

#include "dtyUnit1MmyInt32.h"

#include "sdk_dtyPtfmHwGnrlTypesDefs.h"
using namespace dtyPtfmHwGnrlTypesDefs_t;

#define PROCESS_MAX_NUMBER	    4

class shmManager_t: public shmBase_t {

// // ****************************************************
// // section start **** ENUMs DEFINITIONs *****
//     public:
// 
//         enum k_statusInit_t   {
//              k_statusInit_RUN       // ("RUN - shared memory initialization is not yet completed\n")
//             ,k_statusInit_ERR       // ("ERROR - opening shared memory\n")
//             ,k_statusInit_FULL      // ("FULL - processes buffer is full\n")
//             ,k_statusInit_OK        // ("OK - shared memory initialization is completed\n")
//         };
// 
//     // section end   **** ENUMs DEFINITIONs ***** 
//     // ****************************************************
//     // --------------------------

// ****************************************************
// section start **** PROCESSES SHARED MEMORY MANAGEMENT *****
    public:

        static k_statusInit_t open  (bool p_shm_reset);
        static bool bodyStart       (void);
        static void bodyEnd         (void);
        static bool end             (void);

        static shm_process_struct_t* getpBufferProx    (void);

    private:
        static bool checkProcessesList  (void);
        static void add_2               (void);
        static void del_2               (void);

        typedef struct _shared_mem_struct
        {
            int gNew;
            int gDel;
            int pid;
            int gActivePid;
            uint8_t gActiveProcessNum;
            uint8_t reader_counter;
        	shm_process_struct_t process_buffer[PROCESS_MAX_NUMBER];
            std::atomic_flag gLockProcess;
            int gProcessWriterPid;
        } shared_mem_struct_t;

        static int g_shmFd;
        static shared_mem_struct_t* g_msg_ptr;
    

    // section end   **** PROCESSES SHARED MEMORY MANAGEMENT ***** 
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** CONCURRENT PROCEDURES *****

    protected:
        static void next            (void);

    private:
        static k_statusInit_t semaphore_init  (void);
        static bool semaphore       (void);

    // section end   **** CONCURRENT PROCEDURES ***** 
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** TUI (Text User Interfcae) *****

    public:
        // static dtyMmyInt32_t g_dtyPid;
        // static dtyCntnrBufferShmProx_t g_dtyBufferPid;

        static dtyUnit1MmyInt32_t           g_dtyPid_new;
        //static dtyCntnr1ArrayShmProxList_t  g_dtyBufferPid_new;

    // section end   **** TUI (Text User Interfcae) ***** 
    // ****************************************************
    // --------------------------


};


#endif 	// SHM_MANAGER_H
