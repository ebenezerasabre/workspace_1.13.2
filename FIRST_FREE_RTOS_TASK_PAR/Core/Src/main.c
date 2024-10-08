/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "queue.h"
#include <string.h>
#include "task.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* USER CODE BEGIN PV */
//void StartDefaultTask(void *argument);
void vBlueLedControllerTask(void * pvParameters);
void vRedLedControllerTask(void * pvParameters);
void vGreenLedControllerTask(void * pvParameters);

// task priority functions
void vTask1(void * pvParameters);
void vTask2(void * pvParameters);

// queue pointers
void vStringSendingTask(void * pvParameters);
void vStringReceivingTask(void * pcParameters);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void StartDefaultTask(void *argument);

/* USER CODE BEGIN PFP */

typedef uint32_t TaskProfiler;

TaskProfiler BlueTaskProfiler;
TaskProfiler RedTaskProfiler;
TaskProfiler GreenTaskProfiler;
TaskProfiler task1Profiler;
TaskProfiler task2Profiler;

// task handle
TaskHandle_t xTask1Handle = NULL;
TaskHandle_t xTask2Handle = NULL;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// pointers to led pins, passed to task as pvParameters
const uint16_t * red_led_ptr = (uint16_t *) RED_LED_Pin;
const uint16_t * blue_led_ptr = (uint16_t *) BLUE_LED_Pin;
const uint16_t * green_led_ptr = (uint16_t *) LED_GREEN_Pin;

// define an enumerated typed used to identify the source of the data.
typedef enum {
	eSender1,
	eSender2
} DataSource_t;

// define the structure type that will be passed on the queue.
typedef struct {
	uint8_t ucValue;
	DataSource_t eDataSource;
} Data_t;

// declare two variables of type Data_t that will be passed on the queue
static const Data_t xStructsToSend[2] = {
		{100, eSender1}, // used by sender1
		{200, eSender2}, // used by sender2
};

/* using a queue to create a mailbox
 * a mailbox is used to hold data that can be rad by any task
 * The sender overwrites the value in the mailbox
 * The receiver reads the value in the mailbox but does not remove the value from the mailbox
 * a mailbox can hold a fixed size data
 */
typedef struct xExampleStructure {
	TickType_t xTimeStamp;
	uint32_t ulvalue;
} Example_t;

// for mailbox queue
void vUpdateMailBox(uint32_t ulNewValue);
BaseType_t vReadMailbox(Example_t * pxData);



// for queue
void vSenderTask(void * pvParameters);
void vReceiverTask(void * pvParameters);
uint32_t item_not_sent;
uint32_t item1_received;
uint32_t item2_received;
char first_char;




QueueHandle_t xQueue;
QueueHandle_t xPointerQueue;

// a mailbox is a queue so it's handle is tore in a variable of type QueueHandle_t xMailbox
QueueHandle_t xMailbox;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */


  // a queue of size 3
  xQueue = xQueueCreate(3, sizeof(int32_t));

  // queue that can hold a maximum of 5 pointers
  xPointerQueue = xQueueCreate(5, sizeof(char *));

  //create a queue that is going to be used as a mailbox
  // the queue has a length of 1 to be used with the xQueueOverwrite() API function
  xMailbox = xQueueCreate(1, sizeof(Example_t));

  /* USER CODE END 2 */

  /* Init scheduler */
  //osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  //defaultTaskHandle = osThreadN ew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  // create task

  //* Task created for LED profiling
   /* led pins were passed as pvParameters
  xTaskCreate(vBlueLedControllerTask,
		  "Ble Led controller",
		  100,
		  (void *)blue_led_ptr,
		  1,
		  NULL);

  xTaskCreate(vRedLedControllerTask,
		  "Red Led controller",
		  100,
		  (void *)red_led_ptr,
		  1,
		  NULL);

  xTaskCreate(vGreenLedControllerTask,
		  "Green Led controller",
		  1000,
		  NULL,
		  1,
		  NULL);

  */


 // xTaskCreate(vTask1, "Task 1", 100, NULL, 2, &xTask1Handle);
