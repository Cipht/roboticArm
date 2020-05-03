
int ledpin = 13;//level shifter enable
int pulsepin1 = 15;
int pulsepin2 = 14; 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(2000000);
  
  pinMode(ledpin,OUTPUT);
  digitalWrite(ledpin,HIGH);
  
  pinMode(pulsepin1,INPUT);
  
  pinMode(pulsepin2,INPUT);
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
    return '+';
  }
  
  if(!pin2 && !prepin1 && !hit){
    hit = true;
    prepin1 = pin1;
    prepin2 = pin2;
    Mouse.scroll(-1);
    return '-';
  }
  
  prepin1 = pin1;
  prepin2 = pin2;
  return 0;
}
void loop() {
  char wheel = checkWheel();
  if(wheel){ 
    Serial.println(wheel);
  }
}
