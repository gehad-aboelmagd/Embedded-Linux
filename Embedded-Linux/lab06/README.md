# Lab 6 : Kernel on top of u-boot 🐧

## 1️⃣ PART I (VEXPRESS)
### 1. Customizing linux kernel
```
$ git clone https://github.com/torvalds/linux.git
$ cd linux

$ export ARCH=arm
$ export CROSS_COMPILE=arm-linux-gnueabi-

$ make vexpress_defconfig
$ make V=1 zImage dtbs -j$(nproc)

$ ls arch/arm/boot/zImage 
arch/arm/boot/zImage 
$ ls arch/arm/boot/dts/arm/vexpress-v2p-ca9.dtb 
arch/arm/boot/dts/arm/vexpress-v2p-ca9.dtb 
```

### 2. Copying files into server root directory
```
$ sudo cp arch/arm/boot/zImage /srv/tftp/
$ sudo cp arch/arm/boot/dts/arm/vexpress-v2p-ca9.dtb /srv/tftp/
```

### 3. Running image on top of u-boot
```
$ sudo qemu-system-arm -M vexpress-a9 -m 512 -kernel u-boot -nic tap -net nic --nographic

***************************** gehad@linux => setenv ipaddr 192.168.1.2

***************************** gehad@linux => setenv serverip 192.168.1.1

***************************** gehad@linux => tftp $kernel_addr_r zImage
smc911x: detected LAN9118 controller
smc911x: phy initialized
smc911x: MAC 52:54:00:12:34:56
Using ethernet@3,02000000 device
TFTP from server 192.168.1.1; our IP address is 192.168.1.2
Filename 'zImage'.
Load address: 0x60100000
Loading: #################################################################
	 #################################################################
	 #################################################################
	 #################################################################
	 #################################################################
	 #################################################################
	 #################################
	 7.7 MiB/s
done
Bytes transferred = 6203600 (5ea8d0 hex)
smc911x: MAC 52:54:00:12:34:56

***************************** gehad@linux => tftp $fdt_addr_r vexpress-v2p-ca9.dtb
smc911x: detected LAN9118 controller
smc911x: phy initialized
smc911x: MAC 52:54:00:12:34:56
Using ethernet@3,02000000 device
TFTP from server 192.168.1.1; our IP address is 192.168.1.2
Filename 'vexpress-v2p-ca9.dtb'.
Load address: 0x60000000
Loading: #
	 2 MiB/s
done
Bytes transferred = 14329 (37f9 hex)
smc911x: MAC 52:54:00:12:34:56

***************************** gehad@linux => bootz $kernel_addr_r - $fdt_addr_r
Starting kernel ...

Kernel panic - not syncing: VFS: Unable to mount root fs on unknown-block(0,0)
CPU: 0 UID: 0 PID: 1 Comm: swapper/0 Not tainted 7.0.0-rc3+ #1 VOLUNTARY 
Hardware name: ARM-Versatile Express
Call trace: 
 unwind_backtrace from show_stack+0x10/0x14
 show_stack from dump_stack_lvl+0x54/0x68
 dump_stack_lvl from vpanic+0xfc/0x308
 vpanic from __do_trace_suspend_resume+0x0/0xa4
---[ end Kernel panic - not syncing: VFS: Unable to mount root fs on unknown-block(0,0) ]---

```

### 4. Resolving 1st panic (root file system)
```
****************************** gehad@linux => setenv bootargs root=/dev/mmcblk0p2

****************************** gehad@linux => setenv bootcmd "tftp $kernel_addr_r zImage; tftp $fdt_addr_r vexpress-v2p-ca9.dtb; bootz $kernel_addr_r - $fdt_addr_r"

****************************** gehad@linux => saveenv

****************************** gehad@linux => run bootcmd

Kernel panic - not syncing: No working init found.  Try passing init= option to kernel. See Linux Documentation/admin-guide/init.rst for guidance.
CPU: 0 UID: 0 PID: 1 Comm: swapper/0 Not tainted 7.0.0-rc3+ #1 VOLUNTARY 
Hardware name: ARM-Versatile Express
Call trace: 
 unwind_backtrace from show_stack+0x10/0x14
 show_stack from dump_stack_lvl+0x54/0x68
 dump_stack_lvl from vpanic+0xfc/0x308
 vpanic from __do_trace_suspend_resume+0x0/0xa4
---[ end Kernel panic - not syncing: No working init found.  Try passing init= option to kernel. See Linux Documentation/admin-guide/init.rst for guidance. ]---

```


