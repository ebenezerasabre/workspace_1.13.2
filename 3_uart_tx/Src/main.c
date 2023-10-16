#include "stm32g0xx.h"
#include <stdint.h>

#define USART2_EN	(1U<<17)
#define GPIOA_EN (1U<<0)

//#define USART2_BASE  0x40004400UL  //- 0x4000 47FF
#define SYS_FREQ	16000000
#define APB1_CLK	SYS_FREQ
#define UART_BAUDRATE 115200
#define CR1_TE	(1U<<3)
#define CR1_UE	(1U<<13)
#define ISR_TXE (1U<<7)

// enable clock access to usart2 peripherial ie rcc_apbenr1 bit for usart2
// usart2 is at bit 17

// get address of uart2 peripheral
// find tx and rx pins usart2 uses from alternate functions of the micro-controller


//	USART2_RX	PA3 AF1
//	USART2_TX	PA2 AF1

void usart2_tx_init(void);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periph_clk, uint32_t baud_rate);
void usart2_write(int ch);



int main(void)
{
	usart2_tx_init();


    /* Loop forever */
	for(;;){
		usart2_write('Y');

	}
}


void usart2_tx_init(void){
	/* configure uart gpio pins */

	/*Enable clock access to gpioa*/
	RCC->IOPENR |= GPIOA_EN;

	/*Set PA2 mode to alternate function mode */
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/* Set PA2 alternate function type to UART_TX (AF1)*/
//	GPIOx_AFRL	0001: AF1
	GPIOA->AFR[0]  |= (1U<<8);
	GPIOA->AFR[0]  &= ~(1U<<9);
	GPIOA->AFR[0]  &= ~(1U<<10);
	GPIOA->AFR[0]  &= ~(1U<<11);


	/** configure usart module **/

	// enable clock access to usart2 peripheral
	RCC->APBENR1 |= USART2_EN;

	// configure usart2 baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	// configure transfer direction
	USART2->CR1 = CR1_TE; // set bit3 to 1 and everything else to 0,gives default usart

	// enable usart module
	USART2->CR1 |= CR1_UE;


}



static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periph_clk, uint32_t baud_rate){
	USARTx->BRR = ((periph_clk + (baud_rate/20))/baud_rate);
}

void usart2_write(int ch){
	// make sure transmit data register is empty
	while(!(USART2->ISR & ISR_TXE))
		;
	// write to transmit_data_register
	USART2->TDR = (ch & 0xFF);



}











