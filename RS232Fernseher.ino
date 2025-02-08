const int potPin = A0; // Das Potentiometer ist an Pin A0 angeschlossen
int potValue = 0; // Variable zur Speicherung des ausgelesenen Werts
int lastPercentage = 0; // Variable zur Speicherung des letzten ausgegebenen Prozentwerts

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

const byte volume0[9] = {0x38, 0x30, 0x31, 0x73, 0x35, 0x30, 0x30, 0x30, 0x0D};  //Volume 0%
const byte volume10[9] = {0x38, 0x30, 0x31, 0x73, 0x35, 0x30, 0x31, 0x30, 0x0D};  //Volume 10%
const byte volume20[9] = {0x38, 0x30, 0x31, 0x73, 0x35, 0x30, 0x32, 0x30, 0x0D};  //Volume 20%
const byte volume30[9] = {0x38, 0x30, 0x31, 0x73, 0x35, 0x30, 0x33, 0x30, 0x0D};  //Volume 30%
const byte volume40[9] = {0x38, 0x30, 0x31, 0x73, 0x35, 0x30, 0x34, 0x30, 0x0D};  //Volume 40%
const byte volume50[9] = {0x38, 0x30, 0x31, 0x73, 0x35, 0x30, 0x35, 0x30, 0x0D};  //Volume 50%
const byte volume60[9] = {0x38, 0x30, 0x31, 0x73, 0x35, 0x30, 0x36, 0x30, 0x0D};  //Volume 60%
const byte volume70[9] = {0x38, 0x30, 0x31, 0x73, 0x35, 0x30, 0x37, 0x30, 0x0D};  //Volume 70%
const byte volume80[9] = {0x38, 0x30, 0x31, 0x73, 0x35, 0x30, 0x38, 0x30, 0x0D};  //Volume 80%
const byte volume90[9] = {0x38, 0x30, 0x31, 0x73, 0x35, 0x30, 0x39, 0x30, 0x0D};  //Volume 90%
const byte volume100[9] = {0x38, 0x30, 0x31, 0x73, 0x35, 0x31, 0x30, 0x30, 0x0D};  //Volume 100%

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
  potValue = analogRead(potPin);
  int rawPercentage = map(potValue, 0, 1023, 0, 100); // Skaliere den Wert auf einen Prozentwert zwischen 0 und 100
  int percentage = rawPercentage - (rawPercentage % 10); // Runde den Wert auf den nächsten Zehner
  if (percentage != lastPercentage) {
  lastPercentage = percentage;
  }
 if(muteState == 0) {
  if (percentage != lastPercentage) {
     switch(percentage){
      case 0: //Volume wird auf 09 gestellt
        Serial.write(volume0, 9);
        break;
      case 10: //Fernseher ist auf USB-C
        Serial.write(volume10, 9);
        break;
      case 20: //Fernseher ist auf HDMI2
        Serial.write(volume20, 9);
        break;
      case 30: //Fernseher ist auf HDMI3
        Serial.write(volume30, 9);
        break;
      case 40: //Fernseher ist auf HDMI3
        Serial.write(volume40, 9);
        break;
      case 50: //Fernseher ist auf HDMI3
        Serial.write(volume50, 9);
        break;
      case 60: //Fernseher ist auf HDMI3
        Serial.write(volume60, 9);
        break;
      case 70: //Fernseher ist auf HDMI3
        Serial.write(volume70, 9);
        break;
      case 80: //Fernseher ist auf HDMI3
        Serial.write(volume80, 9);
        break;
      case 90: //Fernseher ist auf HDMI3
        Serial.write(volume90, 9);
        break;
      case 100: //Fernseher ist auf HDMI3
        Serial.write(volume100, 9);
        break;
      default:
        break;
    }    
  }
 }
  delay(100); 
}
