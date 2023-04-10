#include <uart/uart.h>

void onProtocolStarted() {

}

void onDataReceiveCompleted(const uint8_t s)  {
}

int main() {
    startProtocol(2230);
    while (1); /* Running forever! */
	return 0;
}