//  xTaskCreate(vTask2, "Task 2", 100, NULL, 1, &xTask2Handle);


  // with queues start schedule if queue is not null
  if(xQueue != NULL){


//	  xTaskCreate(vSenderTask, "Sender 1", 100, (void *) 100, 1, NULL);
//	  xTaskCreate(vSenderTask, "Sender 2", 100, (void *) 200, 1, NULL);
//	  xTaskCreate(vReceiverTask, "Receiver", 100, NULL, 2, NULL);

	  /** sending with queue custom data */
	  xTaskCreate(vSenderTask, "Sender 1", 100, &(xStructsToSend[0]), 2, NULL);
	  xTaskCreate(vSenderTask, "Sender 1", 100, &(xStructsToSend[1]), 2, NULL);
	  xTaskCreate(vReceiverTask, "Receiver", 100, NULL, 1, NULL);



	  // start the scheduler so the created tasks start executing
	  vTaskStartScheduler();
  } else {
	  // the queue couldn't be created
  }


//  vTaskStartScheduler();	// start schedule

  //int ch[3] = {'H','e','l'};
  while (1)
  {

	  //HAL_UART_Transmit(&huart2, (uint8_t *)ch, sizeof(ch), 0xFFFF);
	  //printf("Hello from stm32\n\r");
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
  // enable two gpio pins D1-PC4 and D0-PC5
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, BLUE_LED_Pin|RED_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_GREEN_Pin */
  GPIO_InitStruct.Pin = LED_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LED_GREEN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BLUE_LED_Pin RED_LED_Pin */
  GPIO_InitStruct.Pin = BLUE_LED_Pin|RED_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */

/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
// repurpose printf to transmit uart
int __io_putchar(int ch){
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, sizeof(ch), 0xFFFF);
	return ch;
}




// craete task


void vBlueLedControllerTask(void * pvParameters)
{
	while(1){
		//printf("vBleLedControllerTask blue...\n\r");
		BlueTaskProfiler++;
		//HAL_GPIO_TogglePin(GPIOC, (uint16_t)pvParameters);
		//HAL_Delay(50);
		//HAL_Delay(50);
	}
}


void vRedLedControllerTask(void * pvParameters)
{
	while(1){
		//printf("vRedLedControllerTask Red...\n\r");
		RedTaskProfiler++;
//		HAL_GPIO_TogglePin(GPIOC, RED_LED_Pin);
		//HAL_GPIO_TogglePin(GPIOC, (uint16_t)pvParameters);
		//HAL_Delay(50);
	}
}

void vGreenLedControllerTask(void * pvParameters)
{
	//while(1){
		/*
		//printf("vGreenLedControllerTask Green...\n\r");
		GreenTaskProfiler++;

		//HAL_GPIO_TogglePin(GPIOA, LED_GREEN_Pin);
		HAL_GPIO_TogglePin(GPIOA, (uint16_t) pvParameters);

		HAL_Delay(100);
		*/

	//}

	UBaseType_t uxPriority;
		// this task will run before task 2
		uxPriority = uxTaskPriorityGet(NULL);
		for(;;){
			task1Profiler++;
			//for(int i=0; i<10000; i++);	// do something
			//vTaskPrioritySet(xTask2Handle, ( uxPriority + 1)); // set priority below task2
		}
}

// for queues by copy
/**
  * @brief writing values to queue Function
  * @param None
  * @retval None
  */
void vSenderTask(void * pvParameters){
	int32_t lValueToSend;
	BaseType_t xStatus;
	const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

	lValueToSend = (int32_t) pvParameters;
	for(;;){
		// when sender task has lower priority than receiver task
		// when queue gets one value it is pre-emptied by sender task
		//xStatus = xQueueSendToBack(xQueue, &lValueToSend, 0);

		// when receiver has higher priority than sender task
		// queue will be filled before sending
		xStatus = xQueueSendToBack(xQueue, pvParameters, xTicksToWait);
		if(xStatus != pdPASS){
			// could not complete
		}
	}

}


