#include <Arduino.h>

//Lights Set Up
int red = 13;
int yellow = 11;
int green = 10;
int white = 12;
int second = 0;

//Count down set up
int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;

//Interrupt Vectors
int V_bu; // Button Signal Vector (Pin: 21)
int V_red; // Red Light Signal Vector (Pin: A4)

// Priority Function's Variables
int i_V_bu;
int j_V_red;

//Traffic State
int state;

void setup() {
  //Count down set up
  int i;
  for (i = 2; i <= 13; i++)
    pinMode(i, OUTPUT);
  Serial.begin(9600);


  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(white, OUTPUT);
  pinMode(9, INPUT);
}

void loop() {
  state = 0;
  fct();
  if (state == 0){
    digitalWrite(green, HIGH);
    delay(3000);
    digitalWrite(green, LOW);
    state += 1;  
  }
  
  else if (state == 1){
    fct();
    digitalWrite(yellow, HIGH);
    delay(3000);
    digitalWrite(yellow, LOW);
    state += 1;
  }
  
  else if(state == 2){
    fct();
    digitalWrite(red, HIGH);
    delay(3000);
    digitalWrite(red, LOW);
}
  else{}
}

void countDown(int length) {
  for (int k = length; k >= 0; k--) {
    display(k);
    delay(1500);
    clearDisplay();
  }
}

void display(int digit) {
  switch (digit) {
    case 0:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      break;
    case 1:
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      break;
    case 2:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 3:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 4:
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 5:
      digitalWrite(a, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 6:
      digitalWrite(a, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 7:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      break;
    case 8:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 9:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
  }
}

//Clears display
void clearDisplay(void){
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

// Master Function
void fct(void){
  polling();
  priority();
  Isr();
}

//Polling Function
void polling(void){
  V_red = analogRead(A4);
  V_bu = digitalRead(21);
  //Additional
}

//Priority Function
void priority(void){
  if (V_red > 0 ){
    j_V_red = 1;
    
  }else if(V_bu > 0){
    i_V_bu = 1;
    
  }else{} //Additional
    
}

// Interrupt Service Routine
void Isr(void){
  if (j_V_red > 0){ // Service Routine for Redlight Camera
      digitalWrite(white, HIGH);
      delay(400);
      digitalWrite(white, LOW);
      delay(50);
      digitalWrite(white, HIGH);
      delay(100);
      digitalWrite(white, LOW);
  }    
  else if (i_V_bu > 0){ // Service Routine for Button Input
      if (state == 0){
        digitalWrite(green, HIGH);
        delay(3000);
        digitalWrite(green, LOW);
        digitalWrite(yellow, HIGH);
        delay(3000);
        digitalWrite(yellow, LOW);
        digitalWrite(red, HIGH);
        delay(3000);
        digitalWrite(red, LOW);
        countDown(9);
        
      }else if (state == 1){
        digitalWrite(yellow, HIGH);
        delay(3000);
        digitalWrite(yellow, LOW);
        digitalWrite(red, HIGH);
        delay(3000);
        digitalWrite(red, LOW);
        countDown(9);
        state = 0;
        
      }else if (state == 2){
        digitalWrite(red, HIGH);
        delay(3000);
        digitalWrite(red, LOW);
        countDown(9);
        state = 0;
     }else{}
}
}
