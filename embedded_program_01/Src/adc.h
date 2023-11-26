/*
 * adc.h
 *
 *  Created on: Nov 16, 2023
 *      Author: ebenezer
 */

#ifndef ADC_H_
#define ADC_H_

#include "base.h"

#define RCC_APBENR2_OFFSET      (0x40UL)
#define RCC_APBENR2             (*(volatile unsigned int *)(RCC_PERIPHERAL + RCC_APBENR2_OFFSET))

#define ADC_ISR_OFFSET          (0x00UL)
#define ADC_ISR                 (*(volatile unsigned int *)(ADC_PERIPHERAL + ADC_ISR_OFFSET))

#define ADC_CR_OFFSET           (0x08)
#define ADC_CR                  (*(volatile unsigned int *)(ADC_PERIPHERAL + ADC_CR_OFFSET))

#define ADC_CFGR1_OFFSET        (0x0C)
#define ADC_CFGR1               (*(volatile unsigned int *)(ADC_PERIPHERAL + ADC_CFGR1_OFFSET))

#define ADC_CHSELR_OFFSET       (0x28UL)
#define ADC_CHSELR              (*(volatile unsigned int *)(ADC_PERIPHERAL + ADC_CHSELR_OFFSET))

#define ADC_DR_OFFSET           (0x40UL)
#define ADC_DR                  (*(volatile  unsigned int *)(ADC_PERIPHERAL + ADC_DR_OFFSET))


/***Function prototypes***/
void adc_init(void);
void adc_conversion(void);
int adc_read(void);
void adc_smp_sgnl(char * buff, int * prgrm_state);
void adc_trnsmt_sgnl(char * buff);

#endif /* ADC_H_ */
