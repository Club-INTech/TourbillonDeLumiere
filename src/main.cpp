#include <Arduino.h>
#include "Zizis.h"
#include "Robot.h"

Zizis myPenis(2);
Robot robot;
IntervalTimer timer;

volatile bool isMatchStarted = 0;

void beginMatch();
void stopMatch();

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

    /*On demarre aussi tous les timers*/
    timer.priority(0); //Priorite maximum, il doit absolument s'arreter
    timer.begin(stopMatch, 98000000); //Timer qui sert pour arreter le match au bout de 100s

    while(!robot.isUnderLoader() && !robot.isMatchFinished) { //on se positionne sous le tube
        if (robot.willNotCrashInOtherRobot()) {
            robot.moveForward(PERCENT_MOTOR); //% de sa vitesse sinon il fonce sous les balles comme un taré
        } else {
            robot.stop();
            delay(100);
        }
    }

    robot.stop();

    //On attend que les balles tombent dans le reservoir
    delay(3000);
    robot.addScore(10);

    //On se positionne à côté de l'abeille
    while(!robot.isAtBee() && !robot.isMatchFinished) {
        if (robot.willNotCrashInOtherRobot()) {
            robot.moveForward(PERCENT_MOTOR_FORWARD); // On évite d'aller trop vite pour ne pas féconder le mur
        } else {
            robot.stop();
            delay(100);
        }
    }

    robot.stop();

    //On lance l'abeille
    robot.fireBee();
    robot.addScore(50);

    timer.end();
    timer.priority(240);

    stopMatch();

    while(robot.isMatchFinished) { //on fait des jolis affichages
        robot.print("    ");
        myPenis.spacePrint(); //impression du zizi avec des espaces devant
        myPenis.randomize(); //changement aléatoire de type de zizi
        delay(500);
        robot.printScore();
        myPenis.spacePrint(); //impression du zizi avec des espaces devant
        myPenis.randomize(); //changement aléatoire de type de zizi
        delay(500);
    }
}

void beginMatch(){
    isMatchStarted = 1;
}


void stopMatch() {
    analogWrite(PIN_MOTEUR_PWM, 0);
    analogWrite(PIN_TURBINE, 0);
    robot.isMatchFinished = 1;
}