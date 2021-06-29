
#define s0 8
#define s1 9
#define s2 10
#define s3 11

#define UpButton 12
#define DownButton 13
#define SendButton 7

#define UP_SHORT_PRESS 1
#define UP_LONG_PRESS  2
#define DOWN_SHORT_PRESS  3
#define DOWN_LONG_PRESS  4
#define SEND_SHORT_PRESS  5
#define SEND_LONG_PRESS  6

uint8_t Signal = 0;
int up = 0;
int beforeup = 0;
int down = 0;
int beforedown = 0;

int muxChannel[16][4]={
  {0,0,0,0}, //channel 0 
  {1,0,0,0}, //channel 1 
  {0,1,0,0}, //channel 2 
  {1,1,0,0}, //channel 3 
  {0,0,1,0}, //channel 4 
  {1,0,1,0}, //channel 5 
  {0,1,1,0}, //channel 6 
  {1,1,1,0}, //channel 7 
  {0,0,0,1}, //channel 8 
  {1,0,0,1}, //channel 9 
  {0,1,0,1}, //channel 10 
  {1,1,0,1}, //channel 11 
  {0,0,1,1}, //channel 12 
  {1,0,1,1}, //channel 13 
  {0,1,1,1}, //channel 14 
  {1,1,1,1} //channel 15 
  };
int controlPin[] = {s0, s1, s2, s3}; 


void setup() {
  pinMode(UpButton, INPUT_PULLUP);
  pinMode(DownButton, INPUT_PULLUP);
  
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);

  digitalWrite(s0, LOW); 
  digitalWrite(s1, LOW); 
  digitalWrite(s2, LOW); 
  digitalWrite(s3, LOW);
}

void loop() {
  up = digitalRead(UpButton);
  down = digitalRead(DownButton);
  snd = digitalRead(SendButton);

  if(up!=beforeup){
    delay(5);
    up = digitalRead(UpButton);
  }
  if(down!=beforedown){
    delay(5);
    down = digitalRead(DownButton);
  }
  if(up == HIGH && beforeup == LOW && Signal < 15){
    Signal ++;
  }
  if(down == HIGH && beforedown == LOW && Signal > 0){
    Signal --;
  }
  if(snd == HIGH&& beforesnd == LOW){
    for( int i = 0; i< 4; i++){
    digitalWrite(controlPin[i], muxChannel[Signal][i]);
  }
  }
  for( int i = 0; i< 4; i++){
    digitalWrite(controlPin[i], muxChannel[Signal][i]);
  }
  
  beforeup = up;
  beforedown = down;
  beforesnd = snd;
}

int readBtn(){
  
}
