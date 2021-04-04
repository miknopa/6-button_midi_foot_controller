/*
   6-button MIDI-footcontroller for Line6 Helix Rack guitar/bass fx-unit
   by: Mikko Nopanen
   last update: 2020-08-16
*/


#include <MIDI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);

MIDI_CREATE_DEFAULT_INSTANCE();

#define expPedal1 A0
#define expPedal2 A1

unsigned long time;

int last1Val = 0;
int last2Val = 0;

int mode;
int midichannel = 1;

int footButton1 = 37;
int footButton2 = 36;
int footButton3 = 35;
int footButton4 = 34;
int footButton5 = 38;
int footButton6 = 39;

boolean footButton1pressed = false;
boolean footButton2pressed = false;
boolean footButton3pressed = false;
boolean footButton4pressed = false;
boolean footButton5pressed = false;
boolean footButton6pressed = false;

int fingerButton1 = 26;
int fingerButton2 = 28;
int fingerButton3 = 30;

//int tapButton = ??;

int led1 = 43;
int led2 = 41;
int led3 = 45;
int led4 = 42;
int led5 = 44;
int led6 = 40;

int led5State = LOW;
int led6State = LOW;

unsigned long previousMillis = 0;

int snapshot;

String row1 = "";
String row2 = "";
String row3 = "";
String row4 = "";

void setup() {

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);

  pinMode(footButton1, INPUT_PULLUP);
  pinMode(footButton2, INPUT_PULLUP);
  pinMode(footButton3, INPUT_PULLUP);
  pinMode(footButton4, INPUT_PULLUP);
  pinMode(footButton5, INPUT_PULLUP);
  pinMode(footButton6, INPUT_PULLUP);

  pinMode(fingerButton1, INPUT_PULLUP);
  pinMode(fingerButton2, INPUT_PULLUP);
  pinMode(fingerButton3, INPUT_PULLUP);

  pinMode(expPedal1, INPUT);
  pinMode(expPedal2, INPUT);

  digitalWrite(footButton1, HIGH);
  digitalWrite(footButton2, HIGH);
  digitalWrite(footButton3, HIGH);
  digitalWrite(footButton4, HIGH);
  digitalWrite(footButton5, HIGH);
  digitalWrite(footButton6, HIGH);
  // digitalWrite(tapButton, HIGH);

  MIDI.begin(MIDI_CHANNEL_OFF);
  //Serial.begin(38400); uncomment for debugging use

  lcd.init();
  lcd.backlight();
  row1 = "MIDI FOOT CONTROLLER";
  row2 = "By: Mikko Nopanen";
  row3 = "";
  row4 = "";
  showTexts();

  delay(1000);

  // startup led test
  digitalWrite(led1, HIGH);
  delay(200);
  digitalWrite(led1, LOW);
  delay(10);
  digitalWrite(led2, HIGH);
  delay(200);
  digitalWrite(led2, LOW);
  delay(10);
  digitalWrite(led3, HIGH);
  delay(200);
  digitalWrite(led3, LOW);
  delay(10);
  digitalWrite(led4, HIGH);
  delay(200);
  digitalWrite(led4, LOW);
  delay(10);
  digitalWrite(led5, HIGH);
  delay(200);
  digitalWrite(led5, LOW);
  delay(10);
  digitalWrite(led6, HIGH);
  delay(200);
  digitalWrite(led6, LOW);

  delay(1000);

  //set startup mode
  mode = 0;
  lcd.clear();
  row1 = "MODE: 6 SNAPSHOTS";
  row2 = "";
  row3 = "";
  row4 = "SNAPSHOT: 1";

  MIDI.sendProgramChange(000, midichannel);

  digitalWrite(led1, HIGH);

  analogReference(DEFAULT);

}

