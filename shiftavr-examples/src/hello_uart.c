#define F_CPU 16000000UL
#include <uart/uart.h>

void on_protocol_started() {
}

void on_protocol_stopped() {
}

void on_data_received(const uint8_t datum) {
    uart_cprint(datum);
    uart_start_transmitter_isr();
    uart_start_udre_isr();
}

void on_data_transmitted(const uint8_t datum) {
    uart_stop_transmitter_isr();
    uart_start_udre_isr();
}

void on_databuffer_cleared() {
    uart_stop_udre_isr();
}

/**
 * @note volatile: marks this object as an interrupt-safe adjustable. 
 */
volatile uart_callbacks _uart_callbacks = {
    on_protocol_started,
    on_protocol_stopped,
    on_data_received,
    on_data_transmitted,
    on_databuffer_cleared
};

int main() {
    /* assigns api callbacks */
    uart_assign_callbacks(&_uart_callbacks);
    /* start the protocol first to enable TX and RX and set BAUD! */
    uart_start_protocol(BAUD_RATE_57600);
    /* starting the ISR should be after starting the protocol! i.e, after enabling RX and TX! */
    uart_start_udre_isr();
    uart_start_receiver_isr();
    uart_start_transmitter_isr();

    while (1); /* Running forever! */
    return 0;
}