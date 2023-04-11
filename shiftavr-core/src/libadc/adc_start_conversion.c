#include<adc/adc.h>

void adc_start_conversion(const uint8_t PIN) {
    /* setup ADMUX */
    ADMUX = 0b01000000 | PIN; /* 1 for REFS0 for (VREF = VCC) */
    ADCSRA |= (1 << ADSC); /* the last step: start conversion */
    if (adc_internal_callbacks != NULL && adc_internal_callbacks->adc_on_start_conversion != NULL) {
        adc_internal_callbacks->adc_on_start_conversion();
    }
}
