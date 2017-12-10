#include "Arduino.h"
#include <Zizis.h>
#include <Robot.h>

Zizis myPenis(2);
Robot robot;

//Initialisation de la Serie
void setup() {
	/*serie*/
	Serial.begin(9600);
	Serial.println("Série OK");
	//delay(250);
        
        robot.init();
}

//Boucle principale
void loop() {
    /*while(!robot.start()) { //on attend le debut du match
    }
    
    while(!robot.isUnderLoader()) { //on se positionne sous le tube
        robot.moveForward(100);
    }
    
    for(int i=0; i<8; i++) { //on lance les 8 balles
        robot.loadBall();
        robot.fire();
    }
    
    while(true) { //on fait des jolis affichages
        myPenis.spacePrint(); //impression du zizi avec des espaces devant
        myPenis.randomise(); //changement aléatoire de type de zizi
        delay(500);
    }*/
    
    Serial.println(digitalRead(PIN_LASER));
    delay(100);
}
