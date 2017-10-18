pcbLength=98.7;
pcbWidth=73.2;
pcbThickness=1.6;
pcbSpaceAround=1; // need some space because of rounded angles

sideThickness=4; 
frontThickness=4; 
bottomThickness=6;
bottomHeight=12;
overlap=4; // overlap between top and bottom

shift=pcbSpaceAround+sideThickness;

supportWidth=6;
supportLength=6;
supportHeight=7;
supportHoleX=3.5;
supportHoleY=3.5;
supportHoleR=1.5;
bottomHoleR=3;
bottomHoleHeight=4;

rotaryX=13.2+shift;
rotaryY=12.8+shift;
rotaryR=4;
rotaryExtension=2;
rotaryExtensionR=6;

screenX=13.4+shift;
screenY=40.5+shift;
screenLength=71.6;
screenWidth=25.1;

cuvetteX=48.7+shift;
cuvetteY=5.4+shift;
cuvetteInternal=12.9;
cuvetteThickness=1.6;
cuvetteWindow=3;
cuvetteWindowHeight=5;
cuvetteBottomSpace=2;

batteryX=10+shift;
batteryY=40+shift;
batteryLength=70;
batteryWidth=30;

screenProtectionHeight=1.5;

radius=3; // using bit of 3

usbHeight=5.8;
usbWidth=10;
usbY=38.2+shift;

frontHeight=frontThickness+usbHeight+supportHeight+pcbThickness;

$fn=10;

// PCB
* color("red",0.2)
    translate([shift,shift,-50])
        cube([pcbLength, pcbWidth, pcbThickness]);

// create the bottom part 
*translate([0, 0, 50])
    difference() {
        cube([
            pcbLength+2*pcbSpaceAround+2*sideThickness,
            pcbWidth+2*pcbSpaceAround+2*sideThickness,
            bottomHeight
        ]);
        
        // remove the external border so it fits in the other part
        difference() {
            cube([
                pcbLength+2*pcbSpaceAround+2*sideThickness,
                pcbWidth+2*pcbSpaceAround+2*sideThickness,
                overlap
            ]);
            translate([sideThickness/2, sideThickness/2, 0])
                roundedParallelepiped4(
                    x=pcbLength+2*pcbSpaceAround+sideThickness,
                    y=pcbWidth+2*pcbSpaceAround+sideThickness,
                    z=overlap,
                    r=radius
                );
        }
        
        // remove the hole for cuvette
        translate([
            cuvetteX-cuvetteBottomSpace,
            cuvetteY-cuvetteBottomSpace,
            0
        ])
        roundedParallelepiped4(x=cuvetteInternal+2*cuvetteBottomSpace, y=cuvetteInternal+2*cuvetteBottomSpace, z=bottomHeight-bottomThickness, r=radius);
        
          // remove the hole for battery
        translate([
            batteryX,
            batteryY,
            0
        ])
            roundedParallelepiped4(x=batteryLength, y=batteryWidth, z=bottomHeight-bottomThickness, r=radius);
        
        // make holes for screws        
        translate([shift+supportHoleX, shift+supportHoleY, 0])
            screwHole(rSmall=supportHoleR, rLarge=bottomHoleR, height=bottomHeight, heightLarge=bottomHoleHeight);
        
        translate([shift+pcbLength-supportHoleX, shift+supportHoleY, 0])
            screwHole(rSmall=supportHoleR, rLarge=bottomHoleR, height=bottomHeight, heightLarge=bottomHoleHeight);
        
        translate([shift+supportHoleX, shift+pcbWidth-supportHoleY, 0])
            screwHole(rSmall=supportHoleR, rLarge=bottomHoleR, height=bottomHeight, heightLarge=bottomHoleHeight);
        
        translate([shift+pcbLength-supportHoleX, shift+pcbWidth-supportHoleY, 0])
            screwHole(rSmall=supportHoleR, rLarge=bottomHoleR, height=bottomHeight, heightLarge=bottomHoleHeight);
        
            
    }
    

// create a hole that is smaller in the middle
module screwHole(rSmall=2, rLarge=4, height=10, heightLarge=3) {
    heightSmall=height-2*heightLarge;
    cylinder(r=rLarge, h=heightLarge);
    translate([0,0,heightLarge])
        cylinder(r=rSmall, h=heightSmall);
     translate([0,0,heightLarge+heightSmall])
        cylinder(r=rLarge, h=heightLarge);
}


// create the cuvette
translate([cuvetteX, cuvetteY, 0])
    cuvette(
        frontHeight,
        r=radius,
        cuvetteInternal,
        cuvetteY,
        overlap,
        pcbSpaceAround,
        supportHeight,
        frontThickness,
        pcbThickness,
        screenProtectionHeight
    );

