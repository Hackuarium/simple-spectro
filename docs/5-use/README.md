# How to use it ?

The control of the spectrometer is done using a rotary push button. To scroll in the menu, turn
the button, to validate an entry, press the button.

The simple-spectro is self-contained. The battery lasts around 3 months in sleep and around 2 days in acquisition mode.
The spectro switches to sleep mode after 100s (if there is no acquisition running). To wake it up simply turn the rotary push button.

3 acquisition modes are available:

- One acquisition (Blank + Sample)
- Sequence of experiments (Blank + many samples, press button for next experiment)
- Kinetic (Blank + Sample x times)

For one acquisition, you may specify the time before the first experiment (Before delay) as well as the time between the 2 experiments (First delay). Those parameters are accessible from the `Settings` menu. You may turn the rotary push button to select `Settings` and then press the button to enter the menu.

To change a value, press the button and turn to set the new value. Once the right value is selected, press the button again to validate.

## The menu

### 1. Acquire

This option will start an acquisition (Blank + Sample). Before acquiring the blank the spectro will
wait `Before delay` seconds (see `Settings`) and between the Blank and the Sample the spectro will wait
`First delay` seconds (see `Settings`).

The acquisition will take all the selected colors as defined in `Settings -> Active leds`.

If you need to stop the acquisition press the rotary-push button twice.

After the acquisition the display will show the absorbance for all the selected colors.
In order to see all the values, turn the rotary-push button.

### 2. Acquisition sequence

This mode allows to acquire the absorbance of a sequence of samples. For example, if you want to check the Beer-Lambert
law, you would first put a blank, then all the known concentration samples and finally the unknown concentration
sample.

Between each sample, press the button to go to the next experiment. The spectro will expect the number
of experiments defined in `Settings` `Number exp`. In order to stop the acquisition before the end, you need to
turn the rotary push button and press `Stop acquis.`. You will then directly see the results.

To check the results you need to go in the `Results` menu (see below).

### 3. Acquisition kinetic

The spectro is able to acquire automatically a sequence of experiments. They are many `settings` that will
define this behaviour:

- `Before delay`: Time in seconds to wait before acquiring the blank
- `First delay` : Time in seconds to wait before the first experiment

### 4. Results

Shows the acquired results in 3 columns:

- Time (in seconds) since the acquisition of the blank
- Absorbance
- Light intensity as measured by the sensor

The results are shown for the colors specified in `Settings -> Result color`.

### 5. Settings

#### 5.1 Before delay

Delay before blank.

#### 5.2 First delay

Delay before first experiment (for kinetics).

#### 5.3 Inter experiment delay

Delay between experiments (for kinetics).

#### 5.4 Number of experiments

Number of experiments that are going to be made during a kinetic.

#### 5.5 Result color

What data is shown in the results. You can choose to show the absorbance in R, G, B or UV (combination of these). The values shown are defined by a number between 0 and 63.

#### 5.6 Rotary mode

Invert the rotation of the button.

#### 5.7 Active leds

What LEDs are going to blink when doing the experiments.

#### 5.8 Main menu

Go back to main menu.

### 6. Status

Show general information about the spectro:

- Current temperature
- Battery level (between 3.7 and 4.2 volts) and a sign telling if it is charging `+`, decharging `-` or fully charged `→`
- Uptime
- Version of the firmware

### 7. Utilities

#### 7.1 Sleep

Put the spectro in sleep mode (reducing the power consumption to around 100µA).

#### 7.2 Test LED

Allows to check that all the LEDs are working correctly. With a blank you should obtain
values in the following ranges:

- R: between 100000 and 450000
- G: between 100000 and 450000
- B: between 100000 and 450000
- UV: between 0 and 2000

To stop the test mode press the button twice.

#### 7.3 Reset

Reset all the parameters to the default values:

- Before delay: 2s
- First delay: 10s
- Inter experiment delay: 20s
- Number experiments: 60
- Result color: red
- Rotary mode: normal
- Active leds: R G B UV

#### 7.4 Boot

#### 7.5 Main menu

Return to the main menu.

## In case of crash

1. Ensure that the battery is not completely flat and connect the spectro to USB.
2. Press the button during 10s and release.
3. If this still does not work you need to open the spectro, unplug the battery and plug it in again.

## Accessing from serial port

It is possible to access the data directly from the serial port.

Please check [this page](serial/README.md) for more information.
