import sys
import matplotlib.pyplot as plt
import numpy as np

# These values are copied from "global.h"
SYSTEM_CLOCK_FREQUENCY_KHZ = 192000
PWM_AUDIO_CLK_DIVIDER = 64
PWM_AUDIO_BIT_DEPTH_PER_CHANNEL = 8
AUDIO_SAMPLING_FREQUENCY = (SYSTEM_CLOCK_FREQUENCY_KHZ*1000.0) / (PWM_AUDIO_CLK_DIVIDER * (1<<PWM_AUDIO_BIT_DEPTH_PER_CHANNEL))


######################################## Main Section ##############################################

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("No file given, please use as follow :\n\tpython3 audio_plotter.py path/to/file.csv")
        quit()

    filename = sys.argv[1]
    
    # Retrieve audio signal
    data = np.genfromtxt(filename, dtype=float)#[:, 1]

    # Plot signal
    fig, ax = plt.subplots(1,1)
    time = np.arange(0, len(data)) / AUDIO_SAMPLING_FREQUENCY
    ax.plot(time, data)

    # Add figure information
    ax.grid()
    ax.set_xlabel("Time (s)")
    ax.set_ylabel("Audio signal")
    ax.set_title("Measured audio signal")

    # TODO : add frequency plot

    # Save figure
    fig.savefig(filename + ".png")
    # Show figure
    plt.show()