### 5. Resolving 2nd panic (init process)
```
****************************** gehad@linux => setenv bootargs root=/dev/mmcblk0p2 rootwait rw init=init.out

****************************** gehad@linux => saveenv 

****************************** gehad@linux => run bootcmd

  #0: ARM AC'97 Interface PL041 rev0 at 0x10004000, irq 37
input: ImExPS/2 Generic Explorer Mouse as /devices/platform/bus@40000000/bus@40000000:motherboard-bus@40000000/bus@40000000:motherboard-bus@40000000:iofpga@7,00000000/10007000.kmi/serio1/input/input2
drm-clcd-pl111 10020000.clcd: [drm] DVI muxed to daughterboard 1 (core tile) CLCD
drm-clcd-pl111 10020000.clcd: [drm] initializing Versatile Express PL111
EXT4-fs (mmcblk0p2): mounted filesystem f6feafc5-a147-458b-91ae-c3ceba1ee06a r/w with ordered data mode. Quota mode: disabled.
VFS: Mounted root (ext4 filesystem) on device 179:2.
VFS: Pivoted into new rootfs
Freeing unused kernel image (initmem) memory: 1024K
Run init.out as init process
Hello, from init

```

💡 **Hint:** We may also set up file system on a remote server (network file system) and use NFS as communication protocol  
For your PC (server side):
```
$ sudo apt install nfs-kernel-server 
$ sudo vim /etc/exports
$ cat /etc/exports
/srv/nfs 192.168.1.2(rw,no_root_squash,no_subtree_check)

$ sudo exportfs -ra
$ sudo systemctl restart nfs-kernel-server
```
For vexpress (client side): it is already implemented within kernel code.
```
****************************** gehad@linux => setenv bootargs "root=/dev/nfs nfsroot=192.168.1.1:/srv/nfs nfsvers=3,tcp rootwait rw rootdelay=2 ip=192.168.1.2:::255.255.255.0:vexpress:eth0 init=init.out"

****************************** gehad@linux => saveenv 
Saving Environment to FAT... OK

****************************** gehad@linux => run bootcmd

IP-Config: Complete:
     device=eth0, hwaddr=52:54:00:12:34:56, ipaddr=192.168.1.2, mask=255.255.255.0, gw=255.255.255.255
     host=vexpress, domain=, nis-domain=(none)
     bootserver=255.255.255.255, rootserver=192.168.1.1, rootpath=
clk: Disabling unused clocks
ALSA device list:
  #0: ARM AC'97 Interface PL041 rev0 at 0x10004000, irq 37
Waiting 2 sec before mounting root device...
VFS: Mounted root (nfs filesystem) on device 0:15.
VFS: Pivoted into new rootfs
Freeing unused kernel image (initmem) memory: 1024K
Run init.out as init process
Hello, from init

```

💡 **Hint:** to compile ```init``` program, make sure it is statically linked if you haven't yet configured the directories of your file system where shared libs should reside.
```
$ arm-linux-gnueabi-gcc init.c -o init.out -static
```

## 2️⃣ PART II (Rasberry-Pi)
### 1. Compiling linux kernel
```
$ git clone https://github.com/raspberrypi/linux.git
$ cd linux

$  ls arch/arm64/configs/ | grep bcm
$ make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- bcm2711_defconfig
$ make -j

$ ls arch/arm64/boot/
dts  Image  Image.gz  install.sh  Makefile

$ ls arch/arm64/boot/dts/broadcom/ | grep bcm2837
bcm2837-rpi-3-a-plus.dtb
bcm2837-rpi-3-a-plus.dts
bcm2837-rpi-3-b.dtb
bcm2837-rpi-3-b.dts
bcm2837-rpi-3-b-plus.dtb
bcm2837-rpi-3-b-plus.dts
bcm2837-rpi-cm3-io3.dtb
bcm2837-rpi-cm3-io3.dts
bcm2837-rpi-zero-2-w.dtb
bcm2837-rpi-zero-2-w.dts
```

