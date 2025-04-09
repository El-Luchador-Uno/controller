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
    // int retry_count = 0;
    // const int max_retries = 10;
    
    printf("Attempting to connect to controller...\n");
    controller_connected = connect_controller();
    
    if (!controller_connected) {
        printf("Failed to connect to controller initially. Exiting.\n");
        return;
    }
    
    // sleep(2);
    
    // while (retry_count < max_retries) {
        js_fd = open(device_path, O_RDONLY);
    //     if (js_fd != -1) {
    //         break;
    //     }
    //     printf("Attempt %d: Waiting for joystick device to become available...\n", retry_count + 1);
    //     sleep(1);
    //     retry_count++;
    // }
    
    if (js_fd == -1) {
        perror("Error opening joystick device after multiple attempts");
        return;
    }
    
    printf("Joystick device opened successfully. Starting input loop.\n");
    
    while (1) {
        ssize_t bytes_read = read(js_fd, &js, sizeof(struct js_event));
        
        if (bytes_read == sizeof(struct js_event)) {
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
            } else if (js.type == JS_EVENT_BUTTON) {
                if (js.number == 0 && js.value == 1) {
                    handle_move(STOP);
                    printf("A button pressed - stopping\n");
                }
            }
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
