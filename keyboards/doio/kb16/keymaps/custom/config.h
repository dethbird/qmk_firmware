#pragma once

// Use bitbang driver for WS2812 (no DMA conflict with I2C)
// STM32F103 at 72MHz - try exact WS2812 timing
#define WS2812_TRST_US 280
