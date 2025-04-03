#include <stdio.h>
#include "bluetooth.h"
#include "joystick.h"
#include <unistd.h>
#include "gpio/gpio.h"

int main() {
    if (!is_paired()) {
        if (pair_controller() != 0) {
            fprintf(stderr, "Could not pair with controller. Exiting...\n");
            return 1;
        }
    }

    if (connect_controller() != 0) {
        fprintf(stderr, "Failed to connect to controller. Exiting...\n");
        return 1;
    }

    initialize_wiring_pi();

    sleep(5);

    printf("Ready to track controller input\n");

    log_joystick_input("/dev/input/js0");
    
    return 0;
}
