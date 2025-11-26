#include <iostream>
#include <utility>
#include <initializer_list>

#include <unistd.h>
#include <fcntl.h>
#include <cstring>

using namespace std;

class FileActions
{
private:
    int *fd = nullptr;
    int * &fd_ref = fd;
    bool rd=false, wr=false, cls=false;
    char buff[200] = {'\0'};
public:
    FileActions(std::string &path)
    {
        fd = new int;
        *fd = open(path.c_str(), O_RDWR);
        if(*fd < 0)
        {
            std::cout << "Unable to open the file\n";
        }
    }
    FileActions(const FileActions &obj)
    {
        if(nullptr == obj.fd) // file was closed
        {
            fd = new int; 
            *fd = -1;
        }
        else                  // file is still opened
        {
            fd = obj.fd;
        }
    }
    ~FileActions()
    {
        std::cout << "deconstructor closing file...\n";
        if(*fd >= 0)        // wasn't closed by execute_actions()
        {
            close(*fd);
        }
        delete(fd);
        fd = nullptr;
    }
    void register_actions(std::initializer_list<std::pair<std::string, bool>> actions)
    {
        for(int i=0; i<actions.size(); i++)
        {
            if(actions.begin()[i].first == "read")
            {
                rd = actions.begin()[i].second;
            }
            else if(actions.begin()[i].first == "write")
            {
                wr = actions.begin()[i].second;
            }
            else if(actions.begin()[i].first == "close")
            {
                cls = actions.begin()[i].second;
            }
        }
    }
    void execute_actions(void)
    {
        if(*fd < 0)
        {
            return;
        }
        if(true == rd)
        {
            read(*fd, buff, sizeof(buff));
            std::cout << "reading...\n";
            std::cout << buff << std::endl;
        }

        if(true == wr)
        {
            std::cout << "writing...\n";
            strcpy(buff, "\nHave a nice day.\n");
            write(*fd, buff, strlen(buff)); // write appends text
        }

        if(true == cls)
        {
            std::cout << "closing file...\n";
            close(*fd);
        }
    }
};


int main()
{
    // std:: string path = "file.txt";

    // FileActions f1(path);
    // std::initializer_list <std::pair <std::string, bool>> actions1 = 
    // {
    //     {"read", true},
    //     {"write", true},
    //     {"close", true}
    // };
    // f1.register_actions(actions1);
    // f1.execute_actions();

    // FileActions f2 = f1;
    // std::initializer_list <std::pair <std::string, bool>> actions2 = 
    // {
    //     {"read", false},
    //     {"write", false},
    //     {"close", false}
    // };
    // f2.register_actions(actions2);
    // f2.execute_actions();


    return 0;
}