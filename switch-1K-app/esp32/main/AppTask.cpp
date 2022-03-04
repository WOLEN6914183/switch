#include "AppTask.h"

static void Key_Check_Task(void *pvParameters);
static void Key_Callback_Task(void *pvParameters);

/**
 * @brief Key_Scan_Lopp
 * 
 */

void AppTask::Key_Scan_Loop(gpio_num_t gpio_num)
{
    
}
/**
 * @brief Key_Check_Task
 * 
 */
static void Key_Check_Task(void *pvParameters)
{ 
   static TickType_t key_tick_waken   =   xTaskGetTickCount();
   const  TickType_t xTimer_key       =   pdMs_TO_TICKS(100);
   xQueueSend(Key_Queue,&key,5);

   while(1)
   {
       vTaskDelayUntil(&key_tick_waken,xTimer_key)
       for(int i =0 ;i<CONFIG_SWITCH_NUMBERS;i++)
        {
            Key_Scan_Loop(i);
        }

   }
}

static void Key_Callback_Task(void *pvParameters)
{
   xQueueReceive(Key_Queue,&key,5);
}
/**
 * @brief StartServer
 * 
 */
void AppTask::StartServer()
{
    xTaskCreat(Key_Check_Task,"Key_Check_Task",2048,NULL,4,NULL);
    xTaskCreat(Key_Callback_Task,"Key_Callback_Task",2048,3,NULL);

    Key_Queue=xQueueCreat(5,sizeof(uint8_t));
}

/**
 * @brief 
 * 
 */
void AppTask::Gpio_Input_Init()
{
    gpio_config_t gpio_conf = {};

    gpio_conf.intr_type     =   GPIO_INTR_DISABLE;
    gpio_conf.mode          =   GPIO_MODE_INPUT;
    gpio_conf.pin_bit_mask  =   GPIO_INPUT_PIN_SEL;
    gpio_conf.pull_down_en  =   0;
    gpio_conf.pull_up       =   0;
    gpio_config(&gpio_conf);
}

/**
 * @brief Gpio_Output_Init
 * 
 */
void AppTask::Gpio_Output_Init()
{

}

/**
 * @brief Key_Zero_Check
 * 
 */
void AppTask::Key_Zero_Check()
{
    ESP_ERROR_CHECK(esp_timer_create(&zero_check_oneshot_timer_args, &zero_check_oneshot_timer));
    ESP_ERROR_CHECK(esp_timer_start_once(zero_check_oneshot_timer, 1000000));
}
