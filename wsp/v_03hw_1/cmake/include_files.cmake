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

    set(${CURR_MOD_NAME}_cmmn_SOURCE_FILES_H

        ${${CURR_MOD_NAME}_SRC_DIR}/clipboard
        ${${CURR_MOD_NAME}_SRC_DIR}/port
        ${${CURR_MOD_NAME}_SRC_DIR}/shm/shmBase/v_${${CURR_MOD_NAME}_shmBase_VER}
        ${${CURR_MOD_NAME}_SRC_DIR}/shm/shmManager/v_${${CURR_MOD_NAME}_shmManager_VER}
        ${${CURR_MOD_NAME}_SRC_DIR}/shm/shmMcuPinPort/v_${${CURR_MOD_NAME}_shmMcuPinPort_VER}
        ${${CURR_MOD_NAME}_SRC_DIR}/shm/shmMcuUsart/v_${${CURR_MOD_NAME}_shmMcuUsart_VER}        

        ${${CURR_MOD_NAME}_SRC_DIR}/mcu
        ${${CURR_MOD_NAME}_SRC_DIR}/mcu/mcuBase/v_${${CURR_MOD_NAME}_mcuBase_VER}
        ${${CURR_MOD_NAME}_SRC_DIR}/mcu/mcuUsart/v_${${CURR_MOD_NAME}_mcuUsart_VER}

    )
