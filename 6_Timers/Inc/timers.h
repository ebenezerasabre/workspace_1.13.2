/*
 * timers.h
 *
 *  Created on: Dec 17, 2023
 *      Author: ebenezer
 */

#ifndef TIMERS_H_
#define TIMERS_H_


#include "base.h"

#define RCC_APBENR1_OFFSET		(0x3C)
#define RCC_APBENR1				(*(volatile unsigned int *)(RCC_BASE + RCC_APBENR1_OFFSET))



#define TIM2_CR1_OFFSET			(0x0000UL)
#define TIM2_CR1				(*(volatile unsigned int *)(TIMER2_BASE + TIM2_CR1_OFFSET))

#define TIM2_SR_OFFSET			(0x10)
#define TIM2_SR					(*(volatile unsigned int *)(TIMER2_BASE + TIM2_SR_OFFSET))

#define TIM2_CNT_OFFSET			(0x24)
#define TIM2_CNT				(*(volatile unsigned int *)(TIMER2_BASE + TIM2_CNT_OFFSET))

#define TIM2_PSC_OFFSET			(0x28)
#define TIM2_PSC				(*(volatile unsigned int *)(TIMER2_BASE +TIM2_PSC_OFFSET))

#define TIM2_ARR_OFFSET			(0x2C)
#define TIM2_ARR				(*(volatile unsigned int *)(TIMER2_BASE + TIM2_ARR_OFFSET))


#define TIM2_CCMR1_OFFSET		(0x18UL)
#define TIM2_CCMR1				(*(volatile unsigned int *)(TIMER2_BASE + TIM2_CCMR1_OFFSET))

//TIMx capture/compare enable register
#define TIM2_CCER_OFFSET		(0x20)
#define TIM2_CCER				(*(volatile unsigned int *)(TIMER2_BASE + TIM2_CCER_OFFSET))


/*Enables*/

#define TIM2_EN					(1U<<0)
#define CR1_CEN					(1U<<0)
#define SR_UIF					(1U<<0)
#define CCER_CC1E				(1U<<0)



void tim2_1hz_init(void);
void tim2_1hz_delay(void);
void tim2_pa5_output_compare(void);
#endif /* TIMERS_H_ */


// TIMx control register 1










