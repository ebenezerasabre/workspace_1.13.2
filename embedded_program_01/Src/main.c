
#include <stdint.h>
#include "gpio.h"
#include "adc.h"
#include "uart.h"
//#include "base.h"

int prgrm_state = OFF;
char adc_buff[64];
int adc_value;

int main(void)
{

    /**Initialize Peripherals**/
    gpio_init();
    adc_init();
    adc_conversion();
    usart_init();


    /* Loop forever */
	for(;;){
	user_led_toggle();
        prgrm_state_set(&prgrm_state);
        prgrm_state_dsply(&prgrm_state);
        adc_smp_sgnl(adc_buff, &prgrm_state);
        adc_value = *adc_buff;
    }
}

