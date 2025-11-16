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


    // printf("%d\n", ptr[0]);

    switch (ptr[0])
    {
    case '\0':
        printf("Please, make sure to provide an order!\n");
        break;
    case 'e':
        printf("Your egg dish is ready\n");
        break;
    case 't':
        printf("Your turkey dish is ready\n");
        break;
    case 's':
        printf("Your salad dish is ready\n");
        break;
    default:
        break;
    }
    
    shmdt(ptr);
    shmctl(id, IPC_RMID, NULL);

    // printf("%s\n", ptr);
    // // Segmentation fault (core dumped)

    return 0;
}