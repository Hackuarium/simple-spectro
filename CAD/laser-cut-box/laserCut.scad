$fn=40;

use <box.scad>;

box(
    width=50,
    height=20,
    depth=30,
    thickness=1,
    fingerWidth=undef,
    labelsSize=3, 
    showLabels=true,
    labels=["Bottom","Top","Front","Back","Left","Right"],
    3d=false,
    space=2,
    holes=[ // relative to the inside of the box
        [
            [2,2,2], // circular hole on the Bottom
            [4,4,1,2], // rectangular hole on the bottom
            [7,2,"Custom",10], // custom share hole on the bottom
            [20,10,"Insert",20,10,1,2] // to insert a 'cuvette'
        ],
        [],
        [],
        [],
        [],
        []
    ]
);
