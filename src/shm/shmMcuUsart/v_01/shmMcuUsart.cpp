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
 * shmMcuUsart.cpp
 *
 *  Created on: Jul, 1st 2024
 *      Author: Marco Dau
 */

#include "shmMcuUsart.h"


#include <cstdint>
#include <string>
#include <atomic>
#include <iostream>

#include <unistd.h>             // for getpid(), ftruncate()

#include <sys/mman.h>           // for shared memory created
#include <fcntl.h>              // for O_* constant: S_IRUSR, S_IWUSR



#define SHARED_MCU_USART_OBJ_NAME         		"/shmMcuUsart"		// "/mpfw_sdk_process"

// int     shmMcuUsart_t::g_shmFd;
// shmMcuUsart_t::shared_mem_struct_t* shmMcuUsart_t::g_ptrShmInit;
// shmMcuUsart_t::shared_mem_struct_t* shmMcuUsart_t::g_ptrShmActive;

shmMcuUsart_t::shared_mem_struct_t* shmMcuUsart_t::g_ptrShmActive;

shmMcuUsart_t::shmMcuUsart_t   (uint8_t p_pid2) :
    g_pid2      {p_pid2}
{}


void shmMcuUsart_t::init    (void)  {


    g_shmFd = shm_open(SHARED_MCU_USART_OBJ_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if(g_shmFd == -1) {
        printf("ERROR - opening shared memory\n");
    } else {
        ftruncate(g_shmFd, k_mcuUsart_t::ch_Num*sizeof(shared_mem_struct_t));
        g_ptrShmInit = (shared_mem_struct_t *) mmap(NULL, k_mcuUsart_t::ch_Num*sizeof(shared_mem_struct_t), PROT_READ | PROT_WRITE, MAP_SHARED, g_shmFd, 0);
    }

}

void shmMcuUsart_t::chEnable       (k_mcuUsart_t p_ch)     {
    g_ptrShmActive = &g_ptrShmInit[p_ch];
    // reset value
    g_ptrShmActive->gDataWriterPid = 0;
}

bool shmMcuUsart_t::pidMatches (void)   {
    return (
                (g_pid  == g_ptrShmActive->gDataWriterPid)
            &&  (g_pid2 == g_ptrShmActive->gDataWriterPid2)
    );
}

uint8_t shmMcuUsart_t::getData         (void)  {
    return  g_ptrShmActive->buffer[0];
}

void shmMcuUsart_t::setData         (uint8_t p_data)    {
    g_ptrShmActive->buffer[0] = p_data;
}


int shmMcuUsart_t::WriterPidGet (void)    {
    return (g_ptrShmActive->gDataWriterPid);
}

void shmMcuUsart_t::WriterPidClr       (void)  {
    g_ptrShmActive->gDataWriterPid2 = 0;
    g_ptrShmActive->gDataWriterPid  = 0;
}

void shmMcuUsart_t::WriterPidSet       (void)  {
    g_ptrShmActive->gDataWriterPid2 = g_pid2;
    g_ptrShmActive->gDataWriterPid  = g_pid;
}

