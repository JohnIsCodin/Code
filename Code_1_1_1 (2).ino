#include <Arduino.h>
#include "SevSeg.h"
SevSeg sevseg;

//Lights Set Up
int red1 = 11;
int yellow1 = 12;
int green1 = 13;

int red2 = 10;
int yellow2 = 9;
int green2 = 8;

int red3 = 5;
int yellow3 = 6;
int green3 = 7;

int red4 = 4;
int yellow4 = 3;
int green4 = 2;
int white = 24;

//Count down set up
int a = 34;
int b = 37;
int c = 38;
int d = 41;
int e = 42;
int f = 45;
int g = 46;
int dp = 12;

//Interrupt Vectors
int V_bu1; // Button Signal Vector (Pin: 22)
int V_bu2;
int V_Induct_1A; //A is for straight
int V_Induct_2A;
int V_Induct_2B; //B is for left hand turn
int V_Induct_3A;
int V_Induct_3B;
int V_Induct_4A;
int V_Induct_4B;
int V_red; // Red Light Signal Vector (Pin: A4)

// Priority Function's Variables
int i_V_bu1 = 0;
int i_V_bu2 = 0;
int j_V_red_1 = 0;
int j_V_Induct_1 = 0;
int j_V_Induct_2 = 0;

//Traffic State
int state = 0;

//Delay
int z = 1000; //2 sec delay

