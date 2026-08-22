#include "core.hpp"

#include "EmbeddedLib/system.hpp"
#include "EmbeddedLib/devices/ws2812b.hpp"
#include "EmbeddedLib/devices/gpio_device.hpp"
#include "EmbeddedLib/devices/adc_device.hpp"

#include "EmbeddedLib/devices/lcd.hpp"

#include "WireLib/communication/protocols/serial_interface.hpp"

#include "color/color_space.hpp"

#include "adc.h"


WS2812B leds = WS2812B(64, &htim3, TIM_CHANNEL_4);
GPIODevice led = GPIODevice(GPIOC, GPIO_PIN_1);
GPIODevice button = GPIODevice(GPIOB, GPIO_PIN_1);
ADCDevice adc = ADCDevice(&hadc1, 3);

LCD lcd = LCD(&hi2c1);

void init()
{
    System::init();

    leds.init();

    adc.start_DMA();

    lcd.init();

} // end of "init()"


void update()
{
    System::update();

    if(button.is_high())
        led.set_high();
    else
        led.set_low();

    // if(System::is_OK())
    //     led.set_high();
    // else
    //     led.set_low();

    // double H = ((sin(System::get_seconds()) + 1) / 2) * 360;
    // double H = fmod(System::get_seconds() / 10, 1) * 360;

    double H = adc.get_percent(0) * 360;

    double S = 1;
    double V = 1;
    // double V = adc.get_percent(1);

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

        auto rgb = color_space::HSV_to_RGB(H_i, S, V).times(255);

        uint8_t r = rgb.at(0);
        uint8_t g = rgb.at(1);
        uint8_t b = rgb.at(2);

        leds.set_color(i, r, g, b, false);
    }

    leds.update();



    lcd.set_cursor(0, 0);
    lcd.send_string(adc.get_percent(1));

    lcd.set_cursor(0, 1);
    lcd.send_string(adc.get_percent(2));

    System::feed();
    
} // end of "update()"


 // Define DMA Callback
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    leds.dma_callback();
}