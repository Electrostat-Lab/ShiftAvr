#include <adc/adc.h>

/**
 * @brief An interrupt service handler, fired when the ADC conversion completes.
 */
ISR(ADC_vect) { 
    volatile uint8_t adcl = ADCL; /* ADCL must be read before ADCH */
    volatile uint8_t adch = ADCH; 
    adc_on_received(((0x00 | adch) << 8) | adcl);
}

void adc_enable_isr() {
    ADCSRA |= (1 << ADIE); /*enable interrupt service*/ 
    sei();
}

