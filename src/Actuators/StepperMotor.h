//
// Created by elektron on 15/05/18.
//

#ifndef TOURBI_STEPPERMOTOR_H
#define TOURBI_STEPPERMOTOR_H

#include <Arduino.h>

class StepperMotor {
    public:
        StepperMotor(int pinDir, int pinStep);
        void setDirection(bool dir);
        void step(int nbStep);
    private:
        int pinDir;
        int pinStep;
};


#endif //TOURBI_STEPPERMOTOR_H
