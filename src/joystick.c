#include "joystick.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "./gpio/gpio.h"
#include "constants.h"
#include <stdbool.h>
#include "handle_move.h"

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
                        handle_move(LEFT);
                        printf("Joystick moved left\n");
                    } else if (js.value > 10000) {
                        handle_move(RIGHT);
                        printf("Joystick moved right\n");
                    }
                } else if (js.number == 1) {
                    if (js.value < -10000) {
                        handle_move(UP);
                        printf("Joystick moved up\n");
                    } else if (js.value > 10000) {
                        handle_move(DOWN);
                        printf("Joystick moved down\n");
                    }
                }
            }
        }
    }

    close(js_fd);
}
