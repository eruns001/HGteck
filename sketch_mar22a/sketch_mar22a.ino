#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3); // 소프트웨어 시리얼 (TX,RX)

void setup() {
  Serial.begin(9600);            // 통신속도 9600으로 설정
  Serial.println("Hello!");      // 시리얼모니터에 Hello 출력
  BTSerial.begin(9600);
}

void loop() {
  while (BTSerial.available()) {
    byte data = BTSerial.read();
    Serial.write(data);
  }

  while (Serial.available()) {
    byte data = Serial.read();
    BTSerial.write(data);
  }
}
