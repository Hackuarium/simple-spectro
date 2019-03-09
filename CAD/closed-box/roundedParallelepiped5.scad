module roundedParallelepiped5(x, y, z, r) {
    union() {
        translate([r,r,r]) cylinder(h=z-r, r=r);
        translate([x-r,r,r]) cylinder(h=z-r, r=r);
        translate([r,y-r,r]) cylinder(h=z-r, r=r);
        translate([x-r,y-r,r]) cylinder(h=z-r, r=r);
        translate([r,0,r]) cube([x-2*r, y, z-r]);
        translate([0,r,r]) cube([x, y-2*r, z-r]);
        
        translate([r,r,r]) sphere(r=r);
        translate([x-r,r,r]) sphere(r=r);
        translate([r,y-r,r]) sphere(r=r);
        translate([x-r,y-r,r]) sphere(r=r);
        translate([r,r,r]) rotate([0,90,0]) cylinder(h=x-2*r, r=r);
        translate([r,y-r,r]) rotate([0,90,0]) cylinder(h=x-2*r, r=r);
        translate([r,y-r,r]) rotate([90,0,0]) cylinder(h=y-2*r, r=r);
        translate([x-r,y-r,r]) rotate([90,0,0]) cylinder(h=y-2*r, r=r);
        translate([r,r,0]) cube([x-2*r, y-2*r, r]);

    }
}

// roundedParallelepiped5(10,20,30,2);