/* Copyright (c) 2025 Felix Schulze, Jannik Rank. 
   All Rights reserved. 
 */
const int button1Pin = 2; //Button Pins
const int button2Pin = 3;
const int button3Pin = 4;
const int button4Pin = 5;
const int button5Pin = 6;
const int button6Pin = 7;

int Volume = 0;
int lastVolume = 10;

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

const byte akzeptieren[9] = {0x38, 0x30, 0x31, 0x73, 0x35, 0x31, 0x30, 0x30, 0x0D};  //Volume 100%  //nicht fertig

const byte down[9] = {0x38, 0x30, 0x31, 0x73, 0x41, 0x30, 0x30, 0x31, 0x0D};
const byte right[9] = {0x38, 0x30, 0x31, 0x73, 0x41, 0x30, 0x30, 0x33, 0x0D};
const byte enter[9] = {0x38, 0x30, 0x31, 0x73, 0x41, 0x30, 0x30, 0x34, 0x0D};

void setup() {
  Serial.begin(9600);
  pinMode(button1Pin, INPUT_PULLUP); // Buttonpins
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
  pinMode(button4Pin, INPUT_PULLUP);
  pinMode(button5Pin, INPUT_PULLUP);
  pinMode(button6Pin, INPUT_PULLUP);



  Serial.write(inputH1, 9); //Auf HDMI1 stellen
  delay(25);
  Serial.write(volume, 9);  //Volume setzen
}

void loop() {
  int buttonState1 = !digitalRead(button1Pin);
  int buttonState2 = !digitalRead(button2Pin);
  int buttonState3 = !digitalRead(button3Pin);
  int buttonState4 = !digitalRead(button4Pin);
  int buttonState5 = !digitalRead(button5Pin);
  int buttonState6 = !digitalRead(button5Pin);

  if (buttonState1 == HIGH) {
    switch (pwrState) {
      case 0: //Fernseher ist aus
        Serial.write(powerOn, 9);
        pwrState = 1;
        delay(100);
        break;
      case 1: //Fernseher ist an
        Serial.write(powerOff, 9);
        pwrState = 0;
        delay(100);
        break;
      default:
        break;
    }
  }
  if (buttonState2 == HIGH) {
    switch (inpState) {
      case 0: //Fernseher ist auf HDMI1
        Serial.write(inputUC, 9);
        inpState = 1;
        lastVolume = 100;
        delay(100);
        break;
      case 1: //Fernseher ist auf USB-C
        Serial.write(inputH2, 9);
        inpState = 2;
        lastVolume = 100;
        delay(100);
        break;
      case 2: //Fernseher ist auf HDMI2
        Serial.write(inputH3, 9);
        inpState = 3;
        lastVolume = 100;
        delay(100);
        break;
      case 3: //Fernseher ist auf HDMI3
        Serial.write(inputH1, 9);
        inpState = 0;
        lastVolume = 100;
        delay(100);
        break;
      default:
        break;
    }
  }
  if (buttonState3 == HIGH) {
    switch (muteState) {
      case 0: //Fernseher nicht Stummgeschalten
        Serial.write(muteOn, 9);
        muteState = 1;
        delay(100);
        break;
      case 1: //Fernseher ist Stummgeschalten
        Serial.write(muteOff, 9);
        muteState = 0;
        delay(100);
        break;
      default:
        break;
    }
  }



  if (muteState == 0) { //ändert nur die Lautstärke, wenn der Fernseher nicht gemutet ist

    if (buttonState4 == HIGH) {
      if (Volume < 100) {
        Volume = Volume + 10;
        delay(100);
      }
    }
    if (buttonState5 == HIGH) {
      if (Volume > 0) {
        Volume = Volume - 10;
        delay(100);
      }
    }
  }
    if (buttonState6 == HIGH) {
      Serial.write(down, 9);
      delay(10);
      Serial.write(right, 9);
      delay(10);
      Serial.write(enter, 9);
      }
    if (Volume != lastVolume) { //ändert nur die Lautstärke, wenn sich der Wert verändert, sodass nicht durchgängig die Lautstärke verändert wird.
      lastVolume = Volume;
      switch (Volume) {
        case 0: //Volume wird auf 0% gestellt
          Serial.write(volume0, 9);
          break;
        case 10: //Volume wird auf 10% gestellt
          Serial.write(volume10, 9);
          break;
        case 20: //Volume wird auf 20% gestellt
          Serial.write(volume20, 9);
          break;
        case 30: //Volume wird auf 30% gestellt
          Serial.write(volume30, 9);
          break;
        case 40: //Volume wird auf 40% gestellt
          Serial.write(volume40, 9);
          break;
        case 50: //Volume wird auf 50% gestellt
          Serial.write(volume50, 9);
          break;
        case 60: //Volume wird auf 60% gestellt
          Serial.write(volume60, 9);
          break;
        case 70: //Volume wird auf 70% gestellt
          Serial.write(volume70, 9);
          break;
        case 80: //Volume wird auf 80% gestellt
          Serial.write(volume80, 9);
          break;
        case 90: //Volume wird auf 90% gestellt
          Serial.write(volume90, 9);
          break;
        case 100: //Volume wird auf 100% gestellt
          Serial.write(volume100, 9);
          break;
        default:
          break;
      }
    }
  }
  delay(100);
}
