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
 * shmMcuUsart.h
 *
 *  Created on: Jul, 1st 2024
 *      Author: Marco Dau
 */


#ifndef SHM_MCU_USART_H
#define SHM_MCU_USART_H

#include "hw0ConfigUsart.h"
#include "shmBase.h"

#define MESSAGE_BUFFER_SIZE 1

class shmMcuUsart_t: public shmBase_t {

protected:
    shmMcuUsart_t   (uint8_t p_pid2);

    typedef struct _shared_mem_struct
    {
        char buffer[MESSAGE_BUFFER_SIZE];
        uint8_t gDataWriterPid2;
        int     gDataWriterPid;
    } shared_mem_struct_t;

    void init                (void);
    bool pidMatches          (void);
    static uint8_t getData          (void);
    static void    setData          (uint8_t p_data);
    int  WriterPidGet        (void);
	void WriterPidClr        (void);
	void WriterPidSet        (void);
    void chEnable            (k_hw0Usart_t p_ch);


private:
    shared_mem_struct_t* g_ptrShmInit;
    static shared_mem_struct_t* g_ptrShmActive;
    int g_shmFd;
protected: 
    uint8_t g_pid2;

};


#endif 	// SHM_MCU_UASRT_H
