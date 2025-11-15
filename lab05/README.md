
# Fifth Sheet Answers ✍🏼

### Description 📝
*This lab is to visualize the concept of interprocess communication, or IPC:*
> * we let a process create and attach a shared data memory.
> * the creator process will write its data, or message on the allocated memory.
> * after finishing execution, the user process is supposed to launch.
> * this process will get access on the same memory to read the message.
> * based on message, the user process will take some action.

*How to compile creator process*
```
$ gcc waiter.c -o waiter.out
```
*How to run creator process*
```
$ ./waiter.out
```
*OUTPUT*
```
Memory ID created successfully: 524312
Memory assigned successfully
successfully write to shared memeory: e
```

*How to compile user process*
```
$ gcc cooker.c -o cooker.out
```
*How to run user process*
```
$ ./cooker.out
```
*OUTPUT*
```
Memory ID created successfully: 524312
Memory assigned successfully
Your egg dish is ready
```

### Important Tip 💡
*to guarantee memory allocated is freed and returned back to the OS, you should always run the user process after the creater one .<br>
Alternatively, you may user our shell script.*
```
$ chmod +x script.sh 
$ ./script.sh
```