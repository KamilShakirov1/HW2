#ifndef PWM_H_
#define PWM_H_

#include "stm32f3xx.h"

void pwm_gpio_init();

void pwm_init_tim1(void);
void pwm_transform(float value);
#endif /* PWM_H_ */
