//  Music box PBL
//  Version 0.4
//  By Sabrina Fontaine
//  Course: Introduction to IoT
//  Dawson College
//  Date: April 29th 2026

//  Libraries
#include <LiquidCrystal.h>
#include <AlignedJoy.h>
#include <Tone.h>

// Pin definitions  Will need to add pins once circuit built
#define rs 8
#define en 7
#define d4 6
#define d5 5
#define d6 4
#define d7 3
#define buttonPin 2
#define buz1Pin
#define buz2Pin 
#define joyXPin A0
#define joyYPin A1

//  Creation of objects
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
AlignedJoy joystick(joyXPin, joyYPin);
Tone buz1();
Tone buz2(); 

//  Function declarations (Actually body of functions are placed after void loop)
int songSelect();

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  //buz1.begin(buz1Pin);
  //buz2.begin(buz2Pin);
  pinMode(buttonPin, INPUT_PULLUP);

  lcd.print("Select a song");
}

void loop() {
  int song = songSelect();
  
  // Determining if the user has made a valid selection
  if (song == 0){
    lcd.clear();
    lcd.print("No song selected");
  }
  else if (song > 0){
    lcd.clear();
    lcd.print("Song selected: ");
    lcd.println(song);
  }

  delay(1000);

}


int songSelect(){
  int song = 0;

  while (digitalRead(buttonPin) == HIGH){   // Will stay in selection mode until confirmed with button press
    int joyX = joystick.read(X);
    int joyY = joystick.read(Y);

    //  Serial printing to determine X and Y value directions and range
    /* Serial.print("X pos.: ");
    Serial.println(joyX);
    Serial.print("Y pos.: ");
    Serial.println(joyY); */
    
    //  Selection of song based on joystick values, while displaying name on LCD
    if (joyX > 900){
      song = 1;
      lcd.clear();
      lcd.print("Wet Hands");
      lcd.setCursor(0, 1);
      lcd.print("By C418");
    }
    else if (joyY < 10){
      song = 2;
      lcd.clear();
      lcd.print("Hummingberg");
      lcd.setCursor(0, 1);
      lcd.print("By Max LL");
    }
    else if (joyY > 800){
      song = 3;
      lcd.clear();
      lcd.print("Stardew Valley");
      lcd.setCursor(0, 1);
      lcd.print("Overture");
    }
    else if (joyX < 100){
      song = 4;
      lcd.clear();
      lcd.print("Song");  // To be changed once decided
      lcd.setCursor(0, 1);
      lcd.print("By someone");
    }

    delay(200);
  }

  return song;
}
