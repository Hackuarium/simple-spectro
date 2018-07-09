
// reference is based on 0,0 on the hole
module cuvette(
    cuvetteInternal,
    cuvetteThickness, cuvetteUVWindow, cuvetteWindow, cuvetteY,
    frontHeight, frontThickness, overlap, pcbSpaceAround, pcbThickness, screenProtectionHeight,
    sideThickness, supportHeight) {
    
    echo ("-------", cuvetteThickness);
    
    difference() {
        union() {
            // the cuvette itself
            translate([-cuvetteThickness,-cuvetteY+sideThickness,screenProtectionHeight]) 
                cube([cuvetteInternal+cuvetteThickness*2,cuvetteInternal+cuvetteThickness+cuvetteY-sideThickness,frontHeight-screenProtectionHeight]);
            
            
            // little extension to make round corners
            translate([-r-cuvetteThickness,sideThickness-cuvetteY, screenProtectionHeight])
                cube([cuvetteInternal+cuvetteThickness*2+2*r,r,frontHeight-overlap-screenProtectionHeight]);
            
            translate([-r-cuvetteThickness,sideThickness+pcbSpaceAround-cuvetteY, screenProtectionHeight])
                cube([cuvetteInternal+cuvetteThickness*2+2*r,r,supportHeight+frontThickness-screenProtectionHeight]);
        }

        // round corners
        translate([-r-cuvetteThickness,-cuvetteY+r+sideThickness+pcbSpaceAround,0])
            cylinder(h=supportHeight+frontThickness, r=r);
        translate([cuvetteInternal+cuvetteThickness+r,-cuvetteY+r+sideThickness+pcbSpaceAround,0])
            cylinder(h=supportHeight+frontThickness, r=r);
        

        // round corners
        translate([-r-cuvetteThickness,sideThickness-cuvetteY+r,frontThickness+supportHeight]) cylinder(h=frontHeight-overlap, r=r);
        translate([cuvetteInternal+cuvetteThickness+r,sideThickness-cuvetteY+r,frontThickness+supportHeight]) cylinder(h=frontHeight-overlap, r=r);
        
        // create the hole for cuvette
        translate([0, 0, 0])
            cube([cuvetteInternal, cuvetteInternal, frontHeight]);
        
        // cutting the windows in cuvette ...
        heightWindow=pcbThickness+frontThickness+supportHeight;
        translate([-cuvetteThickness, (cuvetteInternal-cuvetteWindow)/2, heightWindow])
            cube([cuvetteThickness, cuvetteWindow, frontHeight-overlap]);
        translate([cuvetteInternal, (cuvetteInternal-cuvetteWindow)/2, heightWindow])
            cube([cuvetteThickness, cuvetteWindow, frontHeight-overlap]);
        translate([(cuvetteInternal-cuvetteUVWindow)/2, cuvetteInternal,  heightWindow])
            cube([cuvetteUVWindow, cuvetteThickness, frontHeight-overlap]);
        
        // TEMPORARY to print as today design 
        translate([-r-cuvetteThickness,-cuvetteY, frontThickness+supportHeight])
                cube([cuvetteInternal+cuvetteThickness*2+2*r,cuvetteY-cuvetteThickness,frontHeight-overlap-screenProtectionHeight]);
    }
}

