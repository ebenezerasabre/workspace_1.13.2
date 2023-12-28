/*
 * systick.h
 *
 *  Created on: Dec 5, 2023
 *      Author: ebenezer
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_


/*
 * A cortex_m4 peripheral
 * ~/STM32CubeIDE/workspace_1.13.2/chip_headers/CMSIS/Include/core_cm4.h
 * 4 Registers from cortex_m4_generic user_guide "System timer, SysTick"
 * 0xE000E010 SYST_CSR   (Control and Status Register)      CTRL
 * 0xE000E014 SYST_RVR   (SysTick Reload Value Register)	LOAD
 * 0xE000E018 SYST_CVR   (SysTick Current Value Register)	 VAL
 * 0xE000E01C SYST_CALIB (SysTick Calibration Value Register)
 */
#define SYSTICK_BASE			(0xE000E010)

/**
 * cortex m4 registers
 */

#define SYST_CSR_OFFSET			(0x0000)
#define SYST_CSR				(*(volatile unsigned int *)(SYSTICK_BASE + SYST_CSR_OFFSET))

#define SYST_RVR_OFFSET			(0x0004)
#define SYST_RVR				(*(volatile unsigned int *)(SYSTICK_BASE + SYST_RVR_OFFSET))

#define SYST_CVR_OFFSET			(0x0008)
#define SYST_CVR				(*(volatile unsigned int *)(SYSTICK_BASE + SYST_CVR_OFFSET))

#define SYST_CALIB_OFFSET		(0x0012)
#define SYS_CALIB				(*(volatile unsigned int *)(SYSTICK_BASE + SYST_CALIB_OFFSET))

void systickDelayMS(int n);

#endif /* SYSTICK_H_ */
