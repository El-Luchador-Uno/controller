#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include "../include/constants.h"
void manage_pwm_gpio(int pin_number, int duty_cycle) {
    pinMode(pin_number, PWM_OUTPUT); 
    pwmSetMode(PWM_MODE_MS);       
    pwmSetRange(PWM_RANGE);             
    pwmSetClock(PWM_CLOCK);              
    pwmWrite(pin_number, duty_cycle);
}