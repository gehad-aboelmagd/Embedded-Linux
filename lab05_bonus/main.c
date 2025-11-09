#include <stdio.h>

int my_write(long fd, const char *buff, long size)
{
    long ret;
    long syswrite_id = 1;   // x86_64

    asm(
        "mov %1, %%rax \n"
        "mov %2, %%rdi \n"
        "mov %3, %%rsi \n"
        "mov %4, %%rdx \n"

        "syscall \n"

        "mov %%rax, %0"

        :"=r" (ret)
        :"r" (syswrite_id), "r"(fd), "r"(buff), "r"(size)
        : "rax", "rdi", "rsi", "rdx", "memory"

    );

    return ret;    
}

int main() {
    int fd = 1;     // stdout
    char buff[] = "MyWrite>> Hello World\n";
    int count = sizeof(buff);

    my_write(fd, buff, count);

    return 0;
}