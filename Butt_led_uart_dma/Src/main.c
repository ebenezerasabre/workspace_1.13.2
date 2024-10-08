#include "stm32g0xx.h"
#include <stdint.h>

/*
 * This project will use the state of user button to switch between led and uart
 * Button states:
 * 	state 0: Switch on LED
 * 	state 1: Transmit uart
 * 	State 2: Toggle led
 */


/*
 * Peripherals to address
 * GPIOA
 * USART
 * RCC ( clock )
 * First enable clock access to the peripherals
 */

// user button PC13
// user LED PA5
//usart APB bus


/** Peripherals **/

/*
#define PERIPH_BASE						(0x40000000UL)

#define RCC_OFFSET		 				(0x00021000UL)
#define RCC_BASE						(PERIPH_BASE + RCC_OFFSET)

#define IOPORTPERIPH_OFFSET				(0x10000000UL)
#define IOPORTPERIPH_BASE				(PERIPH_BASE + IOPORTPERIPH_OFFSET)

#define APBPERIPH_OFFSET   				(0x0000UL)
#define APBPERIPH_BASE					(PERIPH_BASE + APBPERIPH_OFFSET)

#define GPIOA_OFFSET					(0x0000UL)
#define GPIOA_BASE						(IOPORTPERIPH_BASE + GPIOA_OFFSET)

#define GPIOC_OFFSET					(0x00000800UL)
#define GPIOC_BASE						(IOPORTPERIPH_BASE + GPIOC_OFFSET)

#define  USART2_OFFSET					(0x00004400UL)
#define  USART2_BASE					(APBPERIPH_BASE + USART2_OFFSET)

*/

/** Registers **/
#define RCC_IOPENR_OFFSET  				(0x34)
#define RCC_IOPENR_R					(*(volatile unsigned int *)(RCC_BASE + RCC_IOPENR_OFFSET))

#define RCC_APBENR1_OFFSET				(0x3C)
#define RCC_APBENR1_R	  				(*(volatile unsigned int *)(RCC_BASE + RCC_APBENR1_OFFSET))

// gpioa registers
#define GPIOA_MODER_OFFSET 				(0x0000UL)
#define GPIOA_MODER_R					(*(volatile unsigned int *)(GPIOA_BASE + GPIOA_MODER_OFFSET))

#define GPIOA_ODR_OFFSET				(0x14)
#define GPIOA_ODR_R						(*(volatile unsigned int *)(GPIOA_BASE + GPIOA_ODR_OFFSET))

#define GPIOA_BSRR_OFFSET				(0x18)
#define GPIOA_BSRR_R					(*(volatile unsigned int *)(GPIOA_BASE + GPIOA_BSRR_OFFSET))

#define GPIOA_AFRL_OFFSET				(0x20UL)
#define GPIOA_AFRL_R					(*(volatile unsigned int *)(GPIOA_BASE + GPIOA_AFRL_OFFSET))

// gpioc registers
#define GPIOC_MODER_OFFSET				(0x0000UL)
#define GPIOC_MODE_R					(*(volatile unsigned int *)(GPIOC_BASE + GPIOC_MODER_OFFSET))

#define GPIOC_IDR_OFFSET				(0x10)
#define GPIOC_IDR_R						(*(volatile unsigned int *)(GPIOC_BASE + GPIOC_IDR_OFFSET))



// usart2 registers

#define USART2_ISR_OFFSET				(0x1C)
#define USART2_ISR_R					(*(volatile unsigned int *)(USART2_BASE + USART2_ISR_OFFSET))

#define USART2_RDR_OFFSET				(0x24)
#define USART2_RDR_R					(*(volatile unsigned int *)(USART2_BASE + USART2_RDR_OFFSET))

#define USART2_TDR_OFFSET				(0x28)
#define USART2_TDR_R					(*(volatile unsigned int *)(USART2_BASE + USART2_TDR_OFFSET))

#define USART2_BRR_OFFSET				(0x0C)
#define USART2_BRR_R					(*(volatile unsigned int *)(USART2_BASE + USART2_BRR_OFFSET))

#define USART2_CR1_OFFSET				(0x0000UL)
#define USART2_CR1_R					(*(volatile unsigned int *)(USART2_BASE + USART2_CR1_OFFSET))

#define USART2_CR3_OFFSET				(0x08UL)
#define USART2_CR3_R					(*(volatile unsigned int *)(USART2_BASE + USART2_CR3_OFFSET))

