#include <stdio.h>
#include "bluetooth.h"
#include "joystick.h"
#include <unistd.h>
#include "gpio.h"
#include "constants.h"

int main() {
    initialize_wiring_pi();

    handle_joystick_input(JS_DEVICE_PATH);
    
    return 0;
}
