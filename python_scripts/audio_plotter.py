import sys
import matplotlib.pyplot as plt
import numpy as np

# These values are copied from "global.h"
SYSTEM_CLOCK_FREQUENCY_KHZ = 192000
PWM_AUDIO_CLK_DIVIDER = 128
PWM_AUDIO_BIT_DEPTH_PER_CHANNEL = 8
AUDIO_SAMPLING_FREQUENCY = (SYSTEM_CLOCK_FREQUENCY_KHZ*1000.0) / (PWM_AUDIO_CLK_DIVIDER * (1<<PWM_AUDIO_BIT_DEPTH_PER_CHANNEL))


######################################## Main Section ##############################################

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("No file given, please use as follow :\n\tpython3 audio_plotter.py path/to/file.csv")
        quit()

    filename = sys.argv[1]
    
    # Retrieve audio signal
    data = np.genfromtxt(filename, dtype=float, delimiter=";")
    time = np.arange(0, len(data)) / AUDIO_SAMPLING_FREQUENCY

    # Check for errors in the input file, translated to nans
    errors = np.where(np.isnan(data))
    if(np.size(errors) != 0):
        print("Input file contains errors at lines " + str(errors[0]+1))


    # Perform frequency analysis
    data_fft = np.fft.fft(data) / len(data)
    freq = np.fft.fftfreq(len(data), d=1./AUDIO_SAMPLING_FREQUENCY)

    # Plot signal
    fig, (ax, ax2) = plt.subplots(2,1)

    # Time
    ax.plot(time, data)
    ax.grid()
    ax.set_xlabel("Time (s)")
    ax.set_ylabel("Audio signal")
    #ax.set_ylim([-1.1, 1.1])
    ax.set_ylim([-(2**4) -(2**31), (2**31) + (2**4)])
    #ax.set_ylim([-(2**4), (2**32) + (2**4)])
    ax.set_title("Measured audio signal")

    # Frequency
    ax2.plot(freq, np.abs(data_fft))
    ax2.grid()
    ax2.set_xlabel("Frequency (Hz)")
    ax2.set_title("Measured audio signal FFT")


    fig.tight_layout()
    # Save figure
    fig.savefig(filename + ".png")
    # Show figure
    plt.show()