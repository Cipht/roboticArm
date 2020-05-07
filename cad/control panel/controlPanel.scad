//
$fn = 60;
panelxsz = 110;
panelysz = 180;
wallsz = 2;
mirror([0,0,0]) difference(){
    union(){
        translate([-32,-60,0]) cube([panelxsz,panelysz,2]);//top plane
        for ( i = [0:1:2]){//col1 psp
            translate([startx - 18 + (i * 30),starty-18,-0.1]) {
                translate([0,-12,2])cylinder(d=5,h=3.75);
                translate([0,12,2])cylinder(d=5,h=3.75);
            }
        
        }
        for ( i = [0:1:2]){//col2 psp
            translate([startx - 18 + (i * 30),starty-18-30,-0.1]) {
                translate([0,-12,2])cylinder(d=5,h=3.75);
                translate([0,12,2])cylinder(d=5,h=3.75);
            }
        
        }
    }    
    translate([0,60,0]){
        translate([-25.8,0,-0.1]) cylinder(3,r=1.5);//rotary encoder screws
        rotate([0,0,120]) translate([-25.8,0,-0.1]) cylinder(3,r=1.5);
        rotate([0,0,240]) translate([-25.8,0,-0.1]) cylinder(3,r=1.5);
        translate([-0,0,-.1])cylinder(3,r=21.2 );//rotary encoder opening
	}
	
    for ( i = [0:1:2]){//col1 psp
        translate([startx - 18 + (i * 30),starty-18,-0.1]) {cylinder(d=18.4,h=5);
            translate([-10,-7,-1])cylinder(d=1.9,h=6);
            translate([0,-12,-2])cylinder(d=1.9,h=10);
            translate([0,12,-2])cylinder(d=1.9,h=10);
        }
    }
    for ( i = [0:1:2]){//col2 psp
        translate([startx - 18 + (i * 30),starty-18-30,-0.1]) {cylinder(d=18.4,h=5);
            translate([-10,-7,-1])cylinder(d=1.9,h=6);
            translate([0,-12,-2])cylinder(d=1.9,h=10);
            translate([0,12,-2])cylinder(d=1.9,h=10);
        }
    }
    
    translate([startx -33.4+ (3 * 30),starty-57,-0.1]){
        cube([16,48,5]);
        translate([8,-3,0]) cylinder(d=1.9,h=5);
        translate([8,51,0]) cylinder(d=1.9,h=5);
        translate([-3,24,0]) cylinder(d=1.9,h=5);
        translate([19,24,0]) cylinder(d=1.9,h=5);
    }
	switchOpening = 14.1;
	switchStrideX = 5.4;
	switchStrideY = 5.4;
	startx = 0;
	starty = 4;
	//switch row -1
	translate([startx+(-1*switchStrideX)+(-1*switchOpening),starty,-0.1]) cube([switchOpening,switchOpening,3]);
	
	translate([startx+(-1*switchStrideX)+(-1*switchOpening),starty+(5*switchStrideY)+(5*switchOpening),-0.1]) cube([switchOpening,switchOpening,3]);
	//switch row 0
	translate([startx,starty,-0.1]) cube([switchOpening,switchOpening,3]);
	translate([startx,starty+(5*switchStrideY)+(5*switchOpening),-0.1]) cube([switchOpening,switchOpening,3]);
	
	//switch row 1
	translate([startx+(1*switchStrideX)+(1*switchOpening),starty,-0.1]) cube([switchOpening,switchOpening,3]);
	translate([startx+(1*switchStrideX)+(1*switchOpening),starty+(5*switchStrideY)+(5*switchOpening),-0.1]) cube([switchOpening,switchOpening,3]);
	
	//switch row 2
    for ( i = [0:1:5]){
        translate([startx+(2*switchStrideX)+(2*switchOpening),starty+(i*switchStrideY)+(i*switchOpening),-0.1]) cube([switchOpening,switchOpening,3]);
    }
	//switch row 3
    for ( i = [0:1:5]){
        translate([3 *(switchStrideX + switchOpening)+startx,i*(switchStrideY + switchOpening)+starty,-0.1]) cube([switchOpening,switchOpening,3]);
    }

}
height = 32;
angle = 4;
difference(){
    union(){
        difference(){
        translate([78,-60,0]) cube([2,panelysz,height]);
  translate([-30+wallsz,-60+wallsz,height-10]) rotate([0,angle,0])cube([150,panelysz-(2*wallsz),40]);
        }
            translate([-32,-60,0]) cube([110,2,height]);
        translate([-32,-62+panelysz,0]) cube([110,2,height]);
        difference(){
            translate([-32,-60,0]) cube([2,panelysz,height]);
            translate([-33,25,26.5]) cube([5,13,6]);
        
        }
    }
    translate([-32,62-panelysz,height]) rotate([0,angle,0])cube([150,2*panelysz,40]);
    
    translate([panelxsz-32-3,panelysz,height-(tan(angle)*(panelxsz-3))-1.5-2])rotate([90,0,0])cylinder(d=3,h=2*panelysz);
    translate([-52,0,height-4])rotate([0,90,0])cylinder(d=3,h=2*panelysz);
    translate([-52,70,height-4])rotate([0,90,0])cylinder(d=3,h=2*panelysz);
}

