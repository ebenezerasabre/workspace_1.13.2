/*
 * base.h
 *
 *  Created on: Nov 16, 2023
 *      Author: ebenezer
 */

/**
 * Task:
 * Base address of peripherals
 * It will also contain registers of all peripherals
*/

#ifndef BASE_H_
#define BASE_H_

#include <stdbool.h>


#define PERIPHERAL_BASE                 (0x40000000UL)

#define APB_PERIPHERAL_OFFSET           (0x0000UL)
#define APB_PERIPHERAL                  (PERIPHERAL_BASE + APB_PERIPHERAL_OFFSET)   

#define ADC_PERIPHERAL_OFFSET           (0x00012400UL)
#define ADC_PERIPHERAL                  (APB_PERIPHERAL + ADC_PERIPHERAL_OFFSET)

#define USART2_PERIPHERAL_OFFSET        (0x00004400UL)
#define USART2_PERIPHERAL               (APB_PERIPHERAL + USART2_PERIPHERAL_OFFSET)

#define IOPORT_PERIHPHERAL_OFFSET       (0x10000000UL)
#define IOPORT_PERIPHERAL               (PERIPHERAL_BASE + IOPORT_PERIHPHERAL_OFFSET)


#define GPIOA_PERIPHERAL_OFFSET         (0x0000UL)
#define GPIOA_PERIPHERAL                (IOPORT_PERIPHERAL + GPIOA_PERIPHERAL_OFFSET)

#define GPIOB_PERIPHERAL_OFFSET         (0x00000400UL)
#define GPIOB_PERIPHERAL                (IOPORT_PERIPHERAL + GPIOB_PERIPHERAL_OFFSET)

#define GPIOC_PERIPHERAL_OFFSET         (0x00000800UL)
#define GPIOC_PERIPHERAL                (IOPORT_PERIPHERAL + GPIOC_PERIPHERAL_OFFSET)


#define AHB_PERIPHERAL_OFF              (0x00020000UL)
#define AHB_PERIPHERAL                  (PERIPHERAL_BASE + AHB_PERIPHERAL_OFF)

#define RCC_PERIPHERAL_OFFSET           (0x00001000UL)
#define RCC_PERIPHERAL                  (AHB_PERIPHERAL + RCC_PERIPHERAL_OFFSET)


enum State {
    OFF = 48,   //int 48 ascii 0
    ON = 49     //int 49 ascii 1
};


#endif /* BASE_H_ */
