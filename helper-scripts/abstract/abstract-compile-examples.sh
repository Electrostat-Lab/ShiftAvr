#!/bin/bash

function compile() {
    local avrhome=${1}
    local target=${2}
    local source_dir=${3}
    local shiftavr=${4}
    local example=${5}
    
    local temp=$(pwd)
    cd ${source_dir}
    
    cmake "-DAVR_HOME=${avrhome}" \
          "-DTARGET=${target}" \
          "-DSHIFT_AVR=${shiftavr}" \
          "-DEXAMPLE=${example}" \
          -S . -B "./build/${target}"
          
    cmake --build "./build/${target}"
    cd ${temp}
}

