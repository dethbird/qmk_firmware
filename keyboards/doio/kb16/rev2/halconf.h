#pragma once

#include_next <halconf.h>

// Enable I2C for OLED
#undef HAL_USE_I2C
#define HAL_USE_I2C TRUE
