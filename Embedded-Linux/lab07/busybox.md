# Busybox 🧰

#### Installing busybox
```
$ git clone https://github.com/mirror/busybox.git
$ cd busybox
```

#### Customizing busybox for rpi-3b+
```
$ make CROSS_COMPILE=aarch64-linux-gnu- defconfig
$ make CROSS_COMPILE=aarch64-linux-gnu- menuconfig
```

options: 
1. Enable Settings-> Build Options -> Build Static binary
2. Set Settings -> Build Options -> Cross Compiler prefix : ```aarch64-linux-gun-```
3. Disable Settings -> SHA1: Use hardware accelerated instructions
4. Disable Settings -> SHA256: Use hardware accelerated instructions
 
#### Compile and install symbolic links
```
$ make CROSS_COMPILE=aarch64-linux-gnu- -j$(nproc)
$ make CROSS_COMPILE=aarch64-linux-gnu- install
$ ls _install
bin  linuxrc  sbin  usr
```

#### Occupying rootfs
```
$ cd /path/to/rootfs
$ mdkir -p bin sbin lib sys proc dev tmp etc srv usr/bin usr/sbin usr/lib usr/include
$ rsync -av /path/to/busybox/_install/* . 
$ rsync -av /path/to/x-tools/aarch64-rpi3-linux-gnu/aarch64-rpi3-linux-gnu/sysroot/* .
$ touch etc/inittab etc/hostname
``` 

#### Minimal ```inittab```
```
::sysinit:/bin/mount -t proc proc /proc
::sysinit:/bin/mount -t sysfs sysfs /sys
::sysinit:/bin/mount -t devtmpfs devtmpfs /dev
::sysinit:/bin/mount -t tmpfs tmpfs /tmp

::askfirst:/bin/sh

::ctrlaltdel:/sbin/reboot

::shutdown:/bin/umount -a -r
```

#### Running on qemu
```
$ qemu-system-aarch64 -M raspi3b -m 1024 -cpu cortex-a53 -kernel u-boot.bin -dtb ../rpi-firmware/custom-uboot/bcm2837-rpi-3-b-plus.dtb -serial null -serial stdio -monitor null -sd ../rpi-img/sd.img 

******************************* gehad@u-boot => printenv bootargs 
bootargs=coherent_pool=1M 8250.nr_uarts=1 snd_bcm2835.enable_headphones=0 cgroup_disable=memory console=ttyS0,115200 earlyprintk debug root=/dev/mmcblk0p2 rootwait rw init=/sbin/init

******************************* gehad@u-boot => printenv bootcmd 
bootcmd=fatload mmc 0:1 $kernel_addr_r Image; fatload mmc 0:1 $fdt_addr_r bcm2710-rpi-3-b-plus.dtb; booti $kernel_addr_r - $fdt_addr_r;

******************************* gehad@u-boot => run bootcmd 
```

#### Demo (qemu)
https://github.com/user-attachments/assets/34a01444-12b5-45b1-b1d8-ba7ab38206e6
