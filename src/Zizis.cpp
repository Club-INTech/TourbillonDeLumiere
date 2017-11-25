/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Zizis.cpp
 * Author: elektron
 * 
 * Created on 23 novembre 2017, 20:48
 */

#include "Zizis.h"
#include "Arduino.h"

Zizis::Zizis(int index) {
    changeType(index);
}

void Zizis::print() {
    for(int i = 1; i<atoi(monZizi[0])+1; i++) {
        Serial.println(monZizi[i]);
    }
}

void Zizis::spacePrint() {
    int nbEspaces = random(0,60);
    String espaces = "";
    for( int i=0; i<nbEspaces; i++) {
        espaces += " ";
    }
    for(int i = 1; i<atoi(monZizi[0])+1; i++) {
        Serial.println(espaces+monZizi[i]);
    }
}

void Zizis::changeType(int index) {
    if (index == 1){
        monZizi = dur;
    } else if (index == 2) {
        monZizi = mignon;
    } else if (index == 3) {
        monZizi = poilu;
    }
}

void Zizis::randomise() {
    changeType(random(1,4));
}