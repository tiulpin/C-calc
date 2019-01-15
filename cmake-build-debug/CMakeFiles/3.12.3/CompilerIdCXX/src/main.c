/*
 * The traffic light project
 * Copyright [2018] [George Chernyshov and Viktor Tiulpin]
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://pevas.club/CHTI
 *
 * 1 tab == 4 spaces!
 */
 
 /*
* This file contains code, which implements manual/automatic traffic light using resources of FreeRTOS. 
* It is not intended to be a user friendly demonstration of the event groups API or any other FreeRTOS feature.
*/

#include "../inc/includes.h"

/*
 * Function used to prepare our STM32F10x board for work. It initializes the required devices: 
 * enables clocking for GPIO ports A, B, C and for TIM3 timer, sets this peripheral devices to the mode
 * which will be needed
 */
void vFreeRTOSInitAll(){
	RCC->APB2ENR |= 1;
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPAEN |  RCC_APB2ENR_IOPBEN; /* enable clocking of GPIOA, GPIOC, GPIOB (according to STM32F10x Reference Manual) */
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; /* enabling clocking of TIM3 (according to STM32F10x Reference Manual)*/
	
	/* Setting the Period value of timer (according to STM32F10x Reference Manual) */
	TIM3->ARR = 0xC34F;
  /* Setting the Prescaler value of timer (according to STM32F10x Reference Manual) */
	TIM3->PSC = 0x383F ;
  /* Generating an update event to reload the Prescaler and the Repetition counter
  values immediately (according to STM32F10x Reference Manual) */
  TIM3->EGR = 0x0000;
	TIM3->SR = 0x0001;
  TIM3->DIER = 0x0001;
	
	/* Setting GPIO ports to desired mode using control registers (according to STM32F10x Reference Manual) */
	GPIOA->CRH = 0x44433333; /* A0-A7 = Push-pull */
	GPIOA->CRL = 0x33344444; /* A0-A7 = Push-pull */
	GPIOC->CRL = 0x44445553; /* C0    = Output Push-pull */
	/* Setting GPIO port B pins to input with pull-up (according to STM32F10x Reference Manual) */
	GPIOB->CRL &= 0xffff0000;
	GPIOB->CRL |= 0x00008888; 
	GPIOB->ODR |= 0xf; //
	
	/* Choosing source of external interrupt for EXTI0, EXTI1, EXTI2 (according to STM32F10x Reference Manual) */
	AFIO->EXTICR[0] |=  0x111;	
	/* Allowing interrupts for first three lines (according to STM32F10x Reference Manual) */
	EXTI->IMR |= 7;
	// up front interrupt (according to STM32F10x Reference Manual)
	EXTI->RTSR |= 7;
	
	/* Adding interrupt handlers to Nested Vector Interrupt Controller (according to STM32F10x Reference Manual) */
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(TIM3_IRQn);
}

/*
 * Function used to make sounds for each change of the state of our traffic light. Uses Event Group feature.
 */
void vSoundTask (void *pvParameters){
	while(pdTRUE) {
		/* Waiting for the signal bits from ledtasks */
		xEventGroupWaitBits(xEventHandler, soundbit,
                        pdTRUE,
                        pdTRUE,
                        portMAX_DELAY);
		int iL = 10000;
		int iH = 1000;
		int iC=iH;
    while (iL>0) {
      iL--;
      iC--;
      if (iC == 0) {
        GPIOC->ODR  ^= 1;
        iC=iH;
      }
    }
	}
}


/*
 * Function used to automatically change the state of our traffic light. Uses Event Group feature.
 */
void vAutoLedTask (void *pvParameters){
	while(pdTRUE) {
		/* check is autobit enabled;  */
		uint32_t result = xEventGroupWaitBits(xEventHandler, autobit,
		                    pdFALSE,  //not clearing (works always in one call)
		                    pdTRUE,   //wait for all bits, not any bit(doesnt matter here)
		                    portMAX_DELAY); //wait indefinitely
		/* if not config mode */
		if(!(result & keypadbit)) {
			if (!Arr[counter])
				counter = 0;
		  GPIOA->ODR  = OFF;
		  GPIOA->ODR  ^= Arr[counter++];
			/* set signal bits for the sound */
		  xEventGroupSetBits(xEventHandler, soundbit);
		  vTaskDelay(100);
		} else
				xEventGroupClearBits(xEventHandler, autobit); //clear bits for not wasting resources
	}	
}

void vManualLedTask (void *pvParameters){
	while(pdTRUE) {
		/* check if manualbit enabled */
		uint32_t result = xEventGroupWaitBits(xEventHandler, manualbit,
		                    pdTRUE,  //clearing after waiting (works once in one call)
		                    pdTRUE,
		                    portMAX_DELAY);
    /* if not config mode */
		if(!(result & keypadbit)) {
			if (!Arr[counter])
				counter = 0;
			GPIOA->ODR  = OFF;
			GPIOA->ODR  ^= Arr[counter++];
			xEventGroupSetBits(xEventHandler, soundbit);
			vTaskDelay(150);
		}
	}	
}

