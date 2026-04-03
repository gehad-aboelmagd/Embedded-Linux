# Lab 8 : Dual rootfs 🎭

### Step 0: Requirements:
* kernel booting and loading ```initramfs```
* ```initramfs``` initializing system
* user is prompted to choose which partition to mount as rootfs
* system switching root to the chosen partition, continuing execution from there...

### Step 1: Setting up sd-card

* resizing rootfs partition & adding an extra partition on the freed space:
```
$ cfdisk sd.img
```
<img width="816" height="564" alt="Screenshot from 2026-04-02 17-38-13" src="https://github.com/user-attachments/assets/feb57fa9-220a-4103-8b34-f6aa6db071d5" />


* formatting both resized & new-added partitions:
```
echo setting up a loop device...
LOOP_DEV=$(sudo losetup --find --show --partscan ~/Desktop/bootloader/rpi-img/sd.img)
echo "Loop device assigned: $LOOP_DEV"

LOOP_DEV_P1=${LOOP_DEV}p1
LOOP_DEV_P2=${LOOP_DEV}p2
LOOP_DEV_P3=${LOOP_DEV}p3

# echo setting up/formatting FAT16 for p1...
# sudo mkfs.vfat -F 16 $LOOP_DEV_P1

echo setting up/formatting EXT4 for p2...
sudo mkfs.ext4 $LOOP_DEV_P2

echo setting up/formatting EXT for p3...
sudo mkfs.ext4 $LOOP_DEV_P3
```

* setting up rootfs
```
$ echo mounting partitinos...
$ sudo mount $LOOP_DEV_P1 ~/Desktop/bootloader/rpi-img/boot
$ sudo mount $LOOP_DEV_P2 ~/Desktop/bootloader/rpi-img/rootfs1
$ sudo mount $LOOP_DEV_P3 ~/Desktop/bootloader/rpi-img/rootfs2

$ cd rpi-img
$ sudo rsync -av ../busybox-ramfs rootfs1
$ sudo rsync -av ../busybox-ramfs rootfs2

$ sync
```

* customizing inittab 
```
$ sudo vim rootfs1/etc/inittab
::sysinit:echo Hello, form parition1
::askfirst:/bin/sh

$ sudo vim rootfs2/etc/inittab
::sysinit:echo Hello, form parition2
::askfirst:/bin/sh
```

### Step 2: Setting up init script
```
#!/bin/sh

# This script runs as PID 1
echo "Initramfs starting..."

# Mount necessary filesystems
mount -t proc proc /proc
mount -t sysfs sysfs /sys
mount -t devtmpfs devtmpfs /dev

# prompting user to select partition
echo "welcome to dual-boot demo :)"
echo "select a partition to boot on(valid options are 2,3): "
read partition
if [ "$partition" = "2" ]; then
	echo "proceeding with partition 2..."
elif [ "$partition" = "3" ]; then
	echo "proceeding with partition 3..."
else
	echo "invalid partition :("
	exec /bin/sh
fi

# Mount the real root
mkdir -p /mnt/root
mount /dev/mmcblk0p${partition} /mnt/root

# Mount virtual filesystems on real root
mount -t proc proc /mnt/root/proc
mount -t sysfs sysfs /mnt/root/sys
mount -t devtmpfs devtmpfs /mnt/root/dev

# Switch to real root
exec switch_root /mnt/root /sbin/init
```

**Hint 💡:** Make sure to fulfill the fulling conditions to have ```$ switch_root /newroot /sbin/init ```   working:
1. Executing as PID 1   
> switch_root must be the final action of the init script and must run as PID 1.  
If you are running it from a rescue shell or shell script, it will fail.
2. ```newroot``` is a Mount Point, not just a regular directory.
3. Target init exists, ```/newroot/sbin/init``` for example.
4. Mandatory Directories: ```/proc```, ```/sys```, and ```/dev``` are mounted or exist in new root filesystem ```/newroot```

### Step 3: Setting up ```initramfs```

```
$ mkdir initramfs & cd initramfs 
$ sudo rsync -av ../busybox-ramfs .

$ sudo vim init.sh

$ sudo chmod +x init.sh

$ find . | cpio -o -H newc | gzip > ../initramfs.cpio.gz 
$ cd ..
$ mkimage -A arm -O linux -T ramdisk -d initramfs.cpio.gz rdinit 
$ sudo cp rdinit rpi-img/boot
$ sync
```

### Step 4: running qemu
```
$ qemu-system-aarch64 -M raspi3b -m 1024 -cpu cortex-a53 -kernel u-boot.bin -dtb arch/arm/dts/bcm2837-rpi-3-b-plus.dtb --serial null -serial stdio -monitor null -sd ../rpi-img/sd.img 

******************************* gehad@u-boot => setenv bootargs 'coherent_pool=1M 8250.nr_uarts=1 snd_bcm2835.enable_headphones=0 cgroup_disable=memory console=ttyS0,115200 earlyprintk debug root=/dev/mmcblk0p2 rootwait rw rdinit=init.sh init=/sbin/init'

******************************* gehad@u-boot => saveenv 
Saving Environment to FAT... OK

******************************* gehad@u-boot => run bootcmd 
```

### Demo

https://github.com/user-attachments/assets/8a807e16-52ca-4f11-9eeb-727f9017bde3
