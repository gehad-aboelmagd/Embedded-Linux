
# Third Sheet Answers ⌨️

### Description 📝
*This demo is to control the functionality of the capslock key. An app is supposed to take one argument:*
> * by giving it 1, the key LED should turn on
> * by giviing it 0, the key LED should turn off
> * other forms of inputs should be ignored.

*How to compile your app <br>*
```
$ gcc main.c -o capslock
```
*How to run your app <br>*
```
$ ./capslock 0
```
*OR*
```
$ ./capslock 1
```

### Important Tip 💡
*To have your app running, you should update the capslock file permission:*
```
$ sudo chmod o+w /sys/devices/platform/i8042/serio0/input/input3/input3::capslock/brightness
```
