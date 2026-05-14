# iot-musicbox-sabrina

This is my final Arduino project for the Intro to IoT course at Dawson College.

It is a music box that allows selection between 4 different songs, which are played on two buzzers. A joystick and push button are used for selection, with a 16x2 LCD to display messages. Potentiometers allow for volume adjustment.

The music is coded into arrays using note frequencies and durations in milliseconds. If the songs need to be changed, the array values must be updated before uploading the program to the Arduino.  

Current playable songs are as follows:  
Wet Hands by C418  
Stardew Valley Overture by ConcernedApe  
His Theme by Toby Fox  

Libraries used: 
---
  Tone by Brett Hagman  
  Aligned Joystick by Marco Palladino  
  LiquidCrystal by Arduino and Adafruit

Circuit diagram:
---
<img width="975" height="631" alt="image" src="https://github.com/user-attachments/assets/c2e30577-445b-4892-8ea5-f55cf76dae11" />  

Made using TinkerCad  
Note: The joystick is not included in the diagram. If using the 4 pin Arduino joystick module, wiring is as follows:  
GND pin to ground, +5V pin to 5V, VRx pin to A0 and VRy pin to A1.
