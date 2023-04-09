#include<uart/uart.h>

/**
 * @brief Triggered when the bit UDRE0 is one (the data register buffer is empty and ready to send data).
 */
ISR (USART_UDRE_vect) {
    REG_UDR = *(transmitData);
    onDataBufferCleared((const uint8_t*) transmitData);
    stopDataRegisterEmptyBufferISR();
}

void startDataRegisterEmptyBufferISR() {
    REG_UCSRB |= (1 << BIT_UDRIE);
    /* start the interrupt service handlers */
    sei();
}

void stopDataRegisterEmptyBufferISR() {
    // Finds the 1s complement of all bits in UDRIE0 ---> eg: 0b11111101
    REG_UCSRB &= ~(1 << BIT_UDRIE); 
}
