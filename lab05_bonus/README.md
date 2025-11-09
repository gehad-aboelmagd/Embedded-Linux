
# My ```write``` syscall Implementation 🛠


### Description 📝

Functions like ```printf()```, ```dprintf()```, ... etc  use the ```write()``` system call under the hood. <br>

```write``` itself is a wrapper around a kernel interrupt; it passes required arguments to the kernal via pre-determined registers, then sends the interrupt signal to the kernal.<br>

This is what we are going to implement ourselves.

### Steps 👣
1. refer to any documentation about [Linux System Call Table](https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md#tables) and navigate to the required system call; ```write``` in our case, and investigate dedicated registers and which register should hold which argument:

* ```syscall : sys_write```
* ```%rax  : 1```
* ```%rdi	: unsigned int fd```	
* ```%rsi	: const char *buf```
* ```%rdx	: size_t count```

2. Implement your own syscall using assmebly lanaguae embedded into your C code; inline assembly, so to speak.

3. Test your functionality against simple input.
```
$ gcc main.c

$ ./a.out 
MyWrite>> Hello World
```