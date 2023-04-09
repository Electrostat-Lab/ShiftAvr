#include<uart/uart.h>

void cprint(char* data) {
    while (!(REG_UCSRA & (1 << BIT_UDRE)));
    REG_UDR = *data;
    startTransmitterISR();
}
