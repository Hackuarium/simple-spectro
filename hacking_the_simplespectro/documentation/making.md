# How to make the spectro-plongeur ?

## List of materials

- translucent acrylic, 3mm thickness
- sheathing
- self-curing acrylic - autopolimerizable acrylic resin
- silicone glue
- cables 26W 
- a soldered PCB with cables for the two LEDs and the receptor

## The acrylic parts

The three parts 7.1, 7.2 and 7.3 are cut using a CNC X-Carve 1000mm x 1000mm from Inventables. The 2D drawings can be found in https://github.com/Hackuarium/simple-spectro/tree/master/hacking_the_simplespectro/CAD. Open the .svg files in easel.inventables.com (a free account can be created). This application allows the user to choose the cut settings. In our case, a 2mm spindle was used and the cut settings were: feed rate - 635mm/min, plunge rate - 228.6 m/min, depth per pass - 0.6 mm

<figure>
<img src="https://github.com/Hackuarium/simple-spectro/blob/Test/hacking_the_simplespectro/images/cutting.jpg" 
alt="Cutting the parts" width="360" height="270" border="10" style="transform:rotate(90deg);"/>
<figcaption>Cutting acrylic with X-Carve CNC.</figcaption>
</figure>

## Assemble the spectro-plongeur

Connect the LEDs and the receptor with sheath to the right cables of the PCB. The parts are pasted together with acrylic resin. It comes in two products, a powder and a liquid. Mix both in roughly one to one proportion in order to get a paste that can be applied in a thin layer on the parts. Apply on the whole surface and let dry for an hour. Repeat the procedure with all parts, making sure the cables are well inserted in the channels. The assembly is clenched with tools for drying. Finally, apply a layer of silicone glue on the junctions on the edge of the spectro-plongeur and let dry for a day.

<figure>
<img src="https://github.com/Hackuarium/simple-spectro/blob/Test/hacking_the_simplespectro/images/pasting.jpg" 
alt="Pasing the parts" width="360" height="270" border="10" />
<figcaption>Pasting the parts with acrylic resin.</figcaption>
</figure>



The spectro-plongeur is then ready to be used - see https://github.com/Hackuarium/simple-spectro/blob/master/hacking_the_simplespectro/documentation/using.md.
