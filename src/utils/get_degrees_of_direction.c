#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double get_degrees_of_direction(int x, int y) {
    double angle_rad = atan2(y, x);
    double angle_deg = angle_rad * (180.0 / M_PI);
    
    if (angle_deg < 0) {
        angle_deg += 360.0;
    }
    
    return angle_deg;
}