/*
 * timers.c
 *
 *  Created on: Dec 17, 2023
 *      Author: ebenezer
 */

#include "timers.h"

void tim2_1hz_init(void){

	// enable clock access to tim2
	RCC_APBENR1 |= TIM2_EN;

	// set  prescaler value
	TIM2_PSC	= 1600 -1;	// 16 000 000 / 1 600 = 10 000

	//set auto-reload value
	TIM2_ARR = 10000 - 1;	// 10 000 / 10 000 = 1

	// clear counter
	TIM2_CNT	=	0;

	// enable timer
	TIM2_CR1 |=	CR1_CEN;

}

void tim2_pa5_output_compare(void){
	// enable clock access to tim2
	RCC_APBENR1 |= TIM2_EN;

	// set  prescaler value
	TIM2_PSC	= 1600 -1;	// 16 000 000 / 1 600 = 10 000

	//set auto-reload value
	TIM2_ARR = 10000 - 1;	// 10 000 / 10 000 = 1

	// set ouput compare toggle mode, OCM1
	TIM2_CCMR1 |= (1U<<4);
	TIM2_CCMR1 |= (1U<<5);
	TIM2_CCMR1 &= ~(1U<<6);
	TIM2_CCMR1 &= ~(1U<<16);

	//capture/compare enable register
	// enable tim2 ch1 compare mode
	TIM2_CCER |= CCER_CC1E;

	// set PA5 to alternate function mode

	// clear counter
	TIM2_CNT	=	0;

	// enable timer
	TIM2_CR1 |=	CR1_CEN;

}


void tim2_1hz_delay(void){
	// wait till flag updated
	while(!(TIM2_SR & SR_UIF))
		;

	TIM2_SR &= ~ SR_UIF;

}

// when a particular period elapse an output compare allows to toggle a pin directly
// not sure if other peripherals can be manipulated

/*
 * Check alternate functions of gpio pins
 * Check which pin  is attached to TIMer alternate function
 * We will use timer to toggle LED
 * LED connected to PA5
 * PA5 has AF2 ( TIM2_CH1_ETR ) alternate function
 */



