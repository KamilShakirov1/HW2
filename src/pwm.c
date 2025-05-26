#include "pwm.h"


void pwm_gpio_init() {
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	GPIOE->MODER |= GPIO_MODER_MODER9_1;
	GPIOE->AFR[1] &= ~(0xF << (4 * 3));
	GPIOE->AFR[1] |=  (0x2 << (4 * 3));
}

void init_tim2_as_pwm() {
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;    GPIOA->MODER |= GPIO_MODER_MODER5_1;
    GPIOA->AFR[0] |= (1 << (4 * 5 - 1));
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->ARR = 7999;    TIM2->PSC = 0;
    TIM2->CCMR1 &= ~TIM_CCMR1_CC1S;
    TIM2->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
    TIM2->CCER |= TIM_CCER_CC1E;

    TIM2->CR1 |= TIM_CR1_CEN;
}

void pwm_init_tim1() {
		pwm_gpio_init();

		TIM1->CCMR1 &= ~TIM_CCMR1_CC1S;

		TIM1->CCMR1 &= ~TIM_CCMR1_OC2M;

		TIM1->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;

		TIM1->CCER |= TIM_CCER_CC2E;

		TIM1->BDTR |= TIM_BDTR_MOE;

		TIM1->PSC = 7;

		TIM1->ARR = 999;

		TIM1->CCR2 = 50;

		TIM1->CR1 |= TIM_CR1_CEN;
}

void pwm_transform(float temp){

	TIM1->CCR2 = TIM1->ARR*(temp/40);

	if(temp>40){
		TIM1->CCR2=1000;
	}
	if(temp<10){
			TIM1->CCR2=100;
	}
}
