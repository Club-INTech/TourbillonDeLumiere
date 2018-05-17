//
// Created by elektron on 15/05/18.
//

#include "StepperMotor.h"

StepperMotor::StepperMotor(int nbStepPerTour, uint8_t pinDir, uint8_t pinStep) {
    this->pinDir = pinDir;
    this->pinStep = pinStep;
    this->nbStepPerTour= nbStepPerTour;
    pinMode(pinDir, OUTPUT);
    pinMode(pinStep, OUTPUT);
}

void StepperMotor::setDirection(bool dir) {
    digitalWrite(pinDir, dir);
}

void StepperMotor::setSpeed(int speed) {
    this->speed = speed;
}

void StepperMotor::step(int nbStep) {
    int timeToDelay = static_cast<int>( 60.0*1000000.0 / (speed*nbStepPerTour));
    Serial.println(timeToDelay);

    for (int i=0; i<nbStep; i++){
        digitalWrite(pinStep, HIGH);
        delayMicroseconds(500);
        digitalWrite(pinStep, LOW);
        delayMicroseconds(static_cast<unsigned int>(timeToDelay - 500));
    }
}

void StepperMotor::stepDegree(int degree) {
    int nbStep = 0;
    nbStep = static_cast<int>((nbStepPerTour * degree) / 360.0);
    step(nbStep);
}