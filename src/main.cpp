#include <Arduino.h>
#include "Zizis.h"
#include "Robot.h"

Zizis myPenis(2);
Robot robot;
IntervalTimer timer;
IntervalTimer antiBlock;
IntervalTimer timerSuicide;

volatile bool isMatchStarted = 0;

void beginMatch();
void checkLoadedFired();

//Initialisation de la Serie
void setup() {
	Serial.begin(9600);
	Serial.println("Série OK");

  	robot.init();
}

//Boucle principale
void loop() {
    /*Attente d'un front montant sur le jumper*/
    attachInterrupt(digitalPinToInterrupt(PIN_JUMPER), beginMatch, RISING);

    while(!isMatchStarted) {
        delay(100);
    }

    /*Début du match, on active les interruptions*/
    attachInterrupt(digitalPinToInterrupt(PIN_LASER), checkLoadedFired, CHANGE);

}

void beginMatch(){
    isMatchStarted = 1;
}

void checkLoadedFired(){
    if (digitalRead(PIN_LASER)) { //front montant
        robot.hasBallLoaded = true;
    } else {    //front decendant
        robot.hasFiredBall = true;
        robot.hasBallLoaded = false;
    }
}