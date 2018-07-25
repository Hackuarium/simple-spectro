# How to make the spectro-plongeur ?

## List of materials

- translucent acrylic, 3mm thickness
- sheathing
- self-curing acrylic - autopolimerizable acrylic resin
- silicone glue
- cables 26W 
- a soldered PCB with cables for the two LEDs and the receptor

<figure>
<img src="https://github.com/Hackuarium/simple-spectro/blob/Test/hacking_the_simplespectro/images/pcb.jpg" 
alt="the PCB of the spectro-plongeur" width="360" height="270" border="10" />
<figcaption>The PCB of the spectro-plongeur. See https://github.com/Hackuarium/simple-spectro/tree/master/docs/1-pcb/solder for instructions on how to solder it.</figcaption>
</figure>

## The acrylic parts

The three parts 7.1, 7.2 and 7.3 are cut using a CNC X-Carve 1000mm x 1000mm from Inventables. The 2D drawings can be found in https://github.com/Hackuarium/simple-spectro/tree/master/hacking_the_simplespectro/CAD. Open the .svg files in easel.inventables.com (a free account can be created). This application allows the user to choose the cut settings. In our case, a 2mm spindle was used and the cut settings were: feed rate - 635mm/min, plunge rate - 228.6 m/min, depth per pass - 0.6 mm

<figure>
<img src="https://github.com/Hackuarium/simple-spectro/blob/Test/hacking_the_simplespectro/images/cutting.jpg" 
alt="Cutting the parts" width="360" height="270" border="10" style="transform:rotate(90deg);"/>
<figcaption>Cutting acrylic with X-Carve CNC.</figcaption>
</figure>

## Assemble the spectro-plongeur

Connect the LEDs and the receptor with sheath to the right cables of the PCB. The parts are pasted together with multipurpose adhesive liquid silicone. The glue is applied thoroughly in a thin layer on the parts (1 and 2), making sure the glue forms a continuous line on the edges to prevent leaks. Let dry for an hour. Repeat the procedure with the third part. The cables must be well inserted in the channels. The assembly is clenched with tools for drying. The surface near the receptor is polished until it can be distinguished through the acrylic. If necessary, apply a layer of silicone on the junctions on the edge of the spectro-plongeur and let dry again. Immerse it in water for at least an hour (water may seeps in very slowly through small cracks)  to check if it is waterproof. If not, apply another layer of silicone. Finally, solder a 8 pins connection to the spectro-plongeur and the PCB. 

The spectro-plongeur is then ready to be used - see https://github.com/Hackuarium/simple-spectro/blob/master/hacking_the_simplespectro/documentation/using.md.

<figure>
<img src="https://github.com/Hackuarium/simple-spectro/blob/Test/hacking_the_simplespectro/images/pasting.jpg" 
alt="Pasting the parts 1 and 2" width="360" height="270" border="10" />
<figcaption>Pasting parts 1 and 2 with silicone.</figcaption>
</figure>



<figure>
<img src="https://github.com/Hackuarium/simple-spectro/blob/Test/hacking_the_simplespectro/images/pins_connection.jpg" 
alt="8 pins connection" width="360" height="270" border="10" />
<figcaption>8 pins connection of the spectro-plongeur.</figcaption>
</figure>



