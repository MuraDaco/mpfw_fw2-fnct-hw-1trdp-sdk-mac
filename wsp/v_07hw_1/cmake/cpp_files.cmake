#   *******************************************************************************
#   
#   mpfw / fw2 - Multi Platform FirmWare FrameWork 
#       library that contains the "main" entry point and, 
#       eventualy, application code that is platform dependent
#   Copyright (C) (2023) Marco Dau
#   
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU Affero General Public License as published
#   by the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#   
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU Affero General Public License for more details.
#   
#   You should have received a copy of the GNU Affero General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.
#   
#   You can contact me by the following email address
#   marco <d o t> ing <d o t> dau <a t> gmail <d o t> com
#   
#   *******************************************************************************

include_guard()


    set(CURR_MOD_NAME       FNCT-HW-1TRDP-SDK-MAC)

    set(${CURR_MOD_NAME}_cmmn_SOURCE_FILES_CPP

        ## utility
        	${${CURR_MOD_NAME}_SRC_DIR}/clipboard/sdkClipboard.cpp
        	${${CURR_MOD_NAME}_SRC_DIR}/port/sdkPortDef.cpp

        ## sdk
            ## unit thread (init, loop, end) routines management
        		${${CURR_MOD_NAME}_SRC_DIR}/shm/shmBase/v_${${CURR_MOD_NAME}_shmBase_VER}/shmBase.cpp
        		${${CURR_MOD_NAME}_SRC_DIR}/shm/shmManager/v_${${CURR_MOD_NAME}_shmManager_VER}/shmManager.cpp

            ## unit
        		${${CURR_MOD_NAME}_SRC_DIR}/shm/shmMcuPinPort/v_${${CURR_MOD_NAME}_shmMcuPinPort_VER}/shmMcuPinPort.cpp
        		${${CURR_MOD_NAME}_SRC_DIR}/shm/shmMcuUsart/v_${${CURR_MOD_NAME}_shmMcuUsart_VER}/shmMcuUsart.cpp

        ## wrapper
            ## unit thread (init, loop, end) routines management
	        	${${CURR_MOD_NAME}_SRC_DIR}/mcu/mcuBase/v_${${CURR_MOD_NAME}_mcuBase_VER}/mcuBase.cpp
	        	${${CURR_MOD_NAME}_SRC_DIR}/mcu/mcuManager/v_${${CURR_MOD_NAME}_mcuManager_VER}/mcuManager.cpp

            ## unit 
	        	${${CURR_MOD_NAME}_SRC_DIR}/mcu/mcuPinPort/v_${${CURR_MOD_NAME}_mcuPinPort_VER}/mcuPinPort.cpp
	        	${${CURR_MOD_NAME}_SRC_DIR}/mcu/mcuPinPort/v_${${CURR_MOD_NAME}_mcuPinPort_VER}/mcuPinPort2.cpp
                ## ${${CURR_MOD_NAME}_SRC_DIR}/mcu/mcuUsart/v_${${CURR_MOD_NAME}_mcuUsart_VER}/mcuUsart.cpp
	        	${${CURR_MOD_NAME}_SRC_DIR}/mcu/mcuUsartRs485/v_${${CURR_MOD_NAME}_mcuUsartRs485_VER}/mcuUsartRs485.cpp

    )
