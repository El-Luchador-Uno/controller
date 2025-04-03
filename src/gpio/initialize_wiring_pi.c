#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>

#define PWM_GPIO 23

int initialize_wiring_pi() {
    if (wiringPiSetup() == -1) {
        fprintf(stderr, "Failed to initialize wiringPi\n");
        return -1;
    }

    printf("WiringPi has been initialized\n");
    return 0;
}