## <img src="https://user-images.githubusercontent.com/60224159/230797593-dafd6c8f-17fc-401f-a766-1461a048430f.png" width="120" height="60"> ShiftAvr

> <sub width=2 height=2> The Avr-Sandbox project </sub> 

[![](https://github.com/Software-Hardware-Codesign/ShiftAvr/actions/workflows/build-shiftavrcore.yml/badge.svg)](https://github.com/Software-Hardware-Codesign/ShiftAvr/actions) 

> [!WARNING]
>
> Archived in [a migration process](https://github.com/Electrostat-Lab/Electrostatic-Sandbox/pull/62) to Electrostatic-Sandbox SDK.

A modern implementation of avr-core and GNU libraries for avr microcontroller units purely written in C.

## This project is composed of several subprojects: 
- [x] shiftavr-core: A low-level API that provides a direct implementation to the internal avr-units.
- [ ] shiftavr-api: A high-level API that provides a combination of several hardware and sensors implementation combined with high-level design patterns and software principles to engage the core into a competitive level.
- [ ] shiftavr-examples: Tech-demos and examples for the shiftavr project.

#### The project `shiftavr-core` includes the following libraries: 
- [x] libuart
- [x] libadc
- [x] libgpio
- [ ] libspi
- [ ] libtwi
- [ ] libpwm
- [ ] libtimer

#### The project `shiftavr-examples` includes the following techdemos: 
- [x] hello_uart
- [x] hello_adc
- [x] hello_gpio_write
- [x] hello_gpio_read
- [ ] hello_spi
- [ ] hello_twi
- [ ] hello_pwm
- [ ] hello_timer

#### The project `shiftavr-api` includes the following libraries: 
- [ ] libmcp3008
- [ ] libstepper
- [ ] libjoystick
- [ ] libultrasonic
- [ ] libmq135
- [ ] libvectormath
- [ ] libnumberformat

