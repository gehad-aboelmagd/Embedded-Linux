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
            close(fd);
            std::cout << "GPIO initialized successfully\n";
        }
        else
        {
            std::cout << "counldn't open the export file\n";
        }
    }
    int GPIO::GPIO_setPinDir(int dir)
    {
        int fd = open(("/sys/class/gpio/gpio"+std::to_string(GPIO_u8Pin)+"/direction").c_str(), O_RDWR);
        if(fd >= 0)
        {
            if(GPIO_INPUT == dir)
            {
                GPIO_u8Dir = dir;
                write(fd, "in", 2);
            }
            else if(GPIO_OUTPUT == dir)
            {
                GPIO_u8Dir = dir;
                write(fd, "out", 3);
            }
            else
            {
                std::cout << "Invalid direction!\n";
            }
            close(fd);
            // std::cout << "direction set successfully\n";
        }
        else
        {
            std::cout << "couldn't opne the direction file\n";
        }
        return fd;
    }
    int GPIO::GPIO_setPinValue(int value)
    {
        int fd = -1;
        if(GPIO_OUTPUT == GPIO_u8Dir)
        {
            fd = open(("/sys/class/gpio/gpio"+std::to_string(GPIO_u8Pin)+"/value").c_str(), O_RDWR);
            if(fd >= 0)
            {
                write(fd, std::to_string(value).c_str(), 1);
                close(fd);
                // std::cout << "value set successfully\n";
            }
            else
            {
                std::cout << "couldn't open the value file\n";
            }
        }
        else
        {
            std::cout << "Please make sure you are writing to the correct pin\n";
        }
        return fd;
    }
    int GPIO::GPIO_getPinValue(int &valueRef)
    {
        int fd = -1;
        char buff[2];
        if(GPIO_INPUT == GPIO_u8Dir)
        {
            fd = open(("/sys/class/gpio/gpio"+std::to_string(GPIO_u8Pin)+"/value").c_str(), O_RDWR);
            if(fd >= 0)
            {
                read(fd, buff, sizeof(buff));
                valueRef = buff[0] - '0';
                close(fd);
                // std::cout << "value read successfully\n";
            }
            else
            {
                std::cout << "couldn't open the value file\n";
            }
        }
        else
        {
            std::cout << "Please make sure you are reading from the correct pin\n";
        }
        return fd;
    }
    GPIO::~GPIO()
    {
        int fd = open("/sys/class/gpio/unexport", O_RDWR);
        if(fd >= 0)
        {
            write(fd, std::to_string(GPIO_u8Pin).c_str(), 3);
            close(fd);
            std::cout << "file unexported succcessfully\n";
        }
        else
        {
            std::cout << "couldn't open the unexport file\n";
        }
    }

}