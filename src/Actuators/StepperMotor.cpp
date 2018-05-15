//
// Created by elektron on 15/05/18.
//

#include "StepperMotor.h"

StepperMotor::StepperMotor(int pinDir, int pinStep) {
    this->pinDir = pinDir;
    this->pinStep = pinStep;
}

void StepperMotor::setDirection(bool dir) {
    digitalWrite(pinDir, dir);
}

void StepperMotor::step(int nbStep) {
    for (int i=0; i<nbStep; i++){
        digitalWrite(pinStep, HIGH);
        delay(1);
        digitalWrite(pinStep, LOW);
        delay(1);
    }
}