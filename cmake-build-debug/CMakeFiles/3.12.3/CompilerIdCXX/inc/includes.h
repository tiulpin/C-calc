#pragma once
/* Scheduler include files. */
#include "FreeRTOS.h"
#include "event_groups.h"
#include "task.h"
#include "queue.h"

/* STM32F10x include files. */
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

/* LED locations definition for more readable code */
#define LR (1<<12)
#define LY (1<<7)
#define LG (1<<6)
#define RR (1<<11)
#define RY (1<<10)
#define RG (1<<9)
#define RRG (1<<8)
#define LLG (1<<5)
#define OFF 0

/* Keypad buttons rows and columns definition */
#define ROW_1 1
#define ROW_2 2
#define ROW_3 4
#define ROW_4 0x10
#define COL_1 0xC //01101111
#define COL_2 0xA //0101
#define COL_3 0x6 //011

/* Generic bit definitions. */
#define manualbit (1 << 0)
#define autobit (1 << 1)
#define soundbit (1 << 2)
#define keypadbit (1 << 3)
#define modebits (0x3)
#define allbits (0xf)

/* Basic GPIO port structure needed for setting up the device */
GPIO_InitTypeDef port;

/* Handles of our tasks */
TaskHandle_t xAutoLedHandle;
TaskHandle_t xManualLedHandle;
TaskHandle_t xKeypadHandle;
TaskHandle_t xSoundHandle;

/* The event group used by all the task based tests. */
EventGroupHandle_t xEventHandler;

/* The array of LED states */
int Arr[30] = { LR | RG, LY | RY, LG | RR, LY | RY }; 

/* The array iterator */
int counter = 0;
