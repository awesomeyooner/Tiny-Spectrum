#include "core.hpp"

#include "EmbeddedLib/system.hpp"
#include "EmbeddedLib/devices/ws2812b.hpp"
#include "EmbeddedLib/devices/gpio_device.hpp"

#include "WireLib/communication/protocols/serial_interface.hpp"

#include "color/color_space.hpp"

#include "adc.h"


WS2812B leds = WS2812B(60, &htim2, TIM_CHANNEL_1);
GPIODevice led = GPIODevice(GPIOC, GPIO_PIN_1);

uint32_t adc[2];

void init()
{
    leds.init();

    HAL_ADC_Start_DMA(&hadc1, adc, 2);

} // end of "init()"


void update()
{
    // double H = ((sin(System::get_seconds()) + 1) / 2) * 360;
    // double H = fmod(System::get_seconds() / 10, 1) * 360;

    double H = ((double)adc[0] / 4096) * 360;
    double V = (double)adc[1] / 4096;

    // auto rgb = color_space::HSV_to_RGB(H).times(255);

    // uint8_t r = rgb.at(0);
    // uint8_t g = rgb.at(1);
    // uint8_t b = rgb.at(2);

    // leds.set_color(r, g, b);

    int num_leds = leds.get_num_leds();

    for(int i = 0; i < num_leds; i++)
    {
        // double H_i = fmod(H + (i * 5), 360);
        double H_i = H;

        auto rgb = color_space::HSV_to_RGB(H_i, 1, V).times(255);

        uint8_t r = rgb.at(0);
        uint8_t g = rgb.at(1);
        uint8_t b = rgb.at(2);

        leds.set_color(i, r, g, b, false);
    }

    leds.update();

    // Serial.println(adc);
    
} // end of "update()"


 // Define DMA Callback
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    leds.dma_callback();
}