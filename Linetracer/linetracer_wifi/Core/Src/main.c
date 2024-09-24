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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "esp.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
#define ARR_CNT 5
#define CMD_SIZE 50
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;


/* USER CODE BEGIN PV */
bool Lsensor= false,Rsensor= false; //status of Rsensor, Lsensor
uint32_t endTime;
float distance;
uint8_t rx2char;
extern cb_data_t cb_data;
extern volatile unsigned char rx2Flag;
extern volatile char rx2Data[50];
char Linetracer_Mode;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */
char strBuff[MAX_ESP_COMMAND_LEN];
void MX_GPIO_LED_ON(int flag);
void MX_GPIO_LED_OFF(int flag);
void esp_event(char *);
float Measure_Distance(void);
static void go(void);								//go forward
//static void back(void);							//go backward
static void turn_left(void);				//turn left
static void turn_right(void);				//turn right
static void stop(void);							//stop
static void l_mode(void);
static void r_mode(void);
void DHT22_Start(void);
uint8_t DHT22_Check_Response(void);
uint8_t DHT22_Read(void);
void DHT22_Read_Data(float *temperature, float *humidity);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
float temperature = 0.0f;
float humidity = 0.0f;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	int ret = 0;
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
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  ret |= drv_uart_init();
	ret |= drv_esp_init();
	if(ret != 0) Error_Handler();
	printf("Start main() \r\n");
	AiotClient_Init();
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  	if(strstr((char *)cb_data.buf,"+IPD") && cb_data.buf[cb_data.length-1] == '\n')
		{
			//?��?��?���?????????  \r\n+IPD,15:[KSH_LIN]HELLO\n
			strcpy(strBuff,strchr((char *)cb_data.buf,'['));
			memset(cb_data.buf,0x0,sizeof(cb_data.buf));
			cb_data.length = 0;
			printf("wifi\r\n");
			esp_event(strBuff);

		}
		if(rx2Flag)
		{
			printf("recv2 : %s\r\n",rx2Data);
			rx2Flag =0;
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		distance = Measure_Distance();
		if(distance >= 15)
		{
			if(Linetracer_Mode=='L')
			{

				l_mode();
			}
			else if(Linetracer_Mode =='R')
			{
				r_mode();
			}
		}
		else
		{
			stop();
//			DHT22_Read_Data(&temperature, &humidity);
//
//			if (temperature != -1 && humidity != -1)
//			{
//					printf("Temperature: %.1f°C, Humidity: %.1f\r\n", temperature, humidity);
//			}
//			else
//			{
//					printf("Error reading DHT22 data\n");
//			}
//
//							// ?��?��?���???? 2초마?�� 갱신 (DHT22?�� 2초마?���???? ?��?��?���???? ?��?�� ?�� ?��?��)
//							HAL_Delay(2000);
		}
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 83;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 83;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 0xFFFF;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 83;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 10000-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DHT22_GPIO_Port, DHT22_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Trig_Pin|LD2_Pin|IN2_Pin|IN3_Pin
                          |IN4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : DHT22_Pin */
  GPIO_InitStruct.Pin = DHT22_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DHT22_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Trig_Pin LD2_Pin IN2_Pin IN3_Pin
                           IN4_Pin */
  GPIO_InitStruct.Pin = Trig_Pin|LD2_Pin|IN2_Pin|IN3_Pin
                          |IN4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Echo_Pin L_Sensor_Pin */
  GPIO_InitStruct.Pin = Echo_Pin|L_Sensor_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : IN1_Pin */
  GPIO_InitStruct.Pin = IN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(IN1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : R_Sensor_Pin */
  GPIO_InitStruct.Pin = R_Sensor_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(R_Sensor_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void MX_GPIO_LED_ON(int pin)
{
	HAL_GPIO_WritePin(LD2_GPIO_Port, pin, GPIO_PIN_SET);
}
void MX_GPIO_LED_OFF(int pin)
{
	HAL_GPIO_WritePin(LD2_GPIO_Port, pin, GPIO_PIN_RESET);
}
void esp_event(char * recvBuf)
{
  int i=0;
  char * pToken;
  char * pArray[ARR_CNT]={0};
  char sendBuf[MAX_UART_COMMAND_LEN]={0};

	strBuff[strlen(recvBuf)-1] = '\0';	//'\n' cut
  printf("\r\nDebug recv : %s\r\n",recvBuf);

  pToken = strtok(recvBuf,"[@]");
  while(pToken != NULL)
  {
    pArray[i] = pToken;
    if(++i >= ARR_CNT)
      break;
    pToken = strtok(NULL,"[@]");
  }

  if(!strcmp(pArray[1],"DEST"))
  {
  	if(!strcmp(pArray[2],"SUN"))
  	{
  		MX_GPIO_LED_ON(LD2_Pin);
  		Linetracer_Mode = 'L';
  	}
		else if(!strcmp(pArray[2],"HYD"))
		{
			MX_GPIO_LED_OFF(LD2_Pin);
			Linetracer_Mode = 'R';
		}
		sprintf(sendBuf,"[%s]%s@%s\n",pArray[0],pArray[1],pArray[2]);
  }
  else if(!strncmp(pArray[1]," New conn",8))
  {
//	   printf("Debug : %s, %s\r\n",pArray[0],pArray[1]);
     return;
  }
  else if(!strncmp(pArray[1]," Already log",8))
  {
// 	    printf("Debug : %s, %s\r\n",pArray[0],pArray[1]);
			esp_client_conn();
      return;
  }
  else
      return;

  esp_send_data(sendBuf);
  printf("Debug send : %s\r\n",sendBuf);
}

float Measure_Distance(void) {
    // 1. ?��리거 ?? HIGH�???????????????????? 10us ?��?�� ?���????????????????????
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);  // Trig ?? HIGH
    HAL_Delay(10);  // 10us ?��?�� ??�????????????????????
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);  // Trig ?? LOW
    //printf("TEST10\r\n");
    // 2. ?���???????????????????? ?? HIGH ?��?�� ??�????????????????????
    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET);
    __HAL_TIM_SET_COUNTER(&htim2, 0);  // ???���?????????????? 카운?���?????????????? 0?���?????????????? ?��?��
    HAL_TIM_Base_Start(&htim2);        // ???���?????????????? ?��?��
    //printf("TEST11\r\n");
    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET);
    endTime = __HAL_TIM_GET_COUNTER(&htim2);  // ?���???????????????????? ?��?�� 종료 ?���???????????????????? 기록
    HAL_TIM_Base_Stop(&htim2);  // ???���?????????????? ?���??????????????
    //printf("TEST12\r\n");
    distance = (endTime * 0.0343f) / 2;  // 거리 계산 (?��?��?? 343m/s)

    return distance;
}

