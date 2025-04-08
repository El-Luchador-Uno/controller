#include <stdbool.h>
#include <stddef.h>

#ifndef GPIO_H
#define GPIO_H

typedef struct {
    int pin_number;
    bool is_on;
} StandardGpioConfig;

int initialize_wiring_pi();
void manage_pwm_gpio(int pin_number, int duty_cycle);
void manage_standard_gpio(StandardGpioConfig configs[], size_t count);

#endif