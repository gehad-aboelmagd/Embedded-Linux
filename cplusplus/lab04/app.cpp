#include <iostream>
#include <memory>
#include <ctime>


#include "gpio.hpp"
#include "LMSensor.hpp"

class TemperatureData
{
private:
    float temperatue_value = 0;
    std::string temperature_time = "";

    std::string get_current_time(void)
    {   
        time_t current;
        time(&current);
        tm *info = localtime(&current);
        
        std::string t;
        
        if(info->tm_hour < 10) t += "0";
        t += std::to_string(info->tm_hour) + ":";
        
        if(info->tm_min < 10) t += "0";
        t += std::to_string(info->tm_min) + ":";
        
        if(info->tm_sec < 10) t += "0";
        t += std::to_string(info->tm_sec);

        return t;
    }
    
    public:
        void setTemperature(float temp)
        {
            temperatue_value = temp;
            temperature_time = get_current_time();

        }
        std::string getTemperatureData()
        {
            std::string data = temperature_time + " ";
            data += std::to_string(temperatue_value) + "\n"; 
            return data;
        }

};

class Logger
{
    private:
        int fd;
        std::string log;
        int counter = 0;
        const int max_logs = 5;
        std::shared_ptr<TemperatureData> data;

    public:
        Logger(std::shared_ptr<TemperatureData> temp_data)
        {
            data = temp_data;
            fd = open("./logs.txt", O_RDWR | O_CREAT);
            if(fd < 0)
            {
                std::cout << "logger opened successfully\n";
            }
            else
            {
                std::cout << "logs file opened susccessfully\n";
            }
        }

        void logTemperature()
        {
            if(fd >= 0)
            {                
                if(counter == max_logs)
                {
                    lseek(fd, 0, SEEK_SET);
                    
                    counter = 0;
                }

                std::cout << counter << std::endl;

                log = data->getTemperatureData() + "\n";
                write(fd, log.c_str(), log.size());
                counter ++;
            }
        }

        ~Logger()
        {
            close(fd);   
        }
};

class Display
{
    private:
        std::shared_ptr<TemperatureData> data;

    public:
        Display(std::shared_ptr<TemperatureData> temp_data)
        {
            data = temp_data;
        }
        void displayTemperature()
        {
            std::cout << "Temperature :" << data->getTemperatureData();
        }
};

int main()
{
    std::unique_ptr <HAL::LMSensor> sensor_ptr(new HAL::LMSensor(7));
    std::shared_ptr<TemperatureData> first_ptr(new TemperatureData);
    Logger logger(first_ptr);
    Display display(first_ptr);

    for(int i=0; i<8; i++)
    {
        first_ptr->setTemperature(sensor_ptr->readTemperature());
        logger.logTemperature();
        display.displayTemperature();
        sleep(1);
    }

    return 0;
}