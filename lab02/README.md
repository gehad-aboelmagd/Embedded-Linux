
# Second Sheet Answers 💡

### Question (1)
Has already been implmented in main.c file

### Question (2)
1.
    ```
    $ sudo mv a.out /usr/local/bin/
    ```

2.
    ```
    $ a.out

    Element 10 is found at -1
    ```
    *Explanation:* /usr/local/bin directory is added to the PATH environment variable, so when moving the binary into this directoy, it is by default seen from any location; like any ordinary Linux command or executable.

### Question (3)
1. 
    ```
    $ cat /etc/shells 

    /bin/sh
    /usr/bin/sh
    /bin/bash
    /usr/bin/bash
    /bin/rbash
    /usr/bin/rbash
    /usr/bin/dash
    ```

2. 
    ```
    $ printenv
    ```

3. 
    ```
    $ echo $0

    bash
    ```

### Question (4)
```
$ echo \
```

Purpose of \ is to wirte a multiline command

### Question (5)
```
$ alias PrintPath="echo $PATH"
$ PrintPath

/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin:/HOME/Desktop/workspace

```
