/*
 * gpio.h
 *
 *  Created on: Nov 16, 2023
 *      Author: ebenezer
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "base.h"

#define RCC_IOPENR_OFFSET       (0x34UL)
#define RCC_IOPENR              (*(volatile unsigned int *)(RCC_PERIPHERAL + RCC_IOPENR_OFFSET))

#define GPIOA_MODER_OFFSET      (0x0000UL)
#define GPIOA_MODER             (*(volatile unsigned int *)(GPIOA_PERIPHERAL + GPIOA_MODER_OFFSET))

#define GPIOA_ODR_OFFSET        (0x14UL)
#define GPIOA_ODR               (*(volatile unsigned int *)(GPIOA_PERIPHERAL + GPIOA_ODR_OFFSET))

#define GPIOA_IDR_OFFSET        (0x10UL)
#define GPIOA_IDR               (*(volatile unsigned int *)(GPIOA_PERIPHERAL + GPIOA_IDR_OFFSET))

#define GPIOA_AFRL_OFFSET       (0x20)
#define GPIOA_AFRL              (*(volatile unsigned int *)(GPIOA_PERIPHERAL + GPIOA_AFRL_OFFSET))


#define GPIOB_MODER_OFF         (0x0000UL)
#define GPIOB_MODER             (*(volatile unsigned int *)(GPIOB_PERIPHERAL + GPIOB_MODER_OFF))

#define GPIOB_ODR_OFFSET        (0x14UL)
#define GPIOB_ODR               (*(volatile unsigned int *)(GPIOB_PERIPHERAL + GPIOB_ODR_OFFSET))


#define GPIOC_MODER_OFFSET      (0x0000UL)
#define GPIOC_MODER             (*(volatile unsigned int *)(GPIOC_PERIPHERAL + GPIOC_MODER_OFFSET))

#define GPIOC_IDR_OFFSET        (0x10)
#define GPIOC_IDR               (*(volatile unsigned int *)(GPIOC_PERIPHERAL + GPIOC_IDR_OFFSET))


/*function prototypes*/
void gpio_init(void);
void red_led_on(void);
void red_led_off(void);
void blue_led_on(void);
void blue_led_off(void);
bool btn_input_prsd(void);
void user_led_toggle(void);
void prgrm_state_set(int * prgrm_state);
void prgrm_state_dsply(int * prgrm_state);


#endif /* GPIO_H_ */
