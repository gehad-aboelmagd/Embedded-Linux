#include "gpio.hpp"

namespace MCAL
{

    GPIO::GPIO(int pin)
    {
        GPIO_u8Pin = pin + GPIO_PIN_SHIFT;
        int fd = open("/sys/class/gpio/export", O_RDWR);
        if(fd >= 0)
        {
            write(fd, std::to_string(GPIO_u8Pin).c_str(), 3);
            std::cout << "initialization done successfully\n";
        }
        else
        {
            std::cout << "counldn't open the export file\n";
        }
    }
    int GPIO::GPIO_setPinDir(int dir)
    {
        int fd = open(("sys/class/gpio/gpio"+std::to_string(GPIO_u8Pin)+"/direction").c_str(), O_RDWR);
        if(fd >= 0)
        {
            if(0 == dir)
            {
                write(fd, "in", 2);
            }
            else if(1 == dir)
            {
                write(fd, "out", 3);
            }
            std::cout << "direction set successfully\n";
        }
        return fd;
    }
    int GPIO::GPIO_setPinValue(int value)
    {
        int fd = -1;
        if(1 == GPIO_u8Dir)
        {
            fd = open(("sys/class/gpio/gpio"+std::to_string(GPIO_u8Pin)+"/value").c_str(), O_RDWR);
            if(fd >= 0)
            {
                write(fd, std::to_string(value).c_str(), 1);
                std::cout << "value set successfully\n";
            }
        }
        return fd;
    }
    int GPIO::GPIO_getPinValue(int &valueRef)
    {
        int fd = -1;
        char buff[2];
        if(0 == GPIO_u8Dir)
        {
            fd = open(("sys/class/gpio/gpio"+std::to_string(GPIO_u8Pin)+"value").c_str(), O_RDWR);
            if(fd >= 0)
            {
                read(fd, buff, sizeof(buff));
                valueRef = buff[0] - '0';
                std::cout << "value read successfully\n";
            }
        }
        return fd;
    }
    GPIO::~GPIO()
    {
        int fd = open("/sys/class/gpio/unexport", O_RDWR);
        if(fd >= 0)
        {
            write(fd, std::to_string(GPIO_u8Pin).c_str(), 3);
        }
    }

}