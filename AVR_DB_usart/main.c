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

#define F_CPU                      (4000000UL) /* using default clock 4MHz*/
#define USART_BAUD_RATE(BAUD_RATE) ((float)(64 * (float)F_CPU / (16 * (float)BAUD_RATE)) + 0.5)

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#define LED_PORT   PORTB
#define LED_VPORT  VPORTB
#define LED_CTRL   PORTB.PIN3CTRL
#define LED_PIN_bm PIN3_bm

void USART3_init(void);
void USART3_sendChar(char c);
void USART3_sendString(char* str);

void USART3_init(void)
{
    PORTB.DIRSET = PIN0_bm; /* set pin 0 of PORT B (TXd) as output */
    PORTB.DIRCLR = PIN1_bm; /* set pin 1 of PORT B (RXd) as input */

    USART3.BAUD = (uint16_t)(USART_BAUD_RATE(9600)); /* set the baud rate*/

    USART3.CTRLC = USART_CHSIZE0_bm | USART_CHSIZE1_bm; /* set the data format to 8-bit*/

    USART3.CTRLB |= USART_TXEN_bm; /* enable transmitter*/
}

void USART3_sendChar(char c)
{
    while (!(USART3.STATUS & USART_DREIF_bm)) {
        ;
    }

    USART3.TXDATAL = c;
}

void USART3_sendString(char* str)
{
    for (size_t i = 0; i < strlen(str); i++) {
        USART3_sendChar(str[i]);
    }
}

int main(void)
{
    /* Configure LED0 pin as output */
    LED_PORT.DIRSET = LED_PIN_bm;

    USART3_init();

    while (1) {
        USART3_sendString("Hello World!\r\n");
        LED_PORT.OUTTGL = LED_PIN_bm;
        _delay_ms(1000);
    }
}
