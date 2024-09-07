# Practice : Python Init

As you may know, the first process created in Linux is the init process, which remains active as long as the system is powered on. Typically, the init program is written in C and compiled statically or dynamically for the target platform.

But is it possible to write init in Python and leverage its libraries?  
Yes, there are several ways to achieve this. Here are some methods:

- **Compile Your Python Script**: You can compile your Python script using PyInstaller or convert it to C with Cython, then compile it with the desired compiler (not recommended).
  
- **Integrate Python into Your Init System**: For example, you can add Python to BusyBox and compile it together with BusyBox for usage.
  
- **Compile Python Source Code**: Compile Python (either statically or dynamically) and place it in the root filesystem (Rootfs) of your target. Then, start your Python script with a shebang pointing to your Python path (recommended).

In this case, I used the last approach. However, this method is primarily for testing purposes, as Python may be too heavy for this task.

### Important Note:
Make sure to create the `dev` directory within your Rootfs because Python requires this directory to pass the `crng init done` stage. Without it, you won't be able to utilize the Python kernel! Creating this directory is essential, as the kernel will mount the necessary files, including those related to random number generation, to the `dev` folder.

## Expected Output

Upon successful execution, the system should be able to utilize the Python init script, allowing for the initialization of processes and other essential tasks within the Linux environment.

![Expected Output](path/to/your/image.png)

