#include <Arduino.h>
#include "Zizis.h"
#include "Robot.h"
#include "Afficheur.h"

Zizis myPenis(2);
Robot robot;
Afficheur afficheur;

bool etat=0;

bool last_state = 0;

//Initialisation de la Serie
void setup() {
	Serial.begin(9600);
	Serial.println("Série OK");
	//delay(250);

  robot.init();
	afficheur.init();
	afficheur.setBrightnessI2C(0xFF);
	afficheur.display("TEST");
}

//Boucle principale
void loop() {
	if(last_state != robot.isUnderLoader()) {
		if (robot.isUnderLoader()) {
			afficheur.display("COOL");
		} else {
			afficheur.display("FEU!");
		}
		last_state = robot.isUnderLoader();
	}

	if(Serial.available()) {
		char x = Serial.read();
    if(x == 'r') {
			robot.loadBall();
		} else if(x == 'f') {
			robot.fire();
		} else if(x == 'g') {
			robot.moveForward(60);
			delay(500);
			robot.stop();
		} else if(x == 'b') {
			robot.moveForward(-60);
			delay(500);
			robot.stop();
		}
		Serial.flush();
	}
}
