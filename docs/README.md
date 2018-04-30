# DIY spectrophotometer

The goal is to create a simple spectrophotometer that measures the
absorbance of a sample at 3 different light colors (red, green, blue), is
autonomous (on battery) and displays the result on a LCD screen.

The initial idea was that you could teach spectrophotometry without
having to buy an expensive instrument, since you can find experiments
that does not require a specific light wavelength. This includes
optical density for bacteria culture, determination of a pigments cncentration in a solution, determination of the kinetic of a reaction and many others.

The device is rather cheap if you buy all the components on aliexpress 
(but one) and have access to a 3D printer. By constructing 10, the price
per spectrophotometer is around $30. However if you want to have a final
product with metal case and assembly, the cost would rather be $90 each if you order 20 of them.

<img src='0-intro/intro.jpg' width='600px' />

## Can we do science with this ?

Before trying to explain how it is done more in detail maybe the first question that we should answer is : can we do science with this ? When thinking about the design of the spectro, we found an electronic component that converts the light energy to frequency and that is linear on a range of nearly 10^6. Only the precision of the component is therefore really promising and shows that we could
do something that gives good results.

* [in chemistry](6-applications/chemistry)
* [in biology](6-applications/biology)

## Using the simple spectrophotometer to teach science

The use of the spectrophotometer is rather simple. Just put a blank, press the button, wait 10s and put the sample. The result is displayed on the screen.

[Using the spectrophotometer](https://www.youtube.com/watch?v=ZfckWQn0Nws)

This device allows to understand how spectrophotometer works. As a result we used it to teah to groups of children and teenager some basic scientific concepts.

[School in Mondomo (Colombia)](https://www.youtube.com/watch?v=Be6p4-nW06k)


## How to make it ?

The project is composed of 3 parts:
* [the PCB](1-pcb) (using eagle)
* [the case](2-case) (using FreeCAD and OpenSCAD)
* [the software](3-software) (using Arduino)

## How to use it ?

[Userguide and connection to the computer](5-use)

## Tests
  * [Reproducibility of results](4-tests/stability)

## Applications
  * [In chemistry](6-applications/chemistry)
  * [In biology](6-applications/biology)

# Workshop
We organize un one day workshop "Build your spectrophotometer"
  * [Slides](7-misc/workshop/slides.pdf)
