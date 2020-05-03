use <../publicDomainGearV1.1.scad>
$fn = 120;
mmteeth = 1.95;

module gearModule(){
rotate([180,0,0])difference(){
translate([0,0,4-3])gear(mm_per_tooth = mmteeth, thickness = 8,number_of_teeth = 55,hole_diameter = 20);

for (i = [0:1:5]){
    rotate([0,0,i*60])translate([12.75,0,-1-3]) cylinder(h=10,d=3);
}

translate([0,0,-0.1-3]) cylinder(d=30,h=3.1);

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


gearModule();

translate([50,0,0]) gearModule_2();
!translate([50,50,0]) gearModule_2_mot();