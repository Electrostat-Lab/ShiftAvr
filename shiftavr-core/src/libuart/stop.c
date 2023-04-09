#include<uart/uart.h>

void stopProtocol() {
    onProtocolStopped();
    REG_UCSRB = 0x00; 
}
