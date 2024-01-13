
#include <stdint.h>
#include <stdio.h>
#include "adc.h"

int sensor_value;

int main(void)
{
	 pa0_adc_init();
	 adc_cnvrsn();

	while(1){

	}

}


// interrupt methods should contain void
void ADC_COMP_IRQHandler(void){
//	sensor_value = adc_read();
	adc_read_intrpt(&sensor_value);
}
