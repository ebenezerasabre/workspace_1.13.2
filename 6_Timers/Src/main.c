
#include <stdint.h>
#include <stdio.h>
#include "adc.h"
#include "systick.h"
#include "timers.h"
#include "base.h"


/**
 * Bring LED to switch on/off with systick
 */



int sensor_value;

// function prototypes
void gpio_init(void);

int main(void)
{
	 pa0_adc_init();
	 adc_cnvrsn();
	 gpio_init();
//	 tim2_1hz_init();

	 // use timer to control pin output
	 tim2_pa5_output_compare();

	while(1){
		//printf("I'm in\n\r");

		//sensor_value = adc_read();
		//printf("sensor value: %d\n", sensor_value);


//		systickDelayMS(1000);


		// general purpose timer2
//		tim2_1hz_delay();
//		led_toggle();

	}




}





