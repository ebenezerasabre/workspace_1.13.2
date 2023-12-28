/*
 * adc.c
 *
 *  Created on: Nov 16, 2023
 *      Author: ebenezer
 */

#include "adc.h"
#include "base.h"
#include "uart.h"

char names[] = "abcd";

/*Enable bits*/
#define RCC_ADCEN       (1U<<20)
#define ADEN            (1U<<0)
#define ADC_IN0_PA0     (1U<<0)
#define ADSTART         (1U<<2)
#define EOC             (1U<<2)


void adc_init(void){

    // enable clock access to adc module
    RCC_APBENR2 |=  RCC_ADCEN;

    // set GPIOA0 pin to analog in gpio_init go to gpio.c

    // set data resolutionj, setting 12 bits
    ADC_CFGR1 &= ~(1U<<3);
    ADC_CFGR1 |= (1U<<4);

    // select channel, PA0,adc_in0
    ADC_CHSELR |= ADC_IN0_PA0;

    // enable adc module
    ADC_CR |= ADEN;

}

void adc_conversion(void){
    // set continuous conversion mode
    ADC_CFGR1 |= (1U<<13);

    // start adc conversion
    ADC_CR |= ADSTART;
}

int adc_read(void){
    // check if conversion is complete
    while(!(ADC_ISR & EOC))
        ;

    return ADC_DR; // return data_register
}

// I think I should pass the gpio analog pin to this
// void adc_smp_sgnl(int * bffr){
void adc_smp_sgnl(char * buff, int * prgrm_state){
    int uart_byte = 0;
    char byte_one;
    if(*prgrm_state == 49){

        // get starting address of buffer
        char * ptr = buff; 
        // usart_write('z');
        // usart_write(':');

        /**
         * Usart Protocol 2 bytes; 13 bits 2^13 = 8192
         * 1st byte, bit 7 is 0
         * 2nd byte, flag bit 6 | 0x40 100 0000
         * 0x7F 127 0111 1111
         * 0x3F 63  0011 1111
         * 0x40 64  0100 0000
        */
       // each loop fills two indexes of array so loopSize = arraySize/2
        for(int x=0; x<64; x++){
            uart_byte = adc_read();
            byte_one = uart_byte & 0x7F;        // first 7bits bit0 - bit6
            // byte_two = ((uart_byte >> 7) & 0x3F) | 0x40; // 2nd 6 bits bit7 - bit12

            // *buff++ = byte_two;
            *buff++ = byte_one;
            

        }

        // transmit adc signals after sampling
        adc_trnsmt_sgnl(ptr);
    }
}


void adc_trnsmt_sgnl(char * buff){
    for(int x=0; x<64; x++){
        usart_write(*buff++);
    }
}
