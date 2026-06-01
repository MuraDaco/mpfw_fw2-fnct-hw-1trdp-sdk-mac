#ifdef      DEBUG_DEF_MCU_USART_RS485_CPP
    {
        static uint8_t l_cnt = 0;
        //              0    5    1    5    2    5    3    5    4
        char l_str[] = "DEBUG - comBufferStatus - TOKEN_1";
        if(g_debug)       {
            l_str[32] = 'A';
        } else {
            l_str[32] = 'B';
        }
        l_cnt++;
        sysDebug_t::msg(54,4, l_str);

    }

#endif  //  DEBUG_DEF_MCU_USART_RS485_CPP
