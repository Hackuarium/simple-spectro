$fn=20;

use <pcb.scad>;
use <bottom.scad>;
use <top.scad>;



showPCB=true;
showBottom=true;
showLogo=false;
showTop=true;

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


//projection(cut = true)
//rotate([90,0,0])
translate([0,-20,0]) {
if (showPCB)
    pcb(shift, pcbLength, pcbWidth, pcbThickness);


if (showBottom)
    bottom(
        batteryHeight, batteryLength, batteryWidth, batteryX, batteryY, bottomClosureSpace, 
        bottomDigged, bottomHeight, bottomMinimal, bottomSmallHoleR, bottomHoleR, bottomHoleExternalHeight,
        bottomHoleInternalHeight, connectorHeight, connectorLength, connectorWidth,
        connectorX, connectorY, cuvetteBottomSpace,
        cuvetteX, cuvetteY, cuvetteInternal, frontHeight,
        overlap, pcbLength, pcbSpaceAround, pcbWidth, radius, shift,
        sideThickness, supportHoleX, supportHoleY, usbSpace, usbSpaceThickness, usbWidth, usbY
    );

if (showTop) 
    top(
        cuvetteInternal, cuvetteThickness, cuvetteUVWindow, cuvetteWindow, cuvetteX,
        cuvetteY, frontHeight, frontThickness, overlap, pcbLength, pcbSpaceAround, pcbThickness, pcbWidth,
        radius, rotaryExtension, rotaryExtensionR, rotaryR, rotaryX, rotaryY,
        screenProtectionHeight, screenProtectionSize, screenX, screenY, screenWidth, screenLength,
        sideThickness, supportHeight, supportHoleR, supportHoleX, supportHoleY, supportLength, supportWidth, usbHeight, usbSpace, usbSpaceThickness, usbWidth, usbY);


// Adding the logo
if (showLogo) 
    translate([logoX, logoY, -0.5]) linear_extrude(height=0.5)  rotate(a=[0,180,0]) scale(0.6) color("purple") import("logo.dxf");



}

