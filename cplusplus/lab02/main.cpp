#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>

class CapsLock
{
private:
    std::string path;
    int fd;
public:
    CapsLock() = delete;
    CapsLock(std::string p)
    {
        path = p;
        fd = open(path.c_str(), O_RDWR);
    }
    ~CapsLock()
    {
        close(fd);
    }
    int CapsLockON()
    {
        if(-1 == fd) return -1;
        dprintf(fd, "1");
        return 0;
    }
    int CapsLockOff()
    {
        if(-1 == fd) return -1;
        dprintf(fd, "0");
        return 0;
    }
};

int main()
{
    // CapsLock g;
    CapsLock cap("/sys/devices/platform/i8042/serio0/input/input3/input3::capslock/brightness");
    // CapsLock cap("sys/class/leds/input3\\:\\:capslock/brightness");
    
    // cap.CapsLockON();
    cap.CapsLockOff();

    return 0;
}