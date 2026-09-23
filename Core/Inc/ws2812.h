#ifndef INC_WS2812_H
#define INC_WS2812_H

#include "tim.h"

#define LED_COUNT 10
#define WS2812_CODE_0 30
#define WS2812_CODE_1 60
#define WS2812_CODE_RESET 0

void ColorSet(int index, uint8_t green, uint8_t red, uint8_t blue);
void Set(uint8_t green, uint8_t red, uint8_t blue);
void WS2812_Update(void);

#endif /* INC_WS2812_H_ */