// DMA registers
// inbuilt



//0x4002 0000 dma1

/** Enables **/
#define GPIOAEN 						(1U<<0)			/*Pin to enable GPIOA*/
#define GPIOCEN 						(1U<<2)			/*Pin to enable GPIOC*/
#define USART2EN						(1U<<17)		/*Pin to enable usart2*/
#define PIN5							(1U<<5)
#define LED_PIN							PIN5			/*User LED attached to PA5*/
#define USER_BUTTON						(1U<<13)		/*Bit to check pin of user button*/
#define USART2_CR1_UE					(1U<<0)			/*Usart enable*/
#define USART2_CR1_TE					(1U<<3)			/*Bit to set usart transfer direction*/
#define USART2_CR1_RE					(1U<<2)   		/*Bit to set uart receiver direction*/
#define USART2_ISR_TXE					(1U<<7)			/*Bit to set usart transfer data registry full or empty*/
#define USART2_ISR_RXE					(1U<<5)         /*Bit to set usart receive data register full or empty*/


/* DMA enables */
#define RCC_DMA1_EN						(1U<<0)
#define DMA_CCRx_EN						(1U<<0)
#define DMA_MINC						(1U<<7)
#define DMA_DIR							(1U<<4)			/*Transfer direction*/
#define DMA_Channel_EN					(1U<<0)			/*Channel enable*/
#define DMA_TCIE						(1U<<1)			/*Transfer complete interrupt*/
//#define DMA_ISR_TCIF6					(1U<<21)		/*transfer complete (TC) flag for channel 6*/
#define DMA1_IFCR_CTCIF6				(1U<<21)		/*transfer complete flag clear for channel 6*/
#define USART2_CR3_DMAT					(1U<<7)         /*DMA enable transmision*/

#define SYS_FREQ						16000000
#define APB1_CLK						SYS_FREQ
#define UART_BAUDRATE 					115200



enum OPTIONS {
	STATE_0,
	STATE_1,
	STATE_2
};


/*Function prototypes*/
void button_state(int * btn_state_cntr);
void usart2_init(void);
void usart2_write(int ch);
static void uart_set_baudrate(uint32_t periph_clk, uint32_t baud_rate);
char usart2_read(void);
void user_led_setup(char key);
void dma1_stream_init(uint32_t src, uint32_t dst, uint32_t len);
static void dma_callback(void);

char key;
int main(void)
{
//	int btn_state_cntr = 0;
	char msg[31] = "Hello from the other side\n\r";

	

	/*Clock configuration*/
	// Enable clock access to GPIOA
	RCC_IOPENR_R |= GPIOAEN;

	// enable clock access to GPIOC
	RCC_IOPENR_R |= GPIOCEN;

	// // enable clock access to usart2
	RCC_APBENR1_R |= USART2EN;


	// configure LED as out put pin
	GPIOA_MODER_R |= (1U<<10);
	GPIOA_MODER_R &= ~(1U<<11);


	/*Configure user_button as input pin*/
	GPIOC_MODE_R &= ~(1U<<26);
	GPIOC_MODE_R &= ~(1U<<27);

	usart2_init();

	dma1_stream_init((uint32_t)msg, (uint32_t)&USART2_TDR_R, 31);


    /* Loop forever */
	for(;;){

//		button_state(&btn_state_cntr);
		// usart2_write('Y');


//		key = usart2_read();
//		user_led_setup(key);
//		// usart2_write(usart2_read());
//		if(key){
//			usart2_write(key);
//		} else {
//			//usart2_write(key);
//		}
		


	}
	
}



void button_state(int * btn_state_cntr){

	if(!(GPIOC_IDR_R & USER_BUTTON)){
			GPIOA_ODR_R ^= PIN5; 
		 for(int x=0; x<100000; x++);	// add delay
	} 
	
}

