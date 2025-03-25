#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <linux/joystick.h>

void log_joystick_input(const char *device_path);

#endif
