# Lab 4 : Baremetal Application on top of u-boot

#### Development phase:
1. writing main logic (configuring, setting and clearing GPIO pin)
2. writing startup code (to initialize SP and jump to main)
3. writing linker script (to collect different object files sections and define application starting point)

#### Compiling phase:
1. using cross-compiler tool chain:
  ```
  $ aarch64-linux-gnu-gcc -T linker.ld     -nostdlib     -ffreestanding     -nostartfiles     -nodefaultlibs     -Wl,-Bstatic     -Wl,--no-dynamic-linker     -Wl,--build-id=none     src/start.s src/main.c     -o build/app.elf
  ```

2. generating proper format for rpi:
  ```
  $ aarch64-linux-gnu-objcopy -O binary build/app.elf build/kernel.bin
  ```

#### Porting Phase:  
1. Simply, copying kernel.bin file into physical sd-card.
2. Booting the rpi, launching minicom alongside:
  ```
  $ sudo minicom -b 115200 -D /dev/ttyUSB0
  ```
3. Loading the binary from sd-card into RAM
  ```
  **************************************** Hello, Gehad => fatload mmc 0:1 $kernel_addr_r kernel.bin
864 bytes read in 2 ms (421.9 KiB/s)
  ```

4. Running the binary
  ```
**************************************** Hello, Gehad => go $kernel_addr_r
## Starting application at 0x00080000 ...
  ```

https://github.com/user-attachments/assets/5115abce-7716-4967-8050-0af00261bd57


