/**
 * @file uart.h
 * @author pavl_g.
 * @brief Controls the UART IO Protocol which involves sending and receiving bits and firing listeners upon that (Concrete Command pattern).
 * @version 0.1
 * @date 2022-07-02
 * 
 * @copyright The AVR-Sandbox Project, Copyright (c) 2022
 * 
 */
#ifndef _UART_H
#define _UART_H 

#include<avr/io.h>
#include<string.h>
#include<stdlib.h>
#include<avr/interrupt.h>

#if defined (__AVR_ATmega32__)

/** UCSRA register */
#   define REG_UCSRA UCSRA
#   define BIT_RXC RXC
#   define BIT_TXC TXC
#   define BIT_UDRE UDRE 
#   define BIT_FE FE 
#   define BIT_PE PE 
#   define BIT_U2X U2X 
#   define BIT_MPCM MPCM

/** UCSRB register */
#   define REG_UCSRB UCSRB
#   define BIT_RXCIE RXCIE
#   define BIT_TXCIE TXCIE
#   define BIT_UDRIE UDRIE
#   define BIT_RXEN RXEN
#   define BIT_TXEN TXEN
#   define BIT_UCSZ2 UCSZ2
#   define BIT_RXB8 RXB8
#   define BIT_TXB8 TXB8

/** UCSRC register */
#   define REG_UCSRC UCSRC 
#   define BIT_URSEL URSEL 
#   define BIT_UMSEL UMSEL 
#   define BIT_UPM0  UPM0 
#   define BIT_UPM1  UPM1
#   define BIT_USBS  USBS
#   define BIT_UCSZ0 UCSZ0
#   define BIT_UCSZ1 UCSZ1
#   define BIT_UCPOL UCPOL

#   define REG_UBRR UBRRH

/** UBRRL register */
#   define REG_UBRRL UBRRL

/** UBRRH register */
#   define REG_UBRRH UBRRH

/** UDR register */
#   define REG_UDR UDR

#   define __vector_USART_RX USART_RXC_vect
#   define __vector_USART_TX USART_TXC_vect

#elif defined (__AVR_ATmega328P__)

/** UCSRA register */
#   define REG_UCSRA UCSR0A
#   define BIT_RXC RXC0
#   define BIT_TXC TXC0
#   define BIT_UDRE UDRE0 
#   define BIT_FE FE0 
#   define BIT_PE PE0 
#   define BIT_U2X U2X0 
#   define BIT_MPCM MPCM0

/** UCSRB register */
#   define REG_UCSRB UCSR0B
#   define BIT_RXCIE RXCIE0
#   define BIT_TXCIE TXCIE0
#   define BIT_UDRIE UDRIE0
#   define BIT_RXEN RXEN0
#   define BIT_TXEN TXEN0
#   define BIT_UCSZ2 UCSZ02
#   define BIT_RXB8 RXB80
#   define BIT_TXB8 TXB80

/** UCSRC register */
#   define REG_UCSRC UCSR0C 
#   define BIT_URSEL URSEL0 
#   define BIT_UMSEL UMSEL0 
#   define BIT_UPM0  UPM00 
#   define BIT_UPM1  UPM01
#   define BIT_USBS  USBS0
#   define BIT_UCSZ0 UCSZ00
#   define BIT_UCSZ1 UCSZ01
#   define BIT_UCPOL UCPOL0

#   define REG_UBRR UBRR0

/** UBRRL register */
#   define REG_UBRRL UBRR0L

/** UBRRH register */
#   define REG_UBRRH UBRR0H

/** UDR register */
#   define REG_UDR UDR0

#   define __vector_USART_RX USART_RX_vect
#   define __vector_USART_TX USART_TX_vect

#endif

#define BAUD_RATE_9600 ((const uint8_t) 0x67) 
#define BAUD_RATE_57600 ((const uint8_t) 0x10)

/**
 * @brief Defines a constant for the carriage return combined with the new line in a single value.
 */
#define NEW_LINE_CARRIAGE_R (char*)"\n\r"

/**
 * @brief Defines a constant for the decimal radix base to print the number in decimal case.
 */
#define DEC_RADIX (const uint8_t) 10

/**
 * @brief Defines a constant for the binary radix base to print the numbner in binary case.
 */
#define BIN_RADIX (const uint8_t) 2

