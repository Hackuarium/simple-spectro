# Electronics, the PCB

The design is compatible with an Arduino. We use the
ATMEGA32U4 microcontroller that is directly connected to the components we need for
this spectrophotometer.

We prefer to design the full board rather than to use a shield. The
extra work to add the microcontroller is rather limited so it does
not make sense from our point of view to create a shield.

The PCB is designed on [Eagle](https://www.autodesk.com/products/eagle/overview). While
this software is rather expensive it is free to use for personal projects 
that have a surface under 80 cm2, which is the case for this board.

We have produced the PCB on [pcbway](https://www.pcbway.com/) that gives excellent 
quality work for $5 for 10 PCB (+ shipping). They are really competitive and 
fast. In our case it costs $30 with shipping and we receive the PCBs in one week.

All the components we use but one are rather mainstream and can
be found on ebay or aliexpress. The only special component  is the light to frequency converter [TSL235R](https://www.sparkfun.com/datasheets/Sensors/Imaging/TSL235R-LF.pdf)
that we buy on [Mouser website](http://www.mouser.com).

<img src='pcb-description.001.jpeg' width='600' />

The board is rather straighforward. The resistors values for the LEDs may however have to be tuned depending on the LEDs you are using. 
If the value is too weak, the detector may saturate and you will get a message 'OVER'. It will also blink just once instead of 10 times.


* [Soldering the PCD](solder)
* [Calibration of LEDs](calibration)
* [Power and battery](power)
* [Debug](voltages)