## Exercise: Adding a Custom Command to U-Boot (Clear Screen Command)

In this exercise, you will learn how to add a custom command to U-Boot, specifically a `clear` command to clear the screen. This exercise aims to teach how to link a new command with your U-Boot image, giving you a better understanding of U-Boot customization.

1. **Write a New Command**: Create a C file to define the clear functionality.
2. **Link the Command**: Learn how to link this new command with the U-Boot build system.
3. **Configure U-Boot**: Modify board-specific configuration files to include your new command.



### Explanation:
One common feature missing from U-Boot is a built-in `clear` command to clean the terminal screen. In this task, you will implement this functionality by creating a custom command, `clear`, that will allow you to clear the screen.

### Expected Output:
Upon successfully adding the command, running `clear` in U-Boot should result in a clean terminal screen without errors.


