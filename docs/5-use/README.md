# How to use it ?

The control of the spectrometer is done using a rotary push button. To move in the menu you should turn
the button, to validate an entry, press the button.

The simple-spectro is battery powered and the battery last around 3 months if not used and around 2 days in acquisition mode.
The spectro goes to sleep after 100s (if there is no acquisition running). To wake it up simple turn the rotary push button.

3 acquisition modes are available:

- one acquisition (Blank + Sample)
- a sequence of experiments (Blank + many samples, press button for next experiment)
- a kinetic (Blank + Sample x times)

For one acquisition you may specify the time before the first experiment (Before delay) as well as the time between the 2 experiments (First delay). Those parameters are accessible from the `Settings` menu. You may use the rotary push button to select settings and then press the button to enter the menu.

To change a value, press the button and turn to set the new value. After, press the button again to validate.

## The menu

### 1. Acquire

This option will start an acquisition (Blank + Sample). Before acquiring the blank the spectro will
wait `Before delay` (see `Settings`) and between the Blank and the Sample the spectro will wait
`First delay` (see `Settings`).

The acquisition will take all the selected colors as defined in `Settings` `Active leds`.

If you need to stop the acquisition press twice the rotary-push button.

After the acquisition the display will show the absorbance for all the selected colors.
To see all the values you need to turn the rotary-push button.

### 2. Acquisition sequence

This mode allows to acquire a sequence of sample. For example if you want to check the Beer-Lambert
law you would first but a blank, then all the known concentration sample and finally the unknown concentration
sample.

Between each sample you press the button to go to the next experiment. The spectro will expect the number
of experiments defined in `Settings` `Number exp`. In order to stop the acquisition before the end you need to
turn the rotary push button and press `Stop acquis.`. You will then directly see the results.

To check the results you need to go in the menu `Results` (see bellow).

### 3. Acquisition kinetic

The spectro is able to acquire automatically a sequence of experiment. There are many `settings` that will
define this behaviour:

- `Before delay`: Time in seconds to wait before acquiring the blank
- `First delay` : Time in seconds to wait before the first experiment

### 4. Results

Shows the acquired results in 3 columns:

- the time (in seconds) since the acquisition of the blank
- the absorbance
- the light intensity as measured by the sensor

The results are shown for the color specified in `Settings` `Result color`.

### 5. Settings

#### 5.1 Before delay

#### 5.2 First delay

#### 5.3 Inter experiment delay

The delay between experiments used for kinetics

#### 5.4 Number of experiments

#### 5.5 Result color

#### 5.6 Rotary mode

#### 5.7 Active leds

#### 5.8 Main menu

Go back to main menu

### 6. Status

Show general information about the spectro:

- current temperature
- battery level (between 3.7 and 4.2 volts) and a sign telling if it is charging `+`, decharging `-` or fully charged `→`
- uptime
- version of the firmware

### 7. Utilities

#### 7.1 Sleep

Put the spectro in sleep (reducing the power consumption to around 100µA)

#### 7.2 Test LED

Allows to check that all the leds are working correctly. With a blank you should obtain
values in the following range:

- R: between 100000 and 450000
- G: between 100000 and 450000
- B: between 100000 and 450000
- UV: between 0 and 2000

To stop the test mode press twice the button.

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

Return to the main menu

## In case of crash

1. Ensure that the battery is not completely flat and connect the spectro to USB
2. Press the button during 10s and release
3. If this still does not work you need to open the spectro, unplug the battery and plug it again

## Accessing from serial port

It is possible to access directly to the data from the serial port.

Please check [this page](serial/README.md) for more information.
