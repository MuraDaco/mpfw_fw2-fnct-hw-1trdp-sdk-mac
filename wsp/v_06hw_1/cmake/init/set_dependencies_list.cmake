#   *******************************************************************************
#   
#   mpfw / fw2 - Multi Platform FirmWare FrameWork 
#       
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

### ---------------------------
##
#   set_depenedecies_list.cmake
#
#   Created on: June, 1st 2025  (Sun)
#   Author: Marco Dau
##
### ---------------------------

include_guard()

    set(CURR_MOD_NAME       FNCT-HW-1TRDP-SDK-MAC)

    set(${CURR_MOD_NAME}_DEPS_LIST   
        ## name             			_WSP_VER    _SRC_CFG    EXTNL_LIB ([N]o/[Y]es)
        FNCT-BASE-0ABST       			00base      00          N
        FNCT-HW-0ABST       			02hw_0      01          N
        FNCT-HW-0ABST-TRDP-SDK-MAC      00hw_0mac	00          N
    )
