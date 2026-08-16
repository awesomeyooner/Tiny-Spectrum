#include "core.hpp"

#include "lcd.hpp"

#include "EmbeddedLib/devices/gpio_device.hpp"
#include "EmbeddedLib/util/string_formatter.hpp"


using namespace status_utils;
using namespace string_formatter;
using namespace std;


GPIODevice led = GPIODevice(GPIOC, GPIO_PIN_1);

LCD lcd = LCD(&hi2c1, 0x4E);


void init()
{
    System::init();

    lcd.init();

} // end of "init()"


void update()
{
    string text = to_string(System::get_seconds(true), 5);

    lcd.set_cursor(0, 0);
    lcd.send_string(text);

    lcd.set_cursor(0, 1);
    lcd.send_string("Hello World!");

} // end of "update()"