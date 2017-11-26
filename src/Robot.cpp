/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Robot.cpp
 * Author: elektron
 * 
 * Created on 26 novembre 2017, 11:19
 */

#include "Robot.h"


Robot::Robot() : interface(serie,2), servo(interface, 254) {
}

void Robot::init() {
    interface.begin(9600);  //Ouvre l'interface
    servo.init();			//Initialise le moteur
    servo.enableTorque();	//Et active le couple
    servo.jointMode();
    
    /*Declaration des sorties*/
    pinMode(PIN_MOTEUR_PWM, OUTPUT);
    pinMode(PIN_MOTEUR_DIR1, OUTPUT);
    pinMode(PIN_MOTEUR_DIR2, OUTPUT);
    pinMode(PIN_TURBINE, OUTPUT);
    
    /*Declaration des entrees*/
    pinMode(PIN_FIN_COURSE, INPUT);
    pinMode(PIN_JUMPER, INPUT);
    pinMode(PIN_LIDAR, INPUT);
    
    /*Activation des resistances de pull-up internes*/
    digitalWrite(PIN_FIN_COURSE, HIGH);
    digitalWrite(PIN_FIN_COURSE, HIGH);
    digitalWrite(PIN_FIN_COURSE, HIGH);
    
    servo.speed(100);
    servo.goalPositionDegree(100);
}

bool Robot::start() {
    return (!digitalRead(PIN_JUMPER));
}

bool Robot::isUnderLoader() {
    //indique si le robot est sous e tube de balles
    return !digitalRead(PIN_FIN_COURSE);
}

void Robot::moveForward(int speedPercent) {
    //fait avancer le robot en avant a une vitesse speedPercent % de sa vitesse max
    digitalWrite(PIN_MOTEUR_DIR1, HIGH);
    digitalWrite(PIN_MOTEUR_DIR2, LOW);
    int speedPwm = map(speedPercent, 0, 100, 0, 125); //on bloque au max pwm a 125 car moteur 12V alimente en 24V
    analogWrite(PIN_MOTEUR_PWM, speedPwm);
}

void Robot::loadBall() {
    //permet de charger une balle dans le canon
    servo.goalPositionDegree(100);
    delay(1000);
    servo.goalPositionDegree(195);
    delay(1000);
    servo.goalPositionDegree(200); //on va un peu plus loin au cas ou la balle ne soit pas bien tombee
    delay(200);
    servo.goalPositionDegree(195);
    delay(200);
}

void Robot::fire() {
    int attempt = 0; //nb de tentatives
    bool isFired = 0; //variable qui indique si la balle est partie
    long lastMillis = millis();
    while (!isFired || attempt < 4) { //tant quela balle n'est pas partie ou qu'on n'a pas fait 4 tentatives
        digitalWrite(PIN_TURBINE, HIGH);
        while(millis() - lastMillis < 500) { //on attend 500ms en verifiant si la balle est partie
            if (digitalRead(PIN_LIDAR ) == LOW) {
                isFired = 1;
            }
        }
        lastMillis = millis();
        digitalWrite(PIN_TURBINE, LOW);
        delay(500);
    }
}