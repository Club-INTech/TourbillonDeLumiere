//
// Created by elektron on 15/05/18.
//

#ifndef TOURBI_STEPPERMOTOR_H
#define TOURBI_STEPPERMOTOR_H

#include <Arduino.h>

class StepperMotor {
public:
    StepperMotor(int nbStepPerTour, uint8_t pinDir, uint8_t pinStep);
    void setDirection(bool dir);
    void step(int nbStep);
    void stepDegree(int nbStepDegree);
    void setSpeed(int speed);
private:
    uint8_t pinDir;
    uint8_t pinStep;
    int nbStepPerTour;
    int speed = 30;
};

#endif //TOURBI_STEPPERMOTOR_H
