#include <Arduino.h>
#include "Zizis.h"
#include "Robot.h"
#include "Afficheur.h"

Zizis myPenis(2);
Robot robot;
Afficheur afficheur;

bool etat=0;

//Initialisation de la Serie
void setup() {
	/*serie*/
	Serial.begin(9600);
	Serial.println("Série OK");
	//delay(250);

  robot.init();
	afficheur.init();
}

//Boucle principale
void loop() {

    /*robot.setLedSide();

    while(!robot.start()) { //on attend le debut du match
    }

    while(!robot.isUnderLoader()) { //on se positionne sous le tube
        robot.moveForward(100);
    }

    robot.stop();

    for(int i=0; i<8; i++) { //on lance les 8 balles
        robot.loadBall();
        robot.fire();
				afficheur.addScore(5);
    }

    while(true) { //on fait des jolis affichages
        myPenis.spacePrint(); //impression du zizi avec des espaces devant
        myPenis.randomise(); //changement aléatoire de type de zizi
        delay(500);
    }*/

    /*while (!robot.isUnderLoader()) {
            robot.moveForward(100);
    }
    robot.stop();
    delay(1000);
    robot.loadBall();
    robot.fire();*/

    robot.moveForward(100);
}