### 2. Copying files into sd-card
```
$ sudo cp arch/arm64/boot/Image ../rpi-img/boot
$ sudo cp arch/arm64/boot/dts/broadcom/bcm2710-rpi-3-b-plus.dtb ../rpi-img/boot
```
### 3. Running image on top of u-boot
```
$ qemu-system-aarch64 -M raspi3b -m 1024 -cpu cortex-a53 -kernel u-boot.bin -dtb arch/arm/dts/bcm2837-rpi-3-b-plus.dtb -serial null -serial stdio -monitor null -sd ../rpi-img/sd.img

******************************* gehad@u-boot => setenv bootargs 'console=tty1 console=ttyAMA0,115200 earlyprintk debug'                               

******************************* gehad@u-boot => setenv bbootcmd 'fatload mmc 0:1 $kernel_addr_r Image; fatload mmc 0:1 $fdt_addr_r bcm2710-rpi-3-b-plus.dtb; booti $kernel_addr_r - $fdt_addr_r;'


******************************* gehad@u-boot => saveenv
Saving Environment to FAT... OK

******************************* gehad@u-boot => run bootcmd

```
<img width="873" height="621" alt="Screenshot from 2026-03-26 01-22-24" src="https://github.com/user-attachments/assets/bacea6a7-0dd8-4300-8f6a-13ba05180b11" />


### 4. Resolving 1st panic (rootfs)
```
$ qemu-system-aarch64 -M raspi3b -m 1024 -cpu cortex-a53 -kernel u-boot.bin -dtb arch/arm/dts/bcm2837-rpi-3-b-plus.dtb -serial null -serial stdio -monitor null -sd ../rpi-img/sd.img

******************************* gehad@u-boot => setenv bootargs 'console=tty1 console=ttyAMA0,115200 earlyprintk debug root=/dev/mmcblk0p2 rootwait rw'

******************************* gehad@u-boot => saveenv 

******************************* gehad@u-boot => run bootcmd 

```
<img width="801" height="540" alt="Screenshot from 2026-03-26 01-26-23" src="https://github.com/user-attachments/assets/99d4676e-5b05-4c4f-9743-7e7057261ded" />


### 5. Resolving 2nd panic (init process)

Edit the init program, let ```init.c``` file:
```
int main()
{
        while(1);
}
```

Compile using appropriate compiler:
```
$ aarch64-linux-gnu-gcc init.c -o init.out -static

$ file init.out 
init.out: ELF 64-bit LSB executable, ARM aarch64, version 1 (GNU/Linux), statically linked, BuildID[sha1]=0110244c9cc406ad32cb52c1217caad75b09488a, for GNU/Linux 3.7.0, not stripped
```

Copy to sd-card mounted rootfs partition:
```
$ sudo cp init.out ../rpi-img/rootfs
```

Edit the ```bootargs``` with the new update for initi process:
```
$ qemu-system-aarch64 -M raspi3b -m 1024 -cpu cortex-a53 -kernel u-boot.bin -dtb arch/arm/dts/bcm2837-rpi-3-b-plus.dtb -serial null -serial stdio -monitor null -sd ../rpi-img/sd.img 

******************************* gehad@u-boot => setenv bootargs console=tty1 console=ttyAMA0,115200 earlyprintk debug root=/dev/mmcblk0p2 rootwait rw init=init.out

******************************* gehad@u-boot => saveenv
Saving Environment to FAT... OK

******************************* gehad@u-boot => run bootcmd
```
  
<img width="801" height="540" alt="Screenshot from 2026-03-26 01-56-27" src="https://github.com/user-attachments/assets/f0ed0b1a-ff3c-45f9-bcc6-64462ecc06af" />
