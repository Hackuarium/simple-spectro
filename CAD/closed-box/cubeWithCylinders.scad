module cubeWithCylinders(x, y, z, r) {
    union() {
        cube([x, y, z]);
        translate([0,0,0]) cylinder(h=z, r=r);
        translate([x,0,0]) cylinder(h=z, r=r);
        translate([0,y,0]) cylinder(h=z, r=r);
        translate([x,y,0]) cylinder(h=z, r=r);
    }
}
