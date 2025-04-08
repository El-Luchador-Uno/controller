#include "connect_controller.h"
#include "bluetooth.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_CONNECTION_ATTEMPTS 100
#define RETRY_DELAY_SECONDS 3

bool connect_controller(void) {
    int attempts = 0;
    bool connection_successful = false;
    
    printf("Attempting to connect to controller...\n");
    
    while (attempts < MAX_CONNECTION_ATTEMPTS && !connection_successful) {
        attempts++;
        printf("Connection attempt %d of %d\n", attempts, MAX_CONNECTION_ATTEMPTS);
        
        if (pair_controller() == 0) {
            printf("Controller paired successfully\n");
            
            if (form_bluetooth_connection() == 0) {
                printf("Bluetooth connection formed successfully\n");
                connection_successful = true;
            } else {
                printf("Failed to form Bluetooth connection\n");
            }
        } else {
            printf("Failed to pair controller\n");
        }
        
        if (!connection_successful) {
            printf("Waiting %d seconds before next attempt...\n", RETRY_DELAY_SECONDS);
            sleep(RETRY_DELAY_SECONDS);
        }
    }
    
    if (connection_successful) {
        printf("Controller connected successfully after %d attempts\n", attempts);
        return true;
    } else {
        printf("Failed to connect to controller after %d attempts\n", MAX_CONNECTION_ATTEMPTS);
        return false;
    }
}
