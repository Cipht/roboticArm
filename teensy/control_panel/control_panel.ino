#include <Bounce.h>

int groundPinArray[5] = { 8,9,10,11,12 };//pin behind diode's cathode, ground for button
int posPin[6] = { 7,6,5,4,3,2 };//pins set to input with pullup resistor

Bounce bounceMatrix[5][6] = {
  { Bounce(posPin[0], 10), Bounce(posPin[1], 10), Bounce(posPin[2], 10), Bounce(posPin[3], 10), Bounce(posPin[4], 10), Bounce(posPin[5], 10)},
  { Bounce(posPin[0], 10), Bounce(posPin[1], 10), Bounce(posPin[2], 10), Bounce(posPin[3], 10), Bounce(posPin[4], 10), Bounce(posPin[5], 10)},
  { Bounce(posPin[0], 10), Bounce(posPin[1], 10), Bounce(posPin[2], 10), Bounce(posPin[3], 10), Bounce(posPin[4], 10), Bounce(posPin[5], 10)},
  { Bounce(posPin[0], 10), Bounce(posPin[1], 10), Bounce(posPin[2], 10), Bounce(posPin[3], 10), Bounce(posPin[4], 10), Bounce(posPin[5], 10)},
  { Bounce(posPin[0], 10), Bounce(posPin[1], 10), Bounce(posPin[2], 10), Bounce(posPin[3], 10), Bounce(posPin[4], 10), Bounce(posPin[5], 10)}
};

int ledpin = 13;//level shifter enable
int pulsepin1 = 15;
int pulsepin2 = 14; 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(2000000);//pc
  
  Serial4.begin(2000000);//remote control
  
  pinMode(ledpin,OUTPUT);
  digitalWrite(ledpin,HIGH);
  
  pinMode(pulsepin1,INPUT);
  
  pinMode(pulsepin2,INPUT);



  pinMode(posPin[0], INPUT_PULLUP);
  pinMode(posPin[1], INPUT_PULLUP);
  pinMode(posPin[2], INPUT_PULLUP);
  pinMode(posPin[3], INPUT_PULLUP);
  pinMode(posPin[4], INPUT_PULLUP);
  pinMode(posPin[5], INPUT_PULLUP);

  for (int i = 0; i <  5; i++) {
    pinMode(groundPinArray[i],HIGH);
  }
  delay(10);
  for(int row = 0; row < 5; row++)
    for (int col= 0; col< 6;col++) 
      bounceMatrix[row][col].update();
  

}
  bool pin1,pin2;
  bool prepin1=true,prepin2=true;
  bool hit = false;
char checkWheel(){
  pin1 = digitalRead(pulsepin1);
  pin2 = digitalRead(pulsepin2);
  if(pin1 && pin2) hit = false;
  
  if(!pin1 && !prepin2 && !hit){
    hit = true;
    prepin1 = pin1;
    prepin2 = pin2;
    Mouse.scroll(1);
    Serial4.println("&&++");
    return '+';
  }
  
  if(!pin2 && !prepin1 && !hit){
    hit = true;
    prepin1 = pin1;
    prepin2 = pin2;
    Mouse.scroll(-1);
    Serial4.println("&&--");
    return '-';
  }
  
  prepin1 = pin1;
  prepin2 = pin2;
  return 0;
}

void keyPressed( int row,int col) {
 Serial.printf("%i %i down\n",row,col);
 if(row == 0){
  Serial4.print("&&M");
  Serial4.println(col);
 }
}
void keyReleased(int row, int col) {
 Serial.printf("%i %i up\n",row,col);
  if(row == 0){
    Serial4.print("&^M");
    Serial4.println(col);
  }
}
int row = 0;
void loop() {
  char wheel = checkWheel();
  if(wheel){ 
    Serial.println(wheel);
  }

    for (int col= 0; col< 6;col++) {
    if (bounceMatrix[row][col].update()) {
      if (bounceMatrix[row][col].fallingEdge()) {
        keyPressed(row, col);
      }
      else if (bounceMatrix[row][col].risingEdge()) {
        keyReleased(row, col);
      }
    }
  }
  pinMode(groundPinArray[row],LOW);

  row++;
  if (row>= 5) {
    row = 0;
  }
  pinMode(groundPinArray[row], HIGH);
  delayMicroseconds(15);
}
