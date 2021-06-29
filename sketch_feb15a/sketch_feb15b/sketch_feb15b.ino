 #include <SoftwareSerial.h>
 #include <EEPROM.h>
 
SoftwareSerial hm10(8,9); //TX, RX 연결
#define LED 5
#define VLED 6
#define buttonBUS 11
#define buttonP 12
#define sound 10
int ledon = 0;
bool ledBool = false;

int delaybus = 0;
int delayp = 0;
int valuebus = 0;
int valuep = 0;

// code, sideNum 255 이하
// bunNum 65,535 이하
// sideNum 0n - 시내버스
// sideNum 1n - 마을버스
int code = 12;
int whenLedOn = 15;
int whenLedOff = 12;
int bunNum = 190;
int sideNum = 0;

String testone = "one";
String testtwo = "two";
bool cmdbool = false;
bool changeBool = false;

int cmdcount = 0;
int cmdNumCount = 0;

int tempNumA =0;
int tempNumB =0;

char cmdtemp[20];
char lost[] = "LOST";
int charcount = 0;
bool countbool = false;
bool didlost = false;
byte data;
void setup() {

  bunNum = EEPROM.read(0) + 256*(EEPROM.read(1));
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("testBLE" + testone);
  hm10.begin(9600);
  //hm10.write("AT+VERR?");
  String cmd = "AT+PACK"+sendfillhex(whenLedOff, bunNum, sideNum);
  cmd.toUpperCase();
  strcpy(cmdtemp,cmd.c_str());
  Serial.println(cmdtemp);
  hm10.write(cmdtemp);
  pinMode(sound, OUTPUT);
  pinMode(LED, OUTPUT); 
  pinMode(VLED, OUTPUT);
  pinMode(buttonBUS, INPUT_PULLUP);
  pinMode(buttonP, INPUT_PULLUP);
}
 
void loop() {
  digitalWrite(VLED, HIGH);
  // put your main code here, to run r
  
  if(hm10.available())
  {
    epeatedly:
    data=hm10.read();
    Serial.write(data);
    
    if(countbool)
    {
      if(charcount == 4)
      {
        //Serial.println("AFSFASFASFASF");
        cmdbool = true;
      }
      
      if(data == lost[charcount])
      {
        //Serial.println(charcount);
        charcount++;
      }
      
      else
      {
        //Serial.println(charcount);
        charcount = 0;
        countbool = false;
      }
      //Serial.println(charcount);
    }
  if(data == '+'){
      charcount = 0;
      countbool = true;
    }
  }
  
  if(Serial.available())
  {
    data=Serial.read();
    //hm10.write([144, 226, 2, 183, 10, 60]);
    hm10.write(data);
  }
    if(cmdbool){
      delay(260);
      hm10.write(cmdtemp);
      Serial.println(cmdtemp);
      cmdbool = false; 
    }

    
  if(ledon==1 && !ledBool){
    ledBool = true;
    digitalWrite(LED, HIGH);
    Serial.println("LED ON\n");
    ledon = 0;

    String cmd = "AT+PACK"+sendfillhex(whenLedOn, bunNum, sideNum);
    cmd.toUpperCase();
    strcpy(cmdtemp,cmd.c_str());
    hm10.write(cmdtemp);
    
    //hm10.write(cmdtemp);
    //cmdbool = true;
    soundaseck();
    Serial.println(EEPROM.read(0));
  }
  if(ledon == 2){
    ledBool = false;
    digitalWrite(LED, LOW);
    Serial.println("LED OFF\n");
    ledon = 0;

    String cmd = "AT+PACK"+sendfillhex(whenLedOff, bunNum, sideNum);
    cmd.toUpperCase();
    strcpy(cmdtemp,cmd.c_str());
    hm10.write(cmdtemp);
  }
  if(changeBool){
    if(cmdNumCount == 2){
      EEPROM.write(0, data);
      tempNumA = EEPROM.read(0);
    }
    if(cmdNumCount== 1){
      EEPROM.write(1, data);
      tempNumB = EEPROM.read(1);
      bunNum = tempNumA + tempNumB * 256;

      String cmd = "AT+PACK"+sendfillhex(whenLedOff, bunNum, sideNum);
      cmd.toUpperCase();
      strcpy(cmdtemp,cmd.c_str());
      hm10.write(cmdtemp);
    
      changeBool = false;
      data = 0;
    }
  }
  
  if(data == 1 && cmdNumCount == 0){
    ledon = 1;
    data = 0;
  }
  if(data == 2  && cmdNumCount == 0){
    ledon = 2;
    data = 0;
  }
  if(cmdNumCount > 0){
    cmdNumCount = cmdNumCount - 1;
  }
  if(data == 3 && cmdNumCount == 0){
    changeBool = true;
    Serial.println("asdfasdasdfsdffdfdf : " + data);
    
    cmdNumCount = 2;
    
    data = 0;
  }
  valuebus = digitalRead(buttonBUS);
  valuep = digitalRead(buttonP);

  if(valuebus != delaybus){
    delay(5);
    delaybus = digitalRead(buttonBUS);
  }
  if(valuep != delayp){
    delay(5);
    delayp = digitalRead(buttonP);
  }
  if (valuebus == LOW)
  {
    ledon = 1;
    delay(100);
    delaybus = valuebus;
  }
  if (valuep == LOW)
  {
    ledon = 2;
    delay(100);
    delayp = valuep;
  }
  
}

/*
    String inString = Serial.readStringUntil('\n');
    Serial.println("inString");
    Serial.println(inString);
*/

void soundaseck(){
    digitalWrite(sound, HIGH);
    Serial.println("sound high");
    delay(1000);
    digitalWrite(sound, LOW);
}
String sendfillhex (int code, int busnum, int sideNum){
  String stWrite = "";

  String fronttemp = "0000";
  String codehex = String(code, HEX);
  String busnumhex = String(busnum, HEX);
  String sideNumhex = String(sideNum, HEX);

  while( codehex.length() < 2){
    codehex = "0" + codehex;
  }
  while( busnumhex.length() <4 ){
    busnumhex = "0" + busnumhex;
  }
  while(sideNumhex.length() <2){
    sideNumhex = "0" + sideNumhex;
  }
  stWrite = stWrite + fronttemp + codehex + busnumhex + sideNumhex;
  return stWrite;
}
