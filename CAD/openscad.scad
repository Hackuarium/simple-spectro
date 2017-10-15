pcbLength=100;
pcbWidth=50;
pcbThickness=1.6;
pcbSpaceAround=5; // need some space because of rounded angles
thickness=8; // thickness of the external box

// PCB
color("red",0.2) cube([pcbLength, pcbWidth, pcbThickness]);


rounded3DRectangle(x=20, y=10, z=5, r=2);


module rounded3DRectangle(x, y, z, r) {
    hull() {
        translate([r,r,0]) cylinder(h=z, r=r);
        translate([x-r,r,0]) cylinder(h=z, r=r);
        translate([r,y-r,0]) cylinder(h=z, r=r);
        translate([x-r,y-r,0]) cylinder(h=z, r=r);
    }

}