const int button1Pin = 2; //Button Pins
const int button2Pin = 3;
const int button3Pin = 4;


int pwrState = 0; // Status des Stroms
int inpState = 0; // Status des Eingangs
int muteState = 0; // Status der Stummschaltung

const byte powerOn[9] = {0x38, 0x30, 0x31, 0x73, 0x21, 0x30, 0x30, 0x31, 0x0D};     //Powerfunktionen
const byte powerOff[9] = {0x38, 0x30, 0x31, 0x73, 0x21, 0x30, 0x30, 0x30, 0x0D};

const byte inputH1[9] = {0x38, 0x30, 0x31, 0x73, 0x22, 0x30, 0x30, 0x34, 0x0D};     //HMDI 1   //Inputs
const byte inputH2[9] = {0x38, 0x30, 0x31, 0x73, 0x22, 0x30, 0x31, 0x34, 0x0D};     //HDMI 2
const byte inputH3[9] = {0x38, 0x30, 0x31, 0x73, 0x22, 0x30, 0x32, 0x34, 0x0D};     //HDMI 3
const byte inputDP[9] = {0x38, 0x30, 0x31, 0x73, 0x22, 0x30, 0x30, 0x39, 0x0D};     //DisplayPort
const byte inputUC[9] = {0x38, 0x30, 0x31, 0x73, 0x22, 0x30, 0x31, 0x39, 0x0D};     //USB-C
const byte inputVGA[9] = {0x38, 0x30, 0x31, 0x73, 0x22, 0x30, 0x30, 0x36, 0x0D};    //VGA
const byte inputEMB[9] = {0x38, 0x30, 0x31, 0x73, 0x22, 0x30, 0x30, 0x41, 0x0D};    //Embedded/Main(Android)
  
const byte volume[9] = {0x38, 0x30, 0x31, 0x73, 0x35, 0x30, 0x39, 0x30, 0x0D};  //Volume 90%

const byte muteOn[9] = {0x38, 0x30, 0x31, 0x73, 0x36, 0x30, 0x30, 0x31, 0x0D}; //Stummschalten
const byte muteOff[9] = {0x38, 0x30, 0x31, 0x73, 0x36, 0x30, 0x30, 0x30, 0x0D}; //Stummschaltung aufheben

const byte menuLockOn[9] = {0x38, 0x30, 0x31, 0x73, 0x3E, 0x30, 0x30, 0x31, 0x0D};  //Menüsperre
const byte menuLockOff[9] = {0x38, 0x30, 0x31, 0x73, 0x3E, 0x30, 0x30, 0x30, 0x0D};
const byte tastLockOn[9] = {0x38, 0x30, 0x31, 0x73, 0x38, 0x30, 0x30, 0x31, 0x0D};  //Tastensperre
const byte tastLockOff[9] = {0x38, 0x30, 0x31, 0x73, 0x38, 0x30, 0x30, 0x30, 0x0D};

void setup() {
  Serial.begin(9600);
  pinMode(button1Pin, INPUT); // Buttonpins
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);

  
  Serial.write(inputH1, 9); //Auf HDMI1 stellen
  delay(25);
  Serial.write(volume, 9);  //Volume setzen
}

void loop() {
  int buttonState1 = digitalRead(button1Pin);
  int buttonState2 = digitalRead(button2Pin);
  int buttonState3 = digitalRead(button3Pin);

  if (buttonState1 == LOW) {
    switch(pwrState){
      case 0: //Fernseher ist aus
        Serial.write(powerOn, 9);
        pwrState = 1;
        break;
      case 1: //Fernseher ist an
        Serial.write(powerOff, 9);
        pwrState = 0;
        break;
      default:
        break;
    }
  }
  if (buttonState2 == LOW) {
     switch(inpState){
      case 0: //Fernseher ist auf HDMI1
        Serial.write(inputUC, 9);
        inpState = 1;
        break;
      case 1: //Fernseher ist auf USB-C
        Serial.write(inputH2, 9);
        inpState = 2;
        break;
      case 2: //Fernseher ist auf HDMI2
        Serial.write(inputH3, 9);
        inpState = 3;
        break;
      case 3: //Fernseher ist auf HDMI3
        Serial.write(inputH1, 9);
        inpState = 0;
        break;
      default:
        break;
    }
  }
  if (buttonState3 == LOW) {
    switch(muteState){
      case 0: //Fernseher nicht Stummgeschalten
        Serial.write(muteOn, 9);
        muteState = 1;
        break;
      case 1: //Fernseher ist Stummgeschalten
        Serial.write(muteOff, 9);
        muteState = 0;
        break;
      default:
        break;
    }
  }    

  delay(100); 
}