void setup() {
  //Count down set up
  byte numDigits1 = 1;
  byte digitPins1[] = {};
  byte segmentPins1[] = {34, 37, 38, 41, 42, 45, 46, 12};
  // A,B,C,D,E,F,G,DP
  bool resistorsOnSegments1 = true;
  byte hardwareConfig1 = COMMON_CATHODE;
  sevseg.begin(hardwareConfig1, numDigits1, digitPins1, segmentPins1, resistorsOnSegments1);
  sevseg.setBrightness(90);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(red1, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(green1,  OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(green2,  OUTPUT);
  pinMode(red3, OUTPUT);
  pinMode(yellow3, OUTPUT);
  pinMode(green3,  OUTPUT);
  pinMode(red4, OUTPUT);
  pinMode(yellow4, OUTPUT);
  pinMode(green4,  OUTPUT);
  pinMode(white,  OUTPUT);
  pinMode(22,  INPUT);

}

void loop() {

  fct();
  if (state == 0) {
    adv_green_1_4();
    digitalWrite(green1, HIGH);
    digitalWrite(green4, HIGH);
    digitalWrite(red2, HIGH);
    digitalWrite(red3, HIGH);
    delay(z);
    fct();
    delay(z);
    display1();
    state += 1;
  }
  else if (state == 1) {
    fct();
    digitalWrite(green1, LOW);
    digitalWrite(green4, LOW);
    digitalWrite(yellow1, HIGH);
    digitalWrite(yellow4, HIGH);
    delay(z);
    fct();
    delay(z);
    digitalWrite(red2, LOW);
    digitalWrite(red3, LOW);
    digitalWrite(yellow1, LOW);
    digitalWrite(yellow4, LOW);

    state += 1;
  }
  else if (state == 2) {
    fct();
    adv_green_2_3();
    digitalWrite(green2, HIGH);
    digitalWrite(green3, HIGH);
    digitalWrite(red1, HIGH);
    digitalWrite(red4, HIGH);
    display2();
    delay(z);
    fct();
    delay(z);
    digitalWrite(green2, LOW);
    digitalWrite(green3, LOW);
    state += 1;
  }
  else if (state == 3) {
    fct();
    digitalWrite(yellow2, HIGH);
    digitalWrite(yellow3, HIGH);
    delay(z);
    fct();
    delay(z);
    digitalWrite(yellow2, LOW);
    digitalWrite(yellow3, LOW);
    digitalWrite(red1, LOW);
    digitalWrite(red4, LOW);
    state = 0;
  }
  else {}
}

//Display
void display1(void) {
  if (i_V_bu1 == 1) {
    for (int i = 9; i >= 0; i--) {
      sevseg.setNumber(i);
      delay(1500);
      sevseg.refreshDisplay();
    }
  }
  i_V_bu1 = 0;
}

void display2(void) {
  if (i_V_bu2 == 1) {
    for (int i = 9; i >= 0; i--) {
      sevseg.setNumber(i);
      delay(1500);
      sevseg.refreshDisplay();
    }
  }
  i_V_bu2 = 0;
}

void adv_green_1_4(void){
  if (j_V_Induct_1 == 1){
  digitalWrite(green1,  LOW);
  digitalWrite(green4, LOW);
  delay(500);

  digitalWrite(green1, HIGH);
  digitalWrite(green4, HIGH);
  delay(1000);

  digitalWrite(green1,  LOW);
  digitalWrite(green4, LOW);
  delay(500);

  digitalWrite(green1, HIGH);
  digitalWrite(green4, HIGH);
  delay(1000);

  digitalWrite(green1,  LOW);
  digitalWrite(green4, LOW);
  delay(500);

  digitalWrite(green1, HIGH);
  digitalWrite(green4, HIGH);
  delay(1000);

  digitalWrite(green1,  LOW);
  digitalWrite(green4, LOW);
  delay(500);

  digitalWrite(green1, HIGH);
  digitalWrite(green4, HIGH);
  delay(1000);
  }
  j_V_Induct_1 = 0;
}

void adv_green_2_3(void){
  if (j_V_Induct_2 == 1){
  digitalWrite(green2,  LOW);
  digitalWrite(green3, LOW);
  delay(500);

  digitalWrite(green2, HIGH);
  digitalWrite(green3, HIGH);
  delay(1000);

  digitalWrite(green2,  LOW);
  digitalWrite(green3, LOW);
  delay(500);

  digitalWrite(green2, HIGH);
  digitalWrite(green3, HIGH);
  delay(1000);

  digitalWrite(green2,  LOW);
  digitalWrite(green3, LOW);
  delay(500);

  digitalWrite(green2, HIGH);
  digitalWrite(green3, HIGH);
  delay(1000);

  digitalWrite(green2,  LOW);
  digitalWrite(green3, LOW);
  delay(500);

  digitalWrite(green2, HIGH);
  digitalWrite(green3, HIGH);
  delay(1000);
  }
  j_V_Induct_2 = 0;
}

// Master Function
void fct(void) {
  polling();
  priority();
  Isr();
}

//Polling Function
void polling(void) {
  V_red = analogRead();
  Serial.println(V_red);
  V_bu1 = digitalRead();
  V_bu2 = digitalRead();
  Serial.println(V_bu1);
  V_Induct_1A = analogRead();
  V_Induct_2A = analogRead();
  V_Induct_2B = analogRead();
  V_Induct_3A = analogRead();
  V_Induct_3B = analogRead();
  V_Induct_4A = analogRead();
  V_Induct_4B = analogRead();
  //Additional
}

//Priority Function
void priority(void) {
  if (V_red < 400 ) {
    j_V_red = 1;

  } else if (V_bu1 == 1) {
    i_V_bu1 = 1;

  }else if (V_bu2 == 1) {
    i_V_bu2 = 1;

  }else if (V_Induct_1A == 1 || V_Induct_4A == 1 ) {
    j_V_Induct_1 = 1;
    
  }else if (V_Induct_1B == 1 || V_Induct_4B == 1 ) {
    j_V_Induct_1 = 1;

  }else if (V_Induct_2A == 1 || V_Induct_3A == 1 ) {
    j_V_Induct_1 = 1;

  }else if (V_Induct_2B == 1 || V_Induct_3B == 1 ) {
    j_V_Induct_1 = 1;
    
  }else{
  } //Additional

}

// Interrupt Service Routine
void Isr(void) {
  if (j_V_red == 1) { // Service Routine for Redlight Camera
    digitalWrite(white, HIGH);
    delay(400);
    digitalWrite(white, LOW);
    delay(50);
    digitalWrite(white, HIGH);
    delay(100);
    digitalWrite(white, LOW);
    j_V_red = 0;
  }
  else if (i_V_bu == 1) { // Service Routine for Button Input

    } else {}
}
