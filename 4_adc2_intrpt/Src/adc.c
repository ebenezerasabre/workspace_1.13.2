/*
 * adc.c
 *
 *  Created on: Oct 25, 2023
 *      Author: ebenezer
 */

#include "adc.h"

/*
 * NOTICE:
 * ADC_BASE is legacy when using #include "stm32g0xx.h"
 * use ADC1_BASE instead
 */

/*
#define PERIPH_BASE				(0x40000000UL)

#define APBPERIPH_OFFSET		(0x0000UL)
#define APBPERIPH_BASE			(PERIPH_BASE + APBPERIPH_OFFSET)

#define ADC_OFFSET				(0x00012400UL)
#define ADC_BASE 				(APBPERIPH_BASE + ADC_OFFSET)

#define IOPORT_OFFSET   		(0x10000000UL)
#define IOPORT_BASE				(PERIPH_BASE + IOPORT_OFFSET)

#define GPIOA_OFFSET			(0x00000000UL)
#define GPIOA_BASE				(IOPORT_BASE + GPIOA_OFFSET)

#define AHBPERIPH_OFFSET		(0x00020000UL)
#define AHBPERIPH_BASE			(PERIPH_BASE + AHBPERIPH_OFFSET)

#define RCC_OFFSET				(0x00001000UL)
#define RCC_BASE				(AHBPERIPH_BASE + RCC_OFFSET)
*/



/** Registers **/
#define GPIOA_MODER_OFFSET		(0x0000UL)
#define GPIOA_MODER_R			(*(volatile unsigned int *)(GPIOA_BASE + GPIOA_MODER_OFFSET))


#define RCC_IOPENR_OFFSET		(0x34UL)
#define RCC_IOPENR_R			(*(volatile unsigned int *)(RCC_BASE + RCC_IOPENR_OFFSET))


#define RCC_APBENR2_OFFSET		(0x40UL)
#define RCC_APBENR2_R			(*(volatile unsigned int *)(RCC_BASE + RCC_APBENR2_OFFSET))


#define ADC_ISR_OFFSET			(0x00UL)
#define ADC_ISR_R				(*(volatile unsigned int *)(ADC1_BASE + ADC_ISR_OFFSET))

#define ADC_CHSELR_OFFSET 		(0x28UL)
#define ADC_CHSELR_R			(*(volatile unsigned int *)(ADC1_BASE + ADC_CHSELR_OFFSET))

#define ADC_CFGR1_OFFSET		(0x0C)
#define ADC_CFGR1_R				(*(volatile unsigned int *)(ADC1_BASE + ADC_CFGR1_OFFSET))

#define ADC_CFGR2_OFFSET		(0x10)
#define ADC_CFGR2_R				(*(volatile unsigned int *)(ADC1_BASE + ADC_CFGR2_OFFSET))


#define ADC_CR_OFFSET			(0x08)
#define ADC_CR_R				(*(volatile unsigned int *)(ADC1_BASE + ADC_CR_OFFSET))

#define ADC_DR_OFFSET			(0x40)
#define ADC_DR_R				(*(volatile unsigned int *)(ADC1_BASE + ADC_DR_OFFSET))

#define ADC_IER_OFFSET			(0x04)
#define ADC_IER_R				(*(volatile unsigned int *)(ADC1_BASE + ADC_IER_OFFSET))

/**Enables **/
#define ADCEN      		(1U<<20) /*enable clock access to ADC rcc_apbenr2*/
#define GPIOAEN			(1U<<0)

// enables from manual
#define ADC_ADEN		(1U<<0)
#define ADC_ADCAL		(1U<<31)
#define ADC_ADSTART		(1U<<2)
#define ADC_CHSELRMOD	(1U<<21)
#define ADC_CHSEL		(1U<<0)
//#define ADC_ISR_EOC		(1U<<2)
#define ADC_SEQ_LEN		(1U<<0)

#define ADC_EOCIE		(1U<<2)



// find pin adc is connected to: find adc. look for additional functions in table
// Pin assignment and description

//using ADC_IN0, PA0

void pa0_adc_init(void){
	// enable clock access to GPIOA
	RCC_IOPENR_R |= GPIOAEN;

	// set mode of PA0 to analog
	GPIOA_MODER_R |= (1UL<0);
	GPIOA_MODER_R |= (1U<<1);

	// set mode of PA1 to analog
	GPIOA_MODER_R |= (1UL<2);
	GPIOA_MODER_R |= (1U<<3);

	// enable clock access to adc module
	RCC_APBENR2_R 	|= ADCEN;




//	Analog-to-digital converter (ADC)
	/*Following guide*/


	// data resolution
	ADC_CFGR1_R &= ~(1U<<3);
	ADC_CFGR1_R |= (1U<<4);


	// conversion sequence length

//	ADC_CFGR1_R &= ~ADC_CHSELRMOD;  //~(1U<<21); //ADC_CHSELRMOD;

//	ADC_CHSELR_R |= (1U<<0); // CH1 pa0
	ADC_CHSELR_R |= (1U<<1); // CH1 pa1


	//enable end-of-conversion interrupt
	ADC_IER_R |= ADC_EOCIE;

	// enable interrupt in NVIC
	NVIC_EnableIRQ(ADC1_COMP_IRQn);
//	NVIC_EnableIRQ(12);


	//enable adc module
	ADC_CR_R |= ADC_ADEN;

}


int adc_read(void){
	// check if conversion is complete
	while(!(ADC_ISR_R & ADC_ISR_EOC)){}
	return ADC_DR_R;
}

void adc_read_intrpt(int * sensor_value){
	// check if conversion is complete
	if((ADC_ISR_R & ADC_ISR_EOC) != 0)
		*sensor_value = ADC_DR_R;
}


void adc_cnvrsn(void){
	// Continuous conversion mode
	ADC_CFGR1_R |= (1U<<13);

	// conversion sequence start
	ADC_CR_R |= ADC_ADSTART;

}



