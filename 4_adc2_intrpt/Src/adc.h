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

#include "stm32g0xx.h"

int adc_read(void);
void pa0_adc_init(void);
void adc_read_intrpt(int * sensor_value);
void adc_cnvrsn(void);

#endif /* ADC_H_ */
