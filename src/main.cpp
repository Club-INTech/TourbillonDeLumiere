#include <Arduino.h>
#include "Zizis.h"
#include "Robot.h"

Zizis myPenis(2);
Robot robot;
IntervalTimer timer;

void comeBackUnderLoader();
void checkLoadedFired();
void stopMatch();

//Initialisation de la Serie
void setup() {
	Serial.begin(9600);
	Serial.println("Série OK");

  	robot.init();
}

//Boucle principale
void loop() {

    while(robot.start()) { //on attend le debut du match
    }

    delay(300); //pour eviter les rebonds du jumper

    while(!robot.start()) { //on attend le debut du match , front montant
        delay(100);
    }

    attachInterrupt(digitalPinToInterrupt(PIN_FIN_COURSE), comeBackUnderLoader, FALLING);
    attachInterrupt(digitalPinToInterrupt(PIN_LASER), checkLoadedFired, CHANGE);
    timer.begin(stopMatch, 100000000);

    while(!robot.willNotCrashInOtherRobot()) {
    }

    while(!robot.isUnderLoader()) { //on se positionne sous le tube
        if (robot.willNotCrashInOtherRobot()) {
            robot.moveForward(PERCENT_MOTOR); //% de sa vitesse sinon il fonce sous les balles comme un taré
        } else {
            robot.stop();
            delay(100);
        }
    }

    robot.stop();
    robot.addScore(10);

    while (robot.getScore() < 50 ){ //on lance les 8 balles
        robot.loadBall();
        robot.fire();
        robot.moveBackward(PERCENT_MOTOR_BACK);
        robot.addScore(5);
    }

    stopMatch();
}

void comeBackUnderLoader(){
	while(!robot.isUnderLoader()){
		robot.moveForward(PERCENT_MOTOR_COME_BACK);
	}
	robot.stop();
}

void checkLoadedFired(){
    if (digitalRead(PIN_LASER)) { //front montant
        robot.hasBallLoaded = true;
    } else {    //front decendant
        robot.hasFiredBall = true;
        robot.hasBallLoaded = false;
    }
}

void stopMatch() {
    analogWrite(PIN_MOTEUR_PWM, 0);
    analogWrite(PIN_TURBINE, 0);
    while(true) { //on fait des jolis affichages
        myPenis.spacePrint(); //impression du zizi avec des espaces devant
        myPenis.randomize(); //changement aléatoire de type de zizi
        delay(500);
    }
}