static void go(void){							//go foward
	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, GPIO_PIN_RESET);

	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,4499);		//right wheel PWM
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,4499); 		//left wheel PWM

}

//static void back(void){
//	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, GPIO_PIN_SET);
//
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,6999);		//right wheel PWM
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,6999); 		//left wheel PWM
//}

static void turn_left(void){ 			//turn left
	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin,  GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, GPIO_PIN_RESET);

	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,7999);	//left wheel PWM
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,7999);
}

static void turn_right(void)				//turn right
{
	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, GPIO_PIN_SET);

	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,7999);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,7999);
}

static void stop(void)							//stop
{
	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, GPIO_PIN_RESET);
}

static void r_mode(void)
{
			if((HAL_GPIO_ReadPin(R_Sensor_GPIO_Port, R_Sensor_Pin))==1) //if Rsensor detect black color
			{
				Rsensor = true;
			}
			else
			{
				Rsensor = false;																					//Sensor detect white color
			}

			if(Rsensor == false )			//R,Lsemsor detect white
			{
				go();
			}
			else
			{
				turn_left();
			}
}

static void l_mode(void)
{
			if((HAL_GPIO_ReadPin(L_Sensor_GPIO_Port, L_Sensor_Pin))==1) //if Lsensor detect black color
			{
				Lsensor = true;
			}
			else
			{
				Lsensor = false;																					//Sensor detect white color
			}
			if(Lsensor == false)			//R,Lsemsor detect white
			{
				go();
			}

			else
			{
				turn_right();
			}
}
void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // ?��?��?? 출력 모드
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);  // GPIO ???�� 출력 모드�???? ?��?��
}

