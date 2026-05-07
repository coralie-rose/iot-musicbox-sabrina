//  Music box PBL
//  Version 0.5.5
//  By Sabrina Fontaine
//  Course: Introduction to IoT
//  Dawson College
//  Date: May 3rd 2026

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
// Note: 30kHz used for silences, since it is above human hearing range
int mcNotes1[] = {NOTE_GS4, NOTE_B4, NOTE_FS4, NOTE_E4, NOTE_FS4, 
NOTE_GS4, NOTE_B4, NOTE_CS5, NOTE_FS4, 30000, NOTE_CS5, NOTE_E5, NOTE_G5, 
NOTE_FS5, NOTE_D5, NOTE_A4, NOTE_B4, NOTE_G5, NOTE_FS5, NOTE_D5, NOTE_A4, 
NOTE_B4, NOTE_A4, NOTE_E4, 30000, NOTE_CS4, NOTE_E4, NOTE_A4, NOTE_CS5};
int mcNotes2[] = {NOTE_A2, NOTE_CS3, NOTE_A3, NOTE_B3, NOTE_CS4, NOTE_B3, 
NOTE_A3, NOTE_E3, NOTE_D3, NOTE_FS3, NOTE_CS4, NOTE_E4, NOTE_CS4, NOTE_A3, 
NOTE_A2, NOTE_CS3, NOTE_A3, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_A3, NOTE_E3, 
NOTE_D3, NOTE_FS3, NOTE_CS4, NOTE_E4, NOTE_CS4, NOTE_A3, NOTE_G2, NOTE_B2, 
NOTE_D3, NOTE_FS3, NOTE_A3, NOTE_FS3, NOTE_D3, NOTE_B2, NOTE_G2, NOTE_B2, 
NOTE_D3, NOTE_FS3, NOTE_A3, NOTE_G2, NOTE_B2, NOTE_D3, NOTE_FS3, NOTE_A3, 
NOTE_FS3, NOTE_D3, NOTE_B2, NOTE_G2, NOTE_B2, NOTE_D3, NOTE_FS3, NOTE_A3, 
NOTE_A2, NOTE_CS3, NOTE_A3, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_A3, NOTE_E3, 
NOTE_A2, NOTE_CS3, NOTE_A3, NOTE_B3};
int mcDuration1[] = {2433, 811, 2433, 405, 405, 2433, 405, 811, 
1622, 405, 405, 405, 1216, 405, 811, 405, 3649, 811, 811, 811, 
405, 2838, 811, 3244, 1622, 405, 405, 405, 811};
int mcDuration2[] = {405, 405, 405, 405, 405, 405, 405, 405, 405, 
405, 405, 405, 405, 851, 405, 405, 405, 405, 405, 405, 405, 405, 
405, 405, 405, 405, 405, 851, 405, 405, 405, 405, 405, 405, 405, 
283, 405, 405, 405, 405, 1135, 405, 405, 405, 405, 405, 405, 405, 
283, 405, 405, 405, 405, 1135, 405, 405, 405, 405, 405, 405, 405, 283, 
405, 405, 405, 405};

int spfrNotes1[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4};
int spfrNotes2[] = {NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3};
int spfrDuration1[] = {500, 500, 1000, 250, 250};
int spfrDuration2[] = {750, 750, 500, 500};

int stdvlNotes1[] = {NOTE_E5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_F5, 
NOTE_G5, NOTE_E5, NOTE_C5, NOTE_E5, NOTE_G5, NOTE_F5, NOTE_A5, NOTE_G5, 
NOTE_D5, 30000, NOTE_E5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_F5, NOTE_G5, 
NOTE_E5, NOTE_C5, 30000, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_A4, 
NOTE_G4, NOTE_C5};
int stdvlNotes2[] = {NOTE_C3, NOTE_E3, NOTE_G3, NOTE_G3, NOTE_C4, 
NOTE_C3, NOTE_E3, NOTE_A3, NOTE_A3, NOTE_C4, NOTE_C3, NOTE_E3, NOTE_G3, 
NOTE_G3, NOTE_C4, NOTE_C3, NOTE_C3, NOTE_G3, NOTE_G3, NOTE_C4, NOTE_C3, 
NOTE_E3, NOTE_G3, NOTE_G3, NOTE_C4, NOTE_C3, NOTE_E3, NOTE_A3, NOTE_A3, 
NOTE_C4, NOTE_G2, NOTE_B2, NOTE_D3, NOTE_D3, NOTE_G3, NOTE_G2, NOTE_B2, 
NOTE_D3, NOTE_G3, NOTE_B3, NOTE_G3, NOTE_C3, NOTE_E3, NOTE_G3, NOTE_G3, 
NOTE_C4, NOTE_C3, NOTE_E3, NOTE_A3, NOTE_A3, NOTE_C4, NOTE_C3, NOTE_E3, 
NOTE_G3, NOTE_G3, NOTE_C4, NOTE_C3, NOTE_E3, NOTE_G3, NOTE_G3, NOTE_C4, 
NOTE_C3, NOTE_E3, NOTE_G3, NOTE_G3, NOTE_C4, NOTE_C3, NOTE_E3, NOTE_A3, 
NOTE_A3, NOTE_C4};
int stdvlDuration1[] = {1318, 659, 659, 659, 659, 1318, 659, 1977, 
1318, 659, 659, 659, 659, 1977, 1977, 1318, 659, 659, 659, 659, 1318, 
659, 1318, 330, 330, 659, 659, 659, 1318, 659, 1977};
int stdvlDuration2[] = {330, 330, 495, 165, 659, 330, 330, 495, 165, 
659, 330, 330, 495, 165, 659, 330, 330, 495, 165, 659, 330, 330, 495, 
165, 659, 330, 330, 495, 165, 659, 330, 330, 495, 165, 659, 330, 330, 
330, 330, 330, 330, 330, 330, 495, 165, 659, 330, 330, 495, 165, 659, 
330, 330, 495, 165, 659, 330, 330, 495, 165, 659, 330, 330, 495, 165, 
659, 330, 330, 495, 165, 659};

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
      while (i < 29 || r < 66){    // Loops until the ends of both arrays are reached
        if (!buz1.isPlaying()){   // Next note is played once previous one stops
          buz1.play(mcNotes1[i], mcDuration1[i]);
          i++;
        }
        if (!buz2.isPlaying() && r < 66){   // Extra condition prevents playing invalid array positions
          buz2.play(mcNotes2[r], mcDuration2[r]);
          r++;
          Serial.println(r);
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
          buz2.play(spfrNotes2[r], spfrDuration2[r]);
          r++;
        }
      }
    break;
    case 3:
      i = 0;
      r = 0;
      while (i < 31 || r < 71){
        if (!buz1.isPlaying()){
          buz1.play(stdvlNotes1[i], stdvlDuration1[i]);
          i++;
        }
        if (!buz2.isPlaying()){
          buz2.play(stdvlNotes2[r], stdvlDuration2[r]);
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
          buz2.play(Notes2[r], Duration2[r]);
          r++;
        }
      }  
    break;
  }
}
