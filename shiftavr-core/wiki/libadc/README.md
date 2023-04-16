## HelloAnalogRead

Shows an example of using ADC pins to read data from a potentiometer connected to ADC0.

--------------
### The ADC Protocol Layout: 

![image](https://user-images.githubusercontent.com/60224159/177138088-32a4244c-2c3f-4c8d-8ddd-51e896dccf6a.png)

#### 1) Some of the major characteristics of the ADC:
- Resolution
- Conversion time
- Vref
- Digital Data output
- Parallel vs Serial ADC
- Analog input channels
- Start conversion and end of conversion (EOC) signals
- Successive approximation ADC

#### 2) Operating ADC in `atmega328p` using C avr lib:
To operate the ADC in the atmega32, you will need to study the `ADMUX` of the multiplexer which encodes the ADC pins and the status and control 
register `ADCSRA` of the avr:

<a name="ADMUX"></a>

- ADMUX: ADC multiplexer selection register:

| `ADMUX Register Bits` |
|-----------------------|
| ![image](https://user-images.githubusercontent.com/60224159/177139833-081cbe02-556b-4bf5-a9af-4ccb066e37b6.png) |

| `AREF Truth table` | `The ADLAR Bit` | `MUX Bits` | 
|------------------------|-------------------|-------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/177140256-67d3e506-b64d-4244-9741-0dec0dfd6974.png) | ![image](https://user-images.githubusercontent.com/60224159/177141673-738104e3-580b-45b1-aacc-636efaa1a7c8.png) | ![image](https://user-images.githubusercontent.com/60224159/177140612-feb0c8c3-c81a-4e3f-9a18-75c70d99a5fa.png) |


- ADSCRA: ADC Control and Status Register:

| `ADCSRA Register Bits` | 
|------------------------|
| ![image](https://user-images.githubusercontent.com/60224159/177142491-bb6aa25e-7377-4627-ba30-95f7483561d0.png) |

<a name="COVERSION"></a>

| `ADC Start Conversion bit` |
|----------------------------|
| To start the ADC Conversion, setting the bit `ADSC` of the `ADCSRA` register to true is an essential step, furhter more the `ADIE` enables the interrupt service routine for the ADC conversion onComplete and the `ADIF` is set to true when the conversion is completed |

| `A/D Conversion time` |
|-----------------------|
| ![image](https://user-images.githubusercontent.com/60224159/177149300-3611afc3-43a1-4a77-976b-d8c8b6cb36ee.png) |

- ADCL: ADC Low Byte Register
- ADCH: ADC High Byte Register

| For more about the internals of the ADC, here is a good article showing the operation of an ADC (MCP3008) with the raspberry pi in depth |
|-------------------------------------------------|
| https://pi4j.com/featured-projects/joystick-game/ |

--------------

### Steps of implementing the ADC protocol using libshiftavr:

The `adc/adc.h` provides the following prototypes with the conventional prefix `adc_`:
```c
void adc_start_protocol();
void adc_stop_protocol();
void adc_enable_isr();
void adc_on_received(const uint16_t READ);
void adc_start_conversion(const uint8_t PIN);
uint16_t adc_read();
```

And provides the following ADC channels through the adc multiplexer: 
```c
/* define analog ADC pins based on the multiplexers codes */
#define ADC_MUX0 ((const uint8_t) 0x00)
#define ADC_MUX1 (ADC_MUX0 + 0x01)
#define ADC_MUX2 (ADC_MUX1 + 0x01)
#define ADC_MUX3 (ADC_MUX2 + 0x01)
#define ADC_MUX4 (ADC_MUX3 + 0x01)
#define ADC_MUX5 (ADC_MUX4 + 0x01)
#define ADC_MUX6 (ADC_MUX5 + 0x01)
#define ADC_MUX7 (ADC_MUX6 + 0x01)
```
The conversion can be applied on only one channel at a time (single-ended conversion), multiple-ended conversions will be covered when implementing `libtimer` and `libjoystick`.

1) Adjusting the `ADCSRA` register: to enable the ADC protocol and the clock pre-scaler to valid clock greater than 200k HZ from the Fosc value (frequency of the crystal oscillator): [--Jump to ADMUX Docs--](#ADMUX)
```c
#include<adc/adc.h>
...
int main() {
    adc_start_protocol();
    while (1); /* Running forever! */
}
```
2) Enable the adc interrupt service subroutine vector (the adc interrupt service handler) and implement `void adc_on_received(uint16_t)`: 
```c
#include<adc/adc.h>
...

void adc_on_received(const uint16_t READ) {
    // do stuff
}

int main() {
    adc_start_protocol();
    adc_enable_isr();
    while (1); /* Running forever! */
}
```
3) Start the conversion on an ADC_MUX channel which encodes for `ADC0...ADC7` according to a truth table: [--Jump to A/D Conversion Docs--](#COVERSION)
```c
#include<adc/adc.h>
...

void adc_on_received(const uint16_t READ) {
    // do stuff
}

int main() {
    adc_start_protocol();
    adc_enable_isr();
    // start conversion on [adc channel 0] with the [AREF = VCC] and Conversion speed = CLK/16
    adc_start_conversion(ADC_MUX0, AVCC_VREF, CLK_16);
    while (1); /* Running forever! */
}
```
4) Read the analog data using `uint16_t adc_read()` or use the interrupt service subroutine `ISR(ADC_vect) {...}` and then re-start conversion to trigger the interrupt service handler again for continous monitoring: 
```c
#include<adc/adc.h>
...

void adc_on_received(const uint16_t READ) {
    // do stuff
    // restart conversion 
    adc_start_conversion(ADC_MUX0, AVCC_VREF, CLK_16);
}

int main() {
    adc_start_protocol();
    adc_enable_isr();
    // start conversion on adc channel 0
    adc_start_conversion(ADC_MUX0);
    while (1); /* Running forever! */
}
```
-------------
