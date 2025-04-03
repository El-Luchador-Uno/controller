#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <stdbool.h>
#include "gpio.h"

void manage_standard_gpio(StandardGpioConfig configs[], size_t count) {
    for (size_t i = 0; i < count; i++) {
        int pin_number = configs[i].pin_number;
        bool is_on = configs[i].is_on;

        pinMode(pin_number, OUTPUT);
        digitalWrite(pin_number, is_on ? HIGH : LOW);
    }
}