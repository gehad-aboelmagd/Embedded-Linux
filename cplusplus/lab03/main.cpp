#include <iostream>
#include "gpio.hpp"

int main()
{
    MCAL::GPIO gpio0(0);
    gpio0.GPIO_setPinDir(1);
    gpio0.GPIO_setPinValue(1);

    MCAL::GPIO gpio1(1);
    int value;
    gpio1.GPIO_setPinDir(0);
    gpio1.GPIO_getPinValue(value);

    return 0;
}