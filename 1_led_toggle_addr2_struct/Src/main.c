#define PERIPH_BASE				(0x40000000UL)							/** Address of peripheral **/
#define IOPORTPERIPH_OFFSET		(0x10000000UL)							/** Address offset of IOPORT to peripheral **/
#define IOPORTPERIPH_BASE		(PERIPH_BASE + IOPORTPERIPH_OFFSET)
#define GPIOA_OFFSET			(0x0000UL)								/** Address offset of GPIO port A relative to IOPORT **/
#define GPIOA_BASE				(IOPORTPERIPH_BASE + GPIOA_OFFSET) 		/** Starting address of GPIO port A **/


#define AHBPERIPH_OFFSET 	(0x00020000UL)
#define AHBPERIPH_BASE 		(PERIPH_BASE + AHBPERIPH_OFFSET)			/** Starting Address of AHB bus **/
#define RCC_OFFSET			(0x00001000UL)
#define RCC_BASE			(AHBPERIPH_BASE + RCC_OFFSET)				/** starting Address of RCC clock **/


#define IOPEN_R_OFFSET		(0x34)
//#define RCC_IOPEN_R		(*(volatile unsigned int *)(RCC_BASE + IOPEN_R_OFFSET))


#define GPIOAEN			(1U<<0) 										/** enable GPIO port A **/
#define MODE_R_OFFSET		(0x00UL)									/** gppio mode register **/
#define OD_R_OFFSET		(0x14UL)										/** Output data register **/
//#define GPIOA_OD_R		(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

#define PIN5			(1U<<5)											/** Set pin 5 high **/
#define LED_PIN			PIN5
#define __IO volatile

typedef unsigned int uint32_t;

/**
 * Creating a structure to hold all the gpio registers
 * we use only the MODER and ODR registers
 */
typedef struct {
	__IO uint32_t	MODER;	/*!< GPIO port mode register, 				Address offset:  0x00*/
	__IO uint32_t	OTYPER; /*!< GPIO port output type register, 		Address offset:  0x04*/
	__IO uint32_t	OSPEEDR; /*!< GPIO port output speed register, 		Address offset:  0x08*/
	__IO uint32_t	PUPDR; /*!< GPIO port pull-up/pull-down register, 	Address offset:  0x0C*/
	__IO uint32_t	IDR; /*!< GPIO port input data register, 			Address offset:  0x10*/
	__IO uint32_t	ODR; /*!< GPIO port output data register, 			Address offset:  0x14*/
	__IO uint32_t	BSRR; /*!< GPIO port bit set/reset register, 		Address offset:  0x18*/
	__IO uint32_t	LCKR; /*!< GPIO port configuration lock register, 	Address offset:  0x1C*/
	__IO uint32_t	AFR[2]; /*!< GPIO port alternate function register, Address offset:  0x20-0x24*/
	__IO uint32_t	BRR; /*!< GPIO port bit reset register, 			Address offset:  0x28*/
}GPIOA_TypeDef;


/**
 * Creating a structure for RCC registers
 */
typedef struct {
	__IO uint32_t	CR; /*!< RCC clock control register 											Address offset: 0x00 */
	__IO uint32_t	ICSCR; /*!< RCC Internal clock source calibration register 						Address offset: 0x04 */
	__IO uint32_t	CFGR; /*!< RCC Clock configuration clock configuration register					Address offset: 0x08 */
	__IO uint32_t	PLLCFGR; /*!< RCC PLL configuration  register 									Address offset: 0x0C */
	__IO uint32_t 	RESERVED; /*!< RCC Reserved register 											Address offset: 0x10 */
	__IO uint32_t	CRRCR; /*!< RCC clock recovery RC  register 									Address offset: 0x14 */
	__IO uint32_t	CIER; /*!< RCC Clock interrupt enable  register 								Address offset: 0x18 */
	__IO uint32_t	CIFR; /*!< RCC Clock interrupt flag register 									Address offset: 0x1C */
	__IO uint32_t	CICR; /*!< RCC Clock interrupt clear  register 									Address offset: 0x20 */
	__IO uint32_t	IOPRSTR; /*!< RCC I/O port reset register 										Address offset: 0x24 */
	__IO uint32_t	AHBRSTR; /*!< RCC AHB peripheral reset  register 								Address offset: 0x28 */
	__IO uint32_t	APBRSTR1; /*!< RCC APB peripheral reset  register1 								Address offset: 0x2C */
	__IO uint32_t	APBRSTR2; /*!< RCC APB peripheral reset register 2 								Address offset: 0x30 */
	__IO uint32_t	IOPENR; /*!< RCC  I/O port clock enable register 								Address offset: 0x34 */
	__IO uint32_t	AHBENR; /*!< RCC AHB peripheral clock enable register 							Address offset: 0x38 */
	__IO uint32_t	APBENR1; /*!< RCC APB peripheral clock enable register 1 						Address offset: 0x3C */
	__IO uint32_t	APBENR2; /*!< RCC APB peripheral clock enable register 2 						Address offset: 0x40 */
	__IO uint32_t	IOPSMENR; /*!< RCC I/O port in Sleep mode clock enable  register 				Address offset: 0x44 */
	__IO uint32_t	AHBSMENR; /*!< RCC AHB peripheral clock enable in Sleep/Stop mode  register 	Address offset: 0x48 */
	__IO uint32_t	APBSMENR1; /*!< RCC APB peripheral clock enable in Sleep/Stop mode register 1 	Address offset: 0x4C */
	__IO uint32_t	APBSMENR2; /*!< RCC APB peripheral clock enable in Sleep/Stop mode register 2  	Address offset: 0x50 */
	__IO uint32_t	CCIPR; /*!< RCC Peripherals independent clock configuration  register 			Address offset: 0x54 */
	__IO uint32_t	CCIPR2; /*!< RCC Peripherals independent clock configuration  register 2 		Address offset: 0x58 */
	__IO uint32_t	BDCR; /*!< RCC RTC domain control register Address offset: 0x5C */
	__IO uint32_t	CSR; /*!< RCC Control/status register Address offset: 0x60 */
}RCC_TypeDef;


#define RCC 	((RCC_TypeDef *) RCC_BASE)
#define GPIOA 	((GPIOA_TypeDef *) GPIOA_BASE)


int main(void){
	// This section has info on the GPIOS
	//General-purpose I/Os (GPIO)

	 /** 1. Enable clock access to GPIOA **/
	RCC->IOPENR |=GPIOAEN;


	 /** 2. Set  PA5 as output pin **/
	//from GPIOx_MODER
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	while(1){
		/**4. Experiment 2: toggle PA5 */
//		GPIOA_OD_R ^= LED_PIN;
		GPIOA->ODR ^= LED_PIN;
		for(int i=0; i<100000; i++);
	}

}

