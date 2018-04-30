# How to use it ?

You have mainly 3 modes:
* one acquisition (Blank + Sample)
* a squence of experiments (Blank + many samples)
* a kinetic (Blank + Sample x times)

For one acquisition you may specify the time before the first experiment (Before delay) as well as the time between the 2 experiments (First delay). Those parameters are accessible from the 'settings' menu. You may use the rotary push button to select settings and then press the button to enter the menu.
To change a value, press the button and turn to set the new value. After, press the button again to validate.


## Accessing the device from the Serial Port

It is possible to control the device from the Serial over USB. You may use for example
the command 'screen' on the bash, but the easiest is probably to use the Arduino program.
Indeed the spectrophotometer appears as a 'Lilipad Arduino USB'. It contains an Atmega 32U4 at 8MHz.
If you install the Arduino software you should first select in 'Tools -> Board -> Lilypad Arduino USB' and
it should appear in 'Tools -> Port -> xxx Lilypad Arduino USB'.

Once you select the port on which the spectrophotometer is connect you may use the Serial Monitor
(top right icon) to connect on this device and control it from the keyboard. When you are in the
serial monitor window, first thing is to select 'Both NL & CR' in the bottom right select menu.

You may now control the spectrophotometer. To see the available commands just enter `h` + Enter.

The instruction  `s`  will show you the current settings


| Parameter | Number | Desciption
|-----------|--------|----------------------
|    A      |  0     | Transmission sample color 1
|    B      |  1     | Transmission sample color 2
|    C      |  2     | Transmission sample color 3
|    D      |  3     | Transmission sample color 4
|    E      |  4     | Transmission sample color 5
|    F      |  5     | Transmission blank color 1
|    G      |  6     | Transmission blank color 2
|    H      |  7     | Transmission blank color 3
|    I      |  8     | Transmission blank color 4
|    J      |  9     | Transmission blank color 5
|    K      |  10    | Delay before acquisition of the blank
|    L      |  11    | Delay before the acquisition of the sample
|    M      |  12    | Delay between each acquisition of a kinetic (after blank and first)
|    N      |  13    | Number of experiments for kinetic (max 240 / (number colors + 1))
|    O      |  14    | Number of the next experiment
|    P      |  15    | Current time waiting
|    Q      |  16    | Number of acquisitions of 100ms that will be taken (default 10). This value could be reduced for fast kinetic
|    R      |  17    | Invert the rotary button direction
|    S      |  18    | Battery voltage (hundredth of volt)
|    T      |  19    | Temperature (hundredth of degree)
|    V      |  21    | Active leds and other. A number between 0 and 63. Each bit represents a function (Red, Green, Blue, UV, Voltage, Temperature). 5 would correspond to Red and Blue (binary combination).
|    W      |  22    | Error
|    X      |  23    | Value of the channel that will be displayed in the result
|    Y      |  24    | Status
|    Z      |  25    | Current menu

You may change the parameters `K`, `L`, `M`, `N`, `Q`, `R`, `V` from the command line. To check a value just enter the corresponding uppercase letter (ie `N`) followed by `Enter`. To set a value, enter the new value just after the uppercase letter (ie `N20` to set 20 experiments for kinetic).

To retrieve all the data acquired in a kinetic, the easiest is use the `d` command. This will dump all the acquired data. Please take care that the data is stored in the RAM and it therefore lost when the deviced is not powered.

The dumped data will contain many columns. The first column corresponds to the time (in ms) since the device was started, the next columns correspond to all the acquired colors.
The first line corresponds to the blank and the next lines to the kinetic. The values for each column is directly proprotional to the quantity of light that reaches the detector. If you want to calculate the corresponding absorbance you need to substract to each value the corresponding value of the first row.

There is a utility that will allows to directly [convert and plot the results on-line](http://www.cheminfo.org/?viewURL=https%3A%2F%2Fcouch.cheminfo.org%2Fcheminfo-public%2F7b6eb01da45510275179c4b587bb63f0%2Fview.json&loadversion=true&fillsearch=Analyse+spectro+log) (using Google Chrome).
