
# Solution: Creating Bootable Images and Setting Up a Web Server

This document provides detailed instructions for completing the steps mentioned in the question. Each command is encapsulated within code blocks for clarity and execution.


## 1. Create File System Images

### 1.1 Boot File System Image (FAT32)
The boot partition contains bootloader, kernel image, and boot configuration files.

```bash
# Create a directory for boot files

# Create the FAT32 image
dd if=/dev/zero of=boot.img bs=1M count=200
mkfs.vfat boot.img

mkdir /mnt/disk1
mount boot.img /mnt/disk1

# Add necessary bootloader, kernel image, and boot configuration
cp {bootfiles} /mnt/disk1

umount /mnt/disk1

```

### 1.2 Root File System Image (SquashFS)
The root partition contains BusyBox and essential scripts.

```bash


# Use BusyBox to create Rootfs

dd if=/dev/zero of=root.squashfs bs=1M count=10

mksquashfs {PathToRootfs} root.squashfs -noappend

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

```

## 3. Write Images to MMC

```bash
# Write each file system image to its respective partition
dd if=boot.img of=/dev/mmcblk0p1 bs=4M
dd if=root.squashfs of=/dev/mmcblk0p2 bs=4M
dd if=data.img of=/dev/mmcblk0p3 bs=4M
sync
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
