The goal is to create a simple spectrophotometer that measure the
absorbance of a sample at 3 different colors (red, green, blue), is
autonomous (on battery) and display the result on a screen.

The initial idea was that you could teach spectrophotometry without
having to buy an expensive instrument because you can find experiments
that does not require a single wavelength. This could included
optical density for bacteria culture, determination of a pigment in
a solution, determination of the kinetic of a reaction.

The device is rather cheap if you buy all the component on aliexpress 
(but one) and have access to a 3D printer. By constructing 10 the price
per spectrophotometer is around $30. However if you want to have a final
product with metal case and assembly the cost would rather be $90 if you 
order 20 of them.

<img src='images/patent-blue-v.jpg' width='600px' />

## Some more documentation

* [Soldering the board](docs/solder)
* [Installing the spectrophotometer in the case](docs/case)
* [Power management](docs/power)

## Can we do science with this ?

Before trying to explain how it is done more in detail maybe the first
question that we should answer is : can we do science with this ? When 
thinking about the design of the spectro we found an electronic
component that converts the light energy to frequency and that is linear
on a range of nearly 10^6. This look really promising that we could
do something that gives good results.

### Patent blue V

To begin we did a very simple experiment that allows to measure the 
absorbance of solutions containing different known concentration of
pattent blue V (E131). A blue pigment that is used in various blue
candies.

<img src='images/patent-blue-v-regression.png' width='600px' />

The result is rather good knowing that the solutions were simply prepared by
adding with a 1mL seringe various volume (0 to 2 mL) of a concentrated solution
to 100mL of water. Not the more accurate method.

### Escherichia coli

Another feature of the simple spectrophotometer is that it works on a 
rechargeable battery (for 2 days) and therefore you can measure a kinetic
even in an incubator.

Optical density (OD) at 600nm is often used in biology to determine the
biomass increase versus the time. In this experiment we have placed 
Escherichia coli with cell growing media directly in the spectrophotometer
cuvette and place the spectrophotometer itself on a shaker in the incubator.
We can then program it to take an abosrbance every X seconds. In our case
we did every 30 minutes (up to 40 measures). The following curve is obtained

<img src='images/bacteria-growing-preliminary.png' />

This experiment shows clearly the log phase and the stationary phase. But
the experiment was faster than expected ... an acquisition every 15 minutes
would be a better choice.

## Using the simple spectrophotometer to teach science

The use of the spectrophotometer is rather simple. Just put a blank, press the button,
wait 10s and put the sample. The result is displayed on the screen.

