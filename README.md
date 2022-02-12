# Synthpathy

*From Synthesizer and Sympathy, you get Synthpathy*

## Description

[Synthpathy](https://github.com/BriceCroix/Synthpathy.git) is a small and versatile audio synthesizer on a microcontroler. It uses a Raspberry Pico microcontroler. Additional information will be added here during the development process.


## How to build

First of all, if not already done, you have to clone the repository of the pico sdk, available at https://github.com/raspberrypi/pico-sdk.git .

```shell
git clone https://github.com/raspberrypi/pico-sdk.git
```

The pico sdk repository also provides a README.txt file with everything necessary in order to compile a raspberry pico project, but in short simply run :

```shell
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
```

You are now able to compile this project by running the following lines (change `/your/sdk/path` for your actual sdk path) :

```shell
mkdir build
cd build
cmake -DPICO_SDK_PATH=/your/sdk/path ..
make
```


## Credits

- Author : [Brice Croix](mailto:brice.croix@gmail.com), 2022


## Versions

Version numbers are of the form X.Y.Z, where :
- X refers to major version, any change in this numbers prevents retro-compatibility with previous data and/or hardware setup.
- Y refers to non-breaking functionality increments.
- Z refers to bugs and mistakes corrections.