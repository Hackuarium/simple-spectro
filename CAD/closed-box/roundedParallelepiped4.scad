module roundedParallelepiped4(x, y, z, r) {
    union() {
        translate([r,r,0]) cylinder(h=z, r=r);
        translate([x-r,r,0]) cylinder(h=z, r=r);
        translate([r,y-r,0]) cylinder(h=z, r=r);
        translate([x-r,y-r,0]) cylinder(h=z, r=r);
        translate([r,0,0]) cube([x-2*r, y, z]);
        translate([0,r,0]) cube([x, y-2*r, z]);
    }
}