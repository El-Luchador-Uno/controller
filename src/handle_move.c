#include "constants.h"
#include "gpio/gpio.h"
#include "handle_move.h"

void handle_move(enum direction dir) {
    StandardGpioConfig gpio_configs[4];

    switch (dir) {
        case UP:
            gpio_configs[0] = (StandardGpioConfig){SL1, true};
            gpio_configs[1] = (StandardGpioConfig){SL2, false};
            gpio_configs[2] = (StandardGpioConfig){SR1, false};
            gpio_configs[3] = (StandardGpioConfig){SR2, true};
            manage_standard_gpio(gpio_configs, sizeof(gpio_configs) / sizeof(StandardGpioConfig));
            return;
        case DOWN:  
            gpio_configs[0] = (StandardGpioConfig){SL1, false};
            gpio_configs[1] = (StandardGpioConfig){SL2, true};
            gpio_configs[2] = (StandardGpioConfig){SR1, false};
            gpio_configs[3] = (StandardGpioConfig){SR2, true};
            manage_standard_gpio(gpio_configs, sizeof(gpio_configs) / sizeof(StandardGpioConfig));
            return;
        case LEFT:
            gpio_configs[0] = (StandardGpioConfig){SL1, false};
            gpio_configs[1] = (StandardGpioConfig){SL2, true};
            gpio_configs[2] = (StandardGpioConfig){SR1, true};
            gpio_configs[3] = (StandardGpioConfig){SR2, false};
            manage_standard_gpio(gpio_configs, sizeof(gpio_configs) / sizeof(StandardGpioConfig));
            return;
        case RIGHT:
            gpio_configs[0] = (StandardGpioConfig){SL1, true};  
            gpio_configs[1] = (StandardGpioConfig){SL2, false};
            gpio_configs[2] = (StandardGpioConfig){SR1, false};
            gpio_configs[3] = (StandardGpioConfig){SR2, true};
            manage_standard_gpio(gpio_configs, sizeof(gpio_configs) / sizeof(StandardGpioConfig));
            return;
    }
}