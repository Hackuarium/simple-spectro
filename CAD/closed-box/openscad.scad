$fn=50;

use <pcb.scad>;
use <bottom.scad>;
use <top.scad>;



showPCB=false;
showBottom=true;
showLogo=false;
showTop=false;

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
supportHeight=9; // was 8 in first design
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
rotaryExtensionR=aluminium ? 5.5 : 0; // 5.5 if you want an extension, was 6 in version 1

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
cuvetteBottomSpace=0; // was 2 in first design
cuvetteTopBottomOverlap = 1;

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
radiusCorner=1.5;

usbHeight=4.6;
usbWidth=10;
usbSpace=2;
usbSpaceThickness=sideThickness/2+bottomClosureSpace;

usbY=38.2+shift;

frontHeight=frontThickness+usbHeight+supportHeight+pcbThickness;


// projection(cut = true)
// rotate([90,0,0])
translate([0,-20,0]) {
if (showPCB)
    pcb(shift, pcbLength, pcbWidth, pcbThickness);


if (showBottom)
    bottom(
        batteryHeight=batteryHeight, batteryLength=batteryLength, batteryWidth=batteryWidth,
        batteryX=batteryX, batteryY=batteryY, 
        bottomClosureSpace=bottomClosureSpace, 
        bottomDigged=bottomDigged, bottomHeight=bottomHeight, bottomMinimal=bottomMinimal,
        bottomSmallHoleR=bottomSmallHoleR, bottomHoleR=bottomHoleR,
        bottomHoleExternalHeight=bottomHoleExternalHeight,
        bottomHoleInternalHeight=bottomHoleInternalHeight, connectorHeight=connectorHeight, connectorLength=connectorLength, connectorWidth=connectorWidth,
        connectorX=connectorX, connectorY=connectorY, cuvetteBottomSpace=cuvetteBottomSpace,
        cuvetteX=cuvetteX, cuvetteY=cuvetteY, cuvetteInternal=cuvetteInternal, cuvetteThickness=cuvetteThickness,  cuvetteUVWindow=cuvetteUVWindow, cuvetteWindow=cuvetteWindow, cuvetteTopBottomOverlap=cuvetteTopBottomOverlap,
        frontHeight=frontHeight,
        overlap=overlap, pcbLength=pcbLength, pcbSpaceAround=pcbSpaceAround, pcbWidth=pcbWidth, radius=radius, radiusCorner=radiusCorner, shift=shift,
        sideThickness=sideThickness, supportHoleX=supportHoleX, supportHoleY=supportHoleY, usbSpace=usbSpace, usbSpaceThickness=usbSpaceThickness, usbWidth=usbWidth, usbY=usbY
    );

if (showTop) 
    top(
        cuvetteInternal=cuvetteInternal, cuvetteThickness=cuvetteThickness, cuvetteUVWindow=cuvetteUVWindow,
        cuvetteWindow=cuvetteWindow, cuvetteX=cuvetteX, cuvetteY=cuvetteY, cuvetteTopBottomOverlap=cuvetteTopBottomOverlap,
        frontHeight=frontHeight, frontThickness=frontThickness, overlap=overlap,
        pcbLength=pcbLength, pcbSpaceAround=pcbSpaceAround, pcbThickness=pcbThickness, pcbWidth=pcbWidth, radius=radius, radiusCorner=radiusCorner, rotaryExtension=rotaryExtension, rotaryExtensionR=rotaryExtensionR, rotaryR=rotaryR, rotaryX=rotaryX, rotaryY=rotaryY, screenProtectionHeight=screenProtectionHeight, screenProtectionSize=screenProtectionSize, screenX=screenX, screenY=screenY, screenWidth=screenWidth, screenLength=screenLength, sideThickness=sideThickness, supportHeight=supportHeight, supportHoleR=supportHoleR, supportHoleX=supportHoleX, supportHoleY=supportHoleY, supportLength=supportLength, supportWidth=supportWidth, usbHeight=usbHeight, usbSpace=usbSpace, usbSpaceThickness=usbSpaceThickness, usbWidth=usbWidth, usbY=usbY
    );


// Adding the logo
if (showLogo) 
    translate([logoX, logoY, -0.5]) linear_extrude(height=0.5)  rotate(a=[0,180,0]) scale(0.6) color("purple") import("logo.dxf");
}

