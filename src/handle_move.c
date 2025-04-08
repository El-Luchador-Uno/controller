#include "constants.h"
#include "gpio.h"
#include "handle_move.h"

void handle_move(enum direction dir) {
    StandardGpioConfig gpio_configs[4];

    switch (dir) {
        case UP:
            manage_pwm_gpio(PWML, 1024);
            manage_pwm_gpio(PWMR, 1024);
            gpio_configs[0] = (StandardGpioConfig){SL1, true};
            gpio_configs[1] = (StandardGpioConfig){SL2, false};
            gpio_configs[2] = (StandardGpioConfig){SR1, false};
            gpio_configs[3] = (StandardGpioConfig){SR2, true};
            manage_standard_gpio(gpio_configs, sizeof(gpio_configs) / sizeof(StandardGpioConfig));
            return;
        case DOWN:  
            manage_pwm_gpio(PWML, 1024);
            manage_pwm_gpio(PWMR, 1024);
            gpio_configs[0] = (StandardGpioConfig){SL1, false};
            gpio_configs[1] = (StandardGpioConfig){SL2, true};
            gpio_configs[2] = (StandardGpioConfig){SR1, false};
            gpio_configs[3] = (StandardGpioConfig){SR2, true};
            manage_standard_gpio(gpio_configs, sizeof(gpio_configs) / sizeof(StandardGpioConfig));
            return;
        case LEFT:
            manage_pwm_gpio(PWML, 1024);
            manage_pwm_gpio(PWMR, 1024);
            gpio_configs[0] = (StandardGpioConfig){SL1, false};
            gpio_configs[1] = (StandardGpioConfig){SL2, true};
            gpio_configs[2] = (StandardGpioConfig){SR1, true};
            gpio_configs[3] = (StandardGpioConfig){SR2, false};
            manage_standard_gpio(gpio_configs, sizeof(gpio_configs) / sizeof(StandardGpioConfig));
            return;
        case RIGHT:
            manage_pwm_gpio(PWML, 1024);
            manage_pwm_gpio(PWMR, 1024);
            gpio_configs[0] = (StandardGpioConfig){SL1, true};  
            gpio_configs[1] = (StandardGpioConfig){SL2, false};
            gpio_configs[2] = (StandardGpioConfig){SR1, false};
            gpio_configs[3] = (StandardGpioConfig){SR2, true};
            manage_standard_gpio(gpio_configs, sizeof(gpio_configs) / sizeof(StandardGpioConfig));
            return;
        case STOP:
            manage_pwm_gpio(PWML, 0);
            manage_pwm_gpio(PWMR, 0);
            gpio_configs[0] = (StandardGpioConfig){SL1, false};
            gpio_configs[1] = (StandardGpioConfig){SL2, false};
            gpio_configs[2] = (StandardGpioConfig){SR1, false};
            gpio_configs[3] = (StandardGpioConfig){SR2, false};
            manage_standard_gpio(gpio_configs, sizeof(gpio_configs) / sizeof(StandardGpioConfig));
            return;
    }
}