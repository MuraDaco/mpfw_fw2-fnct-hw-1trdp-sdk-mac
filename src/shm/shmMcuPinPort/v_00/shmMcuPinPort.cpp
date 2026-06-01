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
 * shmMcuPinPort.cpp
 *
 *  Created on: Jul, 1st 2024
 *      Author: Marco Dau
 */

#include "shmMcuPinPort.h"

#include <cstdint>
#include <string>
#include <atomic>
#include <iostream>

#include <unistd.h>             // for getpid()

#include <sys/mman.h>           // for shared memory created
#include <fcntl.h>              // for O_* constant: S_IRUSR, S_IWUSR

#define SHARED_MCU_PORT_OBJ_NAME         		"/shmMcuPort"		// "/mpfw_sdk_process"

int     shmMcuPinPort_t::g_shmFd = -1;
shmMcuPinPort_t::shared_mem_struct_t* shmMcuPinPort_t::g_ptrShm = nullptr;
//shmMcuPinPort_t::portArray_t* shmMcuPinPort_t::g_ptrShm = nullptr;
shmMcuPinPort_t::k_statusInit_t shmMcuPinPort_t::g_status = k_statusInit_RUN;

fmt_str_t shmMcuPinPort_t::g_fmtStr;


const char* const shmMcuPinPort_t::messagesMatrix[][2] = {
     {"shm -..>" ,"RUN - shared memory initialization is not yet completed\n"    }
    ,{"shm x-->" ,"ERROR - opening shared memory\n"                              }
    ,{"shm -x->" ,"ERROR - memory map\n"                                         }
    ,{"shm --->" ,"OK - shared memory initialization is completed\n"             }
    ,{"shm ...." ,"UNLINK - shared memory unlink has been done\n"                }
    ,{nullptr}
};


uint8_t* shmMcuPinPort_t::init    (bool p_shm_reset)  {

    if(shmBase_t::k_statusInit_t::k_statusInit_OK == shmBase_t::g_status) {

        if(p_shm_reset) shm_unlink(SHARED_MCU_PORT_OBJ_NAME);
        
        // check shared memory pointer
        if(!g_ptrShm)   {
            // the shared memory is not yet initialized
            g_shmFd = shm_open(SHARED_MCU_PORT_OBJ_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
            if(g_shmFd == -1) {
                printf("ERROR - opening shared memory\n");
                g_status = k_statusInit_ERR_OPEN;
            } else {
                ftruncate(g_shmFd, sizeof(shared_mem_struct_t));
                g_ptrShm = (shared_mem_struct_t *) mmap(NULL, sizeof(shared_mem_struct_t), PROT_READ | PROT_WRITE, MAP_SHARED, g_shmFd, 0);
                // ftruncate(g_shmFd, sizeof(portArray_t));
                // g_ptrShm = (portArray_t *) mmap(NULL, sizeof(portArray_t), PROT_READ | PROT_WRITE, MAP_SHARED, g_shmFd, 0);
                g_status = (g_ptrShm) ? k_statusInit_OK : k_statusInit_ERR_MMAP;
            }
        }
    }
    return g_ptrShm->portArray;
}

void shmMcuPinPort_t::end    (void)  {
    if(shmBase_t::k_statusInit_t::k_statusInit_UNLINK == shmBase_t::g_status) {

        if(g_ptrShm)    {
    	    shm_unlink(SHARED_MCU_PORT_OBJ_NAME);
            g_ptrShm = nullptr;
            g_status = k_statusInit_UNLINK;
        }
    }
}

uint8_t* shmMcuPinPort_t::getPtr(uint8_t p_port)  {
    return &g_ptrShm->portArray[p_port]; // N.B.: g_ptrShm = g_ptrShm->portArray
    // uint8_t* l_array = *g_ptrShm;
    // return &(l_array[p_port]);       // N.B.: g_ptrShm == *g_ptrShm but ... i don't know wheather g_ptrShm[p_port] == [ &(l_array[p_port] =  &(*g_ptrShm[p_port]) ]
}

uint8_t* shmMcuPinPort_t::getPtr(void)  {
    return g_ptrShm->portArray;
    //return *g_ptrShm;     // N.B.: g_ptrShm == *g_ptrShm
}

bool shmMcuPinPort_t::getInitStatus(void)  {
    return g_status == k_statusInit_OK;
}

const char* shmMcuPinPort_t::getInitStatusString(void)  {
    return messagesMatrix[g_status][0];
}

fmt_str_t* shmMcuPinPort_t::getInitStatusFormattedString(void)  {
    switch (g_status) {
        case k_statusInit_RUN:
            g_fmtStr.color = kColor_t::yellow;
            break;
        case k_statusInit_ERR_OPEN:
            g_fmtStr.color = kColor_t::red;
            break;
        case k_statusInit_ERR_MMAP:
            g_fmtStr.color = kColor_t::red;
            break;
        case k_statusInit_OK:
            g_fmtStr.color = kColor_t::green;
            break;
        case k_statusInit_UNLINK:
            g_fmtStr.color = kColor_t::white;
            break;
    }
    g_fmtStr.str = messagesMatrix[g_status][0];
    return &g_fmtStr;
}
