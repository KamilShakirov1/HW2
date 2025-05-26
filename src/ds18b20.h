#ifndef DS18B20_H_
#define DS18B20_H_

#include "stdint.h"
#include "stm32f3xx.h"

void delay();

void reset_ds18b20();

uint8_t readbit_ds18b20();

uint8_t readbyte_ds18b20();

void writebit_ds18b20 (uint8_t bit);

void writebyte_ds18b20 (uint8_t dt);

void ConvertT();

void ReadScratchpad(uint8_t*);

float convert_ds18b20(uint16_t);





#endif /* DS18B20_H_ */
