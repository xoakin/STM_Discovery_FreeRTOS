/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "FreeRTOSConfig.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"



void ToggleLED4_task(void * pvParameters);
int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
//	HAL_Init();

	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);

	xTaskCreate(
		ToggleLED4_task,
		"Task1",
		configMINIMAL_STACK_SIZE,
		NULL,
		tskIDLE_PRIORITY + 2,
		NULL);


	vTaskStartScheduler();

	for(;;);
}


void ToggleLED4_task(void * pvParameters)
{
	while(1)
	{
		BSP_LED_Toggle(LED4);
		vTaskDelay(500 / portTICK_PERIOD_MS);
	}
}
