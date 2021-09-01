/*
    \file   main.c

    \brief  ADC Single Conversion

    (c) 2019 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with
   third-party license terms applicable to your use of third-party software (including open source
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

#define F_CPU 4000000UL /* Main clock frequency */

/* Compute the baud rate */
#define USART_BAUD_RATE(BAUD_RATE) (((float)F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

#define LED_PORT   PORTB
#define LED_VPORT  VPORTB
#define LED_CTRL   PORTB.PIN3CTRL
#define LED_PIN_bm PIN3_bm

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include <util/delay.h>
#include <avr/io.h>
#include <avr/cpufunc.h>

void CLKCTRL_init(void);
void PORT_init(void);
void VREF0_init(void);
void ADC0_init(void);
void USART1_init(void);
uint16_t ADC0_read(void);
void ADC0_start(void);
void USART1_Write(const uint8_t data);

/* This function initializes the PORT module */
void PORT_init(void)
{
    /* Configure LED0 pin as output */
    LED_PORT.DIRSET = LED_PIN_bm;

    /* Configure PC0 as output for USART1 TX */
    PORTB.DIRSET = PIN0_bm; /* set pin 0 of PORT B (TXd) as output */
    PORTB.DIRCLR = PIN1_bm; /* set pin 1 of PORT B (RXd) as input */

    /* Disable interrupt and digital input buffer on PD0 */
    PORTD.PIN0CTRL &= ~PORT_ISC_gm;
    PORTD.PIN0CTRL |= PORT_ISC_INPUT_DISABLE_gc;

    /* Disable pull-up resistor */
    PORTD.PIN0CTRL &= ~PORT_PULLUPEN_bm;
}

/* This function initializes the VREF module */
void VREF0_init(void)
{
    VREF.ADC0REF = VREF_REFSEL_4V096_gc; /* Internal 4.096V reference */
}

/* This function initializes the ADC module */
void ADC0_init(void)
{
    ADC0.CTRLC = ADC_PRESC_DIV4_gc;     /* CLK_PER divided by 4 */
    ADC0.CTRLA = ADC_ENABLE_bm          /* ADC Enable: enabled */
                 | ADC_RESSEL_12BIT_gc; /* 12-bit mode */
    ADC0.MUXPOS = ADC_MUXPOS_AIN0_gc;   /* Select ADC channel AIN0 <-> PD0 */
}

/* This function initializes the USART module */
void USART_init(void)
{
    /* Configure the baud rate: 9600 */
    USART3.BAUD = (uint16_t)USART_BAUD_RATE(9600);
    USART3.CTRLB = USART_TXEN_bm;        /* Enable TX */
    USART3.CTRLC = USART_CHSIZE_8BIT_gc; /* Configure character size: 8 bit */
}

/* This function returns the ADC conversion result */
uint16_t ADC0_read(void)
{
    /* Wait for ADC result to be ready */
    while (!(ADC0.INTFLAGS & ADC_RESRDY_bm))
        ;
    /* Clear the interrupt flag by reading the result */
    return ADC0.RES;
}

/* This function starts the ADC conversions*/
void ADC0_start(void)
{
    /* Start ADC conversion */
    ADC0.COMMAND = ADC_STCONV_bm;
}

/* This function transmits one byte through USART */
void USART3_Write(const uint8_t data)
{
    /* Check if USART buffer is ready to transmit data */
    while (!(USART3.STATUS & USART_DREIF_bm))
        ;
    /* Transmit data using TXDATAL register */
    USART3.TXDATAL = data;
}

static int USART3_printChar(char c, FILE* stream)
{
    USART3_Write(c);
    return 0;
}

/* The definition of a custom stream that will be handled by the USART send function */
static FILE USART_stream = FDEV_SETUP_STREAM(USART3_printChar, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
    uint16_t adcValue;

    /* Initialize all peripherals */
    PORT_init();
    VREF0_init();
    ADC0_init();
    USART_init();

    /* Replace the standard output stream */
    stdout = &USART_stream;

    while (1) {
        /* Start the ADC conversion */
        ADC0_start();

        /* Read the ADC result */
        adcValue = ADC0_read();

        /* Transmit the ADC result to be plotted using Data Visualizer */
        printf("ADC Raw Result = %d\r\n", adcValue);
        printf("ADC Result [V] = %.2fV\r\n", adcValue / 4096.0 * 3.3);

        LED_PORT.OUTTGL = LED_PIN_bm;
        _delay_ms(1000);
    }
}
