#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include <Wire.h> // Include the Arduino SPI library

class Afficheur {
  public:
    Afficheur();
    void init();
    void display(String toSend);
    void clearDisplayI2C();
    void setBrightnessI2C(byte value);
    void setDecimalsI2C(byte decimals);
    void addScore(int value);
  private:
    const byte s7sAddress = 0x71;
    int score = 0;
};

#endif /* AFFICHEUR_H */
