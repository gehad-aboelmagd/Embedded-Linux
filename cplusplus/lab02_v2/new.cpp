#include <iostream>
#include <string>

#include <unistd.h>
#include <fcntl.h>
#include <cstring>

using namespace std;

typedef initializer_list<pair<string, int>> actions_t;

class FileActions
{
private:
    int *fd = nullptr;
    int * &fdref;
    actions_t actions;
public:
    FileActions(string path): fdref(fd)
    {
        fd = new int;
        *fd = open(path.c_str(), O_RDWR);
    }
    FileActions(FileActions &obj): fdref(obj.fd)
    {
        fd = new int;
        *fd = *obj.fd;
    }
    void registerActions(actions_t actions_)
    {
        actions = actions_;
    }
    void executeActions()
    {
        char buff[200];

        if(*fdref < 0)
        {
            cout << "Unfortunately, file has already been closed by another object.\n\n";
            return;
        }
        
        for(int i=0; i<actions.size(); i++)
        {
            if(actions.begin()[i].first == "read")
            {
                if(actions.begin()[i].second == 1)
                {
                    cout << "reading...\n";
                    lseek(*fdref, 0, SEEK_SET);
                    read(*fdref, buff, sizeof(buff));
                    cout << buff << "\n\n";
                }
            }
            else if(actions.begin()[i].first == "write")
            {
                if(actions.begin()[i].second == 1)
                {
                    cout << "writing...\n\n";
                    strcpy(buff, "\nHave a nice day.");
                    write(*fdref, buff, strlen(buff));
                }
            }
            else if(actions.begin()[i].first == "close")
            {
                if(actions.begin()[i].second == 1)
                {
                    cout << "closing...\n\n";
                    close(*fdref);
                    *fdref = -1;
                }
            }
            else
            {
                cout << "Invalid Action\n";
            }
        }
    }
    ~FileActions()
    {
        // close if not
        if(*fdref >= 0)
        {
            close(*fdref);
        }
        // free resources
        delete fd;
        fd = nullptr;
    }
};

int main(void)
{
    FileActions f1("file.txt");
    actions_t act1 = 
    {
        {"read", 1},
        {"write", 1},
        {"read", 1},
    };
    f1.registerActions(act1);
    f1.executeActions();

    FileActions f2 = f1;
    actions_t act2 = 
    {
        {"close", 1},
    };
    f2.registerActions(act2);
    f2.executeActions();

    f1.executeActions();

    return 0;
}