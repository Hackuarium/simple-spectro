// create a hole that is smaller in the middle
module screwHole(rSmall=2, rLarge=4, height=10, heightExternal=2.5, heightInternal=2.5) {
    echo(rLarge,heightExternal);
    translate([0,0,height-heightExternal])
    cylinder(r=rLarge, h=heightExternal);
    translate([0,0,height-heightExternal-heightInternal])
        cylinder(r=rSmall, h=heightInternal);
    translate([0,0,0])
        cylinder(r=rLarge, h=height-heightExternal-heightInternal);
}
