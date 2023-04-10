#include<adc/adc.h>

void adc_stop_protocol() {
    ADCH = 0x00;
    ADCL = 0x00;
    ADCSRA = 0x00; /* format the control status register A including the [ADEN] bit */
}

