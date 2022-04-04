#include <stdio.h>
#include <string.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"


EventGroupHandle_t evtGrp;

const int gottask1 = BIT0;
const int gottask2 = BIT1;
const int gottask3 = BIT2;
const int gottask4 = BIT3;

void task1(void *params)
{
    while (true)
    {
        xEventGroupWaitBits(evtGrp, gottask4, true, true, portMAX_DELAY);
        xEventGroupClearBits(evtGrp, gottask3);
        const int SET_GPIO = 2;
        gpio_pad_select_gpio(SET_GPIO);
        gpio_set_direction(SET_GPIO, GPIO_MODE_OUTPUT);
        int i=0;
        while(i<2)
        {
            printf("\n TASK 1- LED 2s \n\n");
            gpio_set_level((gpio_num_t)SET_GPIO, 1);
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            gpio_set_level((gpio_num_t)SET_GPIO, 0);
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            i= i+ 1;

        }
    xEventGroupSetBits(evtGrp, gottask1);
    
    }
}
void task2(void *params)
{
    while (true)
    {
        xEventGroupWaitBits(evtGrp, gottask1, true, true, portMAX_DELAY);
        xEventGroupClearBits(evtGrp, gottask4);
        const int SET_GPIO = 2;
        gpio_pad_select_gpio(SET_GPIO);
        gpio_set_direction(SET_GPIO, GPIO_MODE_OUTPUT);
        int i=0;
        while(i<5)
        {
            printf("\n TASK 2- LED 1s \n\n");
            gpio_set_level((gpio_num_t)SET_GPIO, 1);
            vTaskDelay(1000/ portTICK_PERIOD_MS);
            gpio_set_level((gpio_num_t)SET_GPIO, 0);
            vTaskDelay(1000/ portTICK_PERIOD_MS);
            i= i+ 2;
        }
        
        xEventGroupSetBits(evtGrp, gottask2);
    }
}

void task3(void *params)
{
    while (true)
    {
        xEventGroupWaitBits(evtGrp, gottask2, true, true, portMAX_DELAY);
        xEventGroupClearBits(evtGrp, gottask1);
        const int SET_GPIO = 2;
        gpio_pad_select_gpio(SET_GPIO);
        gpio_set_direction(SET_GPIO, GPIO_MODE_OUTPUT);
        for(int i=0; i<10; i++)
        {
            printf("\n TASK 3- LED 500ms \n\n");
            gpio_set_level((gpio_num_t)SET_GPIO, 1);
            vTaskDelay(500/ portTICK_PERIOD_MS);
            gpio_set_level((gpio_num_t)SET_GPIO, 0);
            vTaskDelay(500/ portTICK_PERIOD_MS);
        }
        xEventGroupSetBits(evtGrp, gottask3);
    }
}

void task4(void *params)
{
    while (true)
    {
        xEventGroupWaitBits(evtGrp, gottask3, true, true, portMAX_DELAY);
        xEventGroupClearBits(evtGrp, gottask2);
        const int SET_GPIO = 2;
        gpio_pad_select_gpio(SET_GPIO);
        gpio_set_direction(SET_GPIO, GPIO_MODE_OUTPUT);
        for(int i=0; i<20; i++)
        {
            printf("\n TASK 4- LED 250ms \n\n");
            gpio_set_level((gpio_num_t)SET_GPIO, 1);
            vTaskDelay(250/ portTICK_PERIOD_MS);
            gpio_set_level((gpio_num_t)SET_GPIO, 0);
            vTaskDelay(250/ portTICK_PERIOD_MS);
        }
        xEventGroupSetBits(evtGrp, gottask4);
    }
}



void app_main(void)
{

    evtGrp = xEventGroupCreate();
    xTaskCreate(&task1, "LED 1", 2048, NULL, configMAX_PRIORITIES-1, NULL);
    xEventGroupSetBits(evtGrp, gottask4);
    xTaskCreate(&task2, "LED 2", 2048, NULL, configMAX_PRIORITIES-1, NULL);
    xTaskCreate(&task3, "LED 3", 2048, NULL, configMAX_PRIORITIES-1, NULL);
    xTaskCreate(&task4, "LED 4", 2048, NULL, configMAX_PRIORITIES-1, NULL);   

}
