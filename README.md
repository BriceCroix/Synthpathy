# Synthpathy

*From Synthesizer and Sympathy, you get Synthpathy*

## Description

[Synthpathy](https://github.com/BriceCroix/Synthpathy.git) is a small and versatile audio synthesizer on a microcontroler. It uses a Raspberry Pico microcontroler. Additional information will be added here during the development process.

Synthpathy is a 4-notes polyphonic synthetizer featuring two types of waveforms (square and saw), an envelope generator (ADSR) with adjustable attack and sustain and a low-pass filter with an adjustable cutoff frequency. The raspberry pico only features 3 ADC channels and a choice had to be made about what parameters could be controlled through potentiometers, but theoretically all ADSR parameters could be handled alongside with filter cutoff and resonnance.

Synthpathy generates sound at 46875 Hertz using raw samples, in floating-point representation, but it would be way more efficient to use 32 or 16 bits fixed-point representation, this issue will be adressed in the future.


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

### Debug messages

The previous section showed that defining the macro `DEBUG_AUDIO` with cmake results in Synthpathy printing raw samples in the console.
Alternatively defining the macro `DEBUG` (with `cmake -DDEBUG=1 ..`) allows to see what events are taken into account and how they are handled.


Defining the macro `TESTS_ONLY` (with `cmake -DTESTS_ONLY=1 ..`) puts the software in a special mode where it does not synthesize anything anymore,
only performing timing measurements. This is useful since it is important that all sound generating functions need to run in about 20 microseconds
(sampling period with a sampling frequency of 50kHz).


## Credits

- Author : [Brice Croix](mailto:brice.croix@gmail.com), 2022


## Versions

Version numbers are of the form X.Y.Z, where :
- X refers to major version, any change in this numbers prevents retro-compatibility with previous data and/or hardware setup.
- Y refers to non-breaking functionality increments.
- Z refers to bugs and mistakes corrections.