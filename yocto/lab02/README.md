# Lab 2 : Building a Custom Recipe

### Description:
Fetching, compiling and packing a static library using a custom recipe.

### Steps:
1. creating a bitbake layer and adding it to ```bblayers.conf```
```
$ bitbake-layers create-layer meta-math
$ bitbake-layers add-layer meta-math
```
2. preparing source files: ```math.h```, ```math.c```
3. writing recipe file ```math_0.1.bb```
4. building recipe using bitbake
```
$ bitbake math
```
5. confirming build output does exist
```
$ tree build-qemuarm64/tmp/work/cortexa57-poky-linux/math/0.1/image/
build-qemuarm64/tmp/work/cortexa57-poky-linux/math/0.1/image/
└── usr
    ├── include
    │   └── math.h
    └── lib
        └── libmath.a

4 directories, 2 files
```