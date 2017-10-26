$fn=50;

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

supportWidth=6;
supportLength=6;
supportHeight=8;
supportHoleX=3.5;
supportHoleY=3.5;
supportHoleR=1.5;
bottomHoleR=3;
bottomHoleExternalHeight=3;
bottomHoleInternalHeight=3;

rotaryX=13.2+shift;
rotaryY=12.8+shift;
rotaryR=4;
rotaryExtension=2;
rotaryExtensionR=6;

logoX=100+shift;
logoY=0+shift;

screenX=13.4+shift;
screenY=40.5+shift;
screenLength=71.6;
screenWidth=25.1;

cuvetteX=48.7+shift;
cuvetteY=5.4+shift;
cuvetteInternal=12.9;
cuvetteThickness=1.6; // 1.6 for current design, 3 in new design
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
connectHeight=batteryHeight;

screenProtectionHeight=2;
screenProtectionSize=3;

radius=3; // using bit of 3

usbHeight=4.6;
usbWidth=10;
usbSpace=2;
usbSpaceThickness=sideThickness/2+bottomClosureSpace;

usbY=38.2+shift;

frontHeight=frontThickness+usbHeight+supportHeight+pcbThickness;


// PCB
* color("red",0.2)
    translate([shift,shift,-50])
        cube([pcbLength, pcbWidth, pcbThickness]);

// Adding the logo
* translate([logoX, logoY, -0.5]) linear_extrude(height=0.5)  rotate(a=[0,180,0]) scale(0.6) color("purple") import("logo.dxf");

// create the bottom part 
translate([0, 0, 50])
    union() {
        difference() {
            
                // the bottom
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
                translate([sideThickness/2+bottomClosureSpace, sideThickness/2+bottomClosureSpace, 0])
                    roundedParallelepiped4(
                        x=pcbLength+2*pcbSpaceAround+sideThickness-2*bottomClosureSpace,
                        y=pcbWidth+2*pcbSpaceAround+sideThickness-2*bottomClosureSpace,
                        z=overlap,
                        r=radius
                    );
            }
            
            // remove some volume to have room for pcb
            translate([sideThickness, sideThickness, 0])
                roundedParallelepiped4(
                    x=pcbLength+2*pcbSpaceAround,
                    y=pcbWidth+2*pcbSpaceAround,
                    z=bottomDigged,
                    r=radius
                );
            
            // remove the hole for cuvette
            translate([
                cuvetteX-cuvetteBottomSpace,
                cuvetteY-cuvetteBottomSpace,
                0
            ])
            roundedParallelepiped4(x=cuvetteInternal+2*cuvetteBottomSpace, y=cuvetteInternal+2*cuvetteBottomSpace, z=bottomHeight-bottomMinimal, r=radius);
            
              // remove the hole for battery
            translate([
                batteryX,
                batteryY,
                0
            ])
                roundedParallelepiped4(x=batteryLength, y=batteryWidth, z=bottomHeight-batteryHeight, r=radius);
            
            translate([
                connectorX,
                connectorY,
                0
            ])
                roundedParallelepiped4(x=connectorLength, y=connectorWidth, z=bottomHeight-connectHeight, r=radius);
            
            
              // we remove the USB port
            translate([0,usbY,0])
                cube([sideThickness,usbWidth,overlap]);
            // remove some more space so the USB plug fits in
            translate([-usbSpaceThickness,usbY-usbSpace,0])
                roundedParallelepiped4(
                    x=usbSpaceThickness*2,
                    y=usbWidth+2*usbSpace,
                    z=overlap+usbSpace,
                    r=1
                );
            
            // make holes for screws        
            translate([shift+supportHoleX, shift+supportHoleY, 0])
                screwHole(rSmall=supportHoleR, rLarge=bottomHoleR, height=bottomHeight, heightExternal=bottomHoleExternalHeight, heightInternal=bottomHoleInternalHeight);
            
            translate([shift+pcbLength-supportHoleX, shift+supportHoleY, 0])
                screwHole(rSmall=supportHoleR, rLarge=bottomHoleR, height=bottomHeight, heightExternal=bottomHoleExternalHeight, heightInternal=bottomHoleInternalHeight);
            
            translate([shift+supportHoleX, shift+pcbWidth-supportHoleY, 0])
                screwHole(rSmall=supportHoleR, rLarge=bottomHoleR, height=bottomHeight, heightExternal=bottomHoleExternalHeight, heightInternal=bottomHoleInternalHeight);
            
            translate([shift+pcbLength-supportHoleX, shift+pcbWidth-supportHoleY, 0])
                screwHole(rSmall=supportHoleR, rLarge=bottomHoleR, height=bottomHeight, heightExternal=bottomHoleExternalHeight, heightInternal=bottomHoleInternalHeight);     
        };
        
        translate([
            cuvetteX-cuvetteBottomSpace-cuvetteThickness,
            cuvetteY-cuvetteBottomSpace-cuvetteThickness,
            overlap
        ])
            difference() {
                cube([
                    cuvetteInternal+2*cuvetteBottomSpace+2*cuvetteThickness,
                    cuvetteInternal+2*cuvetteBottomSpace+2*cuvetteThickness,
                    bottomHeight-bottomMinimal-overlap
                ]);
             // remove the hole for cuvette
                translate([
                    cuvetteThickness,
                    cuvetteThickness,
                    0
                ])
                roundedParallelepiped4(x=cuvetteInternal+2*cuvetteBottomSpace, y=cuvetteInternal+2*cuvetteBottomSpace, z=bottomHeight-bottomMinimal, r=radius);
            }
    };




// create a hole that is smaller in the middle
module screwHole(rSmall=2, rLarge=4, height=10, heightExternal=2.5, heightInternal=2.5) {
    echo(rLarge,heightExternal);
    translate([0,0,height-heightExternal])
    cylinder(r=rLarge, h=heightExternal);
    translate([0,0,height-heightExternal-heightInternal])
        cylinder(r=rSmall, h=heightInternal);
    translate([0,0,0])
        cylinder(r=rLarge, h=height-heightExternal-heightInternal);
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