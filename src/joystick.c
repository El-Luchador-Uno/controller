#include "joystick.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "gpio.h"
#include "constants.h"
#include <stdbool.h>
#include "handle_move.h"
#include "connect_controller.h"

void handle_joystick_input(const char *device_path) {
    int js_fd;
    struct js_event js;
    bool controller_connected = false;
    
    printf("Attempting to connect to controller...\n");
    controller_connected = connect_controller();
    
    if (!controller_connected) {
        printf("Failed to connect to controller initially. Exiting.\n");
        return;
    }
    
    js_fd = open(device_path, O_RDONLY);
    
    if (js_fd == -1) {
        perror("Error opening joystick device after multiple attempts");
        return;
    }
    
    printf("Joystick device opened successfully. Starting input loop.\n");

    struct {
        int x_axis;
        int y_axis;
        enum direction direction;
    } joystick_state = {0, 0, STOP};
    
    while (1) {
        ssize_t bytes_read = read(js_fd, &js, sizeof(struct js_event));
        
        if (bytes_read == sizeof(struct js_event)) {
            if (js.type == JS_EVENT_AXIS) {
                if (js.number == 0) {
                    joystick_state.x_axis = js.value;
                    if (js.value < -10000) {
                        joystick_state.direction = LEFT;
                        printf("Joystick moved left\n");
                    } else if (js.value > 10000) {
                        joystick_state.direction = RIGHT;
                        printf("Joystick moved right\n");
                    }
                } else if (js.number == 1) {
                    joystick_state.y_axis = js.value;
                    if (js.value < -10000) {
                        joystick_state.direction = UP;
                        printf("Joystick moved up\n");
                    } else if (js.value > 10000) {
                        joystick_state.direction = DOWN;
                        printf("Joystick moved down\n");
                    }
                }
            }

            handle_move(joystick_state.direction, joystick_state.x_axis, joystick_state.y_axis);
        } else {
            printf("Error reading from joystick. Controller might be disconnected.\n");
            
            close(js_fd);
            
            printf("Attempting to reconnect to controller...\n");
            controller_connected = connect_controller();
            
            if (controller_connected) {
                js_fd = open(device_path, O_RDONLY);
                if (js_fd == -1) {
                    perror("Error reopening joystick device");
                    return;
                }
                printf("Controller reconnected successfully.\n");
            } else {
                printf("Failed to reconnect to controller. Exiting.\n");
                return;
            }
        }
    }
    
    close(js_fd);
}
