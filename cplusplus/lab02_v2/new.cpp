#include <iostream>
#include <string>
#include <initializer_list>

#include <unistd.h>
#include <fcntl.h>
#include <cstring>

using namespace std;

typedef initializer_list<pair<string, int>> actions_t;

class FileActions
{
private:
    string path;
    int *fd;
    // int * &fdref = fd;
    actions_t actions;
public:
    FileActions(string &path)
    {
        this->path = path;
        fd = new int;
        *fd = open(this->path.c_str(), O_RDWR);
    }
    FileActions(const FileActions &obj)
    {
        path = obj.path;
        fd = new int;
        if(obj.fd != nullptr) // file still opened
        {
            *fd = *obj.fd;
        }
        else // file has been closed by obj
        {
            *fd = open(path.c_str(), O_RDWR);
        }
    }
    void register_actions(actions_t actions)
    {
        this->actions = actions;
    }
    void execute_actions(void)
    {
        char buff[200] = {'\0'};

        if(*fd < 0)
        {
            cout << "problem with the file. Make sure to provide a valid path\n";
            return;
        }
        
        for(int i=0; i<actions.size(); i++)
        {
            if(actions.begin()[i].first == "read")
            {
                if(actions.begin()[i].second == 1)
                {
                    cout << "reading...\n";
                    read(*fd, buff, sizeof(buff));
                    cout << buff << std::endl;
                }
            }
            else if(actions.begin()[i].first == "write")
            {
                if(actions.begin()[i].second == 1)
                {
                    cout << "writing...\n";
                    strcpy(buff, "Have a nice day!");
                    write(*fd, buff, sizeof(buff));
                }
            }
            else if(actions.begin()[i].first == "close")
            {
                if(actions.begin()[i].second == 1)
                {
                    cout << "closing...\n";
                    close(*fd);
                    *fd = -1;
                }
            }
            else
            {
                cout << "Invalid Actions :(\n";
            }

        }
    }
    ~FileActions()
    {
        close(*fd);
        delete fd;
        fd = nullptr;
    }
    int * get_fd_address(void)
    {
        return fd;
    }
    int get_fd_value(void)
    {
        return *fd;
    }
};

void func(FileActions obj)
{
    cout << obj.get_fd_address() << endl;
    cout << obj.get_fd_value() << endl;
    cout << "object deallocated...\n";

    // actions_t actions = {{"read", 1}, {"write", 1}, {"close", 1}};
    // obj.register_actions(actions);
    // obj.execute_actions();
}


int main(void)
{
    string path = "file.txt";
    FileActions act1(path);

    /* ********** testing copy constructor ********** */
    
    cout << "bofore callign func...\n";
    cout << act1.get_fd_address() << endl;
    cout << act1.get_fd_value() << endl << endl;

    cout << "callign func...\n";
    func(act1);
    cout << endl;

    cout << "after callign func...\n";
    cout << act1.get_fd_address() << endl;
    cout << act1.get_fd_value() << endl << endl;


    /* ********** testing acitons functionality ********** */

    actions_t actions = {{"read", 1}, {"write", 1}, {"close", 0}};
    act1.register_actions(actions);
    act1.execute_actions();

    // func(act1);

    // actions = {{"read", 1}, {"write", 1}, {"close", 1}};
    // act1.register_actions(actions);
    // act1.execute_actions();

    // func(act1);

    return 0;
}