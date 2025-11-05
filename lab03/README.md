# Third Sheet Answers 🧠

### Question (1)

*When a new terminal is opened, it is on the same working directory of the parent bash, plus, we can echo both ```$HELLO``` and ```$LOCAL``` variables created in the parent bash; they get inherited by the parent process or parent bash.*

### Question (2)

1. ```
    $ ls /usr/bin > /tmp/commands.list
   ```

2. ```
   $ vim /home/gehad/.bashrc
   ```
    *and modifying the prompt string 1, or PS1:*

    ```
    if [ "$color_prompt" = yes ]; then
    echo -n $(date)
        PS1='gehad@linux-machine:~$ '
        # PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
    else
        PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
    fi
    ```
    
    *now the prompt is something like this:*

    ```
    Wed Nov 5 12:34:03 AM EET 2025 gehad@linux-machine:~$ 
    ```

3. *we can count number of words in a file using the wc command with appropriate option, '-w' for words*

   ```
    $ wc -w ./file
   ```
    *To count number of files(or sub-directories) in a directory, we can use pipe*
    ```
    $ ls . | wc -w
    ```

4. 
*   ```
    $ cat filename1 | cat filename2
    ```
    *In this command, the stdout of first cat should be forwarded to the stdin of the second.<br> However, with the second command having arguments, this will override the stdin reference. <br>
    Concluseion: the first cat will always be ignored, and the second cat is what get executed.
    First cat would be exectured.<br>
    To fix this, we can use:*

    ```
    $ cat file1 | cat
    ``` 
*
    ``` 
    $ ls | rm 

    rm: missing operand
    Try 'rm --help' for more information.
    ```
    *Explanation: The stdout of the ```ls``` command is supposed to be forwarded to the stdin of the ```rm``` command, however, this won't work because ```rm``` only accept arguments from command line.<br>
    To have the command function, use:*
	```
    $ ls | xargs rm
    ```

*   ```
    $ ls /etc/passwd | wc -l

    1
    ```
    *The default behaviour of ```ls``` is to work on directories, when a file name is passed it will only be listed.<br>
    So, the arguments passed to wc is one line containing /etc/passwd directory.<br><br>
    To count number of entries within /etc/passwd file, use instead:*
    ```
    $ cat /etc/passwd | wc -l

    50
    ```

5.  ```
    $ sudo find / -name ".profile"
    ```

6. 
*   ```
    $ ls -id /

    2 /
    ```

*   ```
    $ ls -id /etc

    2228225 /etc
    ```

*   ```
    $ ls -id /etc/hosts

    2228610 /etc/hosts
    ```

7.  ```
    $ sudo ln -s /etc/passwd /boot/passwd
    ```

8.  ```
    $ sudo ln /etc/passwd /boot/passwd
    
    $ find /boot/ -name "passwd"
    /boot/passwd

    ```
    *It worked fine, because the hard link is to a file that exists on the same file system we are currently on.*

9. *We can overwrite the ```PS2``` varuable in  ```.bashrc``` file to whatever custom prompt we need:*
    ```
    $ vim ~/.bashrc
    ```
    *Adding this line:*
    ```
    PS2="-> "
    ```
    Now, the custom prompt is working:
    ```
    $ ls \
    -> ~
    Desktop    Downloads  Music     Public  Templates
    Documents  Pictures   snap      Videos

    ```
