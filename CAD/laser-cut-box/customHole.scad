use <side.scad>;

module customHole(kind, parameters) {
    if (kind=="Custom") {

    } else if (kind=="Insert") {
        echo("INSERT",parameters);
        side(
            width=parameters[0],
            height=parameters[1],
            thickness=parameters[2],
            fingerWidth=parameters[3],
            color="Cyan"
        );
        echo("DONE");
    }
   
}