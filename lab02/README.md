
# Megrating CapsLock App from structured C to object-oriented C++ 


### Code Structure ✒️📑
* ```CapsLock``` class with private data representing encapsulation.
* ```CapsLockON```, ```CapsLockOFF``` methods represinting abstraction.


### Instantiation 🧔 🧑

All you need to do to instantiate an object from the CapsLock is to pass the path to the system file repsonsibel for handling CapsLock State.
```
CapsLock cap(path);
```
Then go ahead, and use CapsLockON(), CapsLockOFF() methods as much as you like.
```
cap.CapsLockON();
```
```
cap.CapsLockOFF();
```

### Hint 💡
Dont't forget to update access to CapsLock File to be executatble
```
$ chmod +x "file-path"
``` 
Dont't forget to run your executatble using sudo
```
$ sudo ./a.out
```