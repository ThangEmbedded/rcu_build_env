// app_main.c
#include <stdio.h>
#include "main.h"
#include "gpio.h"

void _delay_ms(uint32_t ms) {
    HAL_Delay(ms);
}

int main(void) {
    printf("Hello STM32!\n");
    bsp_init();
    // setup gpio c 8 ouput
    HAL_GPIO_Init(GPIOC, &(GPIO_InitTypeDef){
        .Pin = GPIO_PIN_8,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_LOW
    });
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
    // Giả sử đã có hàm HAL_GPIO_TogglePin và cấu hình GPIOC, pin 8
    while(1) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
        _delay_ms(500);
    }
    return 0;
}
