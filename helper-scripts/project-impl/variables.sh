#!/bin/bash

project_root=$(pwd)
# avr home for toolchains and header files to link to sources
AVR_HOME="$project_root/avr8-gnu-toolchain-linux_x86_64" 

# supported targets
mcu_atmega32A="atmega32"
mcu_atmega328p="atmega328p"

# cmake build caches
source_dir="$project_root/shiftavr-core/"
examples_dir="$project_root/shiftavr-examples/"


# AVR-DUDE properties
BAUD_RATE='57600'
PORT='/dev/ttyUSB0'
CHIP='atmega328p'
CHIP_ALIAS='m328p'
PROGRAMMER='arduino'