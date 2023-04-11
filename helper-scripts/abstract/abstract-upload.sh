#!/bin/bash

function convertToHex() {
     local AVR_HOME=${1}
     local elf=${2} 
     local directory=${3}
     
     temp=$(pwd)
     cd ${directory}   
  	 ${AVR_HOME}'/bin/avr-objcopy' -O ihex ${elf} ${elf}'.hex'
  	 cd $temp
	 return $?
}

function upload() {
    local programmer=${1}
    local baud_rate=${2}
    local port=${3}
    local chip=${4}
    local flash_file=${5}
    local directory=${6}
    
    temp=$(pwd)
    cd ${directory}  
	sudo avrdude -c ${programmer} -b${baud_rate} -P${port} -p${chip} -F -U flash:w:${flash_file}
    cd $temp
	return $?
}
