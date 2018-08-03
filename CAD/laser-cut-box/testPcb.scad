$fn=40;

use <pcb.scad>;

pcb(
    length=100,
    width=80,
    padding=1, // space around the pcb
    thickness=3, // thickness of the material
    pcbThickness=1.6,
    topToTop=20, // distance from the top of the PCB to the top of the box
    bottomToBottom=20,
    frontTopHoles=[],
    frontBottomHoles=[],
    backTopHoles=[],
    backBottomHoles=[],
    leftTopHoles=[],
    leftBottomHoles=[],
    rightTopHoles=[],
    rightBottomHoles=[],
    topHoles=[
        [20,30,30,10]
    ], // 0,0 is the pcb
    bottomHoles=[
        [40,40,10],
        [10,10,5,5]
    ], // 0,0 is the pcb
    labelsSize=10,
    showLabels=false,
    3d=false
);
