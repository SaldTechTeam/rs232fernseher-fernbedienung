const int button1Pin = 2;
const int button2Pin = 3;
const int button3Pin = 4;


void setup() {
  Serial.begin(9600);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
}

void loop() {
  int buttonState1 = digitalRead(button1Pin);
  int buttonState2 = digitalRead(button2Pin);
  int buttonState3 = digitalRead(button3Pin);
  
  byte powerOn[9] = {0x38, 0x00, 0x01, 0x73, 0x21, 0x30, 0x30, 0x31, 0x0D};
  byte powerOff[9] = {0x38, 0x00, 0x01, 0x73, 0x21, 0x30, 0x30, 0x30, 0x0D};
  byte inputH1[9] = {0x38, 0x00, 0x01, 0x73, 0x22, 0x30, 0x30, 0x34, 0x0D};
  byte inputH2[9] = {0x38, 0x00, 0x01, 0x73, 0x22, 0x30, 0x31, 0x34, 0x0D};
  byte inputH3[9] = {0x38, 0x00, 0x01, 0x73, 0x22, 0x30, 0x32, 0x34, 0x0D};
  byte inputDP[9] = {0x38, 0x00, 0x01, 0x73, 0x22, 0x30, 0x30, 0x39, 0x0D};
  byte inputUC[9] = {0x38, 0x00, 0x01, 0x73, 0x22, 0x30, 0x31, 0x39, 0x0D};
  byte inputVGA[9] = {0x38, 0x00, 0x01, 0x73, 0x22, 0x30, 0x30, 0x36, 0x0D};
  byte inputEmb[9] = {0x38, 0x00, 0x01, 0x73, 0x22, 0x30, 0x30, 0x3A, 0x0D};
  

  
  if (buttonState1 == LOW) {
    Serial.write(powerOn, 9);
  }
  if (buttonState2 == LOW) {
    Serial.write(powerOff, 9);
  }
  if (buttonState3 == LOW) {
    Serial.write(inputH1, 9); 
  }    
 

  delay(500); 
}