// GPIO�???? ?��?�� 모드�???? ?��?��
void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;  // ?��?�� 모드
    GPIO_InitStruct.Pull = GPIO_NOPULL;  // ???��/???��?�� ?��?�� ?��?��
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);  // GPIO ???�� ?��?�� 모드�???? ?��?��
}

void delay_us(uint16_t us) {
    __HAL_TIM_SET_COUNTER(&htim1, 0);  // ???���??????? 1?�� 카운?���??????? 0?���??????? ?��?��
    while (__HAL_TIM_GET_COUNTER(&htim1) < us);  // �????????��?�� 마이?��로초 ?��?�� ??�???????
}

void DHT22_Start(void) {
		Set_Pin_Output(DHT22_GPIO_Port, DHT22_Pin);  // ???�� 출력 모드�???? ?��?��
    HAL_GPIO_WritePin(DHT22_GPIO_Port, DHT22_Pin, GPIO_PIN_RESET);  // ???�� LOW�??????? ?��?��
    delay_us(18000);  // 18ms ?��?�� ??�???????
    HAL_GPIO_WritePin(DHT22_GPIO_Port, DHT22_Pin, GPIO_PIN_SET);  // ???�� HIGH�??????? ?��?��
    delay_us(30);  // 30us ?��?�� ??�???????
}

uint8_t DHT22_Check_Response(void) {
    uint8_t response = 0;
    Set_Pin_Input(DHT22_GPIO_Port, DHT22_Pin);  // ???�� input 모드�???? ?��?��
    delay_us(40);
    if (!(HAL_GPIO_ReadPin(DHT22_GPIO_Port, DHT22_Pin))) {
        delay_us(80);
        if ((HAL_GPIO_ReadPin(DHT22_GPIO_Port, DHT22_Pin))) response = 1;
        else response = -1;
    }
    while ((HAL_GPIO_ReadPin(DHT22_GPIO_Port, DHT22_Pin)));  // 0?�� ?�� ?��까�? ??�???????
    return response;
}

uint8_t DHT22_Read(void) {
    uint8_t i, j;
    Set_Pin_Input(DHT22_GPIO_Port, DHT22_Pin);  // ???�� 출력 모드�???? ?��?��
    for (j = 0; j < 8; j++) {
        while (!(HAL_GPIO_ReadPin(DHT22_GPIO_Port, DHT22_Pin)));  // 0?�� ?�� ?��까�? ??�???????
        delay_us(40);  // 40us ??�???????
        if (!(HAL_GPIO_ReadPin(DHT22_GPIO_Port, DHT22_Pin))) {
            i &= ~(1 << (7 - j));  // 비트?�� 0
        } else {
            i |= (1 << (7 - j));  // 비트?�� 1
        }
        while ((HAL_GPIO_ReadPin(DHT22_GPIO_Port, DHT22_Pin)));  // 1?�� ?�� ?��까�? ??�???????
    }
    return i;
}


void DHT22_Read_Data(float *temperature, float *humidity) {
    uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;
    uint16_t SUM, RH, TEMP;

    DHT22_Start();
    if (DHT22_Check_Response()) {
        Rh_byte1 = DHT22_Read();
        Rh_byte2 = DHT22_Read();
        Temp_byte1 = DHT22_Read();
        Temp_byte2 = DHT22_Read();
        SUM = DHT22_Read();

        RH = (Rh_byte1 << 8) | Rh_byte2;
        TEMP = (Temp_byte1 << 8) | Temp_byte2;

        *humidity = (float)RH / 10.0;
        *temperature = (float)TEMP / 10.0;
    }
}
/* USER CODE END 4 */

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
