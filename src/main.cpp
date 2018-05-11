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
void comeBackUnderLoader();
void checkLoadedFired();
void stopMatch();
void loaderNotDetected();
void theLastChance();

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

    /*Début du match, on active les interruptions et du timer pour l'arret automatique */
    attachInterrupt(digitalPinToInterrupt(PIN_FIN_COURSE), comeBackUnderLoader, FALLING);
    attachInterrupt(digitalPinToInterrupt(PIN_LASER), checkLoadedFired, CHANGE);

    /*On demarre aussi tous les timers*/
    timer.priority(0); //Priorite maximum, il doit absolument s'arreter
    timer.begin(stopMatch, 100000000); //Timer qui sert pour arreter le match au bout de 100s
    timerSuicide.begin(theLastChance, 90000000);  //Timer qui fait revenir le robot pour liberer des balles au bout de 90s si on n'a pas fait de points
    antiBlock.priority(128);
    antiBlock.begin(loaderNotDetected, 5000000);   //Si on n'a pas detecte le reservoir au bout d'un certain temps on recule et reavance

    while(!robot.isUnderLoader()) { //on se positionne sous le tube
        if (robot.willNotCrashInOtherRobot()) {
            robot.moveForward(PERCENT_MOTOR); //% de sa vitesse sinon il fonce sous les balles comme un taré
        } else {
            robot.stop();
            antiBlock.end();
            while(!robot.willNotCrashInOtherRobot()) { delay(100); }
            antiBlock.begin(loaderNotDetected, 5000000);
        }
    }

    robot.stop();
    antiBlock.end();

    while (robot.getScore() < 50 ){ //on lance les 8 balles
        robot.loadBall();
        robot.fire();
        robot.moveBackward(PERCENT_MOTOR_BACK);
        if (robot.getScore() == 0){
            robot.addScore(10);
        }
        robot.addScore(5);
    }
    stopMatch();
}

void beginMatch(){
    isMatchStarted = 1;
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
    robot.adjustScore();
    while(true) { //on fait des jolis affichages
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

void loaderNotDetected() {
    int count = 0;
    robot.stop();
    robot.moveBackward(PERCENT_MOTOR_BACK);
    delay(300);
    robot.stop();
    while(!robot.isUnderLoader()) { //on se positionne sous le tube
        if (robot.willNotCrashInOtherRobot()) {
            robot.moveForward(PERCENT_MOTOR); //% de sa vitesse sinon il fonce sous les balles comme un taré
            count++;
            if (count > 50) {
                loaderNotDetected();
            }
            delay(100);
        } else {
            robot.stop();
            antiBlock.end();
            while(!robot.willNotCrashInOtherRobot()) { delay(100);}
        }
    }
    antiBlock.end();
}

void theLastChance(){
    if (robot.getScore() < 10) {
        robot.stop();
        delay(1000);
        robot.moveForward(100);
        delay(500);
        robot.moveBackward(PERCENT_MOTOR_BACK);
        delay(2000);
        robot.addScore(10);
        stopMatch();
    }
}