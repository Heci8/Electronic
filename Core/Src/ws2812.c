#include "ws2812.h"
#include "tim.h"

uint8_t color[LED_COUNT][3];

void ColorSet(int index, uint8_t green, uint8_t red, uint8_t blue)
{
    if (index < LED_COUNT)
    {
        color[index][0] = green;
        color[index][1] = red;
        color[index][2] = blue;
    }
}

void Set(uint8_t green, uint8_t red, uint8_t blue)
{
    for (int i = 0; i < LED_COUNT; i++)
    {
        ColorSet(i, green, red, blue);
    }
}

void WS2812_Update(void)
{
    static uint16_t data[LED_COUNT * 3 * 8 + 1];

    for (int i = 0; i < LED_COUNT; i++)
    {
        uint8_t green = color[i][0];
        uint8_t red = color[i][1];
        uint8_t blue = color[i][2];

        for (int j = 0; j < 8; j++)
        {
            data[24 * i + j] = (green & (0x80 >> j)) ? WS2812_CODE_1 : WS2812_CODE_0;
            data[24 * i + 8 + j] = (red & (0x80 >> j)) ? WS2812_CODE_1 : WS2812_CODE_0;
            data[24 * i + 16 + j] = (blue & (0x80 >> j)) ? WS2812_CODE_1 : WS2812_CODE_0;
        }
    }

    data[LED_COUNT * 24] = WS2812_CODE_RESET;

    HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_1);
    __HAL_TIM_SET_COUNTER(&htim3, 0);
    HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t *)data,
                          sizeof(data) / sizeof(uint16_t));
}

