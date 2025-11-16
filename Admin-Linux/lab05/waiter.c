#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

#define KEY 1234
#define BYTES 100

int main()
{
    int id;
    char *ptr;

    id = shmget(KEY, BYTES, IPC_CREAT | 0666);
    if(id == -1) 
    {
        perror("Failed to create shared data segment\n");
        return 1;
    }
    else 
    {
        printf("Memory ID created successfully: %d\n", id);
    }


    ptr = (char *)shmat(id, NULL, 0);
    if(ptr == (char *)(-1)) 
    {
        perror("Failed to attach the shared data segment\n");
        return 1;
    }
    else 
    {
        printf("Memory assigned successfully\n");
    }

    
    ptr[0] = 'e';
    printf("successfully write to shared memeory: %s\n", ptr);

    shmdt(ptr);
    // printf("Now value is: %s\n", ptr);
    // // Segmentation fault (core dumped)

    return 0;
}