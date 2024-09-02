# nInvaders-mpu6050 Solution

In this scenario, the source code of the `nInvaders` game has been modified to read data from the MPU6050 sensor. The game now interacts directly with the default kernel driver of the MPU6050, utilizing the driver's files to control the spaceship within the game.

## Steps

### 1. Dependencies and Requirements

Before proceeding, ensure all necessary dependencies and requirements are met.

### 2. Describe Device in Device Tree

For this project, the MPU6050 should be described on the I2C-1 bus, which is connected to pin 3 (SDA) and pin 5 (SCL) with the address `I2C@7E804000`.

Here are the properties of the MPU6050 node in the Device Tree:

```dts
&i2c1 {
    mpu6050@68 {
        compatible = "invensense,mpu6050";
        reg = <0x68>;
        interrupt-parent = <&gpio>;
        interrupts = <17 IRQ_TYPE_EDGE_RISING>; 
        orientation = <0>;
    };
};
```

**Note**: The interrupt property is not necessary for this project.

### 3. Compile Ncurses with Both Static and Shared Libraries

To compile the `ncurses` library with both static and shared libraries, use the provided bash script. Simply set your cross-compiler within the script. You can find the script here: [ncurses-compile.sh](https://github.com/xmersad/Embedded-Linux-Practices/blob/main/Embedded-Linux-System-Integration/nInvaders-mpu6050/solution_nInvaders-mpu6050/ncurses-compile.sh).

### 4. Compile nInvaders Game

The `nInvaders` source code has been modified specifically for this project. After downloading the source, set your cross-compiler and the install path of `ncurses` in the Makefile. You can access the source and Makefile here: [nInvaders-Makefile](https://github.com/xmersad/Embedded-Linux-Practices/blob/main/Embedded-Linux-System-Integration/nInvaders-mpu6050/solution_nInvaders-mpu6050/nInvaders-Makefile).

### 5. Compile the Kernel

Compile the Linux kernel with the necessary I2C-BCM2835 and MPU6050 modules, which are available in the mainline kernel.

### 6. Deploy to Root Filesystem

Move the kernel image, the `nInvaders` game binary, the MPU6050 module, the `libc`, and the compiled `ncurses` library to your root filesystem.

### 7. Pre-Built Image

For convenience, a pre-built image for this scenario has been prepared. You can download it from this link: [Pre-Built Image](https://mega.nz/file/gisgVaZQ#X_2SQN06o4isfFLOdWuqbvDz3mzDQJuz12SB-Luk7zk).

## Testing

After connecting the hardware and loading the MPU6050 module, verify that the sensor data is being correctly read. Check the corresponding device files in the `/sys/class/i2c-adapter/i2c-1/1-0068/` path. If the files are not present, ensure that the module is properly loaded and the device tree is correctly configured.

## Play

Once everything is set up, run the `nInvaders` game. The spaceship should move left or right based on the tilt along the X-axis of the MPU6050. You can play the game by simply tilting the module.

**Note**: If you come up with another method to control the game using the MPU6050, feel free to implement and explore it.

**Have fun!**
