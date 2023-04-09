#include<uart/uart.h>

void cprintln(char* data) {
    cprint(data);
    sprint(NEW_LINE_CARRIAGE_R);
}
