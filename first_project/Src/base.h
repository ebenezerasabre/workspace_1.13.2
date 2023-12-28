/*
 * base.h
 *
 *  Created on: Dec 4, 2023
 *      Author: ebenezer
 */

#ifndef BASE_H_
#define BASE_H_

#define PERIPHERAL_BASE			            (0x40000000)

#define IOPORT_PERIPHERAL_OFFSET			(0x10000000)
#define IOPORT_PERIPHERAL		            (PERIPHERAL_BASE + IOPORT_OFFSET)

#define APB_PERIPHERAL_OFFSET               (0x0000)
#define APB_PERIPHERAL                      (PERIPHERAL_BASE + APB_PERIPHERAL_OFFSET)

#define AHB_PERIPHERAL_OFFSET               (0x00020000)
#define AHB_PERIPHERAL                      (PERIPHERAL_BASE + AHB_PERIPHERAL_OFFSET)

#define GPIOA_PERIPHERAL_OFFSET             (0x0000)
#define GPIOA_PERIPHERAL                    (IOPORT_PERIPHERAL + GPIOA_PERIPHERAL_OFFSET)

#define GPIOB_PERIPHERAL_OFFSET             (0x0000040)
#define GPIOB_PERIPHERAL                    (IOPORT_PERIPHERAL + GPIOB_PERIPHERAL_OFFSET)

#define GPIOC_PERIPHERAL_OFFSET             (0x00000800)
#define GPIOC_PERIPHERAL                    (IOPORT_PERIPHERAL + GPIOC_PERIPHERAL_OFFSET)

#define ADC_PERIPHERAL_OFFSET               (0x00012400)
#define ADC_PERIPHERAL                      (APB_PERIPHERAL + ADC_PERIPHERAL_OFFSET)

#define USART2_PERIPHERAL_OFFSET            (0x00004400)
#define USART2_PERIPHERAL                   (APB_PERIPHERAL + USART2_PERIPHERAL_OFFSET)

#define RCC_PERIPHERAL_OFFSET               (0x00001000)
#define RCC_PERIPHERAL                      (AHB_PERIPHERAL + RCC_PERIPHERAL_OFFSET)


#endif /* BASE_H_ */









