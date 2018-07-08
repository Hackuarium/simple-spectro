$fn=50;

use <pcb.scad>;
use <bottom.scad>;
use <roundedParallelepiped4.scad>;

showPCB=true;
showBottom=true;

aluminium=true;

pcbLength=98.7;
pcbWidth=73.2;
pcbThickness=1.6;
pcbSpaceAround=1; // need some space because of rounded angles

sideThickness=4; 
frontThickness=5;
bottomDigged=8;
bottomMinimal=2;
bottomHeight=20;
bottomClosureSpace=0.1; // number of mm to be sure it can close
overlap=4; // overlap between top and bottom

shift=pcbSpaceAround+sideThickness;

supportWidth=7;
supportLength=7;
supportHeight=8;
supportHoleX=3.5;
supportHoleY=3.5;
supportHoleR=1.2;
bottomHoleR=3;
bottomSmallHoleR=1.6; // slightly bigger than M3 
bottomHoleExternalHeight=3;
bottomHoleInternalHeight=3;

rotaryX=13.2+shift;
rotaryY=12.8+shift;
rotaryR=4;
rotaryExtension=2; 
rotaryExtensionR=aluminium ? 5.5 : 0; // 5.5 if you want an extension

logoX=100+shift;
logoY=0+shift;

screenX=13.4+shift;
screenY=40.5+shift;
screenLength=71.6;
screenWidth=25.1;

cuvetteX=48.7+shift;
cuvetteY=5.4+shift;
cuvetteInternal=12.9;
cuvetteThickness=aluminium ? 2.5 : 1.6;
cuvetteWindow=3;
cuvetteUVWindow=5;
cuvetteWindowHeight=5;
cuvetteBottomSpace=2;

batteryX=46+shift;
batteryY=26+shift;
batteryLength=50+2;
batteryWidth=33.6+4;
batteryHeight=5.8+2;

connectorX=22+shift;
connectorLength=20;
connectorWidth=15;
connectorY=pcbWidth-15+shift;
connectorHeight=batteryHeight;

screenProtectionHeight=2;
screenProtectionSize=3;

radius=3; // using bit of 6

usbHeight=4.6;
usbWidth=10;
usbSpace=2;
usbSpaceThickness=sideThickness/2+bottomClosureSpace;

usbY=38.2+shift;

frontHeight=frontThickness+usbHeight+supportHeight+pcbThickness;

if (showPCB)
    pcb(shift, pcbLength, pcbWidth, pcbThickness);


if (showBottom)
    bottom(batteryHeight, batteryLength, batteryWidth, batteryX, batteryY, bottomClosureSpace, bottomDigged, bottomHeight, bottomMinimal, bottomSmallHoleR, bottomHoleR, bottomHoleExternalHeight, bottomHoleInternalHeight, connectorHeight, connectorLength, connectorWidth, connectorX, connectorY, cuvetteBottomSpace, cuvetteX, cuvetteY, cuvetteInternal, overlap, pcbLength, pcbSpaceAround, pcbWidth, radius, shift, sideThickness, supportHoleX, supportHoleY, usbSpace, usbSpaceThickness, usbWidth, usbY);


// Adding the logo
* translate([logoX, logoY, -0.5]) linear_extrude(height=0.5)  rotate(a=[0,180,0]) scale(0.6) color("purple") import("logo.dxf");





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
            roundedParallelepiped4(
                    x=screenLength,
                    y=screenWidth,
                    z=screenWidth,
                    r=0.5
                );
            
                // create the hole for cuvette
        translate([cuvetteX, cuvetteY, 0])
            cube([cuvetteInternal, cuvetteInternal, frontHeight]);
            
        // remove part for the screen protection
        translate([screenX-screenProtectionSize, screenY-screenProtectionSize, 0])
            roundedParallelepiped4(
                x=screenLength+2*screenProtectionSize,
                y=screenWidth+2*screenProtectionSize,
                z=screenProtectionHeight,
                r=1
            );
        
        // we remove the USB port
        translate([0,usbY,pcbThickness+frontThickness+supportHeight])
            cube([sideThickness,usbWidth,usbHeight]);
            
        // enlarge the USB to have place for the plastic connector
        translate([-usbSpaceThickness,usbY-usbSpace,pcbThickness+frontThickness+supportHeight-usbSpace])
                roundedParallelepiped4(
                    x=usbSpaceThickness*2,
                    y=usbWidth+2*usbSpace,
                    z=usbHeight+usbSpace,
                    r=1
                );
                
         translate([0,usbY-usbSpace,frontHeight-overlap])       
            cube([usbSpaceThickness,usbWidth+2*usbSpace,overlap]);
                
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
            translate([-cuvetteThickness,-cuvetteY+sideThickness,screenProtectionHeight]) 
                cube([cuvetteInternal+cuvetteThickness*2,cuvetteInternal+cuvetteThickness+cuvetteY-sideThickness,frontHeight-screenProtectionHeight]);
            
            
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
        translate([(cuvetteInternal-cuvetteUVWindow)/2, cuvetteInternal,  heightWindow])
            cube([cuvetteUVWindow, cuvetteThickness, frontHeight-overlap]);
        
        // TEMPORARY to print as today design 
        translate([-r-cuvetteThickness,-cuvetteY, frontThickness+supportHeight])
                cube([cuvetteInternal+cuvetteThickness*2+2*r,cuvetteY-cuvetteThickness,frontHeight-overlap-screenProtectionHeight]);
    }
}



