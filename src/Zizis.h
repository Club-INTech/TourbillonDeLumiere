/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Zizis.h
 * Author: elektron
 *
 * Created on 23 novembre 2017, 20:48
 */

#ifndef ZIZIS_H
#define ZIZIS_H

//#include <locale>


class Zizis {
public:
    Zizis(int index);
    void print();
    void changeType(int index);
    void randomize();
    void spacePrint();
private:
    char** monZizi;
    char* dur[9] = {    "8",
                        "  ___",
                        " //  7",
                        "(_,_/\\",
                        "\\    \\",
                        " \\    \\",
                        " _\\    \\_",
                        "(   \\     )",
                        " \\___|\\___/  "};
    
    char* mignon[17]={  "16",
                        "       ,-,-.       ",
                        "     ,'     `.     ",
                        "    /         \\   ",
                        "   (___________)   ",
                        "     | (.) (.)     ",
                        "     |   (_) |     ",
                        "     |   ,-. |     ",
                        "   ,'         `.   ",
                        "  / /|       |\\ \\  ",
                        " / / |       | \\ \\  ",
                        " \\ \\ |       | / / ",
                        "  (( |       | ))  ",
                        "    ,'`    ` `.    ",
                        "   / ` `  ` ` `\\   ",
                        "   |``` `  ``` |    ",
                        "    `._`,'.`_,'    "};
    
    char* poilu[8]={      "7",
                           "          _,-%/%|",
                           "      _,-'    \\//%\\",
                           "  _,-'        \\%/|%",
                           " / / )    __,--  /%\\",
                           " \\__/_,-'%(%  ;  %)%",
                           "         %\\%,   %\\",
                           "          '--%'" }; 

};

#endif /* ZIZIS_H */

