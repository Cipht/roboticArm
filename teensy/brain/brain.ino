char activeOdrive = 2;

#define serialBuffSize 64

char pc1SBuffer[serialBuffSize];
int pc1SBuffLen = 0;
char odrive1SBuffer[serialBuffSize];
int odrive1SBuffLen = 0;

char pc2SBuffer[serialBuffSize];
int pc2SBuffLen = 0;
char odrive2SBuffer[serialBuffSize];
int odrive2SBuffLen = 0;

char pc3SBuffer[serialBuffSize];
int pc3SBuffLen = 0;
char odrive3SBuffer[serialBuffSize];
int odrive3SBuffLen = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(2000000);//pc

  Serial1.begin(115200);//odrive 1
  Serial2.begin(115200);//odrive 2
  Serial3.begin(115200);//odrive 3

  
  memset(pc1SBuffer,0,serialBuffSize);
  memset(pc2SBuffer,0,serialBuffSize);
  memset(pc3SBuffer,0,serialBuffSize);
  memset(odrive1SBuffer,0,serialBuffSize);
  memset(odrive2SBuffer,0,serialBuffSize);
  memset(odrive3SBuffer,0,serialBuffSize);
}

void odrive1(){
  if(activeOdrive == 1 && Serial.available()){
    if(pc1SBuffLen < serialBuffSize){
      char charIn = Serial.read();
      pc1SBuffer[pc1SBuffLen] = charIn;
      pc1SBuffLen++;
      if(charIn == '\n'){//return char found push entire string and move to start
        if(pc1SBuffLen == 4 && pc1SBuffer[0] == '%' && pc1SBuffer[1] == '%'){//change active odrive
          if (pc1SBuffer[2] == '1') activeOdrive = 1;
          if (pc1SBuffer[2] == '2') activeOdrive = 2;
          if (pc1SBuffer[2] == '3') activeOdrive = 3;
          pc1SBuffLen = 0;
        }
        else{
          Serial1.write(pc1SBuffer,pc1SBuffLen);
          pc1SBuffLen = 0;
        }
      }
    }
    else{//max buffer size push it and clear
        Serial1.write(pc1SBuffer,pc1SBuffLen);
        pc1SBuffLen = 0;
    }
  }
  if(activeOdrive == 1 && Serial1.available()){
    Serial.write(Serial1.read());
  }
};
void odrive2(){
  if(activeOdrive == 2 && Serial.available()){
        if(pc2SBuffLen < serialBuffSize){
      char charIn = Serial.read();
      pc2SBuffer[pc2SBuffLen] = charIn;
      pc2SBuffLen++;
      if(charIn == '\n'){//return char found push entire string and move to start
        if(pc2SBuffLen == 4 && pc2SBuffer[0] == '%' && pc2SBuffer[1] == '%'){//change active odrive
          if (pc2SBuffer[2] == '1') activeOdrive = 1;
          if (pc2SBuffer[2] == '2') activeOdrive = 2;
          if (pc2SBuffer[2] == '3') activeOdrive = 3;
          pc2SBuffLen = 0;
        }
        else{
          Serial2.write(pc2SBuffer,pc2SBuffLen);
          pc2SBuffLen = 0;   
        }
      }
    }
    else{//max buffer size push it and clear
        Serial2.write(pc2SBuffer,pc2SBuffLen);
        pc2SBuffLen = 0;
        
    
    }
  }
  if(activeOdrive == 2 && Serial2.available()){
    Serial.write(Serial2.read());
  }
};
void odrive3(){
  if(activeOdrive == 3 && Serial.available()){
    if(pc3SBuffLen < serialBuffSize){
      char charIn = Serial.read();
      pc3SBuffer[pc3SBuffLen] = charIn;
      pc3SBuffLen++;
      if(charIn == '\n'){//return char found push entire string and move to start
        if(pc3SBuffLen == 4 && pc3SBuffer[0] == '%' && pc3SBuffer[1] == '%'){//change active odrive
          if (pc3SBuffer[2] == '1') activeOdrive = 1;
          if (pc3SBuffer[2] == '2') activeOdrive = 2;
          if (pc3SBuffer[2] == '3') activeOdrive = 3;
          pc3SBuffLen = 0;  
        }
        else{
          Serial3.write(pc3SBuffer,pc3SBuffLen);
          pc3SBuffLen = 0;
        }       
      }
    }
    else{//max buffer size push it and clear
        Serial3.write(pc3SBuffer,pc3SBuffLen);
        pc3SBuffLen = 0;    
    }
  }
  if(activeOdrive == 3 && Serial3.available()){
    Serial.write(Serial3.read());
  }
};


void loop() {
  odrive1();
  odrive2();
  odrive3();
}
