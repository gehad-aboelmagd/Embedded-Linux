#include <iostream>

#include "gpio.hpp"


namespace HAL
{
    class LMSensor
    {
        private:
            MCAL::GPIO gpio_pin;
            int sensorMinRange = -55;
            int sensorMaxRange = 150;
            int temperature;
        public:
            LMSensor(int pin);

            float readTemperature();

            int getMinRage();

            int getMaxRange();

            ~LMSensor();
    };        
}