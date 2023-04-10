/**
 * @file start.c
 * @author pavl_g.
 * @brief An implementation for the [Analog.h] header file.
 * @version 0.1
 * @date 2022-07-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<adc/adc.h>

void adc_start_protocol() {
    /* setup ADCSRA */
    ADCSRA = (1 << ADEN) /*enable adc protocol*/ | (1 << ADPS2) | 
             (1 << ADPS1) | (1 << ADPS0) /*set clock prescaler to clk/128*/; 
}
