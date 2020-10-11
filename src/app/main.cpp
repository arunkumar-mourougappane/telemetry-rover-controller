#include <mbed.h>
#include "Graphics/GraphicsWrapper.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     200ms


int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);
    direction_t *joypadDirection = {};
    joypadDirection->direction = Direction_e::UP;
    joypadDirection->dataReady = true;
    CGraphicsWrapper graphics(joypadDirection);
    graphics.Start();
    while (true) {
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
        if(joypadDirection->dataReady == false)
        {
            joypadDirection->dataReady = true;
        }
    }
}
