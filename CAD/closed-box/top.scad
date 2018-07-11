
use <roundedParallelepiped4.scad>;
use <cubeWithCylinders.scad>;

module top(
    cuvetteInternal, cuvetteThickness, cuvetteUVWindow, cuvetteWindow, cuvetteX, cuvetteY, cuvetteTopBottomOverlap,
    frontHeight, frontThickness, overlap, pcbLength, pcbSpaceAround, pcbThickness, pcbWidth,
    radius, radiusCorner, rotaryExtension, rotaryExtensionR, rotaryR, rotaryX, rotaryY, screenProtectionHeight, screenProtectionSize,
    screenX, screenY, screenWidth, screenLength, sideThickness, supportHeight, supportHoleR, supportHoleX,
    supportHoleY, supportLength, supportWidth, usbHeight, usbSpace, usbSpaceThickness, usbWidth, usbY) {



    // create the cuvette
    translate([cuvetteX, cuvetteY, 0])
        cuvette(r=radius);

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
                cubeWithCylinders(cuvetteInternal, cuvetteInternal, frontHeight, r=radiusCorner);
                
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
                cubeWithCylinders(cuvetteInternal, cuvetteInternal, frontHeight, r=radiusCorner);
            
            // cutting the windows in cuvette ...
            heightWindow=pcbThickness+frontThickness+supportHeight;
            translate([-cuvetteThickness, (cuvetteInternal-cuvetteWindow)/2, heightWindow])
                cube([cuvetteThickness, cuvetteWindow, frontHeight-overlap]);
            translate([cuvetteInternal, (cuvetteInternal-cuvetteWindow)/2, heightWindow])
                cube([cuvetteThickness, cuvetteWindow, frontHeight-overlap]);
            translate([(cuvetteInternal-cuvetteUVWindow)/2, cuvetteInternal,  heightWindow])
                cube([cuvetteUVWindow, cuvetteThickness, frontHeight-overlap]);
            
            // remove the overlap
            cuvetteInternalOverlapCut = cuvetteThickness/2;
            color("blue") 
            translate([-cuvetteThickness,-cuvetteThickness, frontHeight-cuvetteTopBottomOverlap]) 
                difference() {
                    cube([
                        cuvetteInternal+cuvetteThickness*2,
                        cuvetteInternal+cuvetteThickness*2,
                        cuvetteTopBottomOverlap
                    ]);
                    translate([cuvetteInternalOverlapCut+0.15, cuvetteInternalOverlapCut+0.15, 0])
                        cube([
                            cuvetteInternal+cuvetteInternalOverlapCut*2-0.30,
                            cuvetteInternal+cuvetteInternalOverlapCut*2-0.30,
                            cuvetteTopBottomOverlap
                        ]);
                };

            // TEMPORARY to print as today design 
            translate([-r-cuvetteThickness,-cuvetteY, frontThickness+supportHeight])
                    cube([cuvetteInternal+cuvetteThickness*2+2*r,cuvetteY-cuvetteThickness,frontHeight-overlap-screenProtectionHeight]);
        }
    }

}