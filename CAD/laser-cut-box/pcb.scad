use <box.scad>;

module pcb(
    length=100,
    width=80,
    padding=1, // space around the pcb
    thickness=3, // thickness of the material
    pcbThickness=1.6,
    topToTop=20, // distance from the top of the PCB to the top of the box
    bottomToBottom=20, // distance from the bottom of the PCB to the bottom of the box
    frontTopHoles=[],
    frontBottomHoles=[],
    backTopHoles=[],
    backBottomHoles=[],
    leftTopHoles=[],
    leftBottomHoles=[],
    rightTopHoles=[],
    rightBottomHoles=[],
    topHoles=[],
    bottomHoles=[],
    labelsSize=10,
    showLabels=false,
    3d=false
)



box(
    width=length+padding*2+thickness*2,
    depth=width+padding*2+thickness*2,
    height=pcbThickness+topToTop+bottomToBottom,
    thickness=thickness,
    fingerWidth=undef,
    labelsSize=labelsSize, 
    showLabels=showLabels,
    labels=["Top","Bottom","Left","Right","Front","Back"],
    3d=3d,
    space=2,
    holes=[
        [ for(hole = topHoles) concat([hole.x+padding, hole.y+padding],[ for (i=[2:1:len(hole)-1]) hole[i]]) ],
        [ for(hole = bottomHoles) concat([hole.x+padding, hole.y+padding],[ for (i=[2:1:len(hole)-1]) hole[i]]) ],,
        [],
        [],
        [],
        []
    ]
);