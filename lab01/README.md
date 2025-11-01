# First sheet answers 🙌

### Question (1)
Three linux distributions : CentOS, Red Hat, Debian

### Question (2)
 "man" command is used for navigating the documentation of specific command; it provides detailed descriptions more than usual help command; it is based on less, so we can navigate both up and down :)

### Question (3)
"rm" is used to delete a regular file or remove a whole directory using the recursive flag. rmdir is used to delete an empty directory; we cann't use it to delete a non-empty folder.

### Question (4)
1.  
    ```
    cd ~
	mkdir -p dir1/dir11
	mkdir dir1/dir12
	touch dir1/dir11/file1
    ```

2. 
    ```
    mkdir docs
    touch docs/mycv
    ```
	3.
    ```
    mkdir documents
	touch documents/OldFiles	 
	```

*
    ``` rmdir dir1/dir11 ```

	rmdir: failed to remove dir1/dir11: Directory not empty <br>
	Notice: we can't remove a non-empty file using mkdir <br>
  rm -r dir1/dir11

* *if we consider OldFiles as a directory, not a file, we can remove it using the command:* <br>
	```rmdir -p  documents``` <br>
    *Notice: all the subfolders within documents are removed including OldFiles* <br>
	

*
	*absolute dir:*  ```/home/freecomp/docs/mycv``` <br>
	*relative dir:*  ```~/docs/mycv```

4.  
    ``` 
    cp /etc/passwd ~/mypassword 
    ```
### Question (5)

```
    mkdir docs
    touch docs/mycv
```

### Question (6)

``` 
    mv mypassword oldpassword 
```

### Question (7)
``` 
    cd /usr/bin

    cd /home/gehad
    cd ~
    cd ../../home/gehad 
    cd 
```

### Question (8)
```
    ls /usr/bin/w* 
```


### Question (9)

*```type``` command is used to know the command type; for example: shell built-in command (```pwd```, ```cd```, ..) or  a user space command (```mkdir```, ```rm```, ```cp```, ..)*

### Question (10)

*using the command:
	 ```type $(ls c*)```
    we found that file commands are: ```cat```, ```chmod```*

### Question (11)

*using the command
	```man -k file, read, print```
    we found that the command is ```cat```*

### Question (12)

*```apropos``` command is quite equivalent to ```man -k``` command; it searches the manual page for a command using a keyword related to the command description.*

