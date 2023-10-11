// where is the led connected ?
// Port:	A
// Pin:	5

// All registers have to be typecasted to a volatile int pointer
// and the dereference it

//block diagram in datasheet
// memory map in reference manual
#define PERIPH_BASE				(0x40000000UL)
#define IOPORTPERIPH_OFFSET		(0x10000000UL)
#define IOPORTPERIPH_BASE		(PERIPH_BASE + IOPORTPERIPH_OFFSET)
#define GPIOA_OFFSET			(0x0000UL)
#define GPIOA_BASE				(IOPORTPERIPH_BASE + GPIOA_OFFSET)

// The RCC module which is in charge of enabling each bus to transport a clock
// RCC stands for Reset and Clock control
//
#define AHBPERIPH_OFFSET 	(0x00020000UL)
#define AHBPERIPH_BASE 		(PERIPH_BASE + AHBPERIPH_OFFSET)
#define RCC_OFFSET			(0x00001000UL)
#define RCC_BASE			(AHBPERIPH_BASE + RCC_OFFSET)

// The above peripherals contains registers that we need to access
//Next we will locate the addresses of registers we need within these peripherals
// reference manuals tells us about the registers

// Next locate registers of addresses we need within the above peripherals
// Ref man tells us about all the registers
// and the meaning of each and every bit in the registers
#define IOPEN_R_OFFSET		(0x34)
#define RCC_IOPEN_R		(*(volatile unsigned int *)(RCC_BASE + IOPEN_R_OFFSET))

// enable GPIO port A
// 1U<<0 shift 1 to position 0
#define GPIOAEN			(1U<<0) // 0b 0000 0000 0000 0000 0000 0000 0000 0001

// Micro-controllers GPIO ports have at least two registers
// DIRECTION and DATA register: Data reg is used to set pin to either input or output
// DATA register is used to store the data
// Direction register is called different names depending
//on the manufacture of the microcontroller
// in Stm32 it is called mode
// Hence we will use the mode register to configure our GPIO Pin as an output pin
// and use the data register to the data we want to write to a particular pin

/**
 * Search moder in reference manual
 * Found under GPIO registers
 * GPIOA is port A, GPIOA5 PortA pin 5
 * mode0 - mode15 refers to pin in the GPIO port
 */

#define MODE_R_OFFSET		(0x00UL)
#define GPIOA_MODE_R		(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))


/*from GPIOx_MODER
 * setting port PA5 as
 * 01: General purpose output mode
 * (1U<<10) // set bit 10 to 1
 * &=~(1U<<11) // set only bit 11 to zero
 * invert bit 11 and perform an and with current contents of the register
 */


// after configuring pin as output mode we need to write on/off to a particular register
// to turn the led on/off called output register
/*
 * GPIOx_ODR
 * ODR - output register
 * GPIOx_IDR - Input Data Register
 * we are interested in pin 5 of GPIOx_ODR ODS(Pin 5)
 */

#define OD_R_OFFSET		(0x14UL)
#define GPIOA_OD_R		(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

#define PIN5			(1U<<5)	// set 1 at pin5
#define LED_PIN			PIN5


int main(void){
	// This section has info on the GPIOS
	//General-purpose I/Os (GPIO)

	 /** 1. Enable clock access to GPIOA **/
	RCC_IOPEN_R |= GPIOAEN;
	 /** 2. Set  PA5 as output pin **/
	//from GPIOx_MODER
	GPIOA_MODE_R |= (1U<<10); // set bit 10 to 1
	GPIOA_MODE_R &=~(1U<<11); // set bit 11 to 0

	while(1){
		/**3. set PA5 high **/
		// from GPIOx_ODR
		//GPIOA_OD_R |= LED_PIN;

		/**4. Experiment 2: toggle PA5 */
		GPIOA_OD_R ^= LED_PIN;
		for(int i=0; i<100000; i++);
	}

}





