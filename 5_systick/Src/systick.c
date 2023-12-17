/*
 * systick.c
 *
 *  Created on: Dec 5, 2023
 *      Author: ebenezer
 */

/*
 *  Since the systick is a core peripheral of the cortex M architecture
 *  Information about the systick does not exist in any of the ST
 *  microelectronics documents. If we want the complete information about the systick
 *  we need to take a look at the generic user guide of the Cortex M,
 *  Which is provided by Arm: Search for " cortex-m4 generic user guide"
 */

// symbolic names from systic from cortx_m4_generic_user_guide

#include "systick.h"

#define SYSTICK_LOAD_VAL				16000
#define	CTRL_ENABLE					(1U<<0)
#define CTRL_CLKSRC					(1U<<2)
#define CTRL_COUNTFLAG				(1U<<16)

void systickDelayMS(int n){
	// configure systick

	// Reload with number of clocks per ms
	SYST_RVR = SYSTICK_LOAD_VAL;


	// clear systick current register value
	SYST_CVR = 0;

	// enable systick and select internal clk src
	SYST_CSR = (CTRL_ENABLE | CTRL_CLKSRC);

	for(int i=0; i<n; i++){
		// wait until the countFlag is set
		while(!(SYST_CSR & CTRL_COUNTFLAG))
			;
	}
	SYST_CSR = 0;

}
