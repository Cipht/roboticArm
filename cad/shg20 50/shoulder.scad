$fn = 120;
use <./gear.scad>
use <./idler.scad>
use <./shg2050.scad>


rotate([90,0,0])union(){

difference(){//flat
    translate([-47,-47,32])cube([102,94,20]);
    translate([0,0,-10])cylinder(d=21,h=100);//center of gearhead
    
    translate([20,0,71])rotate([0,112,0])cylinder(d=27,h=100);//cable route
    
    //threaded rod
    translate([-38,50,42]) rotate([90,0,0]) cylinder(d=4,h=100);
    translate([35,50,42]) rotate([90,0,0]) cylinder(d=4,h=100);
    
    
    for( i = [0:16]){
        rotate([0,0,i*(360/16)])translate([31,0,0]) cylinder(d=3,h=100);
    }
    shg2050();
}
translate([75,0,55])rotate([90,0,-90])union(){difference(){//side
    
        translate([-47,-47,-10])cube([94,160,30]);
        

        
    translate([0,0,-10.1])cylinder(d=25,h=100);//center of gearhead
    for( i = [5:13]){
        if (i != 7 && i != 11){
        rotate([0,0,i*(360/12)])translate([42,0,-11]) cylinder(d=3,h=32);
        rotate([0,0,i*(360/12)])translate([42,0,20-15]) cylinder(d=6.6,h=20,$fn=6);
        }
    }
    
    translate([0,0,-10.01])cylinder(d=50.2,h=27.01);//gear cutout gearhead
    translate([0,75,-10.01])cylinder(d=50,h=23.01);//gear cutout motor
    translate([0,75,20.01-1.7])cylinder(d=38.6,h=1.71);//motor mount plate
    translate([-25,0,-10.01])cube([50,75,23.01]);//belt cutout
    translate([0,75,0])cylinder(d=16,h=100);//motor shaft
    translate([-20,35,5.01])cube([40,4,23.01]);//belt tensioner slot
    
    //17.6
    
    //motor mounts
    translate([0+(47.14/2),75+(47.14/2),-15])cylinder(d=4,h=100);
    translate([0+(47.14/2),75+(47.14/2),-10.1])cylinder(d=8.2,h=10,$fn=6);
    
    translate([0+(47.14/2),75-(47.14/2),-15])cylinder(d=4,h=100);
    translate([0+(47.14/2),75-(47.14/2),-10.1])cylinder(d=8.2,h=26,$fn=6);
    
    translate([0-(47.14/2),75-(47.14/2),-15])cylinder(d=4,h=100);
    translate([0-(47.14/2),75-(47.14/2),-10.1])cylinder(d=8.2,h=26,$fn=6);
    
    translate([0-(47.14/2),75+(47.14/2),-15])cylinder(d=4,h=100);
    translate([0-(47.14/2),75+(47.14/2),-10.1])cylinder(d=8.2,h=10,$fn=6);
    //
    
    //threaded rod
    translate([-55,-47+14,0]) rotate([0,90,0]) cylinder(d=4,h=150);
    translate([-55,105,0]) rotate([0,90,0]) cylinder(d=4,h=150);
    
    //idler screw
    translate([0,33,2.9]) rotate([0,90,0]) cylinder(d=3,h=50);
    translate([0,33+8,2.9]) rotate([0,90,0]) cylinder(d=3,h=50);
    //idler nut
    translate([15+6.5,33,2.9]) rotate([0,90,0]) cylinder(d=6.6,h=8,$fn=6);
    translate([15+6.5,33+8,2.9]) rotate([0,90,0]) cylinder(d=6.6,h=8,$fn=6);
    //idler countersink    
    translate([40.1,33,2.9]) rotate([0,90,0]) cylinder(d=5.8,h=8.15);
    translate([40.1,33+8,2.9]) rotate([0,90,0]) cylinder(d=5.8,h=8.15);
    
}//end dif
    difference(){
            translate([-30,26,-10])cube([60,22,23-17.6]);//17.6
            translate([-20,35,-11])cube([40,4,23.01]);//17.6
            translate([-20,35-1.5,-10.1])cube([40,7,4]);//17.6
    }

}//end union
%translate([82-5.4,0,92])rotate([90,0,-90])pulleyHolder();
}//end full union


//%translate([85,0,55])rotate([0,90,0])shg2050_2();

/*
translate([49,0,125])rotate([0,0,90])union(){
    import("C:/Users/stein/OneDrive/scad/cad/motor Enclosure_Natural_Cooling.stl");
    import("C:/Users/stein/OneDrive/scad/cad/motor Enclosure_Plate.stl");
}
*/