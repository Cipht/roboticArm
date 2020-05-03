use <./gear.scad>
//g is to toggle render of gear
module shg2050(g=1){
    difference(){
        union(){
            translate([0,0,-5])cylinder(d=30,h=10);
            cylinder(d=95,h=10.5);
            translate([0,0,0])cylinder(d=90,h=25.5);
            translate([0,0,0])cylinder(d=75.3,h=40);
            translate([0,0,0])cylinder(d=50.3,h=48);
           if(g==1){ 
                translate([0,0,-5])gearModule();
           }
        }
        translate([0,0,-10])cylinder(d=20,h=100);
    }
}

module shg2050_2(g=1){
    difference(){
        union(){
            translate([0,0,-9.3-6.6])cylinder(d=35,h=10);
            translate([0,0,-6.6])cylinder(d=50,h=10);
            
            cylinder(d=95,h=13.5);
            translate([0,0,3])cylinder(d=90,h=25.5);
            translate([0,0,3])cylinder(d=75.3,h=40);
            translate([0,0,3])cylinder(d=52,h=53); 
            if(g==1){
                translate([0,0,-16])gearModule_2();
            }
        }
        translate([0,0,-16])cylinder(d=25,h=100);
    }
}

shg2050_2(g = 0);

translate([150,0,0])shg2050(g=0);

