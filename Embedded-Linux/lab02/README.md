# Lab 2
1. 

    ```
    $ touch sd.img

    $ du sd.img 
    0       sd.img

    $ dd if=/dev/zero of=sd.img bs=1M count=1024
    1024+0 records in
    1024+0 records out
    1073741824 bytes (1.1 GB, 1.0 GiB) copied, 11.6096 s, 92.5 MB/s
    ```

2. 
    MBR is an old partitioning system which is capable to handle up to 2T of disk space, with maximum of four primary partitions, often used with ```fdisk``` command.  
    GPT, on the other hand, is the more modern type where it works with modern BIOS and has no limitations regarding disk space or number of partitions, often used for ```gdisk``` command.

3. FAT16 : used with small capacity sd cards, maximum disk size of 2GB, doesn't support file permissions  
   FAT32 : used with modern sd cards, maximum disk size of 2TB, doesn't support file permissions  
   EXT4  : used for internal drives, supports huge file size and disk size, supports file permissions

4. 

5. loop device is a mechanism to use a regular file as block device(one with a file system)  
    a. command to create a loop device
    ```
    $losetup -f --partscan --show sd.img
    ```
    b. command to list all loop devices
    ```
    $losetup -l
    ```
    c. command to detach a (Mounted) loop device
    ```
    sudo losetup -d /dev/loop19
    ```

6. current loop devices limit
    ``` 
    losetup -l
    ```
    ```
    lsblk -f
    ```
    ```
    cat /sys/module/loop/parameters/max_loop

    ```

7. by editing the ```/etc/default/grub``` file, adding ```max_loop=n``` to the existing parameters. 

8. 
    ```
    $sudo losetup -f --partscan --show sd.img 
    ```

9. 
    ```
    $mkfs.vfat -F 16 -n boot /dev/loop19p1 
    mkfs.ext4 -L rootfs /dev/loop19p2
    ```

10. 
    The ```mount``` command is used to atttach a file system on a storage device to a directory, called as mount point so that it can be accessed.  
    ```
    $mount <device> <directory>
    ```

    The ```unmount``` command on the other hand, is used to safely deattach the mounted device in prepration for removal(USB for example)  
    ```
    $unmount <directory>
    ```

11. 

| block device  | character device |
| ------------- |:-------------:|
| read/write data in a fixed-size blocks | data is treated as continous stream of bytes |
| access data in random access           | data access is sequentailly                  |
| can be mounted                         | cannot be mounted                            |

12. ```
    $mount /dev/loop19p1 boot

    $mount /dev/loop19p2 rootfs
    ```