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
#define PERIOD_EXAMPLE_VALUE (0xFFFF)
// #define DUTY_CYCLE_EXAMPLE_VALUE (0xC000) /* 25% duty cycle*/
#define DUTY_CYCLE_EXAMPLE_VALUE (0x8000) /* 50% duty cycle*/
//#define DUTY_CYCLE_EXAMPLE_VALUE (0x4000) /* 75% duty cycle*/

#include <avr/io.h>
/*Using default clock 4MHz */

//#define LED_PORT   PORTB
//#define LED_VPORT  VPORTB
//#define LED_CTRL   PORTB.PIN3CTRL
//#define LED_PIN_bm PIN3_bm

#define LED_PORT   PORTC
#define LED_VPORT  VPORTC
#define LED_CTRL   PORTC.PIN6CTRL
#define LED_PIN_bm PIN6_bm

void PORT_init(void);
void TCA1_init(void);

void PORT_init(void)
{
    /*set pin 6 of PORT C as output*/
    LED_PORT.DIRSET = LED_PIN_bm;
}

void TCA1_init(void)
{
    PORTMUX.TCAROUTEA = PORTMUX_TCA1_PORTC_gc; /* set waveform output on PORT C */

    TCA1.SINGLE.CTRLB = TCA_SINGLE_CMP2EN_bm                /* enable compare channel 2 */
                        | TCA_SINGLE_WGMODE_SINGLESLOPE_gc; /* single-slope PWM mode */

    TCA1.SINGLE.PER = PERIOD_EXAMPLE_VALUE;      /* set PWM frequency*/
    TCA1.SINGLE.CMP2 = DUTY_CYCLE_EXAMPLE_VALUE; /* set PWM duty cycle*/

    TCA1.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV64_gc /* set clock source (main_clk/16) */
                        | TCA_SINGLE_ENABLE_bm;    /* start timer */
}

int main(void)
{
    PORT_init();

    TCA1_init();

    while (1) {
        ;
    }
}
