# Lab 3 (Network Booting) 😋

### Part B (continue)

#### 7. a. setting up TFTP server on my PC:  

First, install TFTP application(protocol):
  ```
  $sudo apt install tftpd-hpa 
  ```

Then, configure TFTP protocol defaults:
  ```
  $systemctl status tftpd-hpa.service
  /usr/sbin/in.tftpd --listen --user tftp --address :69 --secure /srv/tftp

  $cat /etc/default/tftpd-hpa 
  # /etc/default/tftpd-hpa

  TFTP_USERNAME="tftp"
  TFTP_DIRECTORY="/srv/tftp"
  TFTP_ADDRESS=":69"
  TFTP_OPTIONS="--secure"

  $sudo vim /etc/default/tftpd-hpa 

  $systemctl status tftpd-hpa.service
  /usr/sbin/in.tftpd --listen --user tftp --address :69 --secure --create /srv/tftp

  $cat /etc/default/tftpd-hpa 
  # /etc/default/tftpd-hpa

  TFTP_USERNAME="tftp"
  TFTP_DIRECTORY="/srv/tftp"
  TFTP_ADDRESS=":69"
  TFTP_OPTIONS="--secure --create"

  $systemctl restart tftpd-hpa.service
  ```

Hint: If you don't have a /srv/tftp folder, setup one:
  ```
  $sudo mkdir /srv/tftp
  $sudo chown tftp:tftp /srv/tftp
  $sudo chmod 755 /srv/tftp
  ```

  Finally, run your TFTP server:
  ```
  $in.tftpd
  ```

#### b. Configuring network on target(Qemu):  

First, enable virtaul ethernet interface for the targe:  
  ```
  $ sudo qemu-system-arm -M vexpress-a9 -kernel u-boot -nographic -nic tap -net nic
  ```  
Then, set an ip-address for you tap interface:
  ```
  $sudo ip a add 192.168.100.1/24 dev tap0
  ```
Now, setup ip-address, server-id on the client side(u-boot):
  ```
  $setenv ipaddr 192.168.100.2
  
  $setenv serverip 192.168.100.1
  
  $ping $serverip
  smc911x: detected LAN9118 controller
  smc911x: phy initialized
  smc911x: MAC 52:54:00:12:34:56
  Using ethernet@3,02000000 device
  smc911x: MAC 52:54:00:12:34:56
  host 192.168.100.1 is alive

  $tftp $loadaddr file.txt
  smc911x: detected LAN9118 controller
  smc911x: phy initialized
  smc911x: MAC 52:54:00:12:34:56
  Using ethernet@3,02000000 device
  TFTP from server 192.168.100.1; our IP address is 192.168.100.2
  Filename 'file.txt'.
  Load address: 0x60100000
  Loading: #
    7.8 KiB/s
  done
  Bytes transferred = 33 (21 hex)
  smc911x: MAC 52:54:00:12:34:56

  $md $loadaddr
  60100000: 73696874 6c696620 65622065 676e6f6c  this file belong
  60100010: 6f742073 74667420 65732070 72657672  s to tftp server
  60100020: 0000000a 00000000 00000000 00000000  ................
  60100030: 00000000 00000000 00000000 00000000  ................
  60100040: 00000000 00000000 00000000 00000000  ................
  60100050: 00000000 00000000 00000000 00000000  ................
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

#### 8. ```run``` vs. ```go``` commands:
The ```run``` command is use to run a script stored in a variable:
  ```
  $setenv myVar "echo Hello, world;"

  $run myVar 
  Hello, world
  ```

The command ```go``` is used to start an application that has already been loaded into RAM:
  ```
  $go <address>
  ```