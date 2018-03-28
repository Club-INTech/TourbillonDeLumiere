#include <Arduino.h>
#include "Zizis.h"
#include "Robot.h"
#include "Afficheur.h"

Zizis myPenis(2);
Robot robot;
Afficheur afficheur;

void comeBackUnderLoader();
void changeFired();

bool etat=0;

//Initialisation de la Serie
void setup() {
	Serial.begin(9600);
	Serial.println("Série OK");
	//delay(250);

  	robot.init();
	afficheur.init();
	afficheur.setBrightnessI2C(0xFF);
	afficheur.display("SUUS");
}

//Boucle principale
void loop() {

    //robot.setLedSide();

    while(robot.start()) { //on attend le debut du match
    }

    delay(300); //pour eviter les rebonds du jumper

    while(!robot.start()) { //on attend le debut du match , front montant
    }

    attachInterrupt(digitalPinToInterrupt(PIN_FIN_COURSE), comeBackUnderLoader, FALLING);
    attachInterrupt(digitalPinToInterrupt(PIN_LASER), changeFired, CHANGE);

    while(!robot.isUnderLoader()) { //on se positionne sous le tube
        robot.moveForward(PERCENT_MOTOR); //% de sa vitesse sinon il fonce sous les balles comme un taré
    }

    robot.stop();
    afficheur.addScore(10);
    for(int i=0; i<8; i++) { //on lance les 8 balles
        robot.loadBall();
        robot.fire();
        robot.moveBackward(PERCENT_MOTOR_BACK);
        afficheur.addScore(5);
    }

    while(true) { //on fait des jolis affichages
        myPenis.spacePrint(); //impression du zizi avec des espaces devant
        myPenis.randomise(); //changement aléatoire de type de zizi
        delay(500);
    }
}

void comeBackUnderLoader(){
	while(!robot.isUnderLoader()){
		robot.moveForward(PERCENT_MOTOR_COME_BACK);
	}
	robot.stop();
}

void changeFired(){
    if (digitalRead(PIN_LASER)) { //front montant
        robot.hasBallLoaded = true;
    } else {    //front decendant
        robot.hasFiredBall = true;
    }
}

void setLoaded(){

}