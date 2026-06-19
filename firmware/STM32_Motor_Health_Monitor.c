
#include "main.h"
#include <stdio.h>

ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart2;

uint32_t current_value;
uint32_t temp_value;
uint32_t vibration_value;

#define CURRENT_THRESHOLD    3000
#define TEMP_THRESHOLD       2800
#define VIB_THRESHOLD        2500

char uart_buffer[100];

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART2_UART_Init(void);

int main(void)
{
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_USART2_UART_Init();

    while (1)
    {
        /* Current Sensor */
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
        current_value = HAL_ADC_GetValue(&hadc1);

        /* Temperature Sensor */
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
        temp_value = HAL_ADC_GetValue(&hadc1);

        /* Vibration Sensor */
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
        vibration_value = HAL_ADC_GetValue(&hadc1);

        uint8_t fault = 0;

        if(current_value > CURRENT_THRESHOLD)
            fault = 1;

        if(temp_value > TEMP_THRESHOLD)
            fault = 1;

        if(vibration_value > VIB_THRESHOLD)
            fault = 1;

        sprintf(uart_buffer,
                "CUR:%lu,TEMP:%lu,VIB:%lu,FAULT:%d\r\n",
                current_value,
                temp_value,
                vibration_value,
                fault);

        HAL_UART_Transmit(&huart2,
                          (uint8_t*)uart_buffer,
                          strlen(uart_buffer),
                          HAL_MAX_DELAY);

        HAL_Delay(1000);
    }
}
