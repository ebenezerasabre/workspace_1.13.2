/*
 * uart.h
 *
 *  Created on: Nov 16, 2023
 *      Author: ebenezer
 */

#ifndef UART_H_
#define UART_H_
#include "base.h"
#include <stdint.h>


#define RCC_APBENR1_OFFSET      (0X3CUL)
#define RCC_APBENR1             (*(volatile unsigned int *)(RCC_PERIPHERAL + RCC_APBENR1_OFFSET))

#define USART2_CR1_OFFSET       (0x00UL)
#define USART2_CR1              (*(volatile unsigned int *)(USART2_PERIPHERAL + USART2_CR1_OFFSET))

#define USART2_BRR_OFFSET       (0x0C)
#define USART2_BRR              (*(volatile unsigned int *)(USART2_PERIPHERAL + USART2_BRR_OFFSET))

#define USART2_ISR_OFFSET       (0x1C)
#define USART2_ISR              (*(volatile unsigned int *)(USART2_PERIPHERAL + USART2_ISR_OFFSET))

#define USART2_RDR_OFFSET       (0x24UL)
#define USART2_RDR              (*(volatile unsigned int *)(USART2_PERIPHERAL + USART2_RDR_OFFSET))

#define USART2_TDR_OFFSET       (0x28UL)
#define USART2_TDR              (*(volatile unsigned int *)(USART2_PERIPHERAL + USART2_TDR_OFFSET))

void usart_init(void);
void usart_write(int ch);
char usart_read(void);
void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);
#endif /* UART_H_ */
