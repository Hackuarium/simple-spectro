

use <side.scad>;

module box() {
    fingerWidth = (fingerWidth==undef) ? thickness*2 : fingerWidth;
    
    assemble3d=[
        [
            [width/2, depth/2, thickness/2], // bottom
            [0,180,0]
        ],
        [
            [width/2, depth/2, height-thickness/2], // top
            [0,0,0]
        ],
        [
            [width/2, thickness/2, height/2], // front
            [90,0,0]
        ],
        [
            [width/2, depth-thickness/2, height/2], // back
            [270,0,0]
        ],
        [
            [thickness/2, depth/2, height/2], // left
            [0,270,0]
        ],
        [
            [width-thickness/2, depth/2, height/2], // right
            [0,90,0]
        ]
    ];
    
    assemble2d=[
        [
            [width/2, depth/2, 0] // bottom
        ],
        [
            [width/2, depth*3/2+space, 0] // top
        ],
        [
            [width*3/2 + space, height/2, 0] // front
        ],
        [
            [width*3/2 + space, height*3/2 + space, 0] // back
        ],
        [
            [width*2 + height / 2 + space * 2, depth/2, 0] // left
        ],
        [
            [width*2 + height / 2 + space * 2, depth*3/2 + space, 0] // right
        ]
    ];
    assemble=(3d) ? assemble3d : assemble2d;
    
    // bottom
    translate(assemble[0][0])
        rotate(assemble[0][1])
            side(width, depth, thickness, fingerWidth, male=[1,1,1,1],
            name="bottom", sideColor="green", labelsSize=labelsSize, showLabels=showLabels, holes=holes[0]);
    
    // top
    translate(assemble[1][0])
        rotate(assemble[1][1])
            side(width, depth, thickness, fingerWidth, male=[1,1,1,1],
            name="top", sideColor="blue", labelsSize=labelsSize, showLabels=showLabels, holes=holes[1]);
    
    // front
    translate(assemble[2][0])
        rotate(assemble[2][1])
            side(width, height, thickness, fingerWidth, male=[0,1,0,1],
            name="front", sideColor="orange", labelsSize=labelsSize, showLabels=showLabels, holes=holes[2]);
    
    // back
    translate(assemble[3][0])
        rotate(assemble[3][1])
            side(width, height, thickness, fingerWidth, male=[0,1,0,1],
            name="back", sideColor="indigo", labelsSize=labelsSize, showLabels=showLabels, holes=holes[3]);
            
    // left
    translate(assemble[4][0])
        rotate(assemble[4][1])
            side(height, depth, thickness, fingerWidth, male=[0,0,0,0],
            name="left", sideColor="magenta", labelsSize=labelsSize, showLabels=showLabels, holes=holes[4]);
    // right
    translate(assemble[5][0])
        rotate(assemble[5][1])
            side(height, depth, thickness, fingerWidth, male=[0,0,0,0],
            name="right", sideColor="cyan", labelsSize=labelsSize, showLabels=showLabels, holes=holes[5]);
};


