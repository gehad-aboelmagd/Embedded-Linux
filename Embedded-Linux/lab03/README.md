# Lab 3: U-Boot 😋

### Part A

1.  A bootlaoder is a firmware flashed on a read-only memory used to boot the system once powered-on.  
(The CPU is hardwired to look at specific read-only address once powered-on).   

    > Booting means initializing essential hardware componenets (RAM, keyboard, ...etc.), reading a configuration file to decide which application the system should load (U-Boot, which is another bootloader or a direct Linux Image) and load that application into RAM.

2. Booting Sequence of RasperryPi
  * When we first power on rasberry pi, the graphic processor is the first thing to run  
  (the actual processor holds on the reset state).  
  * The graphic processor starts executing code from rasberry pi ROM(first-stage bootloader).  
  * This ROM modest code is intellignet enough to load bootcode.bin from sd-card.
  * Once bootcode.bin is loaded into memory(L2 cache), it starts initializing the system(DRAM)
  * bootcode.bin then loads start.elf from sd-card.
  * start.elf will read a couple of files from sd-card, which you can use to configure different aspects of your kernel.
  * start.elf will load the kernel image at 0x8000 address in memory, and only then will the actual processor be turned on.
  * If the application is UBoot(another yet bootloader), the UBoot will decide futher which application the rasperry pi should boot on.

3. Both U-Boot and Grub are designed for multi-boot options. Grub is used in the context of PCs to enable booting on different OS systems(Ubuntu or Windows). U-Boot is used in the context of embedded systems to enable booting on different applications(Linux Custom Image on SD Card, or remote server or even baremetal applicatoin)

4. Files that must be placed in the Rasberry Pi's boot partition within SD Card in order to boot U-Boot are:
  * bootcode.bin: initialize DRAM, and loads the start.elf into it.
  * start.elf: read configuration files among them is config.txt
  * config.txt: determines either the system will boot on a linux image or yet another bootloader.
  * uboot and its own dtb: necessary for fetching the image from a remote server.

5. Building and testing u-boot in qemu:  
  * move to the root directory of u-boot:
    ```
    $ cd u-boot/
    ```
  * write your specific u-boot configuration either directly to ```.config``` file or using menuconfig:
    ```
    $ make menuconfig
    ```
  * another easy way is to use a ready pre-written configuration:  
    * for rasberry pi:
    ```
    $ ls configs/ | grep rpi

    rpi_0_w_defconfig
    rpi_2_defconfig
    rpi_3_32b_defconfig
    rpi_3_b_plus_defconfig
    rpi_3_defconfig
    rpi_4_32b_defconfig
    rpi_4_acpi_defconfig
    rpi_4_defconfig
    rpi_arm64_defconfig
    rpi_defconfig

    $ make rpi_4_acpi_defconfig
    ```
    * or vexpress:
    ```
    $ ls configs/ | grep vexpress

    vexpress_aemv8a_juno_defconfig
    vexpress_aemv8a_semi_defconfig
    vexpress_aemv8r_defconfig
    vexpress_ca9x4_defconfig
    vexpress_fvp_bloblist_defconfig
    vexpress_fvp_defconfig

    $ make vexpress_ca9x4_defconfig
    ```
    * test u-boot against qemu:
    ```
    $ qemu-system-arm -M vexpress-a9 -kernel u-boot -nographic
    ```
    * exiting qemu CLI:  
    press ```CTRL+A```, release then pess ```x```


6. building u-boot for a physical rasberry pi
    ```
    $ ls configs/ | grep rpi

    rpi_0_w_defconfig
    rpi_2_defconfig
    rpi_3_32b_defconfig
    rpi_3_b_plus_defconfig
    rpi_3_defconfig
    rpi_4_32b_defconfig
    rpi_4_acpi_defconfig
    rpi_4_defconfig
    rpi_arm64_defconfig
    rpi_defconfig


    $ make rpi_arm64_defconfig

    $ make CROSS_COMPILE=aarch64-linux-gnu- -j$(nproc)
    ```

7. the file providing the hardware description for u-boot on rasberry-pi is the ```.dtb``` or Device Tree Binary. It is loaded by u-boot and passed to the kernel to decide which underlying hardware is there, hence how to configure it.

8. by passing ```--partscan``` option, we give the Linux kernel a hint to scan the partition table of the sd-card to create individual block devices for each partition.   
  For exmple:  ```/dev/loop20p1```, ```/dev/loop20p2```   
    ```
    $ sudo losetup -f --partscan --show sd.img 
    ```


