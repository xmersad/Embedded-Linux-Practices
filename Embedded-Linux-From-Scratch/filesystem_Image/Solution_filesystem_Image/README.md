
# Solution: Creating Bootable Images and Setting Up a Web Server

This document provides detailed instructions for completing the steps mentioned in the question. Each command is encapsulated within code blocks for clarity and execution.

---

## 1. Create File System Images

### 1.1 Boot File System Image (FAT32)
The boot partition contains bootloader, kernel image, and boot configuration files.

```bash
# Create a directory for boot files
mkdir -p boot_files

# Add necessary bootloader, kernel image, and boot configuration
cp path/to/u-boot.bin boot_files/
cp path/to/Image boot_files/
cp path/to/bootconfig boot_files/

# Create the FAT32 image
dd if=/dev/zero of=boot.img bs=1M count=200
mkfs.vfat boot.img
mcopy -i boot.img boot_files/* ::
```

### 1.2 Root File System Image (SquashFS)
The root partition contains BusyBox and essential scripts.

```bash
# Create a directory for root file system
mkdir -p root_fs/{bin,sbin,etc,proc,sys,usr,www}

# Copy BusyBox binary and create links
cp /path/to/busybox root_fs/bin/
ln -s /bin/busybox root_fs/init

# Add necessary startup scripts
echo -e '#!/bin/sh
mount -t proc proc /proc
mount -t sysfs sys /sys
' > root_fs/init
chmod +x root_fs/init

# Create SquashFS image
mksquashfs root_fs root.sqsh -comp xz
```

### 1.3 Data File System Image (EXT4)
The data partition contains the web server content.

```bash
# Create a directory for data
mkdir -p data/www

# Add an HTML file
echo '<h1>Welcome to the Web Server</h1>' > data/www/index.html

# Create the EXT4 image
dd if=/dev/zero of=data.img bs=1M count=500
mkfs.ext4 data.img

# Mount the image and copy content
mkdir -p /mnt/data
mount -o loop data.img /mnt/data
cp -r data/www /mnt/data
umount /mnt/data
```

## 2. Partition the MMC

```bash
# Use fdisk to create partitions
fdisk /dev/mmcblk0

# Create three partitions
# Partition 1: 200 MB (FAT32)
# Partition 2: 10 MB (SquashFS)
# Partition 3: Rest of MMC (EXT4)

# Write changes and format partitions
mkfs.vfat /dev/mmcblk0p1
mkfs.ext4 /dev/mmcblk0p3
```

## 3. Write Images to MMC

```bash
# Write each file system image to its respective partition
dd if=boot.img of=/dev/mmcblk0p1 bs=4M
dd if=root.sqsh of=/dev/mmcblk0p2 bs=4M
dd if=data.img of=/dev/mmcblk0p3 bs=4M
sync
```

## 4. Set Up BusyBox Web Server

### 4.1 Add Scripts to Root File System
Ensure the BusyBox HTTP server is configured to start at boot.

```bash
# Create a script to start the HTTP server
echo -e '#!/bin/sh
httpd -h /www -p 80' > root_fs/start_httpd.sh
chmod +x root_fs/start_httpd.sh
```

### 4.2 Mount the Data Partition
The data partition should be mounted at /www during boot.

```bash
# Add mounting commands to the init script
echo -e 'mount /dev/mmcblk0p3 /www
' >> root_fs/init
```

## 5. Verify Setup

- Insert the MMC into the target device.
- Boot the device and check the web server using curl on the host.

```bash
# Example command on the host system
curl http://<target-ip>
```

### Expected Output:

```html
<h1>Welcome to the Web Server</h1>
```

## Pre-built Images

If building the images is not feasible, you can use pre-built images
