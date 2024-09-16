#ifndef __OBSTACLE_MSGS_H__
#define __OBSTACLE_MSGS_H__

#include "pico/stdlib.h"

typedef struct
{
    std_msgs__msg__Int32 raw;
    std_msgs__msg__Float32 ref;
} Bar;

#endif

