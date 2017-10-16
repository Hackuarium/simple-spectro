pcbLength=100;
pcbWidth=50;
pcbThickness=1.6;
pcbSpaceAround=5; // need some space because of rounded angles

sideThickness=8; 
frontThickness=6; 
frontHeight=20;
bottomThickness=6;
bottomHeight=30;
overlap=4; // overlap between top and bottom

supportWidth=15;
supportLength=15;
supportHeight=6;
supportHoleX=6;
supportHoleY=4;
supportHoleR=1.5;
bottomHoleR=3;
bottomHoleHeight=4;

rotaryX=80;
rotaryY=30;
rotaryR=2;

screenX=30;
screenY=30;
screenLength=40;
screenWidth=20;

cuvetteX=50;
cuvetteY=10;
cuvetteInternal=10;
cuvetteThickness=3;
cuvetteWindow=4;
cuvetteWindowHeight=5;
cuvetteBottomSpace=2;

batteryX=70;
batteryY=20;
batteryLength=30;
batteryWidth=30;

$fn=30;

// PCB
* color("red",0.2)
    translate([0,0,supportHeight+frontThickness])
        cube([pcbLength, pcbWidth, pcbThickness]);

// create the bottom part 
translate([-pcbSpaceAround-sideThickness, -pcbSpaceAround-sideThickness, 50])
    difference() {
        roundedParallelepiped6(
            x=pcbLength+2*pcbSpaceAround+2*sideThickness,
            y=pcbWidth+2*pcbSpaceAround+2*sideThickness,
            z=bottomHeight,
            r=2
        );
        
        // remove the external border so it fits in the other part
        difference() {
            roundedParallelepiped5(
                x=pcbLength+2*pcbSpaceAround+2*sideThickness,
                y=pcbWidth+2*pcbSpaceAround+2*sideThickness,
                z=overlap,
                r=2
            );
            translate([sideThickness/2, sideThickness/2, 0])
                roundedParallelepiped4(
                    x=pcbLength+2*pcbSpaceAround+sideThickness,
                    y=pcbWidth+2*pcbSpaceAround+sideThickness,
                    z=overlap,
                    r=2
                );
        }
        
        // remove the hole for cuvette
        translate([
            cuvetteX-cuvetteBottomSpace+pcbSpaceAround+sideThickness,
            cuvetteY-cuvetteBottomSpace+pcbSpaceAround+sideThickness,
            0
        ])
        roundedParallelepiped4(x=cuvetteInternal+2*cuvetteBottomSpace, y=cuvetteInternal+2*cuvetteBottomSpace, z=bottomHeight-bottomThickness, r=2);
        
          // remove the hole for battery
        translate([
            batteryX+pcbSpaceAround+sideThickness,
            batteryY+pcbSpaceAround+sideThickness,
            0
        ])
        roundedParallelepiped4(x=batteryLength, y=batteryWidth, z=bottomHeight-bottomThickness, r=2);
        
        // make holes for screws
        translate([sideThickness+pcbSpaceAround+supportHoleX, sideThickness+pcbSpaceAround+supportHoleY, 0])
            cylinder(r=bottomHoleR, h=bottomHoleHeight);
        
        translate([sideThickness+pcbSpaceAround+pcbLength-supportHoleX, sideThickness+pcbSpaceAround+supportHoleY, 0])
            cylinder(r=bottomHoleR, h=bottomHoleHeight);
        
        translate([sideThickness+pcbSpaceAround+supportHoleX, sideThickness+pcbSpaceAround++pcbWidth-supportHoleY, 0])
            cylinder(r=bottomHoleR, h=bottomHoleHeight);
        
        translate([sideThickness+pcbSpaceAround+pcbLength-supportHoleX, sideThickness+pcbSpaceAround+pcbWidth-supportHoleY, 0])
            cylinder(r=bottomHoleR, h=bottomHoleHeight);
            
    }
    


// create the cuvette
translate([cuvetteX, cuvetteY, 0])
    cuvette(
        frontHeight,
        r=2,
        cuvetteInternal,
        cuvetteY,
        overlap,
        pcbSpaceAround,
        supportHeight,
        frontThickness,
        pcbThickness
    );

