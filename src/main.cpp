#include "Arduino.h"
#include <Actuators/DynamixelInterface.h>
#include <Actuators/DynamixelMotor.h>

HardwareSerial serie;
DynamixelInterface interface(serie,1); //S'ouvre sur le port 1

DynamixelMotor moteur(interface,254); //Ouvre une communication avec tout les AX12 - Remplacer 254 par l'ID

//Initialisation de la Serie
void setup() {
	/*serie*/
	Serial.begin(115200);
	Serial.println("Série OK");
	delay(250);
	
	
	interface.begin(9600);  //Ouvre l'interface

	moteur.init();			//Initialise le moteur
	moteur.enableTorque();	//Et active le couple
	moteur.jointMode();
}

//Boucle principale
void loop() {
	Serial.println("  ___");
        Serial.println(" //  7");
        Serial.println("(_,_/\\");
        Serial.println("\\    \\");
        Serial.println(" \\    \\");
        Serial.println(" _\\    \\_");
        Serial.println("(   \\     )");
        Serial.println(" \\___|\___/  ");
        moteur.goalPositionDegree(100);
        delay(2000);
        moteur.goalPositionDegree(195);
        delay(2000);
}