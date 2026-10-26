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
 * shmManager.cpp
 *
 *  Created on: Jun, 27 2024
 *      Author: Marco Dau
 */

#include "shmManager.h"

#include <cstdint>
#include <string>
#include <atomic>
#include <iostream>


#include <unistd.h>             // for getpid(), ftruncate()

#include <sys/mman.h>           // for shared memory created
#include <fcntl.h>              // for O_* constant: S_IRUSR, S_IWUSR
//#include <sys/stat.h>           // for mode constant: O_CREAT, O_RDWR


// ****************************************************
// section start **** PROCESS MANAGEMENT *****

    #define SHARED_OBJ_NAME         		"/mpfw_sdk_shared_mem"		// "/mpfw_sdk_process"

    int shmManager_t::g_shmFd;
    shmManager_t::shared_mem_struct_t*   shmManager_t::g_msg_ptr;

    shmManager_t::k_statusInit_t shmManager_t::open (bool p_shm_reset) {
        k_statusInit_t l_result = k_statusInit_ERR_PROCESS_BUF;

    	if(p_shm_reset) shm_unlink(SHARED_OBJ_NAME);

      	g_pid = getpid();

        g_shmFd = shm_open(SHARED_OBJ_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
        if(g_shmFd == -1) {
            printf("ERROR - opening shared memory\n");
        } else {
            ftruncate(g_shmFd, sizeof(shared_mem_struct_t));
            g_msg_ptr = (shared_mem_struct_t *) mmap(NULL, sizeof(shared_mem_struct_t), PROT_READ | PROT_WRITE, MAP_SHARED, g_shmFd, 0);
            l_result = k_statusInit_RUN;
        }

        if(k_statusInit_ERR_PROCESS_BUF != l_result)    {
            // 2. add the current process to the list of process that may read/write the shared memory without conflicts
            while (k_statusInit_RUN == l_result)    {
                l_result = semaphore_init();
            }
            //while(k_statusInit_RUN == shmManager_t::semaphore_init()){}
    
            // 3. initialize/create the shared memory about mcuPinPort/vhwPphMcuPinPortWiredTbl_t
            while(!semaphore()){}
        }

        g_status = l_result;
        return l_result;
    }


    bool shmManager_t::bodyStart (void) {
        if(shmManager_t::semaphore())   {
            shmManager_t::checkProcessesList();
            //shmManager_t::next();
            return true;
        }
        return false;
    }

    void shmManager_t::bodyEnd (void) {
        next();
    }

    bool shmManager_t::end(void)	{
    	bool l_result = false;

    	std::cout << "end" << std::endl;

        if(g_shmFd == -1) {
            printf("ERROR - opening shared memory\n");
        } else {

    		// waiting for the current process became active/get the "token" 
    		for(;;) {
    			if(g_pid == g_msg_ptr->gActivePid)	{

    				std::cout << "Last step [[-3]]" << std::endl;

    				// waiting for shared memory became unlocked
    			    if(!g_msg_ptr->gLockProcess.test_and_set(std::memory_order_acquire))	{
                        // now the resource is free, it is possible go ahead to complete the end procedure
    					std::cout << "Last step [[-2]]" << std::endl;
    					break;
    				} else {
                        // the resource is busy, a new process has acquired it to ask the registration, therefore ...
                        // release the token (of "active pid") to the next registered process to not block the processes loop
                        // and wait the next turn/loop
    					next();
    				}
    			}
    		}

    		// activate del procedure
    		if(g_msg_ptr->gDel) {
    			// delete another process that wants exit
    			del_2();
    		}

    		std::cout << "Last step [[-1]]" << std::endl;

    		// now the resource is free & no other processes has asked to be removed
    		g_msg_ptr->gDel = g_pid;

    		// check if the current process is the last one
    		if(1 == g_msg_ptr->gActiveProcessNum)	{
    			std::cout << "The current process is the last" << std::endl;
    			// the current process is the last one
    			// therefore it must perform 
    			// the add procedure of new process if there is a request about it
    			// it is irrevelant the order by which the addition and deleting procedures are performed

    			// check if there is a new process to add
    			if(g_msg_ptr->gNew) {
    				// add new process
    				add_2();
    			}

    			// auto-delete the current process
    			del_2();
    		}

    		bool l_last_process = (0 == g_msg_ptr->gActiveProcessNum);

    		// release the resources
    		g_msg_ptr->gLockProcess.clear(std::memory_order_release);

    		next();

    		std::cout << "Last step [[0]]" << std::endl;

    		munmap(g_msg_ptr, sizeof(shared_mem_struct_t));

    		std::cout << "Last step [[1]]" << std::endl;

    	    close(g_shmFd);

    		std::cout << "Last step [[2]]" << std::endl;
    
    		// remove shared mem object if the current removed process is the last one
    		if(l_last_process) {
    			std::cout << "Last step [[3]]" << std::endl;
    			shm_unlink(SHARED_OBJ_NAME);
    			std::cout << "No process is active -> performed the shm_unlink(.) function - sizeof(int) " << sizeof(int) << " - g_pid: " << g_pid << std::endl;
    		}

    		l_result = true;

    	}

	    return l_result;
    }


    bool shmManager_t::checkProcessesList(void)	{
    	bool l_result = false;

    	// it's own turn to modify o read the processes list

    	// check the lock status of processes list modification requests
    	// it can be locked by
    	// a new process that want to be added
        // N.B.: you can think that ...
        //       another registerd process can lock the resources to remove itself too, but ...
        //       this case is not possible because all other registered processes wait its turn (see sempahore condition) to acquire the resource
    	if(!g_msg_ptr->gLockProcess.test_and_set(std::memory_order_acquire))
    	{
    		// the request of processes list modification is locked

    		// check the request of adding a process
    		if(g_msg_ptr->gNew) {
    			add_2();
    			// the list of processes must be read to update the visualization on console
    			l_result = true;
    			// advise the other processes that the processes list has been modified
    			g_msg_ptr->gProcessWriterPid = g_pid;
    		}

    		// check the request of removing a process
    		if(g_msg_ptr->gDel) {
    			del_2();
    			// the list of processes must be read to update the visualization on console
    			l_result = true;
    			// advise the other processes that the processes list has been modified
    			g_msg_ptr->gProcessWriterPid = g_pid;
    		}

    		// release the resources
    		g_msg_ptr->gLockProcess.clear(std::memory_order_release);

    	}
    
    	// check process buffer status to know wheather process buffer has been modified or to reset the "gProcessWriterPid" parameter
    	if(g_msg_ptr->gProcessWriterPid)	{
    		// one process modified processes list adding or removing a process

    		// check if the current process, now (through the previuos statement), has just added or removed a process
    		if(!l_result)	{
    			// no process has been added or removed by the current process

    			// check 
    			if(g_pid == g_msg_ptr->gProcessWriterPid)	{
    				// the current process has modified process buffer not now but in a previous cycle
    				// all processes have read the new list of processes
    				// therefore the procedure is terminated, reset the associated variable
    				g_msg_ptr->gProcessWriterPid = 0;
    			} else {
    				// the current process has not modified the processes list
    				// therefore ...
    				// the list of processes must be read to update the visualization on console
    				l_result = true;
    			}
    		}
    	}

    	return l_result;
    }

    void shmManager_t::add_2(void)	{
    	// a new process has to be added
    	for(uint8_t i=0;i<PROCESS_MAX_NUMBER;i++) {
    		if(g_msg_ptr->process_buffer[i].pid == 0)	{
    			g_msg_ptr->process_buffer[i].pid = g_msg_ptr->gNew;

    			g_msg_ptr->gNew = 0;
    			g_msg_ptr->gActiveProcessNum = i+1;
    			break;
    		}
    	}

    	// check if the process that has just been added is the first one
    	if(1 == g_msg_ptr->gActiveProcessNum)	{
    		// the process that has just been added is the first one

    		// enable the current process to manage the shared memory
    		// it is possible to enable the current process here because it is the first 
    		// otherwise it is not, it can be dangerous
    		g_msg_ptr->gActivePid = g_pid;
    	}
    }



    void shmManager_t::del_2	(void)	{
    	uint8_t l_active_process_num = 0;
    	// a process has to be removed
    	for(uint8_t i=0;i<PROCESS_MAX_NUMBER;i++) {
    		// std::cout << "Remove process id: " << (int) i << " -- pid: " << g_msg_ptr->gDel << std::endl;
    		// search for pid process to remove
    		if(g_msg_ptr->process_buffer[i].pid == g_msg_ptr->gDel)	{
    			// pid process has been found
    			// std::cout << "Removing process id: " << (int) i << " -- pid: " << g_msg_ptr->gDel << std::endl;

    			// the number of active processes is at least equal to the id of the process to remove
    			l_active_process_num = i;

    			if((PROCESS_MAX_NUMBER-1) == i)	{
    				// the process to remove is the younger and it has the maximum id (the process_buffer is full)
    				// therefore it is not necessary to apply the shift procedure
    				g_msg_ptr->process_buffer[i].pid   = 0;
    			} else {
    				// the process to remove is not the last process of the process_buffer
    				// therefore the shift procedure must be applyed

    				// start the procedure to shift by one position all the younger processes than the removed one
    				for(uint8_t j=i+1;j<PROCESS_MAX_NUMBER;j++) {

    					// check if the next process exists
    					if(g_msg_ptr->process_buffer[j].pid)	{
    						// a younger processes exist

    						// increment the number of active processes
    						l_active_process_num++;
    						// shift the process
    						g_msg_ptr->process_buffer[j-1].pid = g_msg_ptr->process_buffer[j].pid;

    						g_msg_ptr->process_buffer[j].pid   = 0;
    					} else {
    						// no other processes exist
    						// close the removing procedure

    						// note: if "l_active_process_num" variable is 0 it means that the current process, that has been removed, is the last one
    						g_msg_ptr->process_buffer[l_active_process_num].pid = 0;
    						// exit from loop
    						break;
    					}
    				}
    			}

    			g_msg_ptr->gDel = 0;
    			g_msg_ptr->gActiveProcessNum = l_active_process_num;

    			// exit from loop
    			break;
    		}
    	}
    }

    shm_process_struct_t* shmManager_t::getpBufferProx    (void)  {
        return g_msg_ptr->process_buffer;
    }

    // section end   **** PROCESS MANAGEMENT ***** 
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** CONCURRENT PROCEDURES *****


    shmManager_t::k_statusInit_t shmManager_t::semaphore_init (void) {
        shmManager_t::k_statusInit_t l_result = k_statusInit_RUN;
    	// waiting for shared memory unlocked
    	while(g_msg_ptr->gLockProcess.test_and_set(std::memory_order_acquire))	{}

    	if(0 == g_msg_ptr->gNew) {
            if(g_msg_ptr->gActiveProcessNum < PROCESS_MAX_NUMBER)   {
    		    // now the resource is free & no other processes has asked to be added
    		    g_msg_ptr->gNew = g_pid;
                l_result = k_statusInit_OK;
        		// check if the current process is the first one to be added
        		if(0 == g_msg_ptr->gActiveProcessNum)	{
        			// the current process is the first one
        			// so no process is active
                    prox_buffer_clean();
        			add_2();
        		}
            } else {
                l_result = k_statusInit_FULL;
            }

    		// // check if the current process is the first one to be added
    		// if(0 == g_msg_ptr->gActiveProcessNum)	{
    		// 	// the current process is the first one
    		// 	// so no process is active
    		// 	add_2();
    		// }
    
    	}

    	// release the resources
    	g_msg_ptr->gLockProcess.clear(std::memory_order_release);

        return l_result;
    }


    void shmManager_t::prox_buffer_clean (void) {
    	for(uint8_t i=0;i<PROCESS_MAX_NUMBER;i++) {
            g_msg_ptr->process_buffer[i].pid = 0;
        }

    }

    bool shmManager_t::semaphore (void) {
        bool l_result = false;

        if(g_shmFd != -1) {
    		// waiting for acquire the token
            l_result = (g_pid == g_msg_ptr->gActivePid);
        }

        return l_result;
    }


    void shmManager_t::next(void)	{
    	uint8_t l_next_id;
    	for(uint8_t i=0;i<PROCESS_MAX_NUMBER;i++) {
    		if(g_msg_ptr->process_buffer[i].pid == g_pid)	{
    			l_next_id = i+1;

    			// check if the next id is right
    			if(PROCESS_MAX_NUMBER == l_next_id) l_next_id = 0;
    			else if	(0 == g_msg_ptr->process_buffer[l_next_id].pid) l_next_id = 0;

    			// update the active pid
    			g_msg_ptr->gActivePid = g_msg_ptr->process_buffer[l_next_id].pid;
    		}
    	}
    }

    // section end   **** CONCURRENT PROCEDURES ***** 
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** TUI (Text User Interfcae) *****


    // dtyMmyInt32_t              shmManager_t::g_dtyPid(&g_pid);
    // dtyCntnrBufferShmProx_t    shmManager_t::g_dtyBufferPid(getpBufferProx, PROCESS_MAX_NUMBER);

    dtyUnit1MmyInt32_t          shmManager_t::g_dtyPid_new(&g_pid);
    //dtyCntnr1ArrayShmProxList_t shmManager_t::g_dtyBufferPid_new(getpBufferProx, PROCESS_MAX_NUMBER);

    // section end   **** TUI (Text User Interfcae) ***** 
    // ****************************************************
    // --------------------------
