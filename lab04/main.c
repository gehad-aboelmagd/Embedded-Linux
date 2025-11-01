
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd, state;
	if(argc < 2)
	{
		printf("Please Enter CapsLock State!\n");
	}
	else
	{
		fd = open("/sys/devices/platform/i8042/serio0/input/input3/input3::capslock/brightness", O_RDWR);
        if (fd == -1)
        {
			perror("Error opening file");
        }
        else
        {
			if(strlen(argv[1])==1 && strcmp(argv[1], "0")==0)
			{
				dprintf(fd, "0");
			}
			else if(strlen(argv[1])==1 && strcmp(argv[1], "1")==0)
			{
				dprintf(fd, "1");
			}
			else
			{
				printf("Please, enter either 0 or 1\n");
			}
			close(fd);
		}

	}

	return 0;
}
