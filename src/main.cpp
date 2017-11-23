#include "Arduino.h"
#include <Actuators/DynamixelInterface.h>
#include <Actuators/DynamixelMotor.h>
#include <Zizis.h>

HardwareSerial serie;
DynamixelInterface interface(serie,1); //S'ouvre sur le port 1

DynamixelMotor moteur(interface,254); //Ouvre une communication avec tout les AX12 - Remplacer 254 par l'ID

Zizis myPenis(1);

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
    /*String espaces = " ";
    int nb_espaces = random(0,50);
    for( int i=0; i<nb_espaces; i++) {
        espaces += " ";
    }
    Serial.println(espaces+"  ___");
    Serial.println(espaces+" //  7");
    Serial.println(espaces+"(_,_/\\");
    Serial.println(espaces+"\\    \\");
    Serial.println(espaces+" \\    \\");
    Serial.println(espaces+" _\\    \\_");
    Serial.println(espaces+"(   \\     )");
    Serial.println(espaces+" \\___|\\___/  ");
    moteur.goalPositionDegree(100);
    delay(2000);
    moteur.goalPositionDegree(195);
    delay(2000);
    delay(500);*/
    myPenis.print();
    delay(500);
}