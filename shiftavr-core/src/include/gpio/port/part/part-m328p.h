/**
 * @brief Defines GPIO ports for ATMega328p.
 * @author pavl_g.
 * @copyright
 */
#ifndef _GPIO_H_
#   error "The <gpio/port/part/part-m328p.h> header is an internal property, include <gpio/gpio.h> instead of this!"
#endif

#ifndef _GPIO_PORT_PART_ATMEGA328P_H_
#define _GPIO_PORT_PART_ATMEGA328P_H_

#include <avr/io.h>
#include <gpio/port/port.h>

/**
 * @brief A common Microcontroller-unit-control register alias to control PUD(Pull-Up-Disable) state.
 */
#define GPIO_MCUCR MCUCR

/**
 * @brief Prototype for PORTB registers I/O memory addresses.
 */
gpio_port GPIO_PORTB;

/**
 * @brief Prototype for PORTC registers I/O memory addresses.
 */
gpio_port GPIO_PORTC;

/**
 * @brief Prototype for PORTD registers I/O memory addresses.
 */
gpio_port GPIO_PORTD;

#endif 