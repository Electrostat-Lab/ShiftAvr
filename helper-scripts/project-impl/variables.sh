#!/bin/bash

project_root=$(pwd)
# avr home for toolchains and header files to link to sources
AVR_HOME="$project_root/avr8-gnu-toolchain-linux_x86_64" 

# supported targets
mcu_atmega32A="atmega32"
mcu_atmega328p="atmega328p"

# cmake build caches
source_dir="./shiftavr-core/"


