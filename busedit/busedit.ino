 #include <SoftwareSerial.h>
 
#define LED 8
bool ledbool = false;

char data;

void setup() {
  // put your setup code here, to run once:
   pinMode(LED, OUTPUT); 
   Serial.begin(9600);
   Serial.print("asdf");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    data=Serial.read();
    Serial.println(data);
  }
  if(ledbool){
    digitalWrite(LED, HIGH);
  }
  if(!ledbool){
    digitalWrite(LED, LOW);
  }
  if(data =='1'){
    Serial.print("data1");
    data = '0';
    ledbool = !ledbool;
  }
}
