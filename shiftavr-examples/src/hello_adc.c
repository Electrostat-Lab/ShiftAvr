#include <adc/adc.h>

void adc_on_received(const uint16_t READ) {
    // do stuff
    // restart the adc conversion
    adc_start_conversion(ADC_MUX0);
}

int main() {
    adc_start_protocol();
    adc_enable_isr();
    adc_start_conversion(ADC_MUX0);
    while (1); /* Running forever! */
	return 0;
}
