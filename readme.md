AVR128DB48 Curiosity Nano
=========================

Single main.c file examples for 
[AVR128DB48 CURIOSITY NANO EVALUATION KIT](https://www.microchip.com/en-us/development-tool/EV35L43A) Part Number: EV35L43A

Have only 43 projects in the [Microchip PIC & AVR Examples](https://github.com/microchip-pic-avr-examples) mainly for opamp and mvio.

For [AVR128DA48 CURIOSITY NANO EVALUATION KIT](https://www.microchip.com/en-us/development-tool/DM164151) Part Number: DM164151 have 82 projects.

Boards have different pin configuration. Direct move not available.

| pin          | AVR128DA48  | AVR128DB48  |
|--------------|-------------|-------------|
| Yellow LED0  | PC6         | PB3         | 
| User switch (SW0)  | PC7   | PB2         | 
| UART         | USART1      | USART3      | 
| UART RX      | PC0         | PB0         | 
| UART TX      | PC1         | PB1         |

AVR\_DB\_LED\_blink\_delay
--------------------------

[avr128da48-led-blink-delay-example](https://github.com/microchip-pic-avr-examples/avr128da48-led-blink-delay-example/)

AVR\_DB\_LED\_blink\_interrupt
------------------------------

[avr128da48-led-blink-interrupt-example](https://github.com/microchip-pic-avr-examples/avr128da48-led-blink-interrupt-example)


AVR\_DB\_WakeUp
---------------

[avr128da48-ext-int-wakeup-example](https://github.com/microchip-pic-avr-examples/avr128da48-ext-int-wakeup-example)

Demonstrates a simple implementation of a sleep operation with an external interrupt triggering an LED blink.

* SLPCTRL
* Configured for entering Idle Mode when SLEEP instruction is executed

AVR\_DB\_LED\_blink\_sleep
--------------------------

[avr128da48-led-blink-sleep-examplee](https://github.com/microchip-pic-avr-examples/avr128da48-led-blink-sleep-example)


AVR\_DA\_GPIO\_Debouncing
-------------------------
 
[avr128da48-gpio-debouncing-example](https://github.com/microchip-pic-avr-examples/avr128da48-gpio-debouncing-example)

Using EVSYS throwout the TCB0 timer and GPIO.

XOSCHF\_with\_external\_crystal
-------------------------------

One of the [avr128db48-getting-started-with-xoschf](https://github.com/microchip-pic-avr-examples/avr128db48-getting-started-with-xoschf)
lab.

PWM examples
------------

Нельзя перенести напрямую. LED подключен к PB3 - можно подключить к верхней половине TCA в SPLIT режиме.
Для проверки нужно подключить внешний LED на порт PC6, как на CN AVR128DA48.

### AVR\_DB\_LED\_blink\_PWM

[avr128da48-led-dimming-pwm-example](https://github.com/microchip-pic-avr-examples/avr128da48-led-blink-pwm-example)

### AVR\_DB\_LED\_dimming\_PWM

[avr128da48-led-dimming-pwm-example](https://github.com/microchip-pic-avr-examples/avr128da48-led-dimming-pwm-example)

AVR\_DB\_usart
--------------

Based on [avr128da48-usart-exampl](https://github.com/microchip-pic-avr-examples/avr128da48-usart-example)

**DTR ON** in the terminal! 

AVR\_DB\_adc
------------

Based on:

* Lab [avr128da48-using-12-bit-adc](https://github.com/microchip-pic-avr-examples/avr128da48-using-12-bit-adc)
* [avr128da48-adc-differential-example](https://github.com/microchip-pic-avr-examples/avr128da48-adc-differential-example)
* [avr128da48-adc-accumulation-example](https://github.com/microchip-pic-avr-examples/avr128da48-adc-accumulation-example)
* [avr128da48-adc-evsys-example](https://github.com/microchip-pic-avr-examples/avr128da48-adc-evsys-example)

Input pin PD0 - to the variable resistor connected to the 3.3V.

Using printf - need add -lprintf_flt to the linker.

AVR\_DB\_usart\_memory\_mapped
------------------------------

Копия AVR\_DB\_usart - добавлен вывод константы из отображенной в память верхней трети FLASH.
Реализация взята из [DxCore - Arduino support for the NEW AVR DA](https://github.com/SpenceKonde/DxCore)

```c
/* default memory mapped segment */
#define MAPPED_PROGMEM __attribute__((__section__(".FLMAP_SECTION3")))

const char MAPPED_PROGMEM hello1[] = "Hello from flash!\r\n";

LOGGER_sendString(&hello1[0]);
```

Add Linker->Memory settings FLASH segment .FLMAP_SECTION3=0xC000 
