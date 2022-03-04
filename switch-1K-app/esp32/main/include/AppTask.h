#ifndef APP_TASK_H
#define APP_TASK_H

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

QueueHandle_t Key_Queue;
BaseType_t    err;

const esp_timer_create_args_t zero_check_oneshot_timer_args = { .callback = &zero_check_oneshot_timer_callback,
                                                                .name = "zero_check_oneshot_timer" };
esp_timer_handle_t zero_check_oneshot_timer=nullptr;

/*--------------------------------------------------
                   引脚定义  --1K                  
        功能            引脚          有效位         
        背光灯           0              H           
        过零             1              L           
        网络指示灯       10              L             
        KEY2            9              L           
        OUT2            7              H           
 ---------------------------------------------------*/

#define GPIO_OUTPUT_IO_0      (0)
#define GPIO_OUTPUT_IO_1      (5)
#define GPIO_OUTPUT_IO_2      (7)
#define GPIO_OUTPUT_IO_3      (3)
#define GPIO_OUTPUT_IO_4      (20)
#define GPIO_OUTPUT_IO_NET    (10)

#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_OUTPUT_IO_0) | (1ULL<<GPIO_OUTPUT_IO_1) | 
                              (1ULL<<GPIO_OUTPUT_IO_2) | (1ULL<<GPIO_OUTPUT_IO_3) | 
                              (1ULL<<GPIO_OUTPUT_IO_NET)|(1ULL<<GPIO_OUTPUT_IO_4))

#define GPIO_INPUT_IO_1       (4)
#define GPIO_INPUT_IO_2       (6)
#define GPIO_INPUT_IO_3       (9)
#define GPIO_INPUT_IO_4       (21)
#define GPIO_INPUT_PIN_SEL   ((1ULL<<GPIO_INPUT_IO_1)  | (1ULL<<GPIO_INPUT_IO_2)   | 
                              (1ULL<<GPIO_INPUT_IO_3)  | (1ULL<<GPIO_INPUT_IO_4))

#define SWITCH_NUMBERS CONFIG_SWITCH_NUMBERS
#define ACTUATOR_MOVEMENT_PERIOS_MS 2000

class AppTask
{
public:
    void StartServer();
    void Gpio_Input_Init();
    void Gpio_Output_Init();
    void Key_Zero_Check();
    void Key_Scan_Loop();

    uint8_t key;
    uint8_t count_num[4];
    uint8_t count_num_end[4];
    uint8_t count_flag[4];

};

#endif