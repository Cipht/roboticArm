use <../publicDomainGearV1.1.scad>
$fn = 120;
mmteeth = 1.9;

module gearModule(){
    
    
rotate([180,0,0])difference(){
    union(){
translate([0,0,-5])cylinder(d=35,h=8);
        translate([0,0,10])gear(mm_per_tooth = mmteeth, thickness = 15,number_of_teeth = 55,hole_diameter = 20);
    }

for (i = [0:1:5]){
    rotate([0,0,i*60])translate([12.75,0,-1-3]) cylinder(h=100,d=3);
}

translate([0,0,-0.1-5]) cylinder(d=30,h=3.1);

translate([0,0,-0.1-5]) cylinder(d=21,h=100);

}
}
module gearModule_small(){
    
    
rotate([180,0,0])difference(){
    union(){
translate([0,0,0])cylinder(d=35,h=5);
        translate([0,0,10])gear(mm_per_tooth = mmteeth, thickness = 13,number_of_teeth = 30,hole_diameter = 0);
    }

for (i = [0:1:5]){
    rotate([0,0,i*60])translate([12.75,0,-1-3]) cylinder(h=100,d=3);
}

translate([0,0,-0.1]) cylinder(d=30,h=3.1);

translate([0,0,-0.1-5]) cylinder(d=4,h=100);

}
}

module gearModule_2(){
rotate([180,0,0])difference(){
translate([0,0,-1])gear(mm_per_tooth = mmteeth, thickness = 13,number_of_teeth = 65,hole_diameter = 25);

for (i = [0:1:5]){
    rotate([0,0,i*60])translate([15,0,-1-3]) cylinder(h=10,d=3);
}

translate([0,0,-0.1-8]) cylinder(d=35,h=9.1);

}
}
module gearModule_2_mot(){
rotate([180,0,0]){difference(){
translate([0,0,-1])gear(mm_per_tooth = mmteeth, thickness = 13,number_of_teeth = 65,hole_diameter = 0);



translate([0,0,-0.1-8]) cylinder(d=8.3,h=90.1);

}
translate([3.6,-10,-7.5])cube([5,20,13]);
}
}
module gearModule_mot(){
rotate([180,0,0]){difference(){
translate([0,0,-1])gear(mm_per_tooth = mmteeth, thickness = 13,number_of_teeth = 35,hole_diameter = 0);



translate([0,0,-0.1-8]) cylinder(d=8.3,h=90.1);

}
translate([3.6,-3,-7.5])cube([1,6,13]);
}
}

gearModule();
translate([0,50,0])gearModule_mot();
translate([0,100,0])gearModule_small();
translate([50,0,0]) gearModule_2();
translate([50,50,0]) gearModule_2_mot();