# Solution: Displaying a Banner in U-Boot

In this solution, a custom banner is displayed in U-Boot during the boot process. The banner text is converted into character art using a simple program and integrated into U-Boot.

## How It Works

1. **Converting Text to Banner**:
   - A program was written to convert the desired banner text into a character display. You can find the link to this program below or use the version provided in the current directory.
   - [Banner Conversion Program](https://lnkd.in/dXZJKkbf)

2. **Integrating the Banner into U-Boot**:
   - The `show_banner()` function is called in the U-Boot code to print the banner during the boot process.
   - In this case, the banner is displayed after the compile-time message and before the DRAM information. The exact location of the code is:
     - **File**: `common/board_f.c`
     - **Line**: 204
   - Here's the code snippet showing where the banner is included and called:

     ```c
     #include "banner"

     static int announce_dram_init(void)
     {
         show_banner();
         puts("\nDRAM: ");
         return 0;
     }
     ```

3. **Passing the Banner Text**:
   - The banner text can be provided either by hardcoding it into the program or by using `Kconfig` for a more dynamic approach.
   - A new configuration option, `BANNER_TEXT`, was added in the `Kconfig` file under the "Custom Configuration" section.

4. **Compiling the Code**:
   - The banner text is passed as a flag during the compilation of `board_f.c`. Here's the modification in the `Makefile`:
     - **File**: `common/Makefile`
     - **Modification**:
       ```makefile
       CFLAGS_board_f.o += -DBANNERTEXT="$(CONFIG_BANNER_TEXT)"
       ```

By following these steps, U-Boot will display your custom banner during the boot process. The required program for banner generation is available in the current directory as well.


