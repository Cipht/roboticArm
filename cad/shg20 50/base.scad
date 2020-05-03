use <./shg2050.scad>
$fn = 120;
screws = 3;
width = 150;
height = 150;
thickness = 35;
difference(){
    translate([-(width/2),-(height/2),0])cube([width,height,thickness]);
    translate([0,0,33+thickness])rotate([180,0,0])shg2050_2(g=0);
    
    translate([0,0,-60]) cylinder(d=35,h=200);
    
    for( i = [0:16]){
        rotate([0,0,i*(360/16)])translate([-31,0,-10]) cylinder(d=3,h=50);
    }
    translate([-10,.1,-.1])cube([20,height/2,10.1]);
    
    //threaded rod
    translate([-(width/2),-40,15])rotate([0,90,0])cylinder(d=4,h=150);
    translate([-(width/2),40,15])rotate([0,90,0])cylinder(d=4,h=150);
    
    //rails
    translate([-(width/2)-.2,-(height/2)-.1,-15]) cube([20.4,height+.2,40]);
    translate([(width/2)-20.2,-(height/2)-.1,-15]) cube([20.4,height+.2,40]);
    
    for(i = [0:1:screws]){
        translate([(width/2)-10.2,i*((height-20)/screws)-(height/2)+10,20])cylinder(d=4,h=20);
        
        translate([(-width/2)+10.2,i*((height-20)/screws)-(height/2)+10,20])cylinder(d=4,h=20);
    }
}
