//  Music box PBL
//  Version 0.2
//  By Sabrina Fontaine
//  Course: Introduction to IoT
//  Dawson College
//  Date: April 29th 2026

//  Libraries
#include <LiquidCrystal.h>
#include <AlignedJoy.h>

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


void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(buz1Pin, OUTPUT);
  pinMode(buz2Pin, OUTPUT);
}

void loop() {
  

}
