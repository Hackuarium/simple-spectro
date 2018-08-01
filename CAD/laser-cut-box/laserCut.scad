box(
    width=8,
    height=20,
    depth=30,
    thickness=1,
    fingerWidth=undef
);



module box() {
    fingerWidth = (fingerWidth==undef) ? thickness*2 : fingerWidth;
    
    assemble3d=[
        [
            [width/2, depth/2, thickness/2],
            [0,180,0]
        ],
        [
            [width/2, depth/2, height-thickness/2],
            [0,0,0]
        ],
        [
            [width/2, thickness/2, height/2],
            [90,0,0]
        ],
        [
            [width/2, depth-thickness/2, height/2],
            [270,0,0]
        ],
        [
            [thickness/2, depth/2, height/2],
            [0,270,0]
        ],
        [
            [width-thickness/2, depth/2, height/2],
            [0,90,0]
        ]
    ];
    
    assemble2d=[
        [
            [width/2, depth/2, 0]
        ],
        [
            [width/2, depth/2, 0]
        ],
        [
            [width/2, thickness/2, 0]
        ],
        [
            [width/2, depth-thickness/2, 0]
        ],
        [
            [thickness/2, depth/2, 0]
        ],
        [
            [width-thickness/2, depth/2, 0]
        ]
    ];
    
    assemble=assemble2d;
    
    // bottom
    translate(assemble[0][0])
        rotate(assemble[0][1])
            side(width, depth, thickness, fingerWidth, male=[1,1,1,1], name="bottom");
    
    // top
    translate(assemble[1][0])
        rotate(assemble[1][1])
            side(width, depth, thickness, fingerWidth, male=[1,1,1,1],
            name="top");
    
    // front
    translate(assemble[2][0])
        rotate(assemble[2][1])
            side(width, height, thickness, fingerWidth, male=[0,1,0,1], name="front");
    
    // back
    translate(assemble[3][0])
        rotate(assemble[3][1])
            side(width, height, thickness, fingerWidth, male=[0,1,0,1], name="back");
            
    // left
    translate(assemble[4][0])
        rotate(assemble[4][1])
            side(height, depth, thickness, fingerWidth, male=[0,0,0,0], name="left");
    
    // right
    translate(assemble[5][0])
        rotate(assemble[5][1])
            side(height, depth, thickness, fingerWidth, male=[0,0,0,0], name="right");
};


module side(
    width,
    height,
    thickness,
    fingerWidth,
    male=[0,0,0,0]
) {
    textRotation=(width<height) ? 90 : 0;
    color("red")
        translate([0,0,thickness])
            rotate([0,0,textRotation])
                linear_extrude(height=0.1)
                    text(text = name, halign = "center", valign="center");

    translate([-width/2, -height/2, -thickness/2])
        difference() {
        // we create the side
            cube([width, height, thickness]);

                if (male[0]==0) {
                    fingers(width, fingerWidth, thickness);
                } else {
                    invertedFingers(width, fingerWidth, thickness);
                }
                
                translate([thickness, 0, 0]) rotate([0,0,90])
                if (male[1]==0) {
                    fingers(height, fingerWidth, thickness);
                } else {
                    invertedFingers(height, fingerWidth, thickness);
                }
                
                translate([0, height-thickness, 0])
                if (male[2]==0) {
                    fingers(width, fingerWidth, thickness);
                } else {
                    invertedFingers(width, fingerWidth, thickness);
                }
            
            translate([width, 0, 0]) rotate([0,0,90])
                if (male[3]==0) {
                    fingers(height, fingerWidth, thickness);
                } else {
                    invertedFingers(height, fingerWidth, thickness);
                }
        }
}


module invertedFingers(width, fingerWidth, thickness) {
    color("red") difference() {
        cube([width, thickness, thickness]);
        fingers(width, fingerWidth, thickness);
    }
}

module fingers(width, fingerWidth, thickness) {
    fingerNumber=floor((width-2*thickness-fingerWidth)/(fingerWidth*2));
    fingerStart=(width-(fingerNumber*2-1)*fingerWidth)/2;
    for (i= [0:1:fingerNumber-1]) {
        echo(i);
        color("green")
            translate([fingerStart+i*2*fingerWidth,0,0])
                cube( [fingerWidth, thickness, thickness] );
    }
}