/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
  ******************************************************************************
    * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "app_threadx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern UART_HandleTypeDef huart1;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#define TX_NO_TIME_SLICE	10
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
TX_THREAD ThreadOne;
TX_THREAD ThreadTwo;
uint8_t task1[]="im in task one lkzslisnlknalksf aslkfnaksnfklasnf  ASDASDASFASFASFASFASF\r\n";
uint8_t task2[]="im in task two  ASJKFALKSFKASFKAFLKANSFLKAN\r\n";
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void ThreadOne_Entry(ULONG thread_input);
void ThreadTwo_Entry(ULONG thread_input);
void App_Delay(uint32_t Delay);
/* USER CODE END PFP */

/**
  * @brief  Application ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT App_ThreadX_Init(VOID *memory_ptr)
{
  UINT ret = TX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

   /* USER CODE BEGIN App_ThreadX_MEM_POOL */
  (void)byte_pool;
  /* USER CODE END App_ThreadX_MEM_POOL */

  /* USER CODE BEGIN App_ThreadX_Init */
  CHAR *pointer1,*pointer2;

  ret = tx_byte_allocate(byte_pool, (VOID **) &pointer1, APP_STACK_SIZE, TX_NO_WAIT);


   /* Allocate the stack for ThreadOne.  */
//   if (tx_byte_allocate(byte_pool, (VOID **) &pointer1,
//                        APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
//   {
//     ret = TX_POOL_ERROR;
//   }

   /* Create ThreadOne.  */
   if (tx_thread_create(&ThreadOne, "Thread One", ThreadOne_Entry, 0,
                        pointer1, APP_STACK_SIZE,
                        THREAD_ONE_PRIO, THREAD_ONE_PREEMPTION_THRESHOLD,
						TX_8_ULONG, TX_AUTO_START) != TX_SUCCESS)
   {
     ret = TX_THREAD_ERROR;
   }

   ret = tx_byte_allocate(byte_pool, (VOID **) &pointer2,APP_STACK_SIZE, TX_NO_WAIT);


   /* Allocate the stack for ThreadTwo.  */
    if (tx_byte_allocate(byte_pool, (VOID **) &pointer2,
                         APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
    {
      ret = TX_POOL_ERROR;
    }

    /* Create ThreadTwo.  */
    if (tx_thread_create(&ThreadTwo, "Thread Two", ThreadTwo_Entry, 0,
                         pointer2, APP_STACK_SIZE,
                         THREAD_TWO_PRIO, THREAD_TWO_PREEMPTION_THRESHOLD,
						 TX_8_ULONG, TX_AUTO_START) != TX_SUCCESS)
    {
      ret = TX_THREAD_ERROR;
    }
  /* USER CODE END App_ThreadX_Init */

  return ret;
}

  /**
  * @brief  MX_ThreadX_Init
  * @param  None
  * @retval None
  */
void MX_ThreadX_Init(void)
{
  /* USER CODE BEGIN  Before_Kernel_Start */

  /* USER CODE END  Before_Kernel_Start */

  tx_kernel_enter();

  /* USER CODE BEGIN  Kernel_Start_Error */

  /* USER CODE END  Kernel_Start_Error */
}

/* USER CODE BEGIN 1 */
void ThreadOne_Entry(ULONG thread_input)
{
 // uint8_t t1_count=0;


  while(1)									/* Infinite loop */
  {
	  //HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_7);	/* Toggle Green LED */
	  HAL_UART_Transmit(&huart1, &task1, 50, 200);
	App_Delay(10);							/* Delay for 100=1000ms */
//	t1_count++;
//	if(20==t1_count)
//	{
//		t1_count = 0;
//		tx_thread_sleep(10);
//	}
  }
}

void ThreadTwo_Entry(ULONG thread_input)
{
  uint8_t t2_count=0;
  while(1)									/* Infinite loop */
  {
//	HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_6);	/* Toggle Green LED */
	HAL_UART_Transmit(&huart1, &task2, 50, 200);
	App_Delay(50);							/* Delay for 100=1000ms */
	//t2_count++;
//		if(6==t2_count)
//		{
//			t2_count = 0;
//			tx_thread_sleep(10);
//		}
 }
}

/**
  * @brief  Application Delay function.
  * @param  Delay : number of ticks to wait
  * @retval None
  */
void App_Delay(uint32_t Delay)
{
  UINT initial_time = tx_time_get();
  while ((tx_time_get() - initial_time) < Delay);
}

/* USER CODE END 1 */