### Part B
1. ```$ bdinfo``` command is used to list the underlying board information, for example: architecture,  Flash start address & size, DRAM start address & size, IP-Address, ethernet address, baud-rate ...etc. 

2. ```$ printenv``` command is used to print the u-boot environmental variables often saved in flash memory, unless configured in menuconfig to be saved on external sd-card. These variables may include: ```$arch```, ```$cpu```, ```$baudrate```, ```$bootcmd```

3. DRAM start address is the base address where DRAM starts, usually 0x8000000 for ARM architectures. The u-boot address itself is listed under ```relocaddr``` when running ```$bdinfo``` command under u-boot.

4. To list files from FAT partition:
    ```
    $ ls mmc 0:1

    652584   u-boot.bin
    52624   bootcode.bin
    125   config.txt
    7367   fixup.dat
    3027872   start.elf
    35322   bcm2710-rpi-3-b-plus.dtb

    ```
    
    To load a specific file into RAM, we first ensure a valid address to write to:
      ```
      $ echo $loadaddr

      0x40200000
      ```  

      ```
      $ fatload mmc 0:1 0x40200000 config.txt

      $ md 0x40200000

      40200000: 6e72656b 753d6c65 6f6f622d 69622e74  kernel=u-boot.bi
      40200010: 20230a6e 6974704f 6c616e6f 74756220  n.# Optional but
      40200020: 63657220 656d6d6f 6465646e 726f6620   recommended for
      40200030: 72657320 206c6169 736e6f63 3a656c6f   serial console:
      40200040: 616e650a 5f656c62 74726175 690a313d  .enable_uart=1.i
      40200050: 5f74696e 74726175 7561625f 31313d64  nit_uart_baud=11
      40200060: 30303235 696e690a 61755f74 635f7472  5200.init_uart_c
      40200070: 6b636f6c 3030333d 30303030 0000000a  lock=3000000....
      40200080: 00000000 00000000 00000000 00000000  ................
      40200090: 00000000 00000000 00000000 00000000  ................
      402000a0: 00000000 00000000 00000000 00000000  ................
      402000b0: 00000000 00000000 00000000 00000000  ................
      402000c0: 00000000 00000000 00000000 00000000  ................
      402000d0: 00000000 00000000 00000000 00000000  ................
      402000e0: 00000000 00000000 00000000 00000000  ................
      402000f0: 00000000 00000000 00000000 00000000  ................

      ```

5. To update u-boot banner, edit the "bootcmd value" under "Boot Options" under meunconfig:
    ```
    $ echo Welcome to Our-Boot-Intake 46
    ```
6. First, we need to save our commands into a file, and convert it to a format accepted by u-boot(special format for shell scripts)
    ```
    $ touch script.txt
    $ echo "echo Hello, world" > script.txt
    $ mkimage -A arm -n "custom command" -d script.txt custom_command.scr
    ```
  then, copy the ```.scr``` file into a virtual device(FAT or EXT4 partitions)
    
    ```
    geahd@arm => ls mmc 0:1
    18   script.txt
    90   custom_command.scr

    2 file(s), 0 dir(s
    ```
  load file into memory

    ```
    gehad@arm => load mmc 0:1 $loadaddr custom_command.scr
    90 bytes read in 4 ms (21.5 KiB/s)

    gehad@arm => md $loadaddr
    60100000: 56190527 80629834 6d53a369 1a000000  '..V4.b.i.Sm....
    60100010: 00000000 00000000 d6de44be 01060205  .........D......
    60100020: 74737563 63206d6f 616d6d6f 0000646e  custom command..
    60100030: 00000000 00000000 00000000 00000000  ................
    60100040: 12000000 00000000 6f686365 6c654820  ........echo Hel
    60100050: 202c6f6c 6c726f57 00000a64 00000000  lo, World.......
    60100060: 00000000 00000000 00000000 00000000  ................
    60100070: 00000000 00000000 00000000 00000000  ................
    60100080: 00000000 00000000 00000000 00000000  ................
    60100090: 00000000 00000000 00000000 00000000  ................
    601000a0: 00000000 00000000 00000000 00000000  ................
    601000b0: 00000000 00000000 00000000 00000000  ................
    601000c0: 00000000 00000000 00000000 00000000  ................
    601000d0: 00000000 00000000 00000000 00000000  ................
    601000e0: 00000000 00000000 00000000 00000000  ................
    601000f0: 00000000 00000000 00000000 00000000  ................

    ```

  finally, executing custom command using ```$source```  

    ```
    gehad@arm => source $loadaddr
    ## Executing script at 60100000
    Hello, World
    ```

