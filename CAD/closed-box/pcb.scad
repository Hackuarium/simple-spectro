module pcb(shift, pcbLength, pcbWidth, pcbThickness) {
    color("red",0.2)
        translate([shift,shift,-50])
            cube([pcbLength, pcbWidth, pcbThickness]);
}

            