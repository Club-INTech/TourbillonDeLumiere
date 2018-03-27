/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Robot.h
 * Author: elektron
 *
 * Created on 26 novembre 2017, 11:19
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include <Actuators/DynamixelInterface.h>
#include <Actuators/DynamixelMotor.h>
#include <pinMapping.h>
#include <defines.h>

class Robot {
public:
    Robot();
    void init();
    void setLedSide();
    bool isGreen();
    bool start();
    bool isUnderLoader();
    void moveForward(int speedPercent);
    void moveBackward(int speedPercent);
    void stop();
    void loadBall();
    void fire();
private:
    //HardwareSerial serie;
    DynamixelInterface interface; //S'ouvre sur le port 1
    DynamixelMotor servo; //Ouvre une communication avec tout les AX12 - Remplacer 254 par l'ID
};

#endif /* ROBOT_H */
