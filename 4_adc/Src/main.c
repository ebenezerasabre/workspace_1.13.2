
#include <stdint.h>
#include <stdio.h>
#include "adc.h"

int sensor_value;

int main(void)
{
	 pa0_adc_init();

	while(1){
		printf("I'm in\n\r");

		sensor_value = adc_read();
		printf("sensor value: %d\n", sensor_value);
	}

}


