#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include <Wire.h> // Include the Arduino I2C library
#define DISPLAY_ADDRESS 0x71

class Afficheur {
  public:
    Afficheur();
    void init();
    void display(String toSend);
    void clearDisplayI2C();
    void setBrightnessI2C(byte value);
    void setDecimalsI2C(byte decimals);
    void addScore(int value);
    void scrollText(String text);
    void displayInt(int number);
    void constrainScore();
  private:
    int score = 0;
};

#endif /* AFFICHEUR_H */
