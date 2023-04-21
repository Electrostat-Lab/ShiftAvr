/**
 * @brief Defines the data structure for shift-avr port memory address locations system.
 * @note Three I/O memory address locations are allocated for each port, one each for the data register – PORTx, data direction
 *       register – DDRx, and the port input pins – PINx.
 * @author pavl_g.
 * @copyright
 */
#ifndef _GPIO_H_
#   error "The <gpio/port/port.h> header is an internal property, include <gpio/gpio.h> instead of this!"
#endif

#ifndef _GPIO_PORT_H_
#define _GPIO_PORT_H_

/**
 * @brief Defines a GPIO port with 3 I/O memory address locations, PORTx, DDRx and PINx.
 */
typedef struct {
    /**
     * @brief The memory address location for the data register [PORTx].
     */
    volatile uint8_t* PORTx;
    
    /**
     * @brief The memory address location for the data direction register [DDRx].
     */
    volatile uint8_t* DDRx;
    
    /**
     * @brief The memory address location for the port inputs register [PINx].
     */
    volatile uint8_t* PINx;
} gpio_port;

#endif