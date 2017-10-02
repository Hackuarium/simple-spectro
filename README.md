The goal is to create a simple spectrophotometer that measure the
absorbance of a sample at 3 different colors (red, green, blue), is
autonomous (on battery) and display the result on a screen.

The initial idea was that you could teach spectrophotometry without
having to buy an expensive instrument because you can find experiments
that does not require a single wavelength. This could included
optical density for bacteria culture, determination of a pigment in
a solution, determination of the kinetic of a reaction.

The device is rather cheap if you buy all the component on aliexpress 
(but one) and hav eaccess to a 3D printer. By constructing 10 the price
per spectrophotometer is around $25.

<img src='images/patent-blue-v.jpg' width=600>

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
pattent blue V (E131). A blue pigment that is used in various bleu
candies.

<img src='images/patent-blue-v-regression.png' width=600>

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

<img src='images/bacteria-growing-preliminary.png'>

This experiment shows clearly the log phase and the stationary phase. But
the experiment was faster than expected ... an acquisition every 15 minutes
would be a better choice.

### Using the simple spectrophotometer to teach science

The use of the spectrophotometer is rather simple. Just put a blank, press the button,
wait 10s and put the sample. The result is displayed on the screen.

[Using the spectrophotometer](https://www.youtube.com/watch?v=ZfckWQn0Nws)

This device allows to understand hor spectrophotometer works and we were
teaching to group of children and teenager some basic of science

[School in Mondomo (Colombia)](https://www.youtube.com/watch?v=Be6p4-nW06k)

## How to make it ?

The project is composed of 3 parts:
* the PCB (using eagle)
* the case (using FreeCAD and 3D printer)
* the programmation (using Arduino)

## Electronics, the PCB

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
be found on ebay or aliexpress. The only special component  is the light to
frequency converter (TSL235R)[https://www.sparkfun.com/datasheets/Sensors/Imaging/TSL235R-LF.pdf]
that we buy on (Mouser website)[http://www.mouser.com].

<img src='images/pcb-description/pcb-description.001.jpeg' width=600>

The board is rather straighforward. The values for the LEDs may however have to be tuned
depending the LED you are using. Currently the following values are used:
* R: 470 Ω
* G: 680 Ω
* B: 680 Ω
* UV: 100 Ω

If the value is too weak the detector may saturate and you will get a message 'OVER'.


## The case

The case is done using FreeCAD. This software looks rather complex at first but has the huge
advantage that all the parameters may be set in an internal spreadsheet. This allows to design
parametrics boxes that can be easily changed and updated.

We are still improving it a little bit but the top part of the obx is in 'top.stl'

## The software