/**
  * @brief Reading values from queue Function
  * @param None
  * @retval None
  */
void vReceiverTask(void * pvParameters){
	// recieving a single value
	int32_t lReceivedValue;
	BaseType_t xStatus;

	// structure that will hold the values received from the queue
	Data_t xReceivedStructure;
	// max amnt of time task will remain in blocked stated to wait for data
	const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

	for(;;){
		// when receiveer task is of lower priority, it will only run when sender is in blocked state
		// sender will only enter blocked state when queue is full
		// so expect number of items in queue to be equal to queue length
//		if(uxQueueMessagesWaiting(xQueue) != 0){
		if(uxQueueMessagesWaiting(xQueue) != 3){ // queue length define as 3
			// queue should have been empty
		}
		// recevie data from the queue
//		xStatus = xQueueReceive(xQueue, &lReceivedValue, xTicksToWait);
//		xStatus = xQueueReceive(xQueue, &item1_received, xTicksToWait);
		xStatus = xQueueReceive(xQueue, &xReceivedStructure, xTicksToWait);
		if(xStatus == pdPASS){
			// data received successfully from the queue

			if(xReceivedStructure.eDataSource == eSender1){
				// from sender 1
				item1_received++;

			} else {
				// from sender 2
				item2_received++;
			}
		}else {
			// data was not received from the queue
			// even after waiting from 100ms
			item_not_sent++;
		}
	}

}

void vUpdateMailBox(uint32_t ulNewValue){
	Example_t xData;

	// write the new data into the Example_t structure
	xData.ulvalue = ulNewValue;

	// user the rtos tick count as the time stamp stored in the Example_t
	xData.xTimeStamp = xTaskGetTickCount();

	// send the structure to the mailbox
	// overwriting any data that is already in the mailbox
	// newver call xQueueOverwrite function from an interrupt service routine
	xQueueOverwrite(xMailbox, &xData);

}

/*
 * Function to take peek at the element of mailbox queue
 * without removing it
 */
BaseType_t vReadMailbox(Example_t * pxData){
	TickType_t xPreviousTimeStamp;
	BaseType_t xDataUpdated;

	// this function updates an Example_t structure with the latest value
	// received from the mailbox.
	// old record before it gets overwritten
	xPreviousTimeStamp = pxData->xTimeStamp;

	// update the Example_t structure pointed to by pxData with
	// the data contained in the mailbox
	xQueuePeek(xMailbox, pxData, portMAX_DELAY);

	if(pxData->xTimeStamp > xPreviousTimeStamp){
		xDataUpdated = pdTRUE;
	} else {
		xDataUpdated = pdFALSE;
	}

	return xDataUpdated;
}






// The following tasks is for setting priorities
/**
  * @brief changind task priority Function
  * @param None
  * @retval None
  */
void vTask1(void * pvParameters){
	UBaseType_t uxPriority;
	// this task will run before task 2
	uxPriority = uxTaskPriorityGet(NULL);
	for(;;){
		task1Profiler++;
		for(int i=0; i<10000; i++);	// do something
		vTaskPrioritySet(xTask2Handle, ( uxPriority + 1)); // set priority below task2
	}
}

/**
  * @brief changind task priority Function
  * @param None
  * @retval None
  */
void vTask2(void * pvParameters){
	UBaseType_t	uxPriority;


	// task1 will always run before this task
	uxPriority = uxTaskPriorityGet(NULL);

	for(;;){
		task2Profiler++;
		for(int i=0; i<10000; i++); // do something
		if(task2Profiler > 100)
			vTaskDelete(NULL);
		vTaskPrioritySet(NULL, (uxPriority - 2)); //set priority below task1
	}

}


/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
