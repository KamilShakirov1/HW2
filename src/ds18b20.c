#include "ds18b20.h"

void delay(int t){
	for(int i=0; i < t; i++);
}

void reset_ds18b20() {
	GPIOA->MODER &= ~GPIO_MODER_MODER1;
	GPIOA->MODER |= GPIO_MODER_MODER1_0;
	GPIOA->OTYPER |= GPIO_OTYPER_OT_1;
	GPIOA->ODR &= ~GPIO_ODR_1;
	delay(385);
	GPIOA->MODER &= ~GPIO_MODER_MODER1;
	delay(66);
}

uint8_t readbit_ds18b20() {
	uint8_t bit = 0;
	GPIOA->ODR &= ~GPIO_ODR_1;
	delay(1);
	GPIOB->ODR |= GPIO_ODR_1;
	delay(10);
	bit = (GPIOB->IDR & GPIO_IDR_1 ? 1 : 0);
	delay(45);
	return bit;
}

uint8_t readbyte_ds18b20() {
  uint8_t data = 0;
      for (uint8_t i = 0; i <= 7; i++) {
            data += readbit_ds18b20() << i;
      }
  return data;
}

void writebit_ds18b20 (uint8_t bit) {
	GPIOA->MODER &= ~GPIO_MODER_MODER1;
	GPIOA->MODER |= GPIO_MODER_MODER1_0;
	GPIOA->ODR &= ~GPIO_ODR_1;
	delay(bit ? 1 : 66);
	GPIOA->ODR |= GPIO_ODR_1;
	delay(bit ? 66 : 1);

}

void writebyte_ds18b20 (uint8_t dt) {
	GPIOA->MODER &= ~GPIO_MODER_MODER1;
	GPIOA->MODER |= GPIO_MODER_MODER1_0;
	for (uint8_t i = 0; i < 8; i++) {
	    writebit_ds18b20(dt >> i & 1);
	}
}

void ConvertT() {
	reset_ds18b20();
	writebyte_ds18b20(0xCC);
	writebyte_ds18b20(0x44);
	GPIOA->MODER &= ~GPIO_MODER_MODER1_0;
	delay(800);
}

void ReadScratchpad(uint8_t *Data) {
	reset_ds18b20();
	writebyte_ds18b20(0xCC);
	readbyte_ds18b20(0xBE);
	for (int i = 0; i <= 7; i++) {
		Data[i] = readbyte_ds18b20();
	}
}

float convert_ds18b20(uint16_t dt) {
  float t;
  t = (float) (dt>>4); //отборосим знаковые и дробные биты
  //Прибавим дробную часть
  t += (float)(dt&0x000F) / 16.0f;
  return t;
}
