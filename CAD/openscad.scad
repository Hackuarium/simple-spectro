pcbLength=100;
pcbWidth=50;
pcbThickness=1.6;
pcbSpaceAround=5; // need some space because of rounded angles

sideThickness=8; 
frontThickness=6; 
frontHeight=20;
overlap=4; // overlap between top and bottom

supportWidth=15;
supportLength=15;
supportHeight=6;
supportHoleX=6;
supportHoleY=4;
supportHoleR=1.5;

screenX=50;
screenY=30;
screenLength=40;
screenWidth=20;

$fn=50;

// PCB
* color("red",1)
    cube([pcbLength, pcbWidth, pcbThickness]);


* translate([-(pcbSpaceAround+sideThickness), -(pcbSpaceAround+sideThickness), 10])
    color("green",0.8) 
        mirror([0,0,1]) 
            roundedParallelepiped5(
                x=pcbLength+pcbSpaceAround+sideThickness,
                y=pcbWidth+pcbSpaceAround+sideThickness,
                z=10,
                r=2
            );

difference() {
    // the front box
    roundedParallelepiped5(
        x=pcbLength+2*pcbSpaceAround+2*sideThickness,
        y=pcbWidth+2*pcbSpaceAround+2*sideThickness,
        z=frontHeight,
        r=2
    );

    // remove the top layer where the PCB is fixed
    translate([sideThickness, sideThickness, supportHeight + frontThickness])
    roundedParallelepiped4(
        x=pcbLength+2*pcbSpaceAround,
        y=pcbWidth+2*pcbSpaceAround,
        z=frontHeight,
        r=2
    );
    
    // remove the bottom layer as 2 roundParallelepiped
    translate([sideThickness+supportLength+pcbSpaceAround, sideThickness+pcbSpaceAround, topThickness])
    roundedParallelepiped4(
        x=pcbLength-2*supportLength,
        y=pcbWidth,
        z=frontHeight,
        r=2
    );
    translate([sideThickness+pcbSpaceAround, sideThickness+supportWidth+pcbSpaceAround, topThickness])
    roundedParallelepiped4(
        x=pcbLength,
        y=pcbWidth-2*supportWidth,
        z=frontHeight,
        r=2
    );
    
    // we need to remove some material so that is fits together
        translate([sideThickness/2, sideThickness/2, frontHeight - overlap])
    roundedParallelepiped4(
        x=pcbLength+2*pcbSpaceAround+sideThickness,
        y=pcbWidth+2*pcbSpaceAround+sideThickness,
        z=frontHeight,
        r=2
    );
    
    // remove the holes to fix the PCB
    translate([sideThickness+pcbSpaceAround+supportHoleX, sideThickness+pcbSpaceAround+supportHoleY, frontThickness])
        cylinder(r=supportHoleR, h=frontHeight);
    
    translate([sideThickness+pcbSpaceAround+pcbLength-supportHoleX, sideThickness+pcbSpaceAround+supportHoleY, frontThickness])
        cylinder(r=supportHoleR, h=frontHeight);
    
    translate([sideThickness+pcbSpaceAround+supportHoleX, sideThickness+pcbSpaceAround++pcbWidth-supportHoleY, frontThickness])
        cylinder(r=supportHoleR, h=frontHeight);
    
    translate([sideThickness+pcbSpaceAround+pcbLength-supportHoleX, sideThickness+pcbSpaceAround+pcbWidth-supportHoleY, frontThickness])
        cylinder(r=supportHoleR, h=frontHeight);
        
    // we will remove the hole for the screen
    translate([screenX, screenY, -10])
        cube([screenLength, screenWidth, frontHeight]);
}



module roundedParallelepiped4(x, y, z, r) {
    hull() {
        translate([r,r,0]) cylinder(h=z, r=r);
        translate([x-r,r,0]) cylinder(h=z, r=r);
        translate([r,y-r,0]) cylinder(h=z, r=r);
        translate([x-r,y-r,0]) cylinder(h=z, r=r);
    }
}

// top face is flat
module roundedParallelepiped5(x, y, z, r) {
   echo(x,y,z,r);
    hull() {
        translate([r,r,0]) sphere(r=r);
        translate([x-r,r,0]) sphere(r=r);
        translate([r,y-r,0]) sphere(r=r);
        translate([x-r,y-r,0]) sphere(r=r);
        translate([r,r,z-r]) cylinder(h=r, r=r);
        translate([x-r,r,z-r]) cylinder(h=r, r=r);
        translate([r,y-r,z-r]) cylinder(h=r, r=r);
        translate([x-r,y-r,z-r]) cylinder(h=r, r=r);
    }
}

module roundedParallelepiped6(x, y, z, r) {
   echo(x,y,z,r);
    hull() {
        translate([r,r,0]) sphere(r=r);
        translate([x-r,r,0]) sphere(r=r);
        translate([r,y-r,0]) sphere(r=r);
        translate([x-r,y-r,0]) sphere(r=r);
        translate([r,r,z-r]) sphere(r=r);
        translate([x-r,r,z-r]) sphere(r=r);
        translate([r,y-r,z-r]) sphere(r=r);
        translate([x-r,y-r,z-r]) sphere(r=r);
    }
}