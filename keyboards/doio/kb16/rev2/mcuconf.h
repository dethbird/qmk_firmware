#pragma once
#include_next <mcuconf.h>

// Enable I2C2 for OLED
#undef STM32_I2C_USE_I2C2
#define STM32_I2C_USE_I2C2 TRUE
