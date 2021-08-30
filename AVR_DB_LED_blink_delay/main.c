/*
    (c) 2019 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with third
   party license terms applicable to your use of third party software (including open source
   software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.
*/

#include <avr/io.h>

/* Default OSCHF running at the frequency of 4 MHz */
#define F_CPU 4000000UL
#include <util/delay.h>

#define DELAY_TIME 1000

#define LED_PORT   PORTB
#define LED_VPORT  VPORTB
#define LED_CTRL   PORTB.PIN3CTRL
#define LED_PIN_bm PIN3_bm

#define BUTTON_PORT   PORTB
#define BUTTON_VPORT  VPORTB
#define BUTTON_CTRL   PORTB.PIN2CTRL
#define BUTTON_PIN_bm PIN2_bm

int main(void)
{
    /* Configure LED0 pin as output */
    LED_PORT.DIRSET = LED_PIN_bm;

    while (1) {
        /* LED0 on */
        LED_PORT.OUTSET = LED_PIN_bm;
        _delay_ms(DELAY_TIME);
        /* LED0 off */
        LED_PORT.OUTCLR = LED_PIN_bm;
        _delay_ms(DELAY_TIME);
    }
}
