#include<uart/uart.h>

/**
 * @brief Triggered when the RXC0 is settled and the receiving has been completed.
 */
ISR (__vector_USART_RX) {
    onDataReceiveCompleted((const uint8_t) REG_UDR);
}

void startReceiverISR() {
    REG_UCSRB |= (1 << BIT_RXCIE);
    /* start the interrupt service handlers */
    sei();
}

void stopReceiverISR() {
    // Finds the 1s complement of all bits in RXCIE0 ---> eg: 0b11111101
    REG_UCSRB &= ~(1 << BIT_RXCIE); 
}
