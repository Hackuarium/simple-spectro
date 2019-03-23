$fn=50;

screenLength=71.6;
screenWidth=25.1;
screenProtectionSize=3;

! projection(cut=false) translate([0, 0, -10])
    roundedParallelepiped4(
            x=screenLength+2*screenProtectionSize,
            y=screenWidth+2*screenProtectionSize,
            z=screenWidth,
            r=1.5
        );
 
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
