$fn=40;

use <box.scad>;

box(
    width=100,
    height=50,
    depth=80,
    thickness=2,
    fingerWidth=undef,
    labelsSize=10, 
    showLabels=true,
    labels=["Top","Bottom","Left","Right","Front","Back"],
    3d=true,
    space=2,
    holes=[ // relative to the inside of the box
        [
            [20,20,2], // circular hole on the Bottom
            [40,40,1,2], // rectangular hole on the bottom
            [7,2,"Custom",10], // custom share hole on the bottom
            [50,30,"Insert",30,30,2,4] // to insert a 'cuvette'
        ],
        [],
        [],
        [],
        [],
        []
    ]
);
