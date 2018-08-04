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
    screws=[
        [5,5],
        [10,70],
        [85,15],
        [80,60]
    ],
    screwDiameter=3,
    frontHoles=[],
    frontHolesB=[],
    backHoles=[],
    backHolesB=[],
    leftHoles=[],
    leftHolesB=[],
    rightHoles=[],
    rightHolesB=[],
    topHoles=[
        [20,20,30,10]
    ], // 0,0 is the pcb
    bottomHoles=[
        [40,40,10],
        [20,20,5,5]
    ], // 0,0 is the pcb
    labelsSize=10,
    showLabels=true,
    3d=true
);
