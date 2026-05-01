//  Music box PBL
//  Version 0.3.2
//  By Sabrina Fontaine
//  Course: Introduction to IoT
//  Dawson College
//  Date: April 29th 2026

//  Libraries
#include <LiquidCrystal.h>
#include <AlignedJoy.h>
#include <Tone.h>

// Pin definitions  Will need to add pins once circuit built
#define rs 
#define en
#define d4
#define d5
#define d6
#define d7
#define buttonPin 4
#define buz1Pin
#define buz2Pin 
#define joyXPin A0
#define joyYPin A1

//  Creation of objects
// LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
AlignedJoy joystick(joyXPin, joyYPin);
Tone buz1();
Tone buz2(); 

//  Function declarations (Actually body of functions are placed after void loop)
int songSelect();

void setup() {
  //lcd.begin(16, 2);
  Serial.begin(9600);
  //buz1.begin(buz1Pin);
  //buz2.begin(buz2Pin);
  pinMode(buttonPin, INPUT_PULLUP);

  //lcd.print("Select a song");
}

void loop() {
  int song = songSelect();
  
  if (song == 0){
    //lcd.clear();
    //lcd.print("No song selected");
    Serial.println("No song selected");
  }
  else if (song > 0){
    Serial.print("Song selected: ");
    Serial.println(song);
  }

  delay(1000);

}


int songSelect(){
  int song = 0;

  while (digitalRead(buttonPin) == HIGH){
    int joyX = joystick.read(X);
    int joyY = joystick.read(Y);

    //  Serial printing to determine X and Y value directions and range
    /*  Serial.print("X pos.: ");
    Serial.println(joyX);
    Serial.print("Y pos.: ");
    Serial.println(joyY); */
    
    if (joyX > 900){
      song = 1;
    }
    else if (joyY < 10){
      song = 2;
    }
    else if (joyY > 800){
      song = 3;
    }
    else if (joyX < 100){
      song = 4;
    }

    delay(200);
  }

  return song;
}
