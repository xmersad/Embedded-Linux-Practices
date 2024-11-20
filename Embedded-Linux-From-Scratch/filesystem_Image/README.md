# Creating File System Images and Setting Up a Web Server

This README outlines the process for creating file system images, partitioning an MMC, and setting up a web server using BusyBox. The steps below will help you build a multi-partition MMC containing a bootloader, root filesystem, and data filesystem, with a functional web server serving an index.html file.


## Overview

A file system image is a binary snapshot of a file system structure. These images are often used in embedded systems to manage boot processes, store the root filesystem, or handle user data. 

In this task, you will:
1. Create three file system images: FAT32, SquashFS, and EXT4.
2. Partition an MMC and load these images onto their respective partitions.
3. Configure a web server using BusyBox, ensuring it serves an index.html file from the data partition.


## Plan

### Partition Layout

1. Boot File System Image:
   - Format: FAT32
   - Size: 200 MB
   - Content: Bootloader, kernel (Image), and configuration files (bootconfig).

2. Root File System Image:
   - Format: SquashFS
   - Size: 10 MB
   - Content: Minimal root filesystem with BusyBox and scripts for system setup.

3. Data File System Image:
   - Format: EXT4
   - Size: Remaining MMC space
   - Content: index.html file, mounted at /www.


## Steps

### 1. Kernel Configuration
Ensure the kernel supports the required file systems. Enable the following options:
- FAT32 support for boot.
- SquashFS support for a compressed root filesystem.
- EXT4 support for the data partition.

### 2. Create File System Images
- Boot Image: Create and format as FAT32. Include boot files such as Image, bootloader, and bootconfig.
- Root Image: Create a minimal root filesystem with BusyBox and supporting scripts. Format as SquashFS for read-only access.
- Data Image: Create a writable EXT4 partition containing an index.html file to be served by the web server.

### 3. Partition the MMC
- Create three partitions using tools like fdisk or parted:
  - Partition 1: FAT32 (200 MB).
  - Partition 2: SquashFS (10 MB).
  - Partition 3: EXT4 (remaining space).
- Load the created file system images onto their respective partitions.

### 4. Configure BusyBox
- Enable httpd in the BusyBox configuration.
- Add scripts to:
  - Set a static IP address (e.g., 192.168.1.100).
  - Start the HTTP server pointing to /www.

### 5. Verify Web Server
- Boot the target device.
- Use curl from the host system to access the web server


## Expected Output

After completing the steps:
- The target board should boot successfully.
- The web server should serve the index.html file.
- Running the curl command on the host system should display the html file


## Notes

1. Kernel Support:
   - Ensure that the kernel is configured to support FAT32, SquashFS, and EXT4 file systems.

2. SquashFS:
   - SquashFS is a compressed, read-only file system. It is commonly used for embedded systems to save space.
   - Use mksquashfs to create the SquashFS image. Verify that the tools are installed and compatible with your build environment.

3. Networking:
   - Configure a static IP for the target system to ensure reliable communication with the host.
   - Add necessary networking commands in the BusyBox scripts to bring up the network interface during boot.

4. BusyBox Web Server:
   - Ensure that BusyBox is configured with HTTP server support.
   - Verify that the scripts correctly mount the data partition to /www and start the HTTP server.
