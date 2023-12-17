/*
 * gpio.h
 *
 *  Created on: Dec 5, 2023
 *      Author: ebenezer
 */

#ifndef GPIO_H_
#define GPIO_H_


#include "base.h"

#define GPIOA_MODER_OFFSET       (0x00)
#define GPIOA_MODER              (*(volatile unsigned int *)(GPIOA_PERIPHERAL + GPIOA_MODER_OFFSET))

#define GPIOA_ODR_OFFSET         (0x14)
#define GPIOA_ODR                (*(volatile unsigned int *)(GPIOA_PERIPHERAL + GPIOA_ODR_OFFSET))


#define GPIOB_MODER_OFFSET        (0x00)
#define GPIOB_MODER                (*(volatile unsigned int *)(GPIOB_PERIPHERAL + GPIOB_MODER_OFFSET))

#define GPIOB_ODR_OFFSET            (0x14)
#define GPIOB_ODR                   (*(volatile unsigned int *)(GPIOB_PERIPHERAL + GPIOB_ODR_OFFSET))   

#define GPIOC_MODER_OFFSET          (0x00)
#define GPIOC_MODER                 (*(volatile unsigned int *)(GPIOC_PERIPHERAL + GPIOC_MODER_OFFSET))

#define GPIOC_IDR_OFFSET            (0x10)
#define GPIOC_IDR                   (*(volatile unsigned int *)(GPIOC_PERIPHERAL + GPIOC_IDR_OFFSET))

#define RCC_IOPENR_OFFSET           (0x34)
#define RCC_IOPENR                  (*(volatile unsigned int *)(RCC_PERIPHERAL + RCC_IOPENR_OFFSET))


#endif /* GPIO_H_ */
