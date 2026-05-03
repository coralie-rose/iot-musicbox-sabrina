//  Music box PBL
//  Version 0.5.3
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
#define buz1Pin 9
#define buz2Pin 10
#define joyXPin A0
#define joyYPin A1

//  Creation of objects
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
AlignedJoy joystick(joyXPin, joyYPin);
Tone buz1;
Tone buz2; 

// Arrays containing the notes and their durations
int mcNotes1[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4};
int mcNotes2[] = {NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3};
int mcDuration1[] = {500, 500, 1000, 250, 250};
int mcDuration2[] = {750, 750, 500, 500};

int spfrNotes1[] = {};
int spfrNotes2[] = {};
int spfrDuration1[] = {};
int spfrDuration2[] = {};

int stdvlNotes1[] = {};
int stdvlNotes2[] = {};
int stdvlDuration1[] = {};
int stdvlDuration2[] = {};

int Notes1[] = {};
int Notes2[] = {};
int Duration1[] = {};
int Duration2[] = {};

//  Function declarations (Actually body of functions are placed after void loop)
int songSelect();
void playSong(int song);

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  buz1.begin(buz1Pin);
  buz2.begin(buz2Pin);
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
    lcd.print("Song selected: "); // To eventually remove
    lcd.println(song);
    playSong(song);
  }

  delay(1000);
}

int songSelect(){
  int song = 0;

  while (digitalRead(buttonPin) == HIGH){   // Will stay in selection mode until confirmed with button press
    int joyX = joystick.read(X);
    int joyY = joystick.read(Y);

    // Serial printing to determine X and Y value directions and range
    /* Serial.print("X pos.: ");
    Serial.println(joyX);
    Serial.print("Y pos.: ");
    Serial.println(joyY); */
    
    // Selection of song based on joystick values, while displaying name on LCD
    // Uses basic x and y axes, no diagonals
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

void playSong(int song){
  int i;
  int r;
  
  // Selection of the loop with the arrays for the chosen song
  // Note: Only need to cycle through one array per buzzer since
  // there are as many notes as there are corresponding durations
  switch (song){
    case 1:
      i = 0;
      r = 0;
      while (i < 5 || r < 4){    // Loops until the ends of both arrays are reached
        if (!buz1.isPlaying()){   // Next note is played once previous one stops
          buz1.play(mcNotes1[i], mcDuration1[i]);
          i++;
        }
        if (!buz2.isPlaying()){
          buz2.play(mcNotes2[i], mcDuration2[i]);
          r++;
        }
      }
    break;
    case 2:
      i = 0;
      r = 0;
      while (i < 5 || r < 5){  // Array lengths will need to be adjusted for each case
        if (!buz1.isPlaying()){
          buz1.play(spfrNotes1[i], spfrDuration1[i]);
          i++;
        }
        if (!buz2.isPlaying()){
          buz2.play(spfrNotes2[i], spfrDuration2[i]);
          r++;
        }
      }
    break;
    case 3:
      i = 0;
      r = 0;
      while (i < 5 || r < 5){
        if (!buz1.isPlaying()){
          buz1.play(stdvlNotes1[i], stdvlDuration1[i]);
          i++;
        }
        if (!buz2.isPlaying()){
          buz2.play(stdvlNotes2[i], stdvlDuration2[i]);
          r++;
        }
      }
    break;
    case 4:
      i = 0;
      r = 0;
      while (i < 5 || r < 5){
        if (!buz1.isPlaying()){
          buz1.play(Notes1[i], Duration1[i]);
          i++;
        }
        if (!buz2.isPlaying()){
          buz2.play(Notes2[i], Duration2[i]);
          r++;
        }
      }  
    break;
  }
}
