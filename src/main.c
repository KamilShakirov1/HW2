#include "ds18b20.h"
#include "pwm.h"
#include "main.h"
#include "stdint.h"
#include "stdio.h"


void gpioa_init(){
	 RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	 GPIOA->MODER |= GPIO_MODER_MODER1_0;
}
void gptoe_init(){
	RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
}

int main(void)
{
gpioa_init();

gptoe_init();

uint8_t dt[9];

uint16_t raw_temper;

float temp;

pwm_init_tim1();

while(1){
	ConvertT();

	ReadScratchpad(dt);

	raw_temper = ((uint16_t)dt[1]<<8)|dt[0];

	temp = convert_ds18b20(raw_temper);

	pwm_transform(temp);

	}


}
