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
#include "stm32f4xx_it.h"



void ToggleLED4_callback(TimerHandle_t xTimer);
void ToggleLED5_callback(TimerHandle_t xTimer);
void ToggleLeds(void *pvParameters);


int main(void)
{
	SystemInit();
	SysTick_Handler();

	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);

	xTaskCreate(
		ToggleLeds,
		"Toggle",
		configMINIMAL_STACK_SIZE,
		NULL,
		tskIDLE_PRIORITY + 2,
		NULL);

	vTaskStartScheduler();

	for(;;);
}

void ToggleLeds(void *pvParameters)
{
	xTimerHandle timer1, timer2;

	timer1 = xTimerCreate("Timer1",
			500/portTICK_PERIOD_MS,
			pdTRUE, NULL, ToggleLED4_callback);

	timer2 = xTimerCreate("Timer2",
			1000/portTICK_PERIOD_MS,
			pdTRUE, NULL, ToggleLED5_callback);

	xTimerStart(timer1, 0);
	xTimerStart(timer2, 0);

	while(1)
	{

	}

}
void ToggleLED4_callback(TimerHandle_t xTimer)
{
	BSP_LED_Toggle(LED4);
}

void ToggleLED5_callback(TimerHandle_t xTimer)
{
	BSP_LED_Toggle(LED5);
}

