#include "constants.h"
#include "gpio.h"
#include "handle_move.h"
#include <stdio.h>
void handle_move(enum direction dir, int x, int y) {
    StandardGpioConfig gpio_configs[4];

    PWMInputParams params = {x, y,  MAX_AXIS_VALUE, PWM_RANGE};
    DutyCycleValues duty_cycle_values = get_pwm_duty_cycle(params);

    printf("Duty cycle values: %d, %d\n", duty_cycle_values.left_pwm, duty_cycle_values.right_pwm);

    switch (dir) {
        case UP:
            manage_pwm_gpio(PWML, duty_cycle_values.left_pwm);
            manage_pwm_gpio(PWMR, duty_cycle_values.right_pwm);
            gpio_configs[0] = (StandardGpioConfig){SL1, true};
            gpio_configs[1] = (StandardGpioConfig){SL2, false};
            gpio_configs[2] = (StandardGpioConfig){SR1, false};
            gpio_configs[3] = (StandardGpioConfig){SR2, true};
            manage_standard_gpio(gpio_configs, sizeof(gpio_configs) / sizeof(StandardGpioConfig));
            return;
        case DOWN:  
            manage_pwm_gpio(PWML, duty_cycle_values.left_pwm);
            manage_pwm_gpio(PWMR, duty_cycle_values.right_pwm);
            gpio_configs[0] = (StandardGpioConfig){SL1, false};
            gpio_configs[1] = (StandardGpioConfig){SL2, true};
            gpio_configs[2] = (StandardGpioConfig){SR1, false};
            gpio_configs[3] = (StandardGpioConfig){SR2, true};
            manage_standard_gpio(gpio_configs, sizeof(gpio_configs) / sizeof(StandardGpioConfig));
            return;
        case LEFT:
            manage_pwm_gpio(PWML, duty_cycle_values.left_pwm);
            manage_pwm_gpio(PWMR, duty_cycle_values.right_pwm);
            gpio_configs[0] = (StandardGpioConfig){SL1, false};
            gpio_configs[1] = (StandardGpioConfig){SL2, true};
            gpio_configs[2] = (StandardGpioConfig){SR1, true};
            gpio_configs[3] = (StandardGpioConfig){SR2, false};
            manage_standard_gpio(gpio_configs, sizeof(gpio_configs) / sizeof(StandardGpioConfig));
            return;
        case RIGHT:
            manage_pwm_gpio(PWML, duty_cycle_values.left_pwm);
            manage_pwm_gpio(PWMR, duty_cycle_values.right_pwm);
            gpio_configs[0] = (StandardGpioConfig){SL1, true};  
            gpio_configs[1] = (StandardGpioConfig){SL2, false};
            gpio_configs[2] = (StandardGpioConfig){SR1, false};
            gpio_configs[3] = (StandardGpioConfig){SR2, true};
            manage_standard_gpio(gpio_configs, sizeof(gpio_configs) / sizeof(StandardGpioConfig));
            return;
        case STOP:
            manage_pwm_gpio(PWML, duty_cycle_values.left_pwm);
            manage_pwm_gpio(PWMR, duty_cycle_values.right_pwm);
            gpio_configs[0] = (StandardGpioConfig){SL1, false};
            gpio_configs[1] = (StandardGpioConfig){SL2, false};
            gpio_configs[2] = (StandardGpioConfig){SR1, false};
            gpio_configs[3] = (StandardGpioConfig){SR2, false};
            manage_standard_gpio(gpio_configs, sizeof(gpio_configs) / sizeof(StandardGpioConfig));
            return;
    }
}