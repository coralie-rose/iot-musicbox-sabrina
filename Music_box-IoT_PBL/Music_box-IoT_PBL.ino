//  Music box PBL
//  Version 0.3
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
#define buttonPin
#define buz1Pin
#define buz2Pin
#define joyX
#define joyY

//  Creation of objects
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
AlignedJoy joystick(joyX, joyY);
Tone buz1();
Tone buz2(); 


void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  buz1.begin(buz1Pin);
  buz2.begin(buz2Pin);
  pinMode(buttonPin, INPUT);
}

void loop() {
  

}
