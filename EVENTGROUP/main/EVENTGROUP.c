#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

const int SET_GPIO = 2;
gpio_pad_select_gpio(SET_GPIO);
gpio_set_direction(SET_GPIO, GPIO_MODE_OUTPUT);

EventGroupHandle_t evtGrp;

void task1(void *params)
{
    while (true)
    {
        
        gpio_set_level((gpio_num_t)SET_GPIO, 1);

        printf("\n TASK 1- LED 2s \n\n"); 
        vTaskDelay(5000/ portTICK_PERIOD_MS);
    }
}
void task2(void *params)
{
    while (true)
    {
        gpio_set_level((gpio_num_t)SET_GPIO, 0);

        printf("\n TASK 2- LED 1s \n\n"); 
        vTaskDelay(5000/ portTICK_PERIOD_MS);
    }
}

void task3(void *params)
{
    while (true)
    {
        gpio_set_level((gpio_num_t)SET_GPIO, 0);
        
        printf("\n TASK 3- LED 500ms \n\n"); 
        vTaskDelay(5000/ portTICK_PERIOD_MS);
    }
}

void task4(void *params)
{
    while (true)
    {
        gpio_set_level((gpio_num_t)SET_GPIO, 0);
        vTaskDelay(2000/ portTICK_PERIOD_MS);
        printf("\n TASK 4- LED 250ms \n\n"); 
        vTaskDelay(5000/ portTICK_PERIOD_MS);
    }
}



void app_main(void)
{
  evtGrp = xEventGroupCreate();
  xTaskCreate(&task1, "LED 1", 2048, NULL, configMAX_PRIORITIES-1, NULL);
  xTaskCreate(&task2, "LED 2", 2048, NULL, configMAX_PRIORITIES-1, NULL);
  xTaskCreate(&task3, "LED 3", 2048, NULL, configMAX_PRIORITIES-1, NULL);
  xTaskCreate(&task4, "LED 4", 2048, NULL, configMAX_PRIORITIES-1, NULL);
}
