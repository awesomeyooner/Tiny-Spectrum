#include "core.hpp"


#include "EmbeddedLib/devices/ws2812b.hpp"


WS2812B leds = WS2812B(5, &htim2, TIM_CHANNEL_1);


void init()
{
    leds.init();

} // end of "init()"


void update()
{
    leds.set_color(WS2812B::BLUE);
    
} // end of "update()"


 // Define DMA Callback
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    leds.dma_callback();
}