
# Practicing CPP references, classes, allocating/deallocating object-related resources  safely 🤯


### Purpose 🤔
To get all instances of the same class have access to a file state (opened/closed), and the changes made on the file by one object is detected by the others.



### Proof 🫴
1.  First object registering & executing its own actions (didn't close the file yet).
```
FileActions f1("file.txt");
    actions_t act1 = 
    {
        {"read", 1},
        {"write", 1},
        {"read", 1},
    };
    f1.registerActions(act1);
    f1.executeActions();
```
Outupt
```
reading...
Here, I am doing my cplusplus lab for the 2nd time.
This is due to a little of lab misinterpretation.

writing...

reading...
Here, I am doing my cplusplus lab for the 2nd time.
This is due to a little of lab misinterpretation.
Have a nice day.
``` 
2.  Second Ojbect registering its actions, closing the file :( 
```
FileActions f2 = f1;
    actions_t act2 = 
    {
        {"close", 1},
    };
    f2.registerActions(act2);
    f2.executeActions();
```
* Output
```
closing...
```
3.  Now, First object tries to operate on the closed file:
```
f1.executeActions();
```
* Output
```
Unfortunately, file has already been closed by another object.
```