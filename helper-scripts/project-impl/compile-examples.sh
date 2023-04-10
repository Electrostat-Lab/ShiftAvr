#!/bin/bash

source "./helper-scripts/abstract/abstract-compile-examples.sh"
source "./helper-scripts/project-impl/variables.sh"

target_mcu=${1}
example=${2}

compile ${AVR_HOME} ${target_mcu} ${examples_dir} ${source_dir} ${example}

