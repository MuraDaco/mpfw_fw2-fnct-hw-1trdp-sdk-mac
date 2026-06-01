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

// http://stackoverflow.com/questions/478898

/*
 * sdkClipboard.cpp
 *
 *  Created on: Apr, 17 2025 (Thu)
 *      Author: Marco Dau
 */

#include "sdkClipboard.h"

#include <iostream>
#include <sstream>
#include <stdio.h>

string sdkClipboard_t::exec(const char* cmd)
{
  FILE* pipe = popen(cmd, "r");
  if (!pipe) return "ERROR";
  char buffer[128];
  string result = "";
  while(!feof(pipe))
  {
    if(fgets(buffer, 128, pipe) != NULL)
    {
      result += buffer;
    }
  }
  pclose(pipe);
  return result;
}

string sdkClipboard_t::paste(void)
{
  return exec("pbpaste");
}

string sdkClipboard_t::copy(const char * new_clipboard)
{

        stringstream cmd;
        // cmd << "echo \"" << new_clipboard << "\" | tr -d \'\ff\n \' | pbcopy";   // OK: without newline
        cmd << "printf \"" << new_clipboard << "\" | pbcopy";
        return exec(cmd.str().c_str());
        //return string("exec string");

    // string l_string = "default string";
    // if(new_clipboard)   {
    //     stringstream cmd;
    //     cmd << "echo \"" << new_clipboard << "\" | pbcopy";
    //     // return exec(cmd.str().c_str());
    //     return string("exec string");
    // } else {
    //     return string("null string");
    // }
    // return l_string;
}

/*

    int main(int argc, char * argv[])
    {
      using namespace std;
      cout<<"old clipboard: "<<paste()<<endl;
      copy("Bomb!");
      cout<<"new clipboard: "<<paste()<<endl;
      return 0;
    }

*/
