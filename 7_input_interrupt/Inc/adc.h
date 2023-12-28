/*
 * adc.h
 *
 *  Created on: Oct 25, 2023
 *      Author: ebenezer
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <stdio.h>


int adc_read(void);
void pa0_adc_init(void);
void adc_cnvrsn(void);
void gpio_init(void);
void led_toggle(void);




#endif /* ADC_H_ */
