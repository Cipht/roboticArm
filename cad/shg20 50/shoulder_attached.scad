$fn = 120;
use <./gear.scad>
use <./idler.scad>
use <./shg2050.scad>


rotate([0,180,0])union(){

union(){difference(){//side

    translate([-47,-47,-10])cube([94,140,30]);
    //cutout corners
    translate([-70,50,-10.1])rotate([0,0,50])cube([100,100,30.2]);
    translate([70,50,-10.1])rotate([0,0,40])cube([100,100,30.2]);
    
    translate([0,0,-10.1])cylinder(d=25,h=100);//center of gearhead
    for( i = [4:13]){
        
        rotate([0,0,i*(360/12)+15])translate([42,0,-11]) cylinder(d=3,h=32);
        rotate([0,0,i*(360/12)+15])translate([42,0,20-15]) cylinder(d=6.6,h=20,$fn=6);
        
    }
    
    translate([0,0,-10.01])cylinder(d=50.2,h=27.01);//gear cutout gearhead
    
    translate([-20,30-2.5,5.01])cube([40,4,23.01]);//belt tensioner slot
    translate([0,-10,0]){
        translate([0,75,-10.01])cylinder(d=50,h=23.01);//gear cutout motor
        translate([0,75,20.01-1.7])cylinder(d=38.6,h=1.71);//motor mount plate
        translate([-25,10,-10.01])cube([50,65,23.01]);//belt cutout
        translate([0,75,0])cylinder(d=16,h=100);//motor shaft
        
    
    
    
    //motor mounts
        translate([0+(47.14/2),75+(47.14/2),-15])cylinder(d=4,h=100);
        translate([0+(47.14/2),75+(47.14/2),-10.1])cylinder(d=8.2,h=10,$fn=6);
    
        translate([0+(47.14/2),75-(47.14/2),8])cylinder(d=4,h=30);
        translate([0+(47.14/2),75-(47.14/2),6.9])cylinder(d=8.2,h=9,$fn=6);
    
        translate([0-(47.14/2),75-(47.14/2),8])cylinder(d=4,h=30);
        translate([0-(47.14/2),75-(47.14/2),6.9])cylinder(d=8.2,h=9,$fn=6);
    
        translate([0-(47.14/2),75+(47.14/2),-15])cylinder(d=4,h=100);
        translate([0-(47.14/2),75+(47.14/2),-10.1])cylinder(d=8.2,h=10,$fn=6);
    }
    //
    
    //threaded rod
    translate([-55,-47+12,0]) rotate([0,90,0]) cylinder(d=4,h=150);
    
    translate([0,-7.5,0]){
    //idler screw
    translate([0,33,2.9]) rotate([0,90,0]) cylinder(d=3,h=50);
    translate([0,33+8,2.9]) rotate([0,90,0]) cylinder(d=3,h=50);
    //idler nut
    translate([15+6.5,33,2.9]) rotate([0,90,0]) cylinder(d=6.6,h=8,$fn=6);
    translate([15+6.5,33+8,2.9]) rotate([0,90,0]) cylinder(d=6.6,h=8,$fn=6);
    //idler countersink    
    translate([40.1,33,2.9]) rotate([0,90,0]) cylinder(d=5.8,h=8.15);
    translate([40.1,33+8,2.9]) rotate([0,90,0]) cylinder(d=5.8,h=8.15);
    }
    translate([-20,-225,-10.1])cube([40,200,20.1]);//2040 cutout
}//end dif
    difference(){
            translate([-25,21-2.5,-10])cube([50,22,23-17.6]);//17.6
            translate([-20,30-2.5,-11])cube([40,4,23.01]);//17.6
            translate([-20,30-1.5-2.5,-10.1])cube([40,7,4]);//17.6
    }

}//end union
%translate([82-5.4,0,92])pulleyHolder();

//%translate([-20,-225,-10])cube([40,200,30]);
difference(){
hull(){
    translate([-47,-57,-10])cube([94,10,30]);
    translate([-0,-100,-10])cylinder(d=40,h=30);
}
translate([-20,-225,-10.1])cube([40,200,20.1]);//2040 cutout
translate([-55,-75,0]) rotate([0,90,0]) cylinder(d=4,h=150);//threaded rod

//t nut m4 holes
translate([-10,-100,0])  cylinder(d=4,h=50);
translate([10,-100,0])  cylinder(d=4,h=50);

translate([10,-80,0])  cylinder(d=4,h=50);
translate([-10,-80,0])  cylinder(d=4,h=50);

translate([-10,-60,0])  cylinder(d=4,h=50);
translate([10,-60,0])  cylinder(d=4,h=50);
}
}//end full union
