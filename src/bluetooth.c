#include <stdio.h>
#include <stdlib.h>
#include "bluetooth.h"
#include "./utils/utils.h"

int is_paired() {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "bluetoothctl info %s | grep 'Paired: yes'", CONTROLLER_MAC);
    return (system(cmd) == 0);
}

int pair_controller() {
    char cmd[512];
    char* output;

    printf("Attempting to pair with controller...\n");
    snprintf(cmd, sizeof(cmd), "bluetoothctl <<EOF\npair %s\ntrust %s\nexit\nEOF", CONTROLLER_MAC, CONTROLLER_MAC);
    
    output = execute_command(cmd);
    if (output) {
        printf("%s", output);
        free(output);
    }

    return is_paired() ? 0 : -1;
}

int form_bluetooth_connection() {
    char command[256];
    snprintf(command, sizeof(command), "bluetoothctl connect %s", CONTROLLER_MAC);

    char* output = execute_command(command);
    if (output) {
        printf("%s", output);
        free(output);
    }

    return 0;
}