use <screwHole.scad>;
use <roundedParallelepiped4.scad>;
use <cubeWithCylinders.scad>;

module bottom() {
        
    
    // create the bottom part 
    translate([0, 0, frontHeight-overlap+1])
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
                cubeWithCylinders(x=cuvetteInternal+2*cuvetteBottomSpace, y=cuvetteInternal+2*cuvetteBottomSpace, z=bottomHeight-bottomMinimal,  r=radiusCorner);
                
                  // remove the hole for battery
                translate([
                    batteryX,
                    batteryY,
                    bottomDigged
                ])
                    roundedParallelepiped4(x=batteryLength, y=batteryWidth, z=batteryHeight, r=radius);
                 
                 // the hole for the battery connector
                translate([
                    connectorX,
                    connectorY,
                    bottomDigged
                ])
                    roundedParallelepiped4(x=connectorLength, y=connectorWidth, z=connectorHeight, r=radius);
                    
                // small line for battery cable
                translate([
                    connectorX + connectorLength - radius,
                    connectorY,
                    bottomDigged
                ])
                    cube([batteryX-connectorX-connectorWidth + 2 * radius, batteryY + batteryWidth - connectorY, batteryHeight]);
                
                // we remove cutting edges
                translate([
                    batteryX-radius,
                    connectorY-radius,
                    bottomDigged
                ])
                    difference() {
                        cube([radius, radius, batteryHeight]);
                        cylinder(h=batteryHeight, r=radius);
                    };
                
                translate([
                    connectorX + connectorLength + radius,
                    batteryY + batteryWidth+radius-0.001,
                    bottomDigged
                ])
                    difference() {
                        translate([-radius, -radius, 0]) 
                            cube([radius, radius, batteryHeight]);
                        cylinder(h=batteryHeight, r=radius);
                    };
             
                
                
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
                echo(bottomSmallHoleR, bottomSmallHoleR);
                translate([shift+supportHoleX, shift+supportHoleY, 0])
                    screwHole(rSmall=bottomSmallHoleR, rLarge=bottomHoleR, height=bottomHeight, heightExternal=bottomHoleExternalHeight, heightInternal=bottomHoleInternalHeight);
                
                translate([shift+pcbLength-supportHoleX, shift+supportHoleY, 0])
                    screwHole(rSmall=bottomSmallHoleR, rLarge=bottomHoleR, height=bottomHeight, heightExternal=bottomHoleExternalHeight, heightInternal=bottomHoleInternalHeight);
                
                translate([shift+supportHoleX, shift+pcbWidth-supportHoleY, 0])
                    screwHole(rSmall=bottomSmallHoleR, rLarge=bottomHoleR, height=bottomHeight, heightExternal=bottomHoleExternalHeight, heightInternal=bottomHoleInternalHeight);
                
                translate([shift+pcbLength-supportHoleX, shift+pcbWidth-supportHoleY, 0])
                    screwHole(rSmall=bottomSmallHoleR, rLarge=bottomHoleR, height=bottomHeight, heightExternal=bottomHoleExternalHeight, heightInternal=bottomHoleInternalHeight);     
            };
            

            /* little border around the cell */ 
            translate([
                cuvetteX-cuvetteBottomSpace-cuvetteThickness,
                cuvetteY-cuvetteBottomSpace-cuvetteThickness,
                overlap-cuvetteTopBottomOverlap
            ])
                color("red")
                difference() {
                    cube([
                        cuvetteInternal+2*cuvetteBottomSpace+2*cuvetteThickness,
                        cuvetteInternal+2*cuvetteBottomSpace+2*cuvetteThickness,
                        bottomHeight-bottomMinimal-overlap
                    ]);

                    // cutting the windows in cuvette ...
                    heightWindow=bottomDigged-overlap;
                    translate([0, cuvetteThickness+(cuvetteInternal-cuvetteWindow)/2, 0])
                        cube([cuvetteThickness, cuvetteWindow, heightWindow]);
                    translate([cuvetteThickness+cuvetteInternal, cuvetteThickness+(cuvetteInternal-cuvetteWindow)/2, 0])
                        cube([cuvetteThickness, cuvetteWindow, heightWindow]);
                    translate([cuvetteThickness+(cuvetteInternal-cuvetteUVWindow)/2, cuvetteThickness+cuvetteInternal, 0])
                        cube([cuvetteUVWindow, cuvetteThickness, heightWindow]);

                    // remove the hole for cuvette
                    translate([
                        cuvetteThickness,
                        cuvetteThickness,
                        0
                    ])
                    cubeWithCylinders(x=cuvetteInternal+2*cuvetteBottomSpace, y=cuvetteInternal+2*cuvetteBottomSpace, z=bottomHeight-bottomMinimal-overlap, r=radiusCorner);
                
                    // cutting the overlap of the well
                    cuvetteInternalOverlapCut = cuvetteThickness/2+0.15;
                    
                    union() {
                        translate([
                            cuvetteThickness,
                            cuvetteThickness-cuvetteInternalOverlapCut,
                            0
                        ])
                            cube([
                                cuvetteInternal+2*cuvetteBottomSpace,
                                cuvetteInternal+2*cuvetteBottomSpace+2*cuvetteInternalOverlapCut,
                                cuvetteTopBottomOverlap
                            ]);
                        translate([
                            cuvetteThickness-cuvetteInternalOverlapCut,
                            cuvetteThickness,
                            0
                        ])
                            cube([
                                cuvetteInternal+2*cuvetteBottomSpace+2*cuvetteInternalOverlapCut,
                                cuvetteInternal+2*cuvetteBottomSpace,
                                cuvetteTopBottomOverlap
                            ]);
                    }
                
                }
            
            
    };
}
