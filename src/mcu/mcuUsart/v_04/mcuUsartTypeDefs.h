#ifndef MCU_USART_TYPE_DEFS_H
#define MCU_USART_TYPE_DEFS_H

#include <cstdint>

// protocol definitions
typedef void    (*callback_protocol_x_buffer_management_t)  (void* p_ptrData);
typedef uint8_t (*callback_protocol_status_get_t)           (void);
typedef void    (*callback_protocol_status_set_t)           (void);

typedef struct _callback_protocol_functions {
    callback_protocol_x_buffer_management_t tx_buffer_management;
    callback_protocol_x_buffer_management_t rx_buffer_management;

    callback_protocol_status_get_t          tx_status_get__running;
    callback_protocol_status_get_t          tx_status_get__waiting_last_byte_send;
    callback_protocol_status_get_t          tx_status_get__completed;
    callback_protocol_status_get_t          rx_status_get__running;
    callback_protocol_status_get_t          rx_status_get__completed;

    callback_protocol_status_set_t          tx_status_set__free;
    callback_protocol_status_set_t          rx_status_set__free;
    callback_protocol_status_set_t          tx_status_set__running;
    callback_protocol_status_set_t          tx_status_set__completed;
    callback_protocol_status_set_t          rx_status_set__running;

    callback_protocol_status_get_t          rx_status_get__free;

    
    callback_protocol_status_set_t          tx_status_set__txEnd;
    callback_protocol_status_set_t          rx_status_set__rxEnd;
} callback_protocol_functions_t;


#endif 	// MCU_USART_TYPE_DEFS_H
