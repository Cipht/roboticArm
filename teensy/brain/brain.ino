char activeOdrive = 2;

#define serialBuffSize 64
#define rcBuffSize 16

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


char remoteSBuffer[rcBuffSize];
int remoteSBuffLen = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(2000000);//pc

  Serial1.begin(115200);//odrive 1
  Serial2.begin(115200);//odrive 2
  Serial3.begin(115200);//odrive 3

  Serial5.begin(2000000);//remote control
	
  memset(remoteSBuffer,0,rcBuffSize);
  
  memset(pc1SBuffer,0,serialBuffSize);
  memset(pc2SBuffer,0,serialBuffSize);
  memset(pc3SBuffer,0,serialBuffSize);
  memset(odrive1SBuffer,0,serialBuffSize);
  memset(odrive2SBuffer,0,serialBuffSize);
  memset(odrive3SBuffer,0,serialBuffSize);
};

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

void logErr(char logStr){
  Serial.println(logStr);
  
};
bool motActive[6] = {false,false,false,false,false,false};
long motPos[6] = {0,0,0,0,0,0};
int incDistance = 100;
void moveActiveMotors(int dist){
	if(motActive[0]){
		motPos[0]+=dist;
		Serial1.print("t 0 ");
		Serial1.println(motPos[0]);
	}	
	if(motActive[1]){
		motPos[1]+=dist;
		Serial1.print("t 1 ");
		Serial1.println(motPos[1]);
	}	

	if(motActive[2]){
		motPos[2]+=dist;
		Serial2.print("t 0 ");
		Serial2.println(motPos[2]);
	}	
	if(motActive[3]){
		motPos[3]+=dist;
		Serial2.print("t 1 ");
		Serial2.println(motPos[3]);
	}	

	if(motActive[4]){
		motPos[4]+=dist;
		Serial3.print("t 0 ");
		Serial3.println(motPos[4]);
	}	
	if(motActive[5]){
		motPos[5]+=dist;
		Serial3.print("t 1 ");
		Serial3.println(motPos[5]);
	}	

};

bool rcKeyPressed(char keycode1,char keycode2){
  
	if(keycode1 == '+' && keycode2 == '+'){//dial plus
		moveActiveMotors(incDistance);	
	}
	else if(keycode1 == '-' && keycode2 == '-'){//dial minus
		moveActiveMotors(-incDistance);	
	}

	if(keycode1 == 'M'){//set motor active 
		if(keycode2=='0') motActive[0] = true;
    if(keycode2=='1') motActive[1] = true;
    if(keycode2=='2') motActive[2] = true;
    if(keycode2=='3') motActive[3] = true;
    if(keycode2=='4') motActive[4] = true;
    if(keycode2=='5') motActive[5] = true;
	}

 if(keycode1 == 'X'){
    if(keycode2=='0') incDistance = 1;
    if(keycode2=='1') incDistance = 20;
    if(keycode2=='2') incDistance = 100;
    if(keycode2=='3') incDistance = 250;
    if(keycode2=='4') incDistance = 500;
    if(keycode2=='5') incDistance = 1000;
 }
};

bool rcKeyReleased(char keycode1,char keycode2){

	if(keycode1 == 'M'){//disable motor
    if(keycode2=='0') motActive[0] = false;
		if(keycode2=='1') motActive[1] = false;
    if(keycode2=='2') motActive[2] = false;
    if(keycode2=='3') motActive[3] = false;
    if(keycode2=='4') motActive[4] = false;
    if(keycode2=='5') motActive[5] = false;
	}
};

bool rcCommand(char* controlCmd,int len){
  
    if(len == 6 && controlCmd[0] == '&' && controlCmd[1] == '&'){//change active odrive
		  
		  rcKeyPressed(controlCmd[2],controlCmd[3]);
		  return true;
    }
    else if(len == 6 && controlCmd[0] == '&' && controlCmd[1] == '^'){//change active odrive
		  rcKeyReleased(controlCmd[2],controlCmd[3]);
		  return true;
	  }
	  return false;
};

void readRemoteControl(){
  if(Serial5.available()){
    if(remoteSBuffLen < rcBuffSize){
      char charIn = Serial5.read();
      remoteSBuffer[remoteSBuffLen] = charIn;
      remoteSBuffLen++;
      if(charIn == '\n'){//return char found push entire string and move to start
	      rcCommand(remoteSBuffer,remoteSBuffLen);
	      remoteSBuffLen = 0;
      }
    }
    else{//max buffer size push it and clear
      logErr("rc max buffer");
	Serial.write(remoteSBuffer,remoteSBuffLen);
        remoteSBuffLen = 0;    
    }
  }  
};

enum controlMode {serialListen,poseable,remoteControl};
controlMode curState = serialListen;

void loop() {
	if(curState == serialListen){
  		odrive1();
  		odrive2();
  		odrive3();
	}
	readRemoteControl();
}