//TODO: semaphor; keyboard using event groups; 
void vKeypadTask (void *pvParameters){	
	while(pdTRUE){
		xEventGroupWaitBits(xEventHandler, keypadbit,
                        pdFALSE, //not clearing (works always in one call)
                        pdTRUE,
                        portMAX_DELAY);
		GPIOC->ODR = COL_1;
    vTaskDelay(10);
		GPIOA->ODR  = OFF;
		GPIOA->ODR  ^= Arr[counter];	//set the lights to a state that is being modified	
		/* To return */ 
    if(!(GPIOB->IDR & ROW_1)) {
			EXTI->PR |= 0x01;
			xEventGroupClearBits(xEventHandler, keypadbit); //reset config mode
			xEventGroupSetBits(xEventHandler, autobit); //enables auto mode
			vTaskDelay(250); //delay is needed to escape multiple reactions to one button press
			counter = 0;
		}
		/* To start the next state */
    if(!(GPIOB->IDR & ROW_4)) {
		  counter++;
			GPIOA->ODR  = OFF; GPIOA->ODR  ^= Arr[counter];
			vTaskDelay(150);
		} 
               
    GPIOC->ODR = COL_2;
    vTaskDelay(10);
		
		
		/* Setting the state via other buttons */
    if(!(GPIOB->IDR & ROW_1)) {
		  Arr[counter] ^= LR; // on/off the LED
			GPIOA->ODR  = OFF; GPIOA->ODR  ^= Arr[counter];
			vTaskDelay(150);
		}
    if(!(GPIOB->IDR & ROW_2)) {
		  Arr[counter] ^= LY; // on/off the LED
			GPIOA->ODR  = OFF; GPIOA->ODR  ^= Arr[counter];
			vTaskDelay(150);
		}
    if(!(GPIOB->IDR & ROW_3)) {
		  Arr[counter] ^= LG; // on/off the LED
			GPIOA->ODR  = OFF; GPIOA->ODR  ^= Arr[counter];
			vTaskDelay(150);
		}  
    if(!(GPIOB->IDR & ROW_4)) {
		  Arr[counter] ^= LLG; // on/off the LED
			GPIOA->ODR  = OFF; GPIOA->ODR  ^= Arr[counter];
			vTaskDelay(150);
		}
    				    
		GPIOC->ODR = COL_3;
    vTaskDelay(10);
			
    if(!(GPIOB->IDR & ROW_1)) {
		  Arr[counter] ^= RR; // on/off the LED
			GPIOA->ODR  = OFF; GPIOA->ODR  ^= Arr[counter];
			vTaskDelay(150);
		}
    if(!(GPIOB->IDR & ROW_2)) {
		  Arr[counter] ^= RY; // on/off the LED
			GPIOA->ODR  = OFF; GPIOA->ODR  ^= Arr[counter];
			vTaskDelay(150);
		}
    if(!(GPIOB->IDR & ROW_3)) {
		  Arr[counter] ^= RG; // on/off the LED
			GPIOA->ODR  = OFF; GPIOA->ODR  ^= Arr[counter];
			vTaskDelay(150);
		}  
    if(!(GPIOB->IDR & ROW_4)) {
		  Arr[counter] ^= RRG; // on/off the LED
			GPIOA->ODR  = OFF; GPIOA->ODR  ^= Arr[counter];
			vTaskDelay(150);
		}
	}
}

int main(void) {
		vFreeRTOSInitAll();
	  xEventHandler = xEventGroupCreate();
		xEventGroupSetBits(xEventHandler, autobit); //default mode is auto
    /* creating tasks */
		xTaskCreate(vAutoLedTask, "AutoLedTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 3, &xAutoLedHandle);
	  xTaskCreate(vManualLedTask, "ManualLedTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, &xManualLedHandle);
		xTaskCreate(vSoundTask, "SoundTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, &xSoundHandle);
		xTaskCreate(vKeypadTask, "KeypadTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &xKeypadHandle);
    vTaskStartScheduler();
}
/* A button to enable manual mode */
void EXTI0_IRQHandler(void){
	EXTI->PR |= 0x01;
  /* check the mode */
	uint32_t result = xEventGroupGetBits(xEventHandler);
	xEventGroupClearBits(xEventHandler, modebits);
  /* if automode, turn off the timer */
	if(result & autobit){
		TIM3->CNT = 0x0000;
		TIM3->CR1 = 0x0001;	
	} else {
    /* reload the timer */
  	xEventGroupSetBits(xEventHandler, autobit);
    TIM3->CR1 = 0x0000;
	}
}

/* A button to switch lights manually */
void EXTI1_IRQHandler(void){
	EXTI->PR |= 0x01;
  TIM3->CNT = 0x0000; //reload the timer
	xEventGroupSetBits(xEventHandler, manualbit); //allow one state change
}

/* A button to set new combination */
void EXTI2_IRQHandler(void){
	EXTI->PR |= 0x01;
  xEventGroupClearBits(xEventHandler, allbits); //prohibit both modes
	xEventGroupSetBits(xEventHandler, keypadbit); //start config mode
	counter = 0;
}

/* Automatic set to auto mode if lights weren't switched for too long */
void TIM3_IRQHandler(void){
	TIM3->SR = 0x0000;
	xEventGroupSetBits(xEventHandler, autobit); //set the auto mode
}
