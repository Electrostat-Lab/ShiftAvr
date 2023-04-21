/**
 * @brief An example showing a blink on PB5-PORTB.
 * @author pavl_g.
 * @copyright 
 *  
 */
#define F_CPU 16000000UL
#include <gpio/gpio.h>
#include <util/delay.h>

int main() {
    /* assigns the digital port addresses */
    gpio_initialize_ports();
    while (0xFF) {
        /* writes 1 to bit.5 on PORTB data register */
        gpio_write(GPIO_PORTB, PB5, ON);
        _delay_ms(500);
        /* writes 0 to bit.5 on PORTB data register */
        gpio_write(GPIO_PORTB, PB5, OFF);
        _delay_ms(500);
    }
    return 0;
}