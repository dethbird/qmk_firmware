#pragma once

// Disable DMA for I2C (use polling mode) to free DMA1_CH5 for WS2812 PWM
#define I2C1_DMA_DISABLE

// PWM driver config for WS2812 on PA10 (TIM1_CH3)
#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 3
#define WS2812_DMA_STREAM STM32_DMA1_STREAM5
#define WS2812_DMA_CHANNEL 5

// EEPROM clear marker
#define EEPROM_CLEAR_MARKER 0x43
#define EEPROM_MARKER_ADDR  100
