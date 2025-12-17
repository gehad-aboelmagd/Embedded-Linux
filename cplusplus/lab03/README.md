
# Exposing the GPIO Driver in CPP && for Linux-Based Embedded Targets (Raspberry Pi) 


### Purpose 🤔
To get the gpio driver work targets running Linux kernel rather baremetal.

### Steps 👣

1.  First, you need to acquire the proper access rights over some kernel files.
```
$ sudo chmod u+rwx /sys/class/gpio/export
$ sudo chmod u+rwx /sys/class/gpio/unexport 
```

2. Next, run the example code to test GPIO pins functionality 
Outupt
```
$ g++ *.cpp
$ sudo ./a.out
``` 
Make sure to run the test using sudo; in privilaged state.

### Outupt 💡
```
GPIO initialized successfully
direction set successfully
value set successfully
GPIO initialized successfully
direction set successfully
value read successfully
file unexported succcessfully
file unexported succcessfully
```