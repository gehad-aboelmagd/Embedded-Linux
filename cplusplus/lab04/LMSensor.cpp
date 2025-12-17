#include "LMSensor.hpp"

namespace HAL
{
    LMSensor::LMSensor(int pin):gpio_pin(pin)
    {
        gpio_pin.GPIO_setPinDir(GPIO_INPUT); // input
        std::cout << "LM35 initialized successfully\n";
    }

    float LMSensor:: readTemperature()
    {
        gpio_pin.GPIO_getPinValue(temperature);
        if(temperature < sensorMinRange)
        {
            temperature = sensorMinRange;
        }
        else if(temperature > sensorMaxRange)
        {
            temperature = sensorMaxRange;
        }
        return temperature;
    }

    LMSensor::~LMSensor()
    {
        std::cout << "sensor freed successfully\n";
    }
}