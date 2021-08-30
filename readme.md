AVR128DB48 Curiosity Nano
=========================

[AVR128DB48 CURIOSITY NANO EVALUATION KIT](https://www.microchip.com/en-us/development-tool/EV35L43A) Part Number: EV35L43A

Have only 43 projects in the [Microchip PIC & AVR Examples](https://github.com/microchip-pic-avr-examples) mainly for opamp and mvio.

For [AVR128DA48 CURIOSITY NANO EVALUATION KIT](https://www.microchip.com/en-us/development-tool/DM164151) Part Number: DM164151 have 82 projects.

Boards have different pin configuration. Direct move not available.

^ pin          ^ AVR128DA48  ^ AVR128DB48  ^
| Yellow LED0  | PC6         | PB3         | 
| User switch (SW0)  | PC7   | PB2         | 
| UART RX      | PC0         | PB0         | 
| UART TX      | PC1         | PB1         |

AVR\_DB\_LED\_blink\_delay
--------------------------

[avr128da48-led-blink-delay-example](https://github.com/microchip-pic-avr-examples/avr128da48-led-blink-delay-example/)

AVR\_DA\_GPIO\_Debouncing
-------------------------
 
[avr128da48-gpio-debouncing-example](https://github.com/microchip-pic-avr-examples/avr128da48-gpio-debouncing-example)

Using EVSYS throwout the TCB0 timer and GPIO.

XOSCHF\_with\_external\_crystal
-------------------------------

One of the [avr128db48-getting-started-with-xoschf](https://github.com/microchip-pic-avr-examples/avr128db48-getting-started-with-xoschf)
lab.

PWN examples
------------

Нельзя перенести напрямую. LED подключен к PB3 - можно подключить к верхней половине TCA в SPLIT режиме.
Для проверки нужно подключить внешний LED на порт PC6, как на CN AVR128DA48.

####AVR\_DB\_LED\_blink\_PWM

[avr128da48-led-dimming-pwm-example](https://github.com/microchip-pic-avr-examples/avr128da48-led-blink-pwm-example)

####AVR\_DB\_LED\_dimming\_PWM

[avr128da48-led-dimming-pwm-example](https://github.com/microchip-pic-avr-examples/avr128da48-led-dimming-pwm-example)


 
