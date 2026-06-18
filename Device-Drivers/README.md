# procfs handlers

### 🔍 Anatomy of the Handlers
In modern Linux kernels, the standard procfs read and write handlers look like this:
```
ssize_t my_proc_read(struct file *file, char __user *buf, size_t count, loff_t *ppos);
ssize_t my_proc_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos);
```
### 🧩 Where Each Argument Originates
1. ```struct file *file``` (The Kernel's Tracker)
* Where it comes from: The VFS Layer.
* What it is: When the user-space program first called open(), the kernel allocated a unique struct file object in memory to track that specific open instance. The VFS passes a pointer to this object into your handler so you can check file flags (like O_NONBLOCK) or access private session data.

2. ```char __user *buf``` (The User's Bucket)
* Where it comes from: The User-Space System Call Argument.
* What it is: This is the exact memory address inside the user's application buffer.  
If a C program runs ```read(fd, my_buffer, 100);```, ```buf``` is the address of ```my_buffer```.  
Note on __user: This is a safety tag warning the kernel compiler that this address belongs to a user program and cannot be trusted blindly. You must use safe functions like ```copy_to_user()``` or ```copy_from_user()``` to touch it.

3. ```size_t count``` (The Requested Size)
* Where it comes from: The User-Space System Call Argument.
* What it is: This is the maximum number of bytes the user program is asking to transfer.  
In ```read(fd, my_buffer, 100);```, count will be exactly 100.Your handler must respect this and never copy more bytes than count into buf, or you will crash the user's application.

4. ```loff_t *ppos``` (The Bookmark Pointer)
* Where it comes from: The VFS Layer (pointing to a variable inside struct file).
* What it is: This is a pointer to the current file offset tracker (file->f_pos).  
For standard read() or write() calls, the VFS points this directly to the bookmark variable stored in the struct file.  
For positional calls like pread(fd, buf, count, 50), the VFS bypasses the file's main bookmark, creates a temporary variable on the kernel stack with the value 50, and passes a pointer to that temporary variable instead.

### 🔄 The Data Flow Timeline
To visualize the handoff from user-space to your kernel driver handler:
```
[ USER SPACE ]                                [ KERNEL SPACE (VFS) ]                       [ YOUR PROCFS HANDLER ]
                                                    
char my_buf[100];                                  Looks up File Descriptor (fd).
read(fd, my_buf, 100);  ──► [System Call Vector] ──► Finds the matching 'struct file'. ──► Executes:
                                                   Fetches current file->f_pos.            my_proc_read(file, my_buf, 100, &f_pos);
```


# Example implementation of read handler
```
ssize_t my_proc_read(struct file *file, char __user *buf, size_t count, loff_t *ppos) {
    // 1. CHECK THE OFFSET
    if (*ppos > 0) {
        return 0; // "I already gave you data last time. Return EOF."
    }

    // 2. GENERATE AND COPY DATA
    int len = sprintf(kernel_buffer, "Kernel status: OK\n");
    copy_to_user(buf, kernel_buffer, len);

    // 3. INCREMENT THE OFFSET
    *ppos += len; 

    // 4. RETURN BYTES WRITTEN TO USER
    return len;
}
```

The driver handler is just a passive callback function. It does not actively track the state of the user’s loop.  
Instead, the cat program itself determines the looping behavior, while the VFS layer manages the state that the callback uses to decide what to do.  
Here is the step-by-step breakdown of how cat, the VFS, and the driver callback interact to cause this behavior.

### 🔄 Step 1: The cat Program's Infinite Loop
The cat utility is written to read an entire file until it hits the end (EOF). Internally, its source code runs a standard loop that looks something like this:
```
while ((bytes_read = read(fd, buf, sizeof(buf))) > 0) {
    write(STDOUT_FILENO, buf, bytes_read);
}
```
cat does not know it is reading a virtual file in memory. It treats /proc/cpuinfo exactly like a 4GB movie file on a hard drive. It will keep calling the read() system call over and over again until a read() call returns 0 (which means EOF).

### 🧠 Step 2: The VFS Layer Tracks the State
Every time cat triggers that read() system call, control jumps into the kernel's Virtual File System (VFS) layer.  
The VFS looks at the system's open file table and pulls up the struct file for that specific open instance. Inside that struct is the state variable: file->f_pos (the file offset).  
On the first loop: file->f_pos is 0.  
The VFS calls your handler: It executes the driver's callback, passing a pointer to this state: handler(..., &file->f_pos).

### 🛠️ Step 3: Inside the Driver Callback (The Logic Switch)
The driver handler is a stateless callback, but it is handed the pointer to the offset (ppos). The driver code uses the value of *ppos to determine its behavior.  

### step 4: end of the loop
once reaching an EOF, the cat prints the text and immediately calls close(). The file descriptor and its old offset are completely destroyed.  
This enables for future read to start at the very beginning of the file.

# Example implementation of the write handler
```
ssize_t my_proc_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos) {
    char kernel_buffer[256];
 
    if (count > sizeof(kernel_buffer) - 1) {
        return -EINVAL; // Return "Invalid Argument" error to user-space
    }

    if (copy_from_user(kernel_buffer, buf, count)) {
        return -EFAULT; // Return "Bad Address" error if memory copy fails
    }

    kernel_buffer[count] = '\0';

    if (kernel_buffer[0] == '1') {
        // enable_my_feature();
    } else if (kernel_buffer[0] == '0') {
        // disable_my_feature();
    }

    *ppos += count;

    return count;
}

```
For write operations on configurations in virtual filesystems (e.g., changing values under /proc/sys/kernel/ or /sys/class/), the write handler almost completely ignores or sets the offset to zero conceptually.  
Why it acts as Zero: Most procfs and sysfs write handlers are designed to parse a complete string command (like echoing 1 into a control file to enable a feature). Because they always expect a fresh command from the beginning of the text, the driver forces the write to happen at offset 0, completely discarding any previous read or write offset state.  
No lseek required: You can read a value from a procfs file (which increments the offset to the end of the file) and immediately execute a write() on the same open file descriptor without calling lseek(). The virtual filesystem handler will automatically process your write as if the offset was 0