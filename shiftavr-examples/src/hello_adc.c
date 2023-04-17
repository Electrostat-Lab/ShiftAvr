#define F_CPU 16000000UL
#include <adc/adc.h>
#include <stdio.h>
#include <uart/uart.h>
#include <util/delay.h>

void adc_on_received(const uint16_t);
void adc_on_protocol_started();
void on_data_received(const uint8_t);
void on_data_transmitted(const uint8_t);

volatile uint8_t channel = ADC_MUX0;

volatile uint16_t potentio_x = 0;
volatile uint16_t potentio_y = 0;

static inline void switch_channels() {
    if (channel == ADC_MUX0) {
        channel = ADC_MUX1;
    } else {
        channel = ADC_MUX0;
    }
}

static inline void print() {
    if (potentio_x == 0 || potentio_y == 0) {
        return;
    }
    char* buffer = allocate_buffer();
    sprintf(buffer, "[x = %d, y = %d]", potentio_x, potentio_y);
    uart_sprintln(buffer);
    free(buffer);
    // reset values
    potentio_x = 0;
    potentio_y = 0;
}

void adc_on_received(const uint16_t READ) {
    // assign values from channels
    if (channel == ADC_MUX0) {
        potentio_x = READ;
    } else {
        potentio_y = READ;
    }
    
    print();
    switch_channels();

    // restart the adc conversion with a new channel 
    adc_start_conversion(channel, AVCC_VREF, CLK_16);
}

void adc_on_protocol_started() {
    uart_sprintln("Graftpad Application Monitor >>>>>> >>>>> >>>>>>>");
}

/**
 * @note volatile: marks this object as an interrupt-safe adjustable. 
 */
volatile adc_callbacks _adc_callbacks = {
    adc_on_received,
    adc_on_protocol_started,
    NULL,
    NULL,
};

int main() {
    /* setup UART! */
    uart_start_protocol(BAUD_RATE_57600);

    /* setup ADC! */
    adc_assign_callbacks(&_adc_callbacks);
    adc_start_protocol();
    adc_enable_isr();
    /* start with channel zero! */
    adc_start_conversion(channel, AVCC_VREF, CLK_16);

    while (1); /* Running forever! */
    return 0;
}
