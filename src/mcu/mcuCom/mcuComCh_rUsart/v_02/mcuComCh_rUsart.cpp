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
 * mcuComCh_rUsart.cpp
 *
 *  Created on: Aug, 30th 2026  (Sun)
 *      Author: Marco Dau
 */

#include "mcuComCh_rUsart.h"

// ****************************************************
// section start **** CONSTRUCTOR *****

    mcuComCh_rUsart_t::mcuComCh_rUsart_t(mcuComCh_rUsartInitParams_t* p_initParams) :
         g_strDevice        {p_initParams->strDevice}
        ,g_fd               {0}
    {}

    // section end   **** CONSTRUCTOR ***** 
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** EVENTS *****


    // public:
        void mcuComCh_rUsart_t::end (void) {
            if(g_strDevice[0]) {
                cout << "close file descriptor of test serial port comm" << endl;
                close(g_fd);
            }
        }

        void mcuComCh_rUsart_t::init (void) {

            // if (argc < 2 || argc > 3)
            // {
            //     cerr << "usage: " << argv[0] << " device [bauds]" << endl;
            //     return 1;
            // }

            if(g_strDevice[0]) {
            
                // string device = g_strDevice;
                unsigned long bauds = 9600;
                // if (argc == 3)
                // {
                //     char* result;
                //     bauds = strtoul(argv[2], &result, 10);
                //     if (*result != '\0')
                //     {
                //         cerr << "usage: " << argv[0] << " device [bauds]" << endl;
                //         return 1;
                //     }
                // }

                g_fd = open(g_strDevice, O_RDWR | O_NDELAY | O_NOCTTY | O_NONBLOCK);
                if (g_fd == -1)
                {
                    perror((string("can't open ") + g_strDevice).c_str());
                    exit(errno);
                }

                struct termios g_config;
                if (tcgetattr(g_fd, &g_config) < 0)
                {
                    perror("can't get serial attributes");
                    exit(errno);
                }

                if (cfsetispeed(&g_config, bauds) < 0 || cfsetospeed(&g_config, bauds) < 0)
                {
                    perror("can't set baud rate");
                    exit(errno);
                }

                g_config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK | ISTRIP | IXON);
                g_config.c_oflag = 0;
                g_config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
                g_config.c_cflag &= ~(CSIZE | PARENB);
                g_config.c_cflag |= CS8;
                g_config.c_cc[VMIN]  = 1;
                g_config.c_cc[VTIME] = 0;

                //***** con l'aggiunta di questa configurazione funziona anche la scrittura altrimenti no
                // 8N1
                g_config.c_cflag = 0; // &= ~PARENB;
                g_config.c_cflag = 0; // &= ~CSTOPB;
                g_config.c_cflag = 0; // &= ~CSIZE;
                g_config.c_cflag |= CS8;
                // no flow control
                // toptions.c_cflag &= ~CRTSCTS;

                g_config.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
                g_config.c_iflag = IGNPAR; // &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl

                g_config.c_lflag = 0; // &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
                g_config.c_oflag = 0; // &= ~OPOST; // make raw

                g_config.c_cc[VMIN]  = 0;
                g_config.c_cc[VTIME] = 0; // 20;
                //*****


                // TCSANOW
                if (tcsetattr(g_fd, TCSAFLUSH, &g_config) < 0)
                {
                    perror("can't set serial attributes");
                    exit(errno);
                }

                cout << "start test serial port comm - write" << endl;
                //                           0    5    1    5    2    5    3    5    4    5    5
                size_t result = write(g_fd, "- INIT - REAL SERIAL COM - 2026.09.06 ore 15:36!-", 49);
                if (result < 0) {
                    perror("Write failed");
                }
                //
                //    cout << "start test serial port comm - read" << endl;
                //
                //    char buffer[80];
                //    while (true)
                //    {
                //        size_t n = read(fd, buffer, sizeof buffer);
                //        write(STDOUT_FILENO, buffer, n);
                //    }
                //
                // close(g_fd);
            }

        }

        bool    mcuComCh_rUsart_t::chkInterruptsRaised     (void)             {
            return true;
        }

        bool    mcuComCh_rUsart_t::tx_chkInterruptRaised    (void)             {
            return true;
        }


        void    mcuComCh_rUsart_t::tx_eventBegin           (void)                              {
            // "real" case in "virtual"  platform:  do nothing
            // "virtual" case:  do nothing
            // "real" case:     1. enable tx interrupt
            //                  2. set tx-enable pin (automatically clear rx-enable pin)
            // g_pConfig->setTxEnablePin();
        }

        void    mcuComCh_rUsart_t::tx_eventFirstData       (void)                              {
            // "real" case in "virtual"  platform:  do nothing
            //  "virtual" case: lock the channel setting [writerPid] parameter
            //  "real" case:    do nothing
        }

        void mcuComCh_rUsart_t::tx_eventSendData          (uint8_t p_data)	{

            if(g_strDevice[0]) {
                size_t result = write(g_fd, &p_data, 1);
                if (result < 0) {
                    g_error = 1;
                }            
            }
        }

        void    mcuComCh_rUsart_t::tx_eventLastData        (void)                              {
            // "real" case in "virtual"  platform:  do nothing
            // "virtual" case:    do nothing
            // "real" case:       the tx interrupt has to be configured to raise when the last byte is phisically and completely sent
        }

        void    mcuComCh_rUsart_t::tx_eventEnd             (void)                              {
            // "real" case in "virtual"  platform:  do nothing
            // "virtual" case:    un-lock the channel clearing [writerPid] parameter
            // "real" case:       1. disable tx interrupt
            //                    2. clear tx-enable pin (automatically set rx-enable pin)
            // close(g_fd);
        }


    // receive
        bool    mcuComCh_rUsart_t::rx_chkInterruptRaised    (void)             {
            bool l_result = false;
            if(g_strDevice[0]) {
                l_result = (read(g_fd, &g_rxData, 1) == 1);
            }
            return l_result;
        }

        bool    mcuComCh_rUsart_t::rx_chkError_overrun   (void)                         {
            return false;
        }

        // It is called in an "application thread/routine" when the user makes ready to receive a packet 
        // therefore when the buffer status is set to "waiting to receive a packet"
        void    mcuComCh_rUsart_t::rx_eventBegin           (void)                         {
            // "virtual" case:  
            //      . do nothing
            //      . it is not necessary to enable the "rx interrupt" because the "interrupt thread/routine" is always performed
            // "real" case:     
            //      1. enable rx interrupt
            //      2. set rx-enable pin (automatically clear tx-enable pin)
            // Enable receiver interrupt.
        }

        // It is called in an "interrupt thread/routine" when the buffer status is "rx running"
        uint8_t    mcuComCh_rUsart_t::rx_eventReceiveData     (void)                         {
            //  "virtual" case: 
            //      . read from the shared memory buffer, the buffer that is shared with other processes (N.B.: not threads but processes)) 
            //  "real" case: 
            //      . read from the mcu usart register

            return g_rxData;
        }

        // It is called in an "interrupt thread/routine" when the "last byte has been received" or error is detected
        // when the last byte is received the buffer status is set to "rx completed" 
        // when error is detected the buffer status is set to "rx error"
        // 
        void    mcuComCh_rUsart_t::rx_eventEnd             (void)                         {
            // "virtual" case:
            //      . do nothing
            // "real" case:     
            //      1. DIS-able rx interrupt
        }


    // section end   **** EVENTS *****
    // ****************************************************
    // --------------------------