// create the box with the holes
translate([-pcbSpaceAround-sideThickness, -pcbSpaceAround-sideThickness, 0])
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
        translate([sideThickness+supportLength+pcbSpaceAround, sideThickness+pcbSpaceAround, frontThickness])
            roundedParallelepiped4(
                x=pcbLength-2*supportLength,
                y=pcbWidth,
                z=frontHeight,
                r=2
            );
        translate([sideThickness+pcbSpaceAround, sideThickness+supportWidth+pcbSpaceAround, frontThickness])
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
        
        // remove for the rotary push button
        translate([rotaryX, rotaryY, 0])
            cylinder(r=rotaryR, h=frontThickness);
            
            
        // we will remove the hole for the screen
        translate([screenX, screenY, 0])
            cube([screenLength, screenWidth, frontThickness]);
            
                // create the hole for cuvette
        translate([cuvetteX+sideThickness+pcbSpaceAround, cuvetteY+sideThickness+pcbSpaceAround, 0])
            cube([cuvetteInternal, cuvetteInternal, frontHeight]);
    }







// reference is based on 0,0 on the hole
module cuvette() {
    difference() {
        union() {
            // the cuvette itself
            hull() {
                translate([-cuvetteThickness,-cuvetteY-pcbSpaceAround,0]) cube([r,r,frontHeight-overlap]);
                translate([cuvetteInternal+cuvetteThickness-r,-cuvetteY-pcbSpaceAround,0]) cube([r,r,frontHeight-overlap]);
            
                translate([-cuvetteThickness+r,cuvetteInternal + cuvetteThickness - r,0]) cylinder(h=frontHeight-overlap, r=r);
                translate([cuvetteInternal+cuvetteThickness-r,cuvetteInternal+cuvetteThickness-r,0]) cylinder(h=frontHeight-overlap, r=r);
            }
            // little extension to make round corners
            translate([-r-cuvetteThickness,-pcbSpaceAround-cuvetteY, 0])
                cube([cuvetteInternal+cuvetteThickness*2+2*r,r,frontHeight-overlap]);
            
            translate([-r-cuvetteThickness,-cuvetteY, 0])
                cube([cuvetteInternal+cuvetteThickness*2+2*r,r,supportHeight+frontThickness]);
        }
       
        // round corners
        translate([-r-cuvetteThickness,-cuvetteY+r,0]) cylinder(h=supportHeight+frontThickness, r=r);
        translate([cuvetteInternal+cuvetteThickness+r,-cuvetteY+r,0]) cylinder(h=supportHeight+frontThickness, r=r);
        
        // round corners
        translate([-r-cuvetteThickness,-pcbSpaceAround-cuvetteY+r,0]) cylinder(h=frontHeight-overlap, r=r);
        translate([cuvetteInternal+cuvetteThickness+r,-pcbSpaceAround-cuvetteY+r,0]) cylinder(h=frontHeight-overlap, r=r);
        
        // create the hole for cuvette
        translate([0, 0, 0])
            cube([cuvetteInternal, cuvetteInternal, frontHeight]);
        
        // cutting the windows in cuvette ...
        heightWindow=pcbThickness+frontThickness+supportHeight;
        translate([-cuvetteThickness, (cuvetteInternal-cuvetteWindow)/2, heightWindow])
            cube([cuvetteThickness, cuvetteWindow, frontHeight-overlap]);
        translate([cuvetteInternal, (cuvetteInternal-cuvetteWindow)/2, heightWindow])
            cube([cuvetteThickness, cuvetteWindow, frontHeight-overlap]);
        translate([(cuvetteInternal-cuvetteWindow)/2, cuvetteInternal,  heightWindow])
            cube([cuvetteWindow, cuvetteThickness, frontHeight-overlap]);
    }
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
        translate([r,r,r]) sphere(r=r);
        translate([x-r,r,r]) sphere(r=r);
        translate([r,y-r,r]) sphere(r=r);
        translate([x-r,y-r,r]) sphere(r=r);
        translate([r,r,z-r]) cylinder(h=r, r=r);
        translate([x-r,r,z-r]) cylinder(h=r, r=r);
        translate([r,y-r,z-r]) cylinder(h=r, r=r);
        translate([x-r,y-r,z-r]) cylinder(h=r, r=r);
    }
}

module roundedParallelepiped6(x, y, z, r) {
   echo(x,y,z,r);
    hull() {
        translate([r,r,r]) sphere(r=r);
        translate([x-r,r,r]) sphere(r=r);
        translate([r,y-r,r]) sphere(r=r);
        translate([x-r,y-r,r]) sphere(r=r);
        translate([r,r,z-r]) sphere(r=r);
        translate([x-r,r,z-r]) sphere(r=r);
        translate([r,y-r,z-r]) sphere(r=r);
        translate([x-r,y-r,z-r]) sphere(r=r);
    }
}