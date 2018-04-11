#include "Afficheur.h"

Afficheur::Afficheur() {
}

// This custom function works somewhat like a serial.print.
//  You can send it an array of chars (string) and it'll print
//  the first 4 characters in the array.
void Afficheur::display(String toSend) {
  Wire.beginTransmission(DISPLAY_ADDRESS);
  for (int i=0; i<4; i++) {
    Wire.write(toSend[i]);
  }
  Wire.endTransmission();
}


void Afficheur::displayInt(int number)
{
  Wire.beginTransmission(DISPLAY_ADDRESS); // transmit to device #1
  Wire.write(number / 1000); //Send the left most digit
  number %= 1000;
  delay(10);
  Wire.write(number / 100);
  number %= 100;
  delay(10);
  Wire.write(number / 10);
  number %= 10;
  delay(10);
  Wire.write(number); //Send the right most digit
  Wire.endTransmission(); //Stop I2C transmission
}

// Send the clear display command (0x76)
//  This will clear the display and reset the cursor
void Afficheur::clearDisplayI2C() {
  Wire.beginTransmission(DISPLAY_ADDRESS);
  Wire.write(0x76);  // Clear display command
  Wire.endTransmission();
}

// Set the displays brightness. Should receive byte with the value
//  to set the brightness to
//  dimmest------------->brightest
//     0--------127--------255
void Afficheur::setBrightnessI2C(byte value) {
  Wire.beginTransmission(DISPLAY_ADDRESS);
  Wire.write(0x7A);  // Set brightness command byte
  Wire.write(value);  // brightness data byte
  Wire.endTransmission();
}

//  Turn on any, none, or all of the decimals.
//  The six lowest bits in the decimals parameter sets a decimal
//  (or colon, or apostrophe) on or off. A 1 indicates on, 0 off.
//  [MSB] (X)(X)(Apos)(Colon)(Digit 4)(Digit 3)(Digit2)(Digit1)
void Afficheur::setDecimalsI2C(byte decimals) {
  Wire.beginTransmission(DISPLAY_ADDRESS);
  Wire.write(0x77);
  Wire.write(decimals);
  Wire.endTransmission();
}

void Afficheur::init() {
  Wire.begin();
  // Clear the display, and then turn on all segments and decimals
  clearDisplayI2C();  // Clears display, resets cursor
  setBrightnessI2C(255);  // High brightness
  scrollText("JE SUIS UNE LICORNE");
  delay(1500);

  // Clear the display before jumping into loop
  clearDisplayI2C();
}

void Afficheur::scrollText(String text) {
  for (int i=0; i < text.length()-3; i++) {
    display(text.substring(i,i+4));
    delay(300);
  }
}

void Afficheur::addScore(int value) {
  score += value;
  constrainScore();
  displayInt(score);
}

void Afficheur::constrainScore(){
  if(score > 50 ){
    score = 50;
  }
}