void usart2_init(void)
{

	// look at alternate function mapping in the datasheet 
	// to know the pin the usart you are using is connected
	
	// eg PA2 usartx AF1

	// configure gpioa2 tx pin moder to alternate function	
	GPIOA_MODER_R &= ~(1U<<4);
	GPIOA_MODER_R |= (1U<<5);

	// set alternate function type to AF1: GPIOA_AFR
	// configure uart 8-11
	GPIOA_AFRL_R |= (1U<<8);
	GPIOA_AFRL_R &= ~(1U<<9);
	GPIOA_AFRL_R &= ~(1U<<10);
	GPIOA_AFRL_R &= ~(1U<<11);


	// configure gpioa3 that pin moder to alternate function	
	GPIOA_MODER_R &= ~(1U<<6);
	GPIOA_MODER_R |= (1U<<7);

	// set alternate function type to AF1: GPIOA_AFR
	// configure uart 8-11
	GPIOA_AFRL_R |= (1U<<12);
	GPIOA_AFRL_R &= ~(1U<<13);
	GPIOA_AFRL_R &= ~(1U<<14);
	GPIOA_AFRL_R &= ~(1U<<15);

	// configure usart2 baudrate
	uart_set_baudrate(APB1_CLK, UART_BAUDRATE);


	// set usart tx 
	USART2_CR1_R |= USART2_CR1_TE;

	//set usart rx
	USART2_CR1_R |= USART2_CR1_RE;

	// enable usart module
	USART2_CR1_R |= USART2_CR1_UE;


}


void usart2_write(int ch){
	// make sure transmit data register is empty
	while(!(USART2_ISR_R & USART2_ISR_TXE));

	// write to transmit data_register
	USART2_TDR_R = (ch & 0xFF);
}

static void uart_set_baudrate(uint32_t periph_clk, uint32_t baud_rate){
	// USARTx->BRR = ((periph_clk + (baud_rate/2U)) / baud_rate);
	USART2_BRR_R |= ((periph_clk + (baud_rate/2U)) / baud_rate);
}

char usart2_read(void){
	while(!(USART2_ISR_R & USART2_ISR_RXE))
		;
	// return USART2_TDR_R & 0xFF;
	return USART2_RDR_R;
}

void user_led_setup(char key){
	if(key == 'y') GPIOA_ODR_R |= LED_PIN;
	else if(key == 'n') GPIOA_ODR_R &= ~LED_PIN;
}


void dma1_stream_init(uint32_t src, uint32_t dst, uint32_t len){
	// enable clock access to DMA
	RCC->AHBENR |= RCC_DMA1_EN;

	// dma channel configuration procedure
	// reference manual pg 282

	// disable dma1 stream(channel)
	// search dma channel registers
	//DMA1_Channel6->CCR &= ~DMA_CCRx_EN;

	// wait until DMA channel 5 is disabled
	while(DMA1_Channel6->CCR & DMA_CCRx_EN)
		;



	// clear all interrupt flags of stream 20-23
	DMA1->IFCR |= (1U<<20);
	DMA1->IFCR |= (1U<<21);
	DMA1->IFCR |= (1U<<22);
	DMA1->IFCR |= (1U<<23);



	// set the destination buffer ( peripheral register address )
	DMA1_Channel6->CPAR = dst;

	// set the source buffer (memory buffer)
	DMA1_Channel6->CMAR = src;

	// set length
	DMA1_Channel6->CNDTR = len;

	// select stream6 channel4
//	DMA1_Channel6->CCR;

	// enable memory increment
	DMA1_Channel6->CCR |= DMA_MINC;

	// configure transfer direction 0:peripheral to memory
	DMA1_Channel6->CCR |= DMA_DIR;

	// enable DMA transfer complete interrupt
	DMA1_Channel6->CCR |= DMA_TCIE;


	// enable direct mode and diasble FIFO
	//DMA1_Channel6->CCR;; // circular mode

	// enable DMA1 channel6
	DMA1_Channel6->CCR |= DMA_CCRx_EN;

	// enable uart2 transmitter DMA, usart_cr3
	//USART2->CR3 |= USART2_CR3_DMAT;
	USART2_CR3_R |= USART2_CR3_DMAT;



	// DMA interrupt enable in nvic
	NVIC_EnableIRQ(DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQn);

}

// bcos we enable DMA transfer complete interrupt
void DMA1_Channel4_5_6_7_DMAMUX_DMA2_Channel1_2_3_4_5_IRQHandler(void){
	// check for transfer complete interrupt
	if(DMA1->ISR & DMA_ISR_TCIF6){
		// clear interrupt flag
		DMA1->IFCR |= DMA1_IFCR_CTCIF6;

		// do something
		dma_callback();

	}
}

static void dma_callback(void){
	// turn on led when transfer is complete
	GPIOA_ODR_R |= LED_PIN;
}


