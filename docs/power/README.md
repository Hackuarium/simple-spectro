
## Design of the battery part

The device can be powered on a rechargeable battery. The power management
is designed based on [this application note](power-design.pdf).

## Evolution of the battery voltage

The LiPo battery provided as around 750 mAh which corresponds to 2 days of use. The
evolution of the battery voltage versus time can be seen on the following chart

<img src="battery.svg" width=600>

The continuous consumption of the device (v1.4.1) is around 17 mA.


## Detailed consumption of v1.4.1

### Only power supply and LM1117 (no LCD, temperature, TSL235):

**12.80 mA**

### Microcontroller in sleep mode:

**5.4mA**

While the sleep mode of the ATMEGA32U4 is expected to be
around 5μA we are very far from this value with this board.

### Removing the yellow LED

**4.3mA**

This control led is rather useless and by removing it we
win around 1mA.

### Replace LM1117 by MCP1703

**200μA**

It is clear that the LM1117 is not the best choice for this
application because not only it consume around 5mA but also
it is not expected to stabilize the voltage if there is no
power consumption.

Clearly the MCP1703 is the way to go !

### Some more tests

Check R15 : required to activate transistor.
Replacing by 330k instead of 100k increase the power consumption ?!

It seems difficult to reduce the sleep consumption to under 200μA.
The battery being of around 750mA/h this means that we should achieve over 100 days in sleep mode.

With MCP1703 and only the microcontroller (and power management) the consumption of the board running is 10mA.

### Sleep mode and digital IN / OUT and HIGH / LOW

We did some testing to find out in which state the 
microcontroller consume the less. It appears that by
putting all the pins to digital IN and to HIGH the consumption is the lowest.

* OUTPUT / HIGH : 227μA
* OUTPUT / LOW : 228μA
* INPUT / HIGH : 190μA !!!
* INPUT / LOW : 226μA
