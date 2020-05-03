void setup() {
  // put your setup code here, to run once:
  Serial.begin(2000000);//pc
  
  Serial2.begin(115200);//odrive 1
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    Serial2.write(Serial.read());
  }
  if(Serial2.available()){
    Serial.write(Serial2.read());
    
  }
}
