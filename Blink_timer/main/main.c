#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/timers.h"
#include "driver/ledc.h"
//CONSTANTES********************************************************
#define LED 2
//VARIABLES************************************************
uint8_t led_level = 0;
TimerHandle_t Timer;
int timerId = 1;
//INI_FUNCIONES *********************************************************
void blink(uint8_t pin);
void set_timer(uint16_t time);


//FUNCIONES************************************************************

void vTimerCallback(TimerHandle_t pxTimer){
    blink(LED);
    printf("led state: %u \n", led_level);
}

void app_main() {
    //Config inputs and outputs
    gpio_set_direction(LED,GPIO_MODE_OUTPUT);

    set_timer(1000);
    //loop
    //while(1){
        //vTaskDelay(pdMS_TO_TICKS(1000));
        //blink(LED);
        //printf("led state: %u \n", led_level);
    //}
}

void blink(uint8_t pin){
    led_level = !led_level;
    gpio_set_level(pin, led_level);
}

void set_timer(uint16_t time){
    Timer = xTimerCreate("Timer",(pdMS_TO_TICKS(time)),pdTRUE,(void *)timerId, vTimerCallback);

    if (Timer == NULL)
    {
        printf("No se creo \n");
    }
    else
    {
        if (xTimerStart(Timer, 0) != pdPASS)
        {
            printf("No se activo \n");
        }
        
    }
}
