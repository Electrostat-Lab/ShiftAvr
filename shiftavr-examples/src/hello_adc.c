#define F_CPU 16000000UL
#include <adc/adc.h>
#include <uart/uart.h>
#include <util/delay.h>

void adc_on_received(const uint16_t);
void adc_on_protocol_started();
void on_data_received(const uint8_t);
void on_data_transmitted(const uint8_t);

void adc_on_received(const uint16_t READ) {
    // do stuff
    uart_println(READ, 10);
    // restart the adc conversion
    adc_start_conversion(ADC_MUX0, AVCC_VREF, CLK_16);
}

void adc_on_protocol_started() {
}

void on_data_received(const uint8_t datum) {
}

void on_data_transmitted(const uint8_t datum) {
}

/**
 * @note volatile: marks this object as an interrupt-safe adjustable. 
 */
volatile adc_callbacks _adc_callbacks = {
    adc_on_received,
    NULL,
    NULL,
    NULL,
};

/**
 * @note volatile: marks this object as an interrupt-safe adjustable. 
 */
volatile uart_callbacks _uart_callbacks = {
    NULL, 
    NULL,
    NULL,
    NULL,
    NULL
};

int main() {
    /* setup UART! */
    uart_assign_callbacks(&_uart_callbacks);
    uart_start_protocol(BAUD_RATE_57600);

    /* setup ADC! */
    adc_assign_callbacks(&_adc_callbacks);
    adc_start_protocol();
    adc_enable_isr();
    adc_start_conversion(ADC_MUX0, AVCC_VREF, CLK_16);

    while (1); /* Running forever! */
	return 0;
}
