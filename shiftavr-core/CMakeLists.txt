cmake_minimum_required(VERSION 3.18.1)

# define a project with a version
project(shiftavr VERSION 1.0)

message(STATUS "Project: shiftavr")
message(STATUS "AVR_HOME: ${AVR_HOME}")
message(STATUS "Target Hardware: ${TARGET}")

# Cmake variables
set(library "shiftavr")

set(CMAKE_C_COMPILER "${AVR_HOME}/bin/avr-gcc")
set(CMAKE_CXX_COMPILER "${AVR_HOME}/bin/avr-g++")
set(COMPILER_OPTIONS "-mmcu=${TARGET}") 

set(avr_headers "${AVR_HOME}/avr/include/")

set(libuart "${CMAKE_CURRENT_SOURCE_DIR}/src/libuart/uart_start_protocol.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/libuart/uart_stop_protocol.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/libuart/uart_receiver_isr.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/libuart/uart_transmitter_isr.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/libuart/udr_reset_isr.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/libuart/udr_cprint.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/libuart/udr_cprintln.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/libuart/udr_plain_io.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/libuart/udr_print.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/libuart/udr_println.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/libuart/udr_sprint.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/libuart/udr_sprintln.c")
            
set(libadc "${CMAKE_CURRENT_SOURCE_DIR}/src/libadc/adc_start_protocol.c"
           "${CMAKE_CURRENT_SOURCE_DIR}/src/libadc/adc_start_conversion.c"
           "${CMAKE_CURRENT_SOURCE_DIR}/src/libadc/adc_stop_protocol.c"
           "${CMAKE_CURRENT_SOURCE_DIR}/src/libadc/adc_read.c"
           "${CMAKE_CURRENT_SOURCE_DIR}/src/libadc/adc_conversion_isr.c")

set(libgpio "${CMAKE_CURRENT_SOURCE_DIR}/src/libgpio/gpio_read.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/libgpio/gpio_fastread.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/libgpio/gpio_write.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/libgpio/port/part/gpio_part.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/libgpio/gpio_write.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/libgpio/gpio_toggle_pin_pullup.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/libgpio/gpio_toggle_universal_pullup.c")

set(headers "${avr_headers}"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/include/")

set(sources ${libuart} ${libadc} ${libgpio}) 

# add a library target
add_library(${library} STATIC ${sources})

# set both COMPILE_FLAGS and LINK_FLAGS to the specified binary architecture
set_target_properties(${library} PROPERTIES COMPILE_FLAGS "${COMPILER_OPTIONS}" LINK_FLAGS "${COMPILER_OPTIONS}")

# include headers for the target
target_include_directories(${library} PUBLIC ${headers})

# Start building the target
target_sources(${library} PUBLIC ${sources})
