#include "stm32g0xx.h"
#include <stdint.h>
#include <stdio.h>
#include "adc.h"

#define USART2_EN		(1U<<17)	//rcc_apbenr1 enable usart2 from rcc_apbenr
#define USART1_EN		(1U<<14)	//rcc_apbenr2
#define GPIOA_EN 		(1U<<0)
#define GPIOA_5			(1U<<5)
#define LED_PIN			GPIOA_5

#define SYS_FREQ		16000000
#define APB1_CLK		SYS_FREQ
#define UART_BAUDRATE 	115200

#define CR1_TE			(1U<<3)	 /*Enable usart transmitter USART_CR1*/
#define CR1_RE			(1U<<2)  /*Enable usart receiver USART_CR1*/
#define CR1_UE			(1U<<0)	 /*Enable usart USART_CR1*/
#define ISR_TXE 		(1U<<7)	 /*usart transmit data register, USART_ISR*/

#define ISR_RXNE		(1U<<5)	/*usart recieve data register, USART_ISR*/

void usart2_tx_init(void);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periph_clk, uint32_t baud_rate);
void usart2_write(int ch);
char usart2_read(void);


/*Retargeting printf
	* We need re-implement putchar function
*/
int __io_putchar(int ch){
	usart2_write(ch);
	return ch;
}


char key; //character received from uart
int count = 0;
int sensor_value; // for adc

int main(void) {

	 pa0_adc_init();



	RCC->IOPENR |= GPIOA_EN;
	// SET GPIOA5 as output pin
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	usart2_tx_init();

	adc_cnvrsn();

    /* Loop forever */
	for(;;){


//		printf("Im in num \n");
//
//		sensor_value = adc_read();
//
//		printf("sensor value: %d\n", sensor_value);

//*
//		 usart2_write('Y');

//*
//		 printf("Hello from stm32gob1....\n\r");

		key = usart2_read();


		///*
		if(key == '1'){
			GPIOA->ODR &= ~LED_PIN; // led off
		} else {
				GPIOA->ODR |= LED_PIN;	// led on
		}
		//*/

//*/

	}
}


void usart2_tx_init(void){
	/* configure uart gpio pins */

	/*Enable clock access to gpioa*/
	RCC->IOPENR |= GPIOA_EN;

	/*Set PA2 mode to alternate function mode */
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);


	/*Set PA3 mode to alternate function mode*/
	GPIOA->MODER &= ~(1U<<6);
	GPIOA->MODER |= (1U<<7);


	/* Set PA2 alternate function type to UART_TX (AF1)*/
	//alternate function mapping in data sheet to get whieh AF at PA2
	//	GPIOx_AFRL	0001: AF1 AFSEL8-11
	GPIOA->AFR[0]  |= (1U<<8);
	GPIOA->AFR[0]  &= ~(1U<<9);
	GPIOA->AFR[0]  &= ~(1U<<10);
	GPIOA->AFR[0]  &= ~(1U<<11);

	/*Set PA3 alternate function type to UART_RX (AF1)*/
	// GPIOx_AFRL	0001: AF1 AFSEL12-15
	GPIOA->AFR[1]  |= (1U<<12);
	GPIOA->AFR[1]  &= ~(1U<<13);
	GPIOA->AFR[1]  &= ~(1U<<14);
	GPIOA->AFR[1]  &= ~(1U<<15);


	// enable clock access to usart2 peripheral
	RCC->APBENR1 |= USART2_EN;

	// configure usart2 baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	//enable usart tx and rx transfer directions
	USART2->CR1 = (CR1_TE | CR1_RE);

	// enable usart module
	USART2->CR1 |= CR1_UE;

}



static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periph_clk, uint32_t baud_rate){
	USARTx->BRR = ((periph_clk + (baud_rate/2U)) / baud_rate);
}

void usart2_write(int ch){
	// make sure transmit data register is empty
	while(!(USART2->ISR & ISR_TXE))
		;

	// write to transmit_data_register
	USART2->TDR = (ch & 0xFF);
}


char usart2_read(void){
	/*Make sure recieve data register is not empty*/
	while(!(USART2->ISR & ISR_RXNE))
		;
	/*Read data*/
	return USART2->RDR;
}






