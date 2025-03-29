#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>

#define PWM_GPIO 23

void setup_pwm(int duty_cycle) {
    if (wiringPiSetup() == -1) {
        fprintf(stderr, "Failed to initialize wiringPi\n");
        return;
    }

    pinMode(PWM_GPIO, PWM_OUTPUT); 
    pwmSetMode(PWM_MODE_MS);       
    pwmSetRange(1024);             
    pwmSetClock(10);              
    pwmWrite(PWM_GPIO, duty_cycle);

    printf("PWM started on GPIO %d with duty cycle %d\n", PWM_GPIO, duty_cycle);
}