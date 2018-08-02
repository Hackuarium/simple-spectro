use <side.scad>;

module customHole(kind, parameters) {
            echo(kind);
        echo(parameters);
    if (kind=="Custom") {

    } else if (kind=="Insert") {
        translate([0,0,50])
        side(
            width=parameters[0],
            height=parameters[1],
            thickness=parameters[2],
            fingerWidth=parameters[3],
            color="Cyan"
        );
    }
   
}