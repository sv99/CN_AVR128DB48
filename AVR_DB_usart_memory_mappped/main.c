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

/* default memory mapped segment */
#define MAPPED_PROGMEM __attribute__((__section__(".FLMAP_SECTION3")))

#define LED_PORT   PORTB
#define LED_VPORT  VPORTB
#define LED_CTRL   PORTB.PIN3CTRL
#define LED_PIN_bm PIN3_bm

#define LOGGER            USART3
#define LOGGER_RXC_vect   USART3_RXC_vect
#define LOGGER_DRE_vect   USART3_DRE_vect
#define LOGGER_TXD_PORT   PORTB
#define LOGGER_TXD_VPORT  VPORTB
#define LOGGER_TXD_CTRL   PORTB.PIN0CTRL
#define LOGGER_TXD_PIN_bm PIN0_bm
#define LOGGER_RXD_PORT   PORTB
#define LOGGER_RXD_VPORT  VPORTB
#define LOGGER_RXD_CTRL   PORTB.PIN1CTRL
#define LOGGER_RXD_PIN_bm PIN1_bm

void LOGGER_init(void);
void LOGGER_sendChar(char c);
void LOGGER_sendString(const char* str);

void LOGGER_init(void)
{
    LOGGER_TXD_PORT.DIRSET = LOGGER_TXD_PIN_bm; /* set pin 0 of PORT B (TXd) as output */
    LOGGER_RXD_PORT.DIRCLR = LOGGER_RXD_PIN_bm; /* set pin 1 of PORT B (RXd) as input */

    LOGGER.BAUD = (uint16_t)(USART_BAUD_RATE(9600)); /* set the baud rate*/

    LOGGER.CTRLC = USART_CHSIZE0_bm | USART_CHSIZE1_bm; /* set the data format to 8-bit*/

    LOGGER.CTRLB |= USART_TXEN_bm; /* enable transmitter*/
}

void LOGGER_sendChar(char c)
{
    while (!(LOGGER.STATUS & USART_DREIF_bm)) {
        ;
    }

    LOGGER.TXDATAL = c;
}

void LOGGER_sendString(const char* str)
{
    for (size_t i = 0; i < strlen(str); i++) {
        LOGGER_sendChar(str[i]);
    }
}

const char* hello = "Hello from sram!\r\n";
const char MAPPED_PROGMEM hello1[] = "Hello from flash!\r\n";

int main(void)
{
    /* Configure LED0 pin as output */
    LED_PORT.DIRSET = LED_PIN_bm;

    LOGGER_init();

    while (1) {
        LOGGER_sendString(hello);
        LOGGER_sendString(&hello1[0]);
        LED_PORT.OUTTGL = LED_PIN_bm;
        _delay_ms(1000);
    }
}
