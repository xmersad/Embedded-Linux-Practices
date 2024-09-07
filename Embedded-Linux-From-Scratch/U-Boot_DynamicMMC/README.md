# Dynamic Searching for MMC

One common issue you might encounter is that after modifying your device tree or changing the hardware, the MMC numbering changes. For example, what used to be `mmc 0` could become `mmc 1`. This can cause issues when U-Boot tries to load files from the wrong MMC device.

Typically, to address this issue, you would:

1. Tell U-Boot to read files from a different location.
2. Modify the device tree to adjust to the new MMC numbering.

However, both solutions require recompiling U-Boot, which isn't always efficient. Wouldn’t it be easier if U-Boot could dynamically determine the correct MMC device?

### Problem Statement:
How can you configure U-Boot so that it dynamically searches for the correct MMC without the need for manual device tree modifications or recompilation, ensuring tasks like `sysboot`, file writes, file loads, and any other MMC-related operations proceed smoothly?

### Expected Output:

- U-Boot should be able to automatically detect and use the correct MMC device.
- The MMC-related commands (like `sysboot`, file operations) should succeed without manual intervention.

![Expected Output](https://github.com/xmersad/Embedded-Linux-Practices/blob/main/Embedded-Linux-From-Scratch/U-Boot_Banner/Solution_U-Boot-Banner/Banner.jpeg)


#### Additional Information:
By making certain changes to the source file `disk/part.c`, you can enable U-Boot to dynamically perform the necessary operations on the correct MMC device.

