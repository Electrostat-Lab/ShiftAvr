/**
 * @brief An example showing a dirty switch processor which reads the state on PB2 and apply it
 *        on PB5 on PORTB.
 * @author pavl_g.
 * @copyright 
 *  
 */
#define F_CPU 16000000UL
#include <gpio/gpio.h>
#include <util/delay.h>

int main() {
    /* assigns port addresses */
    gpio_initialize_ports();
    while (0xFF) {
        /* reads gpio PB2 Pin with initial Pull-up [OFF] state */
        const uint8_t state = gpio_read(GPIO_PORTB, PB2, OFF);
        /* assigns the output state to bit PB5 in PORTB data register */
        gpio_write(GPIO_PORTB, PB5, state);
    }
    return 0;
}