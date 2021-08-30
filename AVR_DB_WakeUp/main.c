/**
 * \file main.c
 *
 * \brief Main source file.
 *
 (c) 2019 Microchip Technology Inc. and its subsidiaries.
    Subject to your compliance with these terms, you may use this software and
    any derivatives exclusively with Microchip products. It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define LED_PORT   PORTB
#define LED_VPORT  VPORTB
#define LED_CTRL   PORTB.PIN3CTRL
#define LED_PIN_bm PIN3_bm

#define BUTTON_PORT   PORTB
#define BUTTON_VPORT  VPORTB
#define BUTTON_CTRL   PORTB.PIN2CTRL
#define BUTTON_PIN_bm PIN2_bm
#define BUTTON_vect   PORTB_PORT_vect

static void PORT_init(void);
static void SLPCTRL_init(void);

static void PORT_init(void)
{
    LED_PORT.OUTSET = LED_PIN_bm;
    LED_PORT.DIRSET = LED_PIN_bm;

    BUTTON_PORT.DIRCLR = BUTTON_PIN_bm;
    BUTTON_CTRL |= PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc;
}

static void SLPCTRL_init(void)
{
    SLPCTRL.CTRLA = SLPCTRL_SMODE_IDLE_gc;
}

ISR(BUTTON_vect)
{
    LED_PORT.OUTCLR = LED_PIN_bm;
    BUTTON_PORT.INTFLAGS = BUTTON_PIN_bm;
}

int main(void)
{
    PORT_init();
    SLPCTRL_init();
    sei();

    while (1) {
        sleep_mode();

        _delay_ms(1000);
        LED_PORT.OUTSET = LED_PIN_bm;
    }
}
