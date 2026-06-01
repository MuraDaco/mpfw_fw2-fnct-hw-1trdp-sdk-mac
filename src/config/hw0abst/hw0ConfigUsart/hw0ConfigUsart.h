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
 * hw0ConfigUsart.h
 *
 *  Created on: Jun, 27 2024
 *      Author: Marco Dau
 */


#ifndef HW_0_CONFIG_USART_H
#define HW_0_CONFIG_USART_H

enum k_hw0Usart_t {
	 ch_1
	,ch_2
	,ch_Num
};


#define HW_0_USART_CHANNEL_NUM   k_hw0Usart_t::ch_Num

#endif 	// HW_0_CONFIG_USART_H