[Using the spectrophotometer](https://www.youtube.com/watch?v=ZfckWQn0Nws)

This device allows to understand hor spectrophotometer works and we were
teaching to group of children and teenager some basic of science

[School in Mondomo (Colombia)](https://www.youtube.com/watch?v=Be6p4-nW06k)

## How to use it ?

You have mainly 2 modes:
* one acquisition (Blank + Sample)
* a kinetic (Blank + Sample x times)

For one acquisition you may specify the time before the first experiment (Before delay)
as well as the time between the 2 experiments (First delay). Those parameters are accessible
from the 'settings' menu. You may use the rotary push button to select settings and then
press the button to enter the menu.
To change a value, press the button and turn to set the new value. After press again the button
to validate.


### Accessing the device from the Serial Port

It is possible to control the device from the Serial over USB. You may use for example
the command 'screen' on the bash but the easiest is probably to use the program Arduino.
Indeed the spectrophotometer appears as a 'Lilipad Arduino USB'. It contains an Atmega 32U4 at 8MHz.
If you install the Arduino software you should first select in 'Tools -> Board -> Lilypad Arduino USB' and
it should appear in 'Tools -> Port -> xxx Lilypad Arduino USB'.

One you select the port on which the spectrophotometer is connect you may use the Serial Monitor
(top right icon) to connect to this device and control it from the keyboard. When you are in the
serial monitor window, first thing is to select 'Both NL & CR' in the bottom right select menu.

You may now control the spectrophotometer. To see the available command just enter  h  and Enter.

The instruction  s  will show you the current settings


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
|    M      |  12    | Delay between the each acquisition of a kinetic (after blank and first)
|    N      |  13    | Number of experiments for kinetic (max 240 / (number colros + 1))
|    O      |  14    | Number of the next experiment
|    P      |  15    | Current time waiting
|    Q      |  16    | Number of acquisition of 100ms that will be taken (default 10). This value could be reduced for fast kinetic
|    R      |  17    | Invert the rotary direction
|    S      |  18    | Battery voltage (hundredth of volt)
|    T      |  19    | Temperature (hundredth of degree)
|    V      |  21    | Active leds and other. A number between 0 and 63. Each bit represents a function (Red, Ggreeb, Bleu, UV, Voltage, Temperature). 5 would corresponds to Red and Blue.
|    W      |  22    | Error
|    X      |  23    | Value of the channel that will be displayed in the result
|    Y      |  24    | Status
|    Z      |  25    | Current menu

You may change the parameter `K`, `L`, `M`, `N`, `Q`, `R`, `V` from the command line. To check a value just enter the corresponding uppercase letter (ie `N`) followed by `Enter`. To set a value just enter the new value just after (ie `N20` to set 20 experiments for kinetic).

To retrieve all the data acquired in a kinetic, the easiest is use the `d` command. This will dump all the acquired data. Please take care that the data are stored in RAM and it is lost in case there is no power.

The dump data will contains many columns. The first column corresponds to the time (in ms) since the device was started, the next columns correspond to all the acquired colors.
The first line corresponds to the blank and the next lines to the kinetic. The values for each column is directly proprotional to the quantity of light that reach the detector. If you want to calculate the corresponding absorbance you need to substract to each value the corresponding value of the first row.

There is a utility that will allow to directly [convert and plot the results on-line](http://www.cheminfo.org/?viewURL=https%3A%2F%2Fcouch.cheminfo.org%2Fcheminfo-public%2F7b6eb01da45510275179c4b587bb63f0%2Fview.json&loadversion=true&fillsearch=Analyse+spectro+log) (using Google Chrome).

## How to make it ?

The project is composed of 3 parts:
* the PCB (using eagle)
* the case (using FreeCAD and 3D printer)
* the programmation (using Arduino)

### Electronics, the PCB

The design is compatible with an Arduino. We use the microcontroller
ATMEGA32U4 that is directly connected to the components we need for
this spectrophotometer.

We prefer to design the full board rather that to use a shield. The
extra work to add the microcontroller is rather limited so it does
not make sence at our point of view to create a shield.

The PCB is designed on [Eagle](https://www.autodesk.com/products/eagle/overview). While
this software is rather expensive it is free to use for personal projects 
that have a surface under 80 cm2 which is the case for this board.

We have produced the PCB on [pcbway](https://www.pcbway.com/) that gives excellent 
quality work for $5 for 10 PCB (+ shipping). They are really very competitive and 
fast. In our case it cost $30 with shipping and we receive PCBs in one week.

All the components we use but one are rather mainstream and can
be found on ebay or aliexpress. The only special component  is the light to frequency converter [TSL235R](https://www.sparkfun.com/datasheets/Sensors/Imaging/TSL235R-LF.pdf)
that we buy on [Mouser website](http://www.mouser.com).

<img src='images/pcb-description/pcb-description.001.jpeg' width='600' />

The board is rather straighforward. The values for the LEDs may however have to be tuned
depending the LED you are using. Currently the following values are used:
* R: 470 Ω
* G: 1 kΩ
* B: 1 kΩ
* UV: 100 Ω

If the value is too weak the detector may saturate and you will get a message 'OVER'.


### The case

The case is done using FreeCAD. This software looks rather complex at first but has the huge advantage that all the parameters may be set in an internal spreadsheet. This allows to design parametric boxes that can be easily changed and updated.

Currently we have 2 vesions of the box:
* the open-box can be easily open to understand the way it works
* the closed-box is designed to be screwed and possibly done by milling aluminium.

### The software

When you finish soldering the PCB you need to burn the boot loader. Before this tep you will not be able to control the device from USB.

To burn the boot loader you should first install the Arduino program and select in 'Tools -> Board -> Lilypad Arduino USB'. You may then either use a 'tag-connect' connected to a USBTinyISP or a normal cable for ICSP (you will have to solder the IDC 6 pins socket in this case).

Once the bootloader has been burned you should be able to select it from the Arduino program in it should appear in 'Tools -> Port -> xxx Lilypad Arduino USB'. You can now open the eagle project and program the spectrophotometer.

In order to set raisonnable parameters you should make a reset either from the Serial menu or from the LCD (Utilities -> Reset). The spectrophotometer is now ready to be used. 
