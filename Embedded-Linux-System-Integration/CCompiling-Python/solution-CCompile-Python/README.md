# Solution: Cross-Compiling Python for ARM64

This document outlines the steps I followed to successfully cross-compile Python 3.12.8 for an ARM64-based target (Raspberry Pi 4).


## Steps Taken

### 1. Downloading and Compiling Dependencies

#### zlib
The Python build process requires zlib for compression-related functionality. I downloaded and compiled zlib using the following commands:
```
./configure --prefix=/path/to/temp/rootfs/usr  
make  
make install  
```
Reason: Without zlib, the Python build process fails to include compression-related modules such as zipfile or gzip.

#### libffi
Another dependency for Python is libffi, essential for modules like ctypes. I downloaded and compiled it with default configurations:
```
./configure --prefix=/path/to/temp/rootfs/usr  
make  
make install  
```
Reason: Python uses libffi for foreign function interface support, allowing Python to call C functions.

---

### 2. Cross-Compiling Python

I configured the Python source code for the ARM64 target using the following command:

./configure \
  --host=aarch64-linux-gnu \
  --build=x86_64-linux-gnu \
  --prefix=/path/to/temp/rootfs/usr \
  CFLAGS="-I/path/to/temp/rootfs/usr/include" \
  LDFLAGS="-L/path/to/temp/rootfs/usr/lib"

I then built and installed Python:

```
make  
make install  
```
---

### 3. Issue with pip Installation
During the Python installation process, an error occurred when attempting to upgrade pip using the embedded ensurepip module. The error was caused by an existing pip installation on the host system (Debian), managed by the apt package manager. The issue was due to a missing RECORD file, preventing the uninstallation of the system's pip.

#### Solution:
1. Added CFLAGS and LDFLAGS to explicitly point to the compiled libraries in the temporary rootfs.
2. Installed Python with the --no-ensurepip option to skip the pip installation step:

make install  
/path/to/python3.12 -m ensurepip --no-default-pip  

---

### 4. Final Setup

After compilation, all libraries and binaries were placed in a temporary root filesystem (/path/to/temp/rootfs) with the usr prefix to match the target directory structure.

The resulting Python installation was verified to work correctly with the necessary modules and dependencies.

---

## Outcome

The cross-compilation process was completed successfully. Python 3.12.8 was installed in the target rootfs, along with its dependencies (zlib and libffi), and is fully functional for ARM64 architecture.
[Download Image Link](https://mega.nz/file/Jy8WDJDQ#6PaSjU4r1qIyTmmYovXNCBqRpwjfG9cNF7jx9Y_Bnvc)
---

## Additional Resource

A pre-built ext4 filesystem image containing the compiled Python binaries and dependencies for Raspberry Pi 4 is available. This image can be used to save time and ensure a functional setup.
Provided by Mersad Karimi
[Download Image Link](https://mega.nz/file/Jy8WDJDQ#6PaSjU4r1qIyTmmYovXNCBqRpwjfG9cNF7jx9Y_Bnvc)
**have a fun!**