/**
 * @brief Allocates an expandable string buffer for small/medium/large integers and clears the buffer to zero.
 * 
 * @example For decimal base 10: 155 is the same as saying [const char str[] = {'155', NULL};] or [char str[] = {'155', '\0'};].
 * @example For binary base 2: 0b11110000 is the same as saying [const char str[] = {'1', '1' ,'1', '1', '0', '0', '0', '0', '\0'};],
 * i.e. one character for each bit plus one for the string terminator '\0' which is (NULL).     
 */
#define allocate_buffer_address() ((char*) calloc(1, sizeof(char*))) 

/**
 * @brief Callbacks for the uart protocol, use the struct initializer to instantiate these pointers.
 */
typedef struct {
    void (*on_protocol_started)();
    void (*on_protocol_stopped)();
    void (*on_data_receive_completed)(const uint8_t);
    void (*on_data_transmission_completed)(const uint8_t);
    void (*on_databuffer_cleared)();
} uart_callbacks;

/**
 * Interrupt-safe re-assignable callbacks.
 */
volatile uart_callbacks* uart_internal_callbacks;

static inline void uart_assign_callbacks(volatile uart_callbacks* in_callbacks) {
    uart_internal_callbacks = in_callbacks;
}

/**
 * @brief Sets the Transmit Data Register to be used by the UDR when the UDRE bit is set.
 * 
 * @param data the data buffer to transmit.
 */
void uart_set_transmitter_register(const uint8_t data);

/**
 * @brief Starts the UART Protocol by setting up the control status registers and the baud rate register.
 * it operates the UART as Tx and Rx.
 * 
 * @param BAUD_RATE_VAL the code for the baud rate.
 */
void uart_start_protocol(const uint16_t BAUD_RATE_VAL);

/**
 * @brief Stops the UART protocol by setting [UCSRB] to zero.
 */
void uart_stop_protocol();

/**
 * @warning Internal use only.
 * 
 * @brief Activates the ISR handler for the UDRE (Data register empty) bit.
 */
void uart_start_udre_isr();

/**
 * @warning Internal use only.
 * 
 * @brief Activates the ISR handler for the RXC bit (Receiver Complete).
 */
void uart_start_receiver_isr();

/**
 * @warning Internal use only.
 * @brief Activates the ISR handler for the TXC bit (Transmitter Complete).
 */
void uart_start_transmitter_isr();

/**
 * @warning Internal use only.
 * 
 * @brief Deactivates the ISR handler for the UDRE (Data register empty) bit.
 */
void uart_stop_udre_isr();

/**
 * @warning Internal use only.
 * 
 * @brief Deactivates the ISR handler for the RXC bit (Receiver Complete).
 */
void uart_stop_receiver_isr();

/**
 * @warning Internal use only.
 * 
 * @brief Deactivates the ISR handler for the TXC bit (Transmitter Complete).
 */
void uart_stop_transmitter_isr();

/**
 * @brief Reads the [UDR0] Data register in ASCII as default.
 * 
 * @return uint8_t an 8-bit integer read from the UDR0, the output is in ascii.
 */
volatile uint8_t uart_poll_read_ascii();

/**
 * @brief Reads the [UDR0] Data register in Integers after converting from ASCII by subtracting the result from '0' aka [48].
 * 
 * @return uint8_t 
 */
volatile uint8_t uart_poll_read_int();

/**
 * @brief Prints a charachter data to the serial stream.
 * 
 * @param data a char data of 8-bit size.
 */
void uart_cprint(char data);

/**
 * @brief Prints a charachter data to the serial stream in a new line.
 * 
 * @param data a char data of 8-bit size.
 */
void uart_cprintln(char data);

/**
 * @brief Prints a string (char array) buffer to the serial stream.
 * 
 * @param data the string buffer to print.
 */
void uart_sprint(char* data);

/**
 * @brief Prints a string (char array) buffer to the serial stream in a new line with a carriage return [(\n\r)].
 * 
 * @param data the string buffer to print.
 */
void uart_sprintln(char* data);

/**
 * @brief Prints an integer data of max 64-bits with a base radix (2 for binary print or 10 for decimal print).
 * 
 * @param data the integer to print.
 * @param base the base, either 2 for binary print ()
 */
void uart_print(const int64_t data, const uint8_t base);

/**
 * @brief Prints an integer data of max 64-bits with a base radix (2 for binary print or 10 for decimal print) 
 * in a new line with carriage return [(\n\r)].
 * 
 * @param data the integer to print.
 * @param base the base, either 2 for binary print (with max size = 64 * sizeof(uint8_t) + 1) or 10 for decimal print
 * (with max size = 1 * sizeof(int64_t) + 1).
 */
void uart_println(const int64_t data, const uint8_t base);


#endif
