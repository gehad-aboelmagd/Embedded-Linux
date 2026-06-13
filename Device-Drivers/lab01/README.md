# Kernel Module 🧩
This module is intended to control GPIO pin on RPI, using the procfs as the mechanism to forward set & get commands to the kernel.

1. compiling the module
   ```
   $ make all
   ```

2. inserting the module into the kernel space
   ```
   $ sudo insmod brightness.ko
   ```

3. setting gpio pin value 
   ```
   $ cat 1 > /proc/brightness
   ```

4. getting the gpio pin value
   ```
   $ echo /proc/brightness
   ```
5. removing the module from kernel code
   ```
   $ sudo rmmod brightness
   ```

https://github.com/user-attachments/assets/433db1f6-0e2a-4e81-a8f5-82e30651e038

