/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Robot.h
 * Author: elektron (Lucas Molia)
 *
 * Created on 26 novembre 2017, 11:19
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include <Actuators/DynamixelInterface.h>
#include <Actuators/DynamixelMotor.h>
#include <pinMapping.h>
#include <constexpr.h>
#include "Afficheur.h"

class Robot {
public:
    Robot();
    void init();
    bool isGreen();
    bool start();
    bool willNotCrashInOtherRobot();
    bool isUnderLoader();
    void moveForward(int speedPercent);
    void moveBackward(int speedPercent);
    void stop();
    void loadBall();
    void fire();
    void setAngleAndWait(uint16_t angle);
    void tiltAX12();
    bool hasFiredBall;
    bool hasBallLoaded;
    void addScore(int scoreToAdd);
    int getScore();
    void print(String chaine);
    void printScore();
private:
    DynamixelInterface interface; //S'ouvre sur le port 1
    DynamixelMotor servo; //Ouvre une communication avec tout les AX12 - Remplacer 254 par l'ID
    Afficheur afficheur;
    uint16_t currentAngle;
    int score = 0;
};

#endif /* ROBOT_H */
