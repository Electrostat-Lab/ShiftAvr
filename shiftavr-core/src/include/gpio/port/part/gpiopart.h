/**
 * @brief Defines dependent GPIO registers.
 * @author pavl_g.
 * @copyright
 */
#ifndef _GPIO_H_
#   error "The <gpio/port/part/gpiopart.h> header is an internal property, include <gpio/gpio.h> instead of this!"
#endif

#ifndef _GPIO_PART_H_
#define _GPIO_PART_H_

#if defined (__AVR_ATmega32__)
#  include <gpio/port/part/part-m32.h>
#elif defined (__AVR_ATmega328P__)
#  include <gpio/port/part/part-m328p.h>
#endif

#endif