# Solution: Dynamic Searching for MMC

One issue that might occur when working with U-Boot is that after modifying the device tree, the MMC numbering changes (e.g., `mmc 0` becomes `mmc 1`). Typically, this would require recompiling U-Boot to either update the device tree or point U-Boot to the correct MMC manually. However, this solution enables U-Boot to dynamically search for the correct MMC device without recompilation.

### Code Overview:
In the source code located in `disk/part.c` at line 536 (U-Boot version v2023.10), the following modifications are made to allow dynamic searching:

```c
/* Look up the device */
dev = blk_get_device_by_str(ifname, "1", dev_desc);
printf("\n***Trying to read mmc 1***");
if (dev < 0) {
    printf(" ->Failed \n***Bad mmc number... try mmc 0*** -> ");
    dev = blk_get_device_by_str(ifname, "0", dev_desc);
    if (dev < 0) {
        printf("** Bad device specification %s %s **\n", ifname, dev_str);
        ret = dev;
        goto cleanup;
    }
}
```

### Explanation:
- The code attempts to access `mmc 1` first. If it fails, it will try `mmc 0` as a fallback.
- If both `mmc 1` and `mmc 0` are unavailable, an error message is displayed, and the operation is halted.

### How to Use:
- Implement this modification in `disk/part.c` at line 536 (U-Boot v2023.10).
- Depending on the board you are working with, you may need to add more `if` conditions to check for additional MMC devices (e.g., `mmc 2`).

By making these changes, U-Boot will automatically attempt to find the correct MMC device dynamically for operations such as `sysboot`, file loading, writing, and more without requiring manual changes to the device tree or re-compiling.