// create the box with the holes
translate([0, 0, 0])
    difference() {
        // the front box
        cube([
            pcbLength+2*pcbSpaceAround+2*sideThickness,
            pcbWidth+2*pcbSpaceAround+2*sideThickness,
            frontHeight
        ]);

        // remove the top layer where the PCB is fixed
        translate([sideThickness, sideThickness, supportHeight + frontThickness])
            roundedParallelepiped4(
                x=pcbLength+2*pcbSpaceAround,
                y=pcbWidth+2*pcbSpaceAround,
                z=frontHeight,
                r=radius
            );
        
        // remove the bottom layer as 2 roundParallelepiped
        translate([sideThickness+supportLength+pcbSpaceAround, sideThickness+pcbSpaceAround, frontThickness])
            roundedParallelepiped4(
                x=pcbLength-2*supportLength,
                y=pcbWidth,
                z=frontHeight,
                r=radius
            );
        translate([sideThickness+pcbSpaceAround, sideThickness+supportWidth+pcbSpaceAround, frontThickness])
            roundedParallelepiped4(
                x=pcbLength,
                y=pcbWidth-2*supportWidth,
                z=frontHeight,
                r=radius
            );
        
        // we need to remove some material so that is fits together
            translate([sideThickness/2, sideThickness/2, frontHeight - overlap])
        roundedParallelepiped4(
            x=pcbLength+2*pcbSpaceAround+sideThickness,
            y=pcbWidth+2*pcbSpaceAround+sideThickness,
            z=frontHeight,
            r=radius
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
        translate([cuvetteX, cuvetteY, 0])
            cube([cuvetteInternal, cuvetteInternal, frontHeight]);
            
        // remove part for the screen protection
        translate([sideThickness, sideThickness, 0])
            roundedParallelepiped4(
                x=pcbLength+2*pcbSpaceAround,
                y=pcbWidth+2*pcbSpaceAround,
                z=screenProtectionHeight,
                r=radius
            );
        
        // we remove the USB port
        translate([0,usbY,pcbThickness+frontThickness+supportHeight])
            cube([sideThickness,usbWidth,usbHeight]);
    

    }
    
    
    // we add a border around push button
    difference() {
        height=rotaryExtension+screenProtectionHeight;
        translate([rotaryX, rotaryY, -2])
            cylinder(r=rotaryExtensionR, h=height);
        translate([rotaryX, rotaryY, -2])
            cylinder(r=rotaryR, h=height);
    }



// reference is based on 0,0 on the hole
module cuvette() {
    difference() {
        union() {
            // the cuvette itself
            hull() {
                translate([-cuvetteThickness,-cuvetteY+sideThickness,screenProtectionHeight]) cube([r,r,frontHeight-screenProtectionHeight]);
                translate([cuvetteInternal+cuvetteThickness-r,-cuvetteY+sideThickness,screenProtectionHeight]) cube([r,r,frontHeight-screenProtectionHeight]);
            
                translate([-cuvetteThickness,cuvetteInternal + cuvetteThickness - r,screenProtectionHeight]) cube([r,r,frontHeight-screenProtectionHeight]);
                translate([cuvetteInternal+cuvetteThickness-r,cuvetteInternal+cuvetteThickness-r,screenProtectionHeight]) cube([r,r,frontHeight-screenProtectionHeight]);
                
     
            }
            // little extension to make round corners
            translate([-r-cuvetteThickness,sideThickness-cuvetteY, screenProtectionHeight])
                cube([cuvetteInternal+cuvetteThickness*2+2*r,r,frontHeight-overlap-screenProtectionHeight]);
            
            translate([-r-cuvetteThickness,sideThickness+pcbSpaceAround-cuvetteY, screenProtectionHeight])
                cube([cuvetteInternal+cuvetteThickness*2+2*r,r,supportHeight+frontThickness-screenProtectionHeight]);
        }
       
        // round corners
        translate([-r-cuvetteThickness,-cuvetteY+r+sideThickness+pcbSpaceAround,0])
            cylinder(h=supportHeight+frontThickness, r=r);
        translate([cuvetteInternal+cuvetteThickness+r,-cuvetteY+r+sideThickness+pcbSpaceAround,0])
            cylinder(h=supportHeight+frontThickness, r=r);
        

        // round corners
        translate([-r-cuvetteThickness,sideThickness-cuvetteY+r,frontThickness+supportHeight]) cylinder(h=frontHeight-overlap, r=r);
        translate([cuvetteInternal+cuvetteThickness+r,sideThickness-cuvetteY+r,frontThickness+supportHeight]) cylinder(h=frontHeight-overlap, r=r);
        
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
        
        // TEMPORARY to print as today design 
        translate([-r-cuvetteThickness,-cuvetteY, frontThickness+supportHeight])
                cube([cuvetteInternal+cuvetteThickness*2+2*r,cuvetteY-cuvetteThickness,frontHeight-overlap-screenProtectionHeight]);
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