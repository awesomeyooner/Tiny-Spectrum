#include "core.hpp"

#include "EmbeddedLib/system.hpp"
#include "EmbeddedLib/devices/ws2812b.hpp"
#include "EmbeddedLib/devices/gpio_device.hpp"

#include "WireLib/communication/protocols/serial_interface.hpp"

#include "color/color_space.hpp"


WS2812B leds = WS2812B(5, &htim2, TIM_CHANNEL_1);
GPIODevice led = GPIODevice(GPIOC, GPIO_PIN_1);

void init()
{
    leds.init();

} // end of "init()"


void update()
{
    double H = ((sin(System::get_seconds()) + 1) / 2) * 360;

    auto rgb = color_space::HSV_to_RGB(H).times(255);

    uint8_t r = rgb.at(0);
    uint8_t g = rgb.at(1);
    uint8_t b = rgb.at(2);

    leds.set_color(r, g, b);
    
} // end of "update()"


 // Define DMA Callback
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    leds.dma_callback();
}