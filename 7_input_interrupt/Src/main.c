
#include <stdint.h>
#include <stdio.h>
#include "adc.h"
#include "systick.h"
#include "timers.h"
#include "base.h"
#include "exti.h"


#define LED			(1U<<5)											/** Set pin 5 high **/


// function prototypes
void gpio_init(void);
static void exti_callback(void);
int num = 0;

int main(void){
	 pa0_adc_init();
	 adc_cnvrsn();
	 gpio_init();
//	 tim2_1hz_init();

//	 tim2_pa5_output_compare();

//	 GPIOA->MODER
//	 GPIOA->MODER

	 num = 7;
	while(1){
		//printf("I'm in\n\r");
//		exti_callback();

	}

}

void EXTI4_15_IRQHandler(void){
	num = 20;
	//check if interrupt is from line 13
	if((EXTI->FPR1 & LINE13) != 0){
		// clear pr flag
		EXTI->FPR1 |= LINE13;

		// do something
		exti_callback();
	}
}

static void exti_callback(void){

//	GPIOA->ODR ^= LED;
//	for(int i=0; i<100000; i++)
		;
}