void loop() {

  unsigned long currentMillis = millis();

  if (digitalRead(fingerButton1) == LOW && mode > 0) {
    while (true) {
      // long press action

      // short press action
      if (digitalRead(fingerButton1) == HIGH) {
        mode--;
        break;
      }
    }
  }

  if (digitalRead(fingerButton3) == LOW && mode < 2) {
    while (true) {
      // long press action

      // short press action
      if (digitalRead(fingerButton3) == HIGH) {
        mode++;
        break;
      }
    }
  }


  time = 0;

  switch (mode)
  {
    case 0: // MODE1: Line6 Helix snapshot mode


      row1 = "MODE1: SNAPSHOTS    ";

      // FOOTBUTTON 1

      if (digitalRead(footButton1) == LOW && !footButton1pressed) {
        MIDI.sendProgramChange(000, midichannel);
        turnLedsOff();
        digitalWrite(led1, HIGH);
      }

      if (digitalRead(footButton1) == HIGH) {
        footButton1pressed = false;
      }

      // FOOTBUTTON 2

      if (digitalRead(footButton2) == LOW && !footButton2pressed) {
        MIDI.sendProgramChange(001, midichannel);
        turnLedsOff();
        digitalWrite(led2, HIGH);
      }

      if (digitalRead(footButton2) == HIGH) {
        footButton2pressed = false;
      }

      // FOOTBUTTON 3

      if (digitalRead(footButton3) == LOW && !footButton3pressed) {
        MIDI.sendProgramChange(002, midichannel);
        turnLedsOff();
        digitalWrite(led3, HIGH);
      }

      if (digitalRead(footButton3) == HIGH) {
        footButton3pressed = false;
      }

      // FOOTBUTTON 4

      if (digitalRead(footButton4) == LOW && !footButton4pressed) {
        MIDI.sendProgramChange(003, midichannel);
        turnLedsOff();
        digitalWrite(led4, HIGH);
      }

      if (digitalRead(footButton4) == HIGH) {
        footButton4pressed = false;
      }

      // FOOTBUTTON 5

      if (digitalRead(footButton5) == LOW && !footButton5pressed) {
        MIDI.sendProgramChange(004, midichannel);
        turnLedsOff();
        digitalWrite(led5, HIGH);
      }

      if (digitalRead(footButton5) == HIGH) {
        footButton5pressed = false;
      }



      // FOOTBUTTON 6

      if (digitalRead(footButton6) == LOW && !footButton6pressed) {
        MIDI.sendProgramChange(005, midichannel);
        turnLedsOff();
        digitalWrite(led6, HIGH);
      }

      if (digitalRead(footButton6) == HIGH) {
        footButton4pressed = false;
      }



      break;

    case 1: // MODE2: Line6 Helix Upper row = presets lower row = snapshots

      row1 = "MODE2: PRES + SNAPS";

      // FOOTBUTTON 1

      if (digitalRead(footButton1) == LOW && !footButton1pressed) {
        MIDI.sendControlChange(69, 0, midichannel);
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);

        row4 = "SNAPSHOT: 1";
        footButton1pressed = true;
      }

      if (digitalRead(footButton1) == HIGH) {
        footButton1pressed = false;
      }

      // FOOTBUTTON 2

      if (digitalRead(footButton2) == LOW && !footButton2pressed) {
        MIDI.sendControlChange(69, 1, midichannel);
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, LOW);
        row4 = "SNAPSHOT: 2";
        footButton2pressed = true;
      }

      if (digitalRead(footButton2) == HIGH) {
        footButton2pressed = false;
      }

      // FOOTBUTTON 3

      if (digitalRead(footButton3) == LOW && !footButton3pressed) {
        MIDI.sendControlChange(69, 2, midichannel);
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, HIGH);
        row4 = "SNAPSHOT: 3";
        footButton3pressed = true;
      }

      if (digitalRead(footButton3) == HIGH) {
        footButton3pressed = false;
      }

      // FOOTBUTTON 4

      if (digitalRead(footButton4) == LOW && !footButton4pressed) {
        MIDI.sendControlChange(49, 127, midichannel);
        digitalWrite(led4, HIGH);
        digitalWrite(led5, LOW);
        digitalWrite(led6, LOW);
        row4 = "SNAPSHOT: 3";
        footButton4pressed = true;
      }

      if (digitalRead(footButton4) == HIGH) {
        footButton4pressed = false;
      }

      break;


    case 2: //MODE3: Line6 helix Looper mode

      //     "--------------------";
      row1 = "UNDO   PLAY 1  BLOCK";
      row2 = "                    ";
      row3 = "                    ";
      row4 = "REC     PLAY    STOP";


      // FOOTBUTTON 1 rec + odub

      if (digitalRead(footButton1) == LOW && !footButton1pressed) {
        MIDI.sendControlChange(60, 64, midichannel); //record
        digitalWrite(led1, HIGH);

        footButton1pressed = true;
      }

      if (digitalRead(footButton1) == HIGH) {
        footButton1pressed = false;
      }

      // FOOTBUTTON 2 play + stop

      if (digitalRead(footButton2) == LOW && !footButton2pressed) {
        MIDI.sendControlChange(61, 64, midichannel); //record
        digitalWrite(led2, HIGH);

        footButton2pressed = true;
      }

      if (digitalRead(footButton2) == HIGH) {
        footButton2pressed = false;
      }

      // FOOTBUTTON 3 play once

      if (digitalRead(footButton3) == LOW && !footButton3pressed) {
        MIDI.sendControlChange(62, 64, midichannel);
        digitalWrite(led3, HIGH);

        footButton3pressed = true;
      }

      if (digitalRead(footButton3) == HIGH) {
        footButton3pressed = false;
      }

      // FOOTBUTTON 4 undo

      if (digitalRead(footButton4) == LOW && !footButton4pressed) {
        MIDI.sendControlChange(63, 64, midichannel);
        digitalWrite(led4, HIGH);

        footButton4pressed = true;
      }

      if (digitalRead(footButton4) == HIGH) {
        footButton4pressed = false;
        digitalWrite(led4, LOW);
      }


      // FOOTBUTTON 6

      if (digitalRead(footButton6) == LOW && !footButton6pressed) {
        MIDI.sendControlChange(67, 64, midichannel); //record
        digitalWrite(led6, HIGH);

        footButton6pressed = true;
      }

      if (digitalRead(footButton6) == HIGH) {
        footButton6pressed = false;
      }

      break;
  }


  // EXP1

  int current1Val = analogRead(expPedal1);

  current1Val = map(current1Val, 0, 1023, 0, 127);

  if (abs(current1Val - last1Val) > 1)
  {
    MIDI.sendControlChange(1, current1Val, midichannel);
    Serial.println(current1Val);
    last1Val = current1Val;
  }


  // EXP2

  int current2Val = analogRead(expPedal2);

  current2Val = map(current2Val, 0, 1023, 0, 127);

  if (abs(current2Val - last2Val) > 1)
  {
    MIDI.sendControlChange(2, current2Val, midichannel);
    last2Val = current2Val;
  }

  // UPDATE DISPLAY TEXTS
  showTexts ();

}

void showTexts() {
  lcd.setCursor(0, 0);
  lcd.print(row1);
  lcd.setCursor(0, 1);
  lcd.print(row2);
  lcd.setCursor(0, 2);
  lcd.print(row3);
  lcd.setCursor(0, 3);
  lcd.print(row4);
}

void turnLedsOff() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
}
