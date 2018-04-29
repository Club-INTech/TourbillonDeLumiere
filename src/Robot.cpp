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
    interface.begin(9600);  //Ouvre l'interface
    servo.communicationSpeed(9600);
    servo.init();			//Initialise le moteur
    servo.enableTorque();	//Et active le couple
    servo.jointMode();

    afficheur.init();
    afficheur.setBrightnessI2C(0xFF);
    afficheur.display("SUUS");

    SoftPWMBegin(SOFTPWM_NORMAL);

    /*Declaration des sorties*/
    pinMode(PIN_MOTEUR_PWM, OUTPUT);
    pinMode(PIN_MOTEUR_DIR, OUTPUT);
    //pinMode(PIN_TURBINE, OUTPUT);

    /*Declaration des entrees*/
    pinMode(PIN_FIN_COURSE, INPUT);
    pinMode(PIN_JUMPER, INPUT);
    pinMode(PIN_LASER, INPUT);
    pinMode(PIN_SELECT_SIDE, INPUT);

    /*Activation des resistances de pull-up internes*/
    digitalWrite(PIN_FIN_COURSE, HIGH);
    digitalWrite(PIN_LASER, HIGH);
    digitalWrite(PIN_JUMPER, HIGH);
    digitalWrite(PIN_SELECT_SIDE, HIGH);

    /*Mise à 0 initiale des sorties*/
    digitalWrite(PIN_MOTEUR_PWM, LOW);
    digitalWrite(PIN_MOTEUR_DIR, LOW);
    SoftPWMSet(PIN_TURBINE,0);

    analogWriteFrequency(PIN_MOTEUR_PWM, PWM_FREQUENCY);

    servo.speed(SERVO_SPEED);
    if (isGreen()) {
        servo.goalPositionDegree(ANGLE_AX12_VERT);
        currentAngle = ANGLE_AX12_VERT;
    } else {
        servo.goalPositionDegree(ANGLE_AX12_ORANGE);
        currentAngle = ANGLE_AX12_ORANGE;
    }
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
    return (analogRead(PIN_SHARP) < TRIGGER_SHARP);
}

bool Robot::isUnderLoader() {
    //indique si le robot est sous le tube de balles
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

void Robot::loadBall() {
    //permet de charger une balle dans le canon
    uint16_t angle_load;

    if (isGreen()) {
        angle_load = ANGLE_AX12_VERT;
    } else {
        angle_load = ANGLE_AX12_ORANGE;
    }
    
    setAngleAndWait(angle_load);
    tiltAX12();

    setAngleAndWait(ANGLE_AX12_MID);
    tiltAX12();
}

void Robot::tiltAX12(){
    int sign = isGreen() ? -1 : 1;
    setAngleAndWait(uint16_t(currentAngle + (10*sign)));
    setAngleAndWait(uint16_t(currentAngle - (10*sign)));
    delay(100);
    setAngleAndWait(uint16_t(currentAngle - (10*sign)));
    setAngleAndWait(uint16_t(currentAngle + (10*sign)));
}

void Robot::fire() {
    //permet d'allumer la turbine, en vérifiant qu'une balle est partie grâce au laser
    int attempt_tilt = 0;
    while (!hasBallLoaded){
        if (attempt_tilt < TENTATIVE_TILT_MAX) {
            tiltAX12();
            attempt_tilt++;
        } else {
            attempt_tilt = 0;
            moveBackward(PERCENT_MOTOR_COME_BACK);
            loadBall();
        }
    }
    int attempt_turbine = 0; //nb de tentatives reellement faites
    hasFiredBall = false; //on remet a zero la variable utilisee par l'interruption
    while (!hasFiredBall && attempt_turbine < TENTATIVE_MAX) { //tant que la balle n'est pas partie ou qu'on n'a pas fait 4 tentatives
        if (isGreen()) {
            SoftPWMSet(PIN_TURBINE, PWM_TURBINE_GREEN);
        } else {
            SoftPWMSet(PIN_TURBINE, PWM_TURBINE_ORANGE);
        }
        delay(500);
        SoftPWMSet(PIN_TURBINE, 0);
        attempt_turbine++;
        delay(1000);
    }
}

void Robot::setAngleAndWait(uint16_t angle) {
    servo.speed(SERVO_SPEED);
    servo.goalPositionDegree(angle);
    uint32_t timeToMove = (uint32_t)(2200*abs(currentAngle - angle))/SERVO_SPEED;
    delay(timeToMove); //valeur a ajuster
    currentAngle = angle;
}

int Robot::getScore() {
    return score;
}

void Robot::addScore(int scoreToAdd){
    score += scoreToAdd;
    afficheur.displayInt(score);
}