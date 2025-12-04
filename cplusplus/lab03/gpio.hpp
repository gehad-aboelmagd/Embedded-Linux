#ifndef GPIO_DRIVER
#define GPIO_DRIVER

#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <string>

namespace MCAL
{
    class GPIO
    {
        private:
            int GPIO_u8Pin;
            int GPIO_u8Dir;
            int GPIO_u8Value;
            static const int GPIO_PIN_SHIFT = 512;
        public:
            GPIO(int pin);
            int GPIO_setPinDir(int dir);
            int GPIO_setPinValue(int value);
            int GPIO_getPinValue(int &valueRef);
            ~GPIO();
    };
}

#endif // GPIO_DRIVER