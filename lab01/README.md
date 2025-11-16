
# Updating C++ Code to make it compile using either C/C++ compiler 🛠


### Porblem 🤯

C++ is considered as a superset of the C programming; which means some language-specific features aren't understood by the C compiler. For example, if you try to compile the following line usign C compiler:
```
auto x = 4;
error: type defaults to 'int' in declaration of 'x'
```
You will get a compilation error raised !!

### Tackling 💡

Here comes the power of the C++ predefined macro : ```__cplusplus```. If the compilation is done using C++ compiler, then it will be identified; otherwise it will be undefined.

So, wherever we have C++ specific feature, we could wrap it within the ```#if #endif``` block to flag it is only compiled while using ```g++```

### Steps 👣
* write your logic once, make it adaptable towards different compilers
* compile using C compiler and test for the output
```
$ gcc main.cpp -o c.out
$ ./c.out
```
* compile using C++ compielr and test for the output
```
$ g++ main.cpp -o cpp.out
$ ./cpp.out
```
