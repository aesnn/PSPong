# How to build PSPong

First of all, install the PSP SDK from [https://pspdev.github.io/](https://pspdev.github.io/)

Then, copy this repository with ``` git clone https://github.com/aesnn/PSPong.git ```

Once inside the directory, run ``` mkdir -p build ```, and cd into it.

To build it, run ``` psp-cmake ..``` and then ``` make ```, easy as that!

## How to play it

Inside the build directory, you will get a file called ` EBOOT.PBP `, this is the game.

You can copy this to your PSP's SD card and play it on actual hardware, but you can also launch it with an emulator, such as PPSSPP.

Have fun :)
