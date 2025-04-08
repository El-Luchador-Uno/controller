#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <linux/joystick.h>

void handle_joystick_input(const char *device_path);

#endif