//bottom panel
panelwall = 7;
clearance = 0.4;
rotate([0,180-angle,0])translate([63,0,-52.35])
//translate([0,0,-18])
union(){
    


    
    difference(){
        union(){
        translate([-32+wallsz+clearance,-60+wallsz+clearance,42])rotate([0,angle,0])cube([(panelxsz+2)/cos(angle)-((wallsz+clearance)*2),panelysz-((wallsz+clearance)*2),8]);
                translate([-32+wallsz+clearance,-60+wallsz+clearance,48])rotate([0,angle,0])cube([(panelxsz+2)/cos(angle)-((wallsz+clearance)*2),panelysz-((wallsz+clearance)*2),2]);
        
        }
        translate([-32+wallsz+panelwall,-60+wallsz+panelwall,40])rotate([0,angle,0])cube([(panelxsz+2)/cos(angle)-(wallsz*2)-(panelwall*2),panelysz-(wallsz*2)-(panelwall*2),8]);
    translate([-33,25,42]) rotate([0,angle,0])cube([15,13,7]);

        
        translate([panelxsz-32-3,panelysz,height+(tan(angle)*(panelxsz+4))-1])rotate([90,0,0])cylinder(d=2.7,h=2*panelysz);
        
        translate([-52,0,height+14])rotate([0,90,0])cylinder(d=2.7,h=35);
        
        translate([-52,70,height+14])rotate([0,90,0])cylinder(d=2.7,h=35);
          
      //cable support
        translate([-17,42,height+10]){
                translate([0,-12,2])cylinder(d=1.9,h=10);
                translate([0,12,2])cylinder(d=1.9,h=10);
            
        }
        translate([-10,32,height+10]){
                translate([0,-12,2])cylinder(d=1.9,h=10);
                translate([0,12,2])cylinder(d=1.9,h=10);
            
     }
        }
        translate([-5,5,0]){
        %translate([0,1,40])rotate([0,angle,0])cube([70,50,2]);
        translate([0+2.5,1+2.5,43])rotate([0,angle,0])
            difference(){cylinder(d=5,h=3.5);translate([0,0,-1])cylinder(d=1.9,h=5);}
      
        translate([69-2.5,1+2.5,43-70*tan(angle)])rotate([0,angle,0])
            difference(){cylinder(d=5,h=3.8);translate([0,0,-1])cylinder(d=1.9,h=5);} 
      
            
        translate([0+2.5,51-2.5,43])rotate([0,angle,0])
            difference(){cylinder(d=5,h=3.5);translate([0,0,-1])cylinder(d=1.9,h=5);}
      
        translate([69-2.5,51-2.5,43-70*tan(angle)])rotate([0,angle,0])
            difference(){cylinder(d=5,h=3.8);translate([0,0,-1])cylinder(d=1.9,h=5);}
  
        
        %translate([0,-51,40])rotate([0,angle,0])cube([70,50,2]);
    
        translate([0+2.5,-51+2.5,43])rotate([0,angle,0])
            difference(){cylinder(d=5,h=3.5);translate([0,0,-1])cylinder(d=1.9,h=5);}
      
        translate([69-2.5,-51+2.5,43-70*tan(angle)])rotate([0,angle,0])
            difference(){cylinder(d=5,h=3.8);translate([0,0,-1])cylinder(d=1.9,h=5);} 
      
            
        translate([0+2.5,-1-2.5,43])rotate([0,angle,0])
            difference(){cylinder(d=5,h=3.5);translate([0,0,-1])cylinder(d=1.9,h=5);}
      
        translate([69-2.5,-1-2.5,43-70*tan(angle)])rotate([0,angle,0])
            difference(){cylinder(d=5,h=3.8);translate([0,0,-1])cylinder(d=1.9,h=5);}
        

        translate([0,52,0]){
            %translate([0,1,40])rotate([0,angle,0])cube([70,50,2]);
            translate([0+2.5,1+2.5,43])rotate([0,angle,0])difference(){
                cylinder(d=5,h=3.5);translate([0,0,-1])cylinder(d=1.9,h=5);
            }
      
            translate([69-2.5,1+2.5,43-70*tan(angle)])rotate([0,angle,0])difference(){            cylinder(d=5,h=3.8);translate([0,0,-1])cylinder(d=1.9,h=5);
            } 
      
            translate([0+2.5,51-2.5,43])rotate([0,angle,0]) difference(){
                cylinder(d=5,h=3.5);translate([0,0,-1])cylinder(d=1.9,h=5);
            }
      
            translate([69-2.5,51-2.5,43-70*tan(angle)])rotate([0,angle,0])difference(){
                cylinder(d=5,h=3.8);translate([0,0,-1])cylinder(d=1.9,h=5);
            }
            
        }
        }

  
}

mirror([0,0,180])translate([87,-52,-5]){//lcd plate
    difference(){
        union(){
            cube([16,48,2]);
            translate([-5,-5,2])cube([16+10,48+10,3]);
        }
        translate([8,-3,1]) cylinder(d=1.9,h=5);
        translate([8,51,1]) cylinder(d=1.9,h=5);
        translate([-3,24,1]) cylinder(d=1.9,h=5);
        translate([19,24,1]) cylinder(d=1.9,h=5);
    }
}
for(j = [0 : 1 : 1])
for(i  = [0 : 1 : 2])
translate([87+(j*12),20+(i * 35),-5])difference(){
    translate([-5,-15,5])cube([10,30,3]);
    translate([0,-12,-5])cylinder(d=2,h=30);
    translate([0,12,-5])cylinder(d=2,h=30);
}