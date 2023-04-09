#include<uart/uart.h>

void sprint(char* data) {
    int i = 0;
    while (i < strlen(data)) {
        cprint(&data[i++]);
    }
}
