# workspace_1.13.2

## stm32 bare metal programming journey
Learning Bare Metal Programming with stm32 nucleo-64 board

In this repository, I document my journey of learning bare metal programming on stm32 nucleo board. 

## 0_led_toggle_addr
In the first project which I named 0_led_toggle_addr, I create addresses and registers from the addresses for the NUCLEO-GOB1RE micro-controller by means of  utilizing the reference manual (RM0444), Datasheet (STM32G0B1xB/xC/xE), user manual (UM2324) and schematic diagram of the NUCLEO-GOB1RE board. I use the address the GPIOA port to toggle the LED_PIN_5.

## 1_led_toggle_addr2_struct
In this project, I organize all the address of registes of a particular peripheral into a struct. I make sure the alignment of each item in the struct corresponds to the offset of that particular register.

## 2_gpio_output
In this project, I change the state of LED(GPIOA5) based on the state of user_button. To do this, I first enable clock access for GPIOA and PC13. Then I use the MODER registers of  GPIOA and GPIOC to set GPIOA and PC13 as output and input respectively. I read the state of Input_data_register of GPIOC(USER_BUTTON) and then write to the output_data_register of GPIOA(LED) to change the state of LED.
