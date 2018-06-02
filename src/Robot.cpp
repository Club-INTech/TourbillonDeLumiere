/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Robot.cpp
 * Author: elektron (Lucas Molia)
 *
 * Created on 26 novembre 2017, 11:19
 */

#include <Robot.h>
#include <SoftPWM.h>

Robot::Robot() : interface(Serial2), servo(interface, 254) {
}

void Robot::init() {

    SoftPWMBegin(SOFTPWM_NORMAL);

    /*Declaration des sorties*/
    pinMode(PIN_MOTEUR_PWM, OUTPUT);
    pinMode(PIN_MOTEUR_DIR, OUTPUT);
    //pinMode(PIN_TURBINE, OUTPUT);

    /*Declaration des entrees*/
    pinMode(PIN_FIN_COURSE, INPUT);
    pinMode(PIN_JUMPER, INPUT);
    pinMode(PIN_LASER_ORANGE, INPUT);
    pinMode(PIN_SELECT_SIDE, INPUT);

    /*Activation des resistances de pull-up internes*/
    digitalWrite(PIN_FIN_COURSE, HIGH);
    digitalWrite(PIN_LASER_ORANGE, HIGH);
    digitalWrite(PIN_SELECT_SIDE, HIGH);

    /*Mise à 0 initiale des sorties*/
    digitalWrite(PIN_MOTEUR_PWM, LOW);
    digitalWrite(PIN_MOTEUR_DIR, LOW);
    SoftPWMSet(PIN_TURBINE,0);

    analogWriteFrequency(PIN_MOTEUR_PWM, PWM_FREQUENCY);

    afficheur.init();

    interface.begin(9600);  //Ouvre l'interface
    servo.communicationSpeed(9600);
    servo.init();			//Initialise le moteur
    servo.enableTorque();	//Et active le couple
    servo.jointMode();

    servo.speed(SERVO_SPEED);
    if (isGreen()) {
        servo.goalPositionDegree(ANGLE_AX12_VERT);
        currentAngle = ANGLE_AX12_VERT;
    } else {
        servo.goalPositionDegree(ANGLE_AX12_ORANGE);
        currentAngle = ANGLE_AX12_ORANGE;
    }

    afficheur.display("SUUS");
}

bool Robot::isGreen() {
    //permet de faire la selection du côté
    //Serial.println(digitalRead(PIN_SELECT_SIDE) ? "I AM ORANGE" : "I AM GREEN");
    return !digitalRead(PIN_SELECT_SIDE);
}

bool Robot::start() {
    //retourne l'état du jumper pour savoir si on démarre le match
    return (digitalRead(PIN_JUMPER));
}

bool Robot::willNotCrashInOtherRobot() {
    //indique si il y a un obstacle devant le robot
    return (analogRead(PIN_SHARP) < TRIGGER_SHARP);
}

bool Robot::isUnderLoader() {
    //indique si le robot est sous le tube de balles
    if (isGreen()){
        return digitalRead(PIN_LASER_VERT);
    } else {
        return digitalRead(PIN_LASER_ORANGE);
    }
}

bool Robot::isAtBee() {
    //indique si le robot est au niveau de l'abeille
    return digitalRead(PIN_FIN_COURSE);
}

void Robot::moveForward(int speedPercent) {
    //fait avancer le robot en avant a une vitesse speedPercent % de sa vitesse max
    digitalWrite(PIN_MOTEUR_DIR, HIGH);
    int speedPwm = map(speedPercent, 0, 100, 0, 125); //on bloque au max pwm a 125 car moteur 12V alimente en 24V
    analogWrite(PIN_MOTEUR_PWM, speedPwm);
}

void Robot::moveBackward(int speedPercent) {
    //fait reculer le robot pour le recaler au laser
    digitalWrite(PIN_MOTEUR_DIR,LOW);
    int speedPwm = map(speedPercent,0,100, 0, 125); //on bloque au max pwm a 125 car moteur 12V alimente en 24V
    analogWrite(PIN_MOTEUR_PWM, speedPwm);
}

void Robot::stop() {
    //arrête le moteur du robot
    analogWrite(PIN_MOTEUR_PWM, 0);
}

void Robot::fireBee() {
    //lance l'abeille
    setAngleAndWait(ANGLE_AX12_MID);
    if (isGreen()) {
        setAngleAndWait(ANGLE_AX12_VERT);
    } else {
        setAngleAndWait(ANGLE_AX12_ORANGE);
    }
}

void Robot::setAngleAndWait(uint16_t angle) {
    //amene l'AX12 sur un angle et attends qu'il soit arrive
    angle = (uint16_t)constrain(angle, 0, 300);
    servo.speed(SERVO_SPEED);
    servo.goalPositionDegree(angle);
    uint32_t timeToMove = (uint32_t)(2200*abs(currentAngle - angle))/SERVO_SPEED; //valeur a ajuster
    delay(timeToMove);
    currentAngle = angle;
}

int Robot::getScore() {
    //renvoie le score reellement effectue par le robot
    return score;
}

void Robot::addScore(int scoreToAdd){
    //increment le score de scoreToAdd et met a jour l'afficheur
    score += scoreToAdd;
    afficheur.displayInt(score);
}

void Robot::print(String chaine){
    afficheur.display(chaine);
}

void Robot::printScore(){
    afficheur.displayInt(score);
}