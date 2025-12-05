#pragma once
#include_next <mcuconf.h>

// Enable I2C2 for OLED
#undef STM32_I2C_USE_I2C2
#define STM32_I2C_USE_I2C2 TRUE

// Try keeping TX DMA but disabling RX DMA
// I2C2_TX uses DMA1_CH4, I2C2_RX uses DMA1_CH5
// We need DMA1_CH5 for WS2812 PWM
#undef STM32_I2C_I2C2_RX_DMA_STREAM
#define STM32_I2C_I2C2_RX_DMA_STREAM STM32_DMA_STREAM_ID_ANY

// Enable TIM1 for PWM (PA10 is TIM1_CH3)
#undef STM32_PWM_USE_TIM1
#define STM32_PWM_USE_TIM1 TRUE
