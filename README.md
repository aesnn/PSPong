# How to build PSPong

First of all, install the PSP SDK/Toolchain from [https://pspdev.github.io/](https://pspdev.github.io/).

Then, generate the build files:
```sh
git clone https://github.com/aesnn/PSPong.git
cd PSPong
mkdir -p build
cd build
psp-cmake ..
```

And build:
```sh
make
```

Easy as that!

## How to play it

Inside the build directory, you will get a file called `EBOOT.PBP`, this is the game.

You can play this with an emulator, such as PPSSPP, or try it out on hardware by installing it on your PSP under `PSP/GAME/PSPong/EBOOT.PBP`.

Have fun :)
