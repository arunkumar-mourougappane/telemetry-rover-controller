#include <mbed.h>


// Blinking rate in milliseconds
#define BLINKING_RATE     2s


int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);

    while (true) {
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
