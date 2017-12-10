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


Robot::Robot() : interface(Serial2), servo(interface, 254) {
}

void Robot::init() {
    interface.begin(9600);  //Ouvre l'interface
    servo.init();			//Initialise le moteur
    servo.enableTorque();	//Et active le couple
    servo.jointMode();
    
    /*Declaration des sorties*/
    pinMode(PIN_MOTEUR_PWM, OUTPUT);
    pinMode(PIN_MOTEUR_DIR, OUTPUT);
    pinMode(PIN_TURBINE, OUTPUT);
    
    /*Declaration des entrees*/
    pinMode(PIN_FIN_COURSE, INPUT);
    pinMode(PIN_JUMPER, INPUT);
    pinMode(PIN_LASER, INPUT);
    
    /*Activation des resistances de pull-up internes*/
    digitalWrite(PIN_FIN_COURSE, HIGH);
    digitalWrite(PIN_LASER, HIGH);
    digitalWrite(PIN_JUMPER, HIGH);
    
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
    digitalWrite(PIN_MOTEUR_PWM, HIGH);
    int speedPwm = map(speedPercent, 0, 100, 0, 125); //on bloque au max pwm a 125 car moteur 12V alimente en 24V
    analogWrite(PIN_MOTEUR_DIR, speedPwm);
}

void Robot::loadBall() {
    //permet de charger une balle dans le canon
    servo.goalPositionDegree(300);
    delay(2500);
    servo.goalPosition(310);
    delay(500);
    servo.goalPositionDegree(195);
    delay(2000);
    servo.goalPositionDegree(185); //on va un peu plus loin au cas ou la balle ne soit pas bien tombee
    delay(500);
    servo.goalPositionDegree(195);
    delay(500);
}

void Robot::fire() {
    int attempt = 0; //nb de tentatives
    bool isFired = 0; //variable qui indique si la balle est partie
    long lastMillis = millis();
    while (!isFired || attempt < 4) { //tant que la balle n'est pas partie ou qu'on n'a pas fait 4 tentatives
        analogWrite(PIN_TURBINE, 200);
        lastMillis = millis();
        while(millis() - lastMillis < 500) { //on attend 500ms en verifiant si la balle est partie
            if (digitalRead(PIN_LASER ) == LOW) {
                isFired = 1;
            }
        }
        analogWrite(PIN_TURBINE, 0);
        attempt++;
        delay(500);
    }
}