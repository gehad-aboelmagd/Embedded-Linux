# Lab 1 : Yocto-Project Hello World

### Description:
This lab aims to building a minimal rpi3b+ linux image using yocto project. All we have to do is cloning the pre-built raspberrypi meta and configure the yocto project to use the meta.

### Requirements:
Build Host Packages
```
sudo apt-get install build-essential chrpath cpio debianutils diffstat file gawk gcc git iputils-ping libacl1 locales python3 python3-git python3-jinja2 python3-pexpect python3-pip python3-subunit socat texinfo unzip wget xz-utils zstd
```

Poky 
```
$ git clone https://github.com/yoctoproject/poky.git --branch=scarthgap
```

Raspberrypi Meta
```
$ git clone  https://git.yoctoproject.org/meta-raspberrypi --branch=scarthgap
```

### Steps
1. Initializing build environment
```
$ source poky/oe-init-build-env build-rpi
```

2. Configuring target machine
```
$ ls meta-raspberrypi/conf/machine/ | grep raspberrypi3-64.conf
raspberrypi3-64.conf

$ vim build-rpi/conf/local.conf 
#MACHINE ??= "qemux86-64"
MACHINE = "raspberrypi3-64"

DL_DIR = "${TOPDIR}/downloads"
SSTATE_DIR = "${TOPDIR}/sstate-cache"
TMPDIR = "${TOPDIR}/tmp"
```

3. Running bitbake against ```core-image-minimal``` recipe
```
$ bitbake core-image-minimal
```

4. Confirming output
```
$ ls build-rpi/tmp/deploy/images/raspberrypi3-64/ | grep core-image-minimal

core-image-minimal.env
core-image-minimal-raspberrypi3-64.rootfs-20260410014244.ext3
core-image-minimal-raspberrypi3-64.rootfs-20260410014244.manifest
core-image-minimal-raspberrypi3-64.rootfs-20260410014244.spdx.tar.zst
core-image-minimal-raspberrypi3-64.rootfs-20260410014244.tar.bz2
core-image-minimal-raspberrypi3-64.rootfs-20260410014244.testdata.json
core-image-minimal-raspberrypi3-64.rootfs-20260410014244.wic.bmap
core-image-minimal-raspberrypi3-64.rootfs-20260410014244.wic.bz2
core-image-minimal-raspberrypi3-64.rootfs.ext3
core-image-minimal-raspberrypi3-64.rootfs.manifest
core-image-minimal-raspberrypi3-64.rootfs.spdx.tar.zst
core-image-minimal-raspberrypi3-64.rootfs.tar.bz2
core-image-minimal-raspberrypi3-64.rootfs.testdata.json
core-image-minimal-raspberrypi3-64.rootfs.wic.bmap
core-image-minimal-raspberrypi3-64.rootfs.wic.bz2
```

5. Preparing SD-Card
```
sudo bzcat core-image-minimal-raspberrypi3-64.rootfs.wic.bz2 | sudo dd of=/dev/sdb bs=4M status=progress conv=fsync
```