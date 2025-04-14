#include <utils.h>
#include <constants.h>
#include <gpio.h>
#include <stdlib.h>

DutyCycleValues get_pwm_duty_cycle(PWMInputParams params) {
    DutyCycleValues duty_cycle_values = {0, 0};

    int deadzone = params.max_axis_value * 3 / 100;

    if (abs(params.x) < deadzone && abs(params.y) < deadzone) {
        return duty_cycle_values;
    }

    double distance = get_distance_from_center(params.x, params.y);
    double degrees = get_degrees_of_direction(params.x, params.y);
    double percent_of_max_duty_cycle = distance / params.max_axis_value;
    double max_duty_cycle = params.pwm_range * percent_of_max_duty_cycle;

    double ratio;
    int quadrant = (int)(degrees / 90);
    double angle_in_quadrant = degrees - (quadrant * 90);
    
    if (angle_in_quadrant > 45) {
        angle_in_quadrant = 90 - angle_in_quadrant;
    }
    
    ratio = 1.0 - (0.5 * (angle_in_quadrant / 45.0));

    switch (quadrant) {
        case 0: // 0-89 degrees (forward-left)
            duty_cycle_values.right_pwm = (int)max_duty_cycle;
            duty_cycle_values.left_pwm = (int)(max_duty_cycle * ratio);
            break;
        case 1: // 90-179 degrees (forward-right)
            duty_cycle_values.left_pwm = (int)max_duty_cycle;
            duty_cycle_values.right_pwm = (int)(max_duty_cycle * ratio);
            break;
        case 2: // 180-269 degrees (backward-right)
            duty_cycle_values.left_pwm = (int)max_duty_cycle;
            duty_cycle_values.right_pwm = (int)(max_duty_cycle * ratio);
            break;
        case 3: // 270-359 degrees (backward-left)
            duty_cycle_values.right_pwm = (int)max_duty_cycle;
            duty_cycle_values.left_pwm = (int)(max_duty_cycle * ratio);
            break;
    }

    return duty_cycle_values;
}