#include <stdbool.h>
#include <stddef.h>

#ifndef GPIO_H
#define GPIO_H

typedef struct {
    int pin_number;
    bool is_on;
} StandardGpioConfig;

typedef struct {
    int left_pwm;
    int right_pwm;
} DutyCycleValues;

typedef struct {
    int x;
    int y;
    int max_axis_value;
    int pwm_range;
} PWMInputParams;

int initialize_wiring_pi();
void manage_pwm_gpio(int pin_number, int duty_cycle);
void manage_standard_gpio(StandardGpioConfig configs[], size_t count);
DutyCycleValues get_pwm_duty_cycle(PWMInputParams params);

#endif