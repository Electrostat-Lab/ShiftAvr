#include<uart/uart.h>

void print(const int64_t data, const uint8_t base) {
    char* strBuffer = allocateStringBuffer();
    // convert input to string
    itoa(data, strBuffer, base);
    int i = 0;
    while (i < strlen(strBuffer)) {
        cprint(&strBuffer[i++]);
    }
    free(strBuffer);
}
