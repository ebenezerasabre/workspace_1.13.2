
#include <stdint.h>
#include <stdio.h>
#include "adc.h"
#include "systick.h"

/**
 * Bring LED to switch on/off with systick
 */



int sensor_value;

// function prototypes
void gpio_init(void);

int main(void)
{
	 //pa0_adc_init();
	 //adc_cnvrsn();
	 gpio_init();


	while(1){
		//printf("I'm in\n\r");

		//sensor_value = adc_read();
		//printf("sensor value: %d\n", sensor_value);

		led_toggle();
		systickDelayMS(1000);
	}

}









