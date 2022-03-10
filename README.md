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

If you have a standard Ubuntu distribution (this is probably also true for other distributions), the pico should mount under `/media/user/RPI-RP2` (replace `user` by your actual login).
So if you press the bootsel button, plug the pico, and release the button, you can load the executable with :

```shell
cp Synthpathy.uf2 /media/user/RPI-RP2/
```

## Development notes

### Visualize generated sound

If you have minicom and python 3 installed on your computer, you can visualize the waveform created by the software with the following process :

```shell
mkdir build
cd build
cmake -DPICO_SDK_PATH=/your/sdk/path -DDEBUG_AUDIO=1 ..
make
cp Synthpathy.uf2 /media/user/RPI-RP2/
minicom -b 115200 -o -D /dev/ttyACM0 -C capture.txt

python3 ../python_scripts/audio_plotter.py capture.txt
```

After starting minicom, you will see the raw samples created by Synthpathy. You are supposed to use it in order to see anything else than zeros.
You can leave minicom with Ctrl+A, X. These samples are saved in `capture.txt`, which can be interpreted as a csv.
The csv is then processed by `audio_plotter.py` in order to display the audio waveform in a much more pleasing way.


## Credits

- Author : [Brice Croix](mailto:brice.croix@gmail.com), 2022


## Versions

Version numbers are of the form X.Y.Z, where :
- X refers to major version, any change in this numbers prevents retro-compatibility with previous data and/or hardware setup.
- Y refers to non-breaking functionality increments.
- Z refers to bugs and mistakes corrections.