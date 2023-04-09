#include<uart/uart.h>

void println(const int64_t data, const uint8_t base) {
    print(data, base);
    sprint(NEW_LINE_CARRIAGE_R);
}
