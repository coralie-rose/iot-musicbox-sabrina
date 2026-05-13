//  Music box PBL
//  Version 1.0
//  By Sabrina Fontaine
//  Course: Introduction to IoT
//  Dawson College
//  Date: May 13th 2026

// Libraries
#include <LiquidCrystal.h>
#include <AlignedJoy.h>
#include <Tone.h>

// Pin definitions
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
405, 405, 405, 405, 952, 405, 405, 405, 405, 405, 405, 405, 405, 
405, 405, 405, 405, 405, 952, 405, 405, 405, 405, 405, 405, 405, 
192, 355, 405, 405, 405, 1360, 405, 405, 405, 405, 405, 405, 405, 
192, 355, 405, 405, 405, 1360, 405, 405, 405, 405, 405, 405, 405, 193, 
355, 405, 405, 405};

int stdvlNotes1[] = {NOTE_E5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_F5, 
NOTE_G5, NOTE_E5, NOTE_C5, NOTE_E5, NOTE_G5, NOTE_F5, NOTE_A5, NOTE_G5, 
NOTE_D5, 30000, NOTE_E5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_F5, NOTE_G5, 
NOTE_E5, NOTE_C5, 30000, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_A4, 
NOTE_G4, NOTE_C5};
int stdvlNotes2[] = {NOTE_C3, NOTE_E3, NOTE_G3, NOTE_G3, NOTE_C4, 
NOTE_C3, NOTE_E3, NOTE_A3, NOTE_A3, NOTE_C4, NOTE_C3, NOTE_E3, NOTE_G3, 
NOTE_G3, NOTE_C4, NOTE_C3, NOTE_E3, NOTE_G3, NOTE_G3, NOTE_C4, NOTE_C3, 
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
165, 659, 330, 330, 495, 165, 397, 330, 330, 495, 165, 395, 330, 330, 
330, 330, 330, 330, 330, 330, 495, 165, 659, 330, 330, 495, 165, 659, 
330, 330, 495, 165, 659, 330, 330, 495, 165, 659, 330, 330, 495, 165, 
659, 330, 330, 495, 165, 659};

int undtlNotes1[] = {NOTE_FS5, NOTE_CS6, NOTE_B5, NOTE_FS5, NOTE_AS5, 
30000, NOTE_AS5, NOTE_B5, 30000, NOTE_FS5, NOTE_B5, NOTE_FS5, NOTE_AS5, 
30000, NOTE_AS5, NOTE_B5, NOTE_FS5, NOTE_CS6, NOTE_B5, NOTE_FS5, NOTE_AS5, 
30000, NOTE_AS5, NOTE_B5, 30000, NOTE_FS5, NOTE_B5, NOTE_DS6, NOTE_CS6, 
NOTE_B5, NOTE_CS6};
int undtlNotes2[] = {NOTE_E3, NOTE_B3, NOTE_FS4, NOTE_B3, NOTE_FS3, 
NOTE_B3, NOTE_AS4, NOTE_FS4, NOTE_GS3, NOTE_DS4, NOTE_AS4, NOTE_DS4, 
NOTE_B3, NOTE_FS4, NOTE_CS5, NOTE_B4};
int undtlDuration1[] = {353, 353, 353, 353, 450, 80, 530, 353, 353, 353, 
353, 353, 450, 80, 530, 353, 353, 353, 353, 353, 450, 80, 530, 353, 353, 353, 
353, 353, 530, 530, 353};
int undtlDuration2[] = {706, 706, 706, 706, 706, 706, 706, 706, 706, 
706, 706, 706, 706, 706, 706, 706};

// Function declarations (Actual body of functions are placed after void loop)
int songSelect();
void playSong(int song);

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  buz1.begin(buz1Pin);
  buz2.begin(buz2Pin);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  lcd.clear();
  lcd.print("Select a song");
  int song = songSelect();
  
  // Determining if the user has made a valid selection
  if (song == 0){
    lcd.clear();
    lcd.print("No song selected");
  }
  else if (song == 4){
    lcd.clear();
    lcd.print("Not available");
  }
  else if (song > 0){
    playSong(song);
  }

  delay(2500);
}

int songSelect(){
  int song = 0;

  while (digitalRead(buttonPin) == HIGH){   // Will stay in selection mode until confirmed with button press
    int joyX = joystick.read(X);
    int joyY = joystick.read(Y);

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
      lcd.print("Stardew Valley");
      lcd.setCursor(0, 1);
      
      lcd.print("Overture");
    }
    else if (joyY > 800){
      song = 3;
      lcd.clear();
      lcd.print("His Theme");
      lcd.setCursor(0, 1);
      lcd.print("By Toby Fox");
    }
    else if (joyX < 100){
      song = 4;
      lcd.clear();
      lcd.print("Hummingberg");
      lcd.setCursor(0, 1);
      lcd.print("By Max LL");
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
      while (i < 29 || r < 66){   // Loops until the ends of both arrays are reached
        if (!buz1.isPlaying()){   // Next note is played once previous one stops
          buz1.play(mcNotes1[i], mcDuration1[i]);
          i++;
        }
        if (!buz2.isPlaying() && r < 66){   // Extra condition prevents playing invalid array positions
          buz2.play(mcNotes2[r], mcDuration2[r]);
          r++;
        }
      }
    break;
    case 2:
      i = 0;
      r = 0;
      while (i < 31 || r < 71){
        if (!buz1.isPlaying()){
          buz1.play(stdvlNotes1[i], stdvlDuration1[i]);
          i++;
        }
        if (!buz2.isPlaying() && r < 71){
          buz2.play(stdvlNotes2[r], stdvlDuration2[r]);
          r++;
        }
      }
    break;
    case 3:
      i = 0; 
      r = 0;
      int loop = 0;
      while (i < 31 ||r < 16 || !loop){
        if (i == 31 && r == 16){   // Checks if reached end of array and allows looping once
          loop = 1;
          r = 0;
          i = 0;
        }
        if (!buz1.isPlaying()){
          buz1.play(undtlNotes1[i], undtlDuration1[i]);
          i++;
        }
        if (!buz2.isPlaying()){
          buz2.play(undtlNotes2[r], undtlDuration2[r]);
          r++;
        }
      } 
    break;
  }
}
