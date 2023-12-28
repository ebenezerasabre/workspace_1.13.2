/*
 * exti.h
 *
 *  Created on: Dec 19, 2023
 *      Author: ebenezer
 */

#ifndef EXTI_H_
#define EXTI_H_

#include "base.h"
#include "stm32g0xx.h"

#define EXTI_EXTICRx_OFFSET		(0x6C)
#define EXTI_EXTICR4			(*(volatile unsigned int *)(EXTI_BASE + EXTI_EXTICRx_OFFSET))

#define EXTI_IMRI_OFFSET		(0x080)
#define EXTI_IMR1				(*(volatile unsigned int *)(EXTI_BASE + EXTI_IMRI_OFFSET))

#define EXTI_FTSR1_OFFSET		(0x004)
#define EXTI_FTSR1				(*(volatile unsigned int *)(EXTI_BASE + EXTI_FTSR1_OFFSET))

/*
 * Enables
 */
#define IMR13					(1U<<13)
#define FT13					(1U<<13)
#define SYSCFGEN				(1U<<0)
#define LINE13					(1U<<13)


void user_button_exti_init(void);

#endif /* EXTI_H_ */
