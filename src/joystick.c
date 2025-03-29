#include "joystick.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "./gpio/gpio.h"

void log_joystick_input(const char *device_path) {
    int js_fd = open(device_path, O_RDONLY);
    if (js_fd == -1) {
        perror("Error opening joystick device");
        return;
    }

    struct js_event js;
    while (1) {
        if (read(js_fd, &js, sizeof(struct js_event)) == sizeof(struct js_event)) {
            if (js.type == JS_EVENT_AXIS) {
                if (js.number == 0) {
                    if (js.value < -10000) {
                        setup_pwm(1024);
                        printf("Joystick moved left\n");
                    } else if (js.value > 10000) {
                        setup_pwm(0);
                        printf("Joystick moved right\n");
                    }
                } else if (js.number == 1) {
                    if (js.value < -10000) {
                        printf("Joystick moved up\n");
                    } else if (js.value > 10000) {
                        printf("Joystick moved down\n");
                    }
                }
            }
        }
    }

    close(js_fd);
}
