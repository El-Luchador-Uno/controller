#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* execute_command(const char* command) {
    char buffer[128];
    char* result = malloc(1);
    result[0] = '\0';

    FILE* pipe = popen(command, "r");
    if (!pipe) {
        perror("popen failed");
        return NULL;
    }

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        int old_len = strlen(result);
        int add_len = strlen(buffer);
        result = realloc(result, old_len + add_len + 1);
        if (result == NULL) {
            perror("realloc failed");
            pclose(pipe);
            return NULL;
        }
        strcpy(result + old_len, buffer);
    }

    pclose(pipe);
    return result;
}