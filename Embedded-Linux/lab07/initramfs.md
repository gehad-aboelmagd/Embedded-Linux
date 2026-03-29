# initramfs

#### Customizing rootfs for ramfs init running
```
$ mkdir init-ramfs & cd init-ramfs
$ mkdir bin sbin sys proc dev tmp usr srv lib etc

$ sudo rsync -av /path/to/busybox/_install/bin init-ramfs/bin
$ sudo rsync -av /path/to/busybox/_install/sbin/init init-ramfs/sbin

$ touch etc/initramfs
$ vim etc/initramfs

::sysinit:/bin/echo 'Hello, from initramfs'
::sysinit:/bin/mount -t proc plapla /proc
::sysinit:/bin/mount -t sysfs plapla /sys
::sysinit:/bin/mount -t tmpfs plapla /tmp

::wait:/lib/modules/kernel/custom_uart.ko

::askfirst:/bin/sh

```

#### Archiving & compressing ramfs
```
$ find . | cpio -H newc -o --owner root:root > initramfs.cpio
$ ls
bin  dev  etc  initramfs.cpio  lib  proc  sbin  srv  sys  tmp  usr

$ gzip initramfs.cpio
$ ls
bin  dev  etc  initramfs.cpio.gz  lib  proc  sbin  srv  sys  tmp  usr

$ mkimage -n 'Ramdisk Image' -A arm64 -O linux -T ramdisk  -d initramfs.cpio.gz initramfs
$ls
bin  etc        initramfs.cpio.gz  proc  srv  tmp
dev  initramfs  lib                sbin  sys  usr

$ file initramfs
initramfs: u-boot legacy uImage, Ramdisk Image, Linux/ARM 64-bit, RAMDisk Image (gzip), 2949923 bytes, Sun Mar 29 11:01:26 2026, Load Address: 00000000, Entry Point: 00000000, Header CRC: 0X8696C502, Data CRC: 0X73443EA9
```

#### Copying initramfs image to sd-card boot partition
```
$ sudo losetup --partscan --show -f rpi-img/sd.img 
$ sudo mount /dev/loop23p1 rpi-img/boot/

$ sudo cp ram-rootfs/initramfs rpi-img/boot/
$ sync
```

#### Booting kernel with initramfs
```
$ qemu-system-aarch64 -M raspi3b -m 1024 -cpu cortex-a53 -kernel u-boot.bin -dtb arch/arm/dts/bcm2837-rpi-3-b-plus.dtb -serial null -serial stdio -monitor null -sd ../rpi-img/sd.img 

******************************* gehad@u-boot => setenv bootargs 'coherent_pool=1M 8250.nr_uarts=1 snd_bcm2835.enable_headphones=0 cgroup_disable=memory console=ttyS0,115200 earlyprintk debug root=/dev/mmcblk0p2 rootwait rw rdinit=/sbin/init init=/sbin/init'

******************************* gehad@u-boot => settenv bootcmd 'fatload mmc 0:1 $kernel_addr_r Image; fatload mmc 0:1 $fdt_addr_r bcm2710-rpi-3-b-plus.dtb; fatload mmc 0:1 $ramdisk_addr_r initramfs; booti $kernel_addr_r $ramdisk_addr_r $fdt_addr_r;'

******************************* gehad@u-boot => saveenv

******************************* gehad@u-boot => run bootcmd 
```

#### Demo

https://github.com/user-attachments/assets/d1cfb532-3236-4a91-ad2f-fb312711152b

