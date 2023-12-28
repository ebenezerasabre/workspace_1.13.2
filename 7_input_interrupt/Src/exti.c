/*
 * exti.c
 *
 *  Created on: Dec 19, 2023
 *      Author: ebenezer
 */

// create interrupt when user buton pc13 is pressed

#include "exti.h"

void user_button_exti_init(void){


	// diable global interrupts
//	__disable_irq();
	__disable_irq();

	// enable clock access fro GPIOC
	/*done in adc.c*/

	// set PC13 as input
	/*done in adc.c*/

	// enable clock access to SYSCFG
	// enable clock access to SYSCFG mine is EXTI
	RCC->APBENR2 |= SYSCFGEN; //SYSCFG interrupt line 15 status register

	//	SYSCFG_ITLINE7
	SYSCFG->IT_LINE_SR[7] |= (1U<<9); // EXTI13

	// select PORTC, pin13 for EXTI13, Bits 15:8 EXTIm+1[7:0], set 15:8 t0 2
		/*search for below in ref_m, using EXTIm+1*/
	 	 /*EXTI external interrupt selection register*/
	EXTI_EXTICR4 |= (1U<<9); 	// PC13, 0x02: PC[m+1] pin
//	EXTI->EXTICR[3] |= (1U<<9);


	// Unmask EXTI13
//	EXTI_IMR1 |= IMR13;
	EXTI->IMR1 |= IMR13;

	// select falling edge trigger
//	EXTI_FTSR1 |= FT13;
	EXTI->FTSR1 |= FT13;

	// enable EXT13 line in NVIC (Nested Vector interrupt control)
	NVIC_EnableIRQ(EXTI4_15_IRQn);
//	NVIC_EnableIRQ(40);

	// enable glocal interrupts
//	__enable_irq();
	__enable_irq();

}
