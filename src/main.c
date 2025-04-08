#include <stdio.h>
#include "bluetooth.h"
#include "joystick.h"
#include <unistd.h>
#include "gpio.h"

int main() {
    initialize_wiring_pi();

    handle_joystick_input("/dev/input/js0");
    
    return 0;
}
