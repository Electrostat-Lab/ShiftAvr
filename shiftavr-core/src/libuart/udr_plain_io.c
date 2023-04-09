#include<uart/uart.h>

void setTransmitDataRegister(const uint8_t* ptransmitData) {
    *(transmitData) = *ptransmitData;
    startDataRegisterEmptyBufferISR();
    startTransmitterISR();
}

uint8_t readASCII() {
    while (!(REG_UCSRA & (1 << BIT_RXC)));
    return REG_UDR;
}
