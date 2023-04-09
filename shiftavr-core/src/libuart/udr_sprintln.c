#include<uart/uart.h>

void sprintln(char* data) {
    sprint(data);
    sprint(NEW_LINE_CARRIAGE_R);
}
