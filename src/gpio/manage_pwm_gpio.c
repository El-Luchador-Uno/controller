#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>

void manage_pwm_gpio(int pin_number, int duty_cycle) {
    pinMode(pin_number, PWM_OUTPUT); 
    pwmSetMode(PWM_MODE_MS);       
    pwmSetRange(1024);             
    pwmSetClock(10);              
    pwmWrite(pin_number, duty_cycle);
}