#include "stm32g0xx.h"

#define GPIOAEN	(1U<<0)		// enable port A
#define GPIOCEN	(1U<<2)		// enable port C
#define PIN5	(1U<<5)
#define PIN13	(1U<<13)
#define LED_PIN			PIN5
#define USER_BUTTON 	PIN13

/*Function prototypes*/
static void reset_led(void);
static void read_user_button(void);

int main(void)
{

	// enable clock access for GPIOA
	RCC->IOPENR |= GPIOAEN;

	// enable clock access to PC13
	RCC->IOPENR |= GPIOCEN;

	// set GPIOA5 as output
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	// set GPIOC13 as intput
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);


    /* Loop forever */
	for(;;){

//		reset_led();

//		GPIOA->ODR |= LED_PIN;
		read_user_button();

	}
}


static void reset_led(void){
	//set pin5
	GPIOA->BSRR |= (1U<<5);
	for(int i=0; i < 100000; i++);


	//reset pin5
	GPIOA->BSRR |= (1U<<21);
	for(int i=0; i < 100000; i++);
}

static void read_user_button(void){
	if(GPIOC->IDR &  USER_BUTTON){
		GPIOA->ODR |= LED_PIN;	// Put on LED
	}

}

