# Synthpathy specifications

The feature IDs are of the form `X.Yz` where :
- **X** is the related major version
- **Y** is an unique identifier
- **z** is an optional letter for sub-features

The status is one of the following :
- ***none*** or **To do** : implementation has not started yet
- **Active** : implementation has started
- **Done** : Feature is complete
- **Closed** : Feature has been abandoned for a reason to be specified in the comments


----------------------------------------------------------------------------------------------------

## Version 1.0.0

### Minimum features

| Feat ID | Description                                                         | Status | Comment |
|:-------:|:--------------------------------------------------------------------|:------:|:--------|
|1.0      |Ability to generate analog audio output at 44100 Hz sampling frequency |Active
|1.1      |Ability to process buttons                                           |Done    |Using a 5 by 5 button matrix
|  1.1a   |12 buttons for a full octave                                         |Done
|  1.1b   |2 buttons for octave up/down                                         |Done
|  1.1c   |1 button for waveform selection                                      |Done
|1.2      |Ability to generate simple waveforms at specific frequencies         |Active
|  1.2a   |Saw Wave                                                             |Active
|  1.2b   |Square Wave                                                          |Active
|1.3      |Ability to generate simple envelopes such as Attack-Sustain          |Active
|1.9      |Ability to provide user visual indications with 3 LEDs               |Done    |Squarewave / Sawwave


### Optional features

| Feat ID | Description                                                         | Status | Comment |
|:-------:|:--------------------------------------------------------------------|:------:|:--------|
|1.4      |Ability to control additional parameters on generated waveforms      |
|  1.4a   |Square wave duty cycle                                               |
|1.5      |Ability to generate full Attack-Decay-Sustain-Release envelopes      |Active
|1.6      |Ability to use an Low Frequency Oscillator signal to modulate one or several commands (in which case button(s) must be added) |
|1.7      |Ability to process MIDI input                                        |
|1.8      |Ability to process MIDI Output                                       |Closed  |Useless feature
|1.10     |Addition of audio effects
|  1.10a  |Digital filters (low-pass, band-pass, peaking eq)
|  1.10b  |Audio delay
|  1.10c  |Reverberation
|  1.10d  |Distortion and/or Overdrive and/or Fuzz
|1.11     |Ability to add noise to the output


----------------------------------------------------------------------------------------------------

## Version 2.0.0

| Feat ID | Description                                                         | Status | Comment |
|:-------:|:--------------------------------------------------------------------|:------:|:--------|
|2.0      |Ability to pilot an external device for additional analog inputs
|2.1      |Ability to pilot lots of LEDs with SIPO registers (such as 74AHC594)