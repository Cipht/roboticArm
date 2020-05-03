//pulley carrier
$fn = 60;
module m4pulley(){
    difference(){
        cylinder(d = 16, h = 10);
        translate([0,0,-0.1])cylinder(d = 4, h = 11);
    
    }
}


translate([0,0,.1])m4pulley();

module pulleyHolder(){
    difference(){
        translate([-8,-10,-3]) cube([21,20,16]); 
        translate([-11,-11,-.9]) cube([20,22,11.8]);
        translate([0,0,-5])cylinder(d = 4, h = 20);
        
        translate([11.1, 4,4.5])rotate([0,90,0])cylinder(d = 4.5, h = 2,$fn=6);
        translate([11.1,-4,4.5])rotate([0,90,0])cylinder(d = 4.5, h = 2,$fn=6);
    }
}

!rotate([90,0,0])pulleyHolder();