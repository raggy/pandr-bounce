/*
 *  text.cpp
 *  BallDrop
 *
 *  Created by Robin Hayes on 04/05/2010.
 *  Copyright 2010 Propellor and Ratchet Games. All rights reserved.
 *
 */

#include <string>
#include <sstream>
#include <iostream>

#include "text.h"

using namespace std;


string itostring(int number){
    string s;
    stringstream out;
    out << number;
    return out.str();
}
string ftostring(float number){
    string s;
    stringstream out;
    out << number;
    return out.str();
}

void Text(string msg, int x, int y){
    Text(msg, x, y, 1, 1, 1, 1.0);
}

void Text(string msg, int x, int y, float size){
    Text(msg, x, y, size, 1, 1, 1.0);
}

void Text(string msg, int x, int y, float size, GLfloat colour[]){
    Text(msg, x, y, size, colour[0], colour[1], colour[2]);
}

void Text(string msg, int x, int y, float size = 1.0, double r=1, double g=1, double b=1){
    //letters are 3x6. Lowercase only for now.
    //1px space and baseline so 4x7 really.
    glPushMatrix();
        glTranslated(x, y, 0);
        glScalef(size, size, 0);
        GLfloat temp[] = {r, g, b, 1.0};
        //glMaterialfv(GL_FRONT, GL_DIFFUSE, temp);
        glColor4f(temp[0], temp[1],temp[2], temp[3]);
    for(int letter = 0; letter < msg.length(); letter++){
        glBegin(GL_QUADS);
        if (msg.at(letter) == 'a' || msg.at(letter) == 'A'){
            glVertex2f(1, 0);//top
            glVertex2f(2, 0);
            glVertex2f(2, 1);
            glVertex2f(1, 1);
            glVertex2f(1, 2);//bridge
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(1, 3);
            glVertex2f(0, 1);//left
            glVertex2f(1, 1);
            glVertex2f(1, 5);
            glVertex2f(0, 5);
            glVertex2f(2, 1);//right
            glVertex2f(3, 1);
            glVertex2f(3, 5);
            glVertex2f(2, 5);
            //cout << x<<" "<<y<<" "<<letter<<" "<<size<<"\n";
        }
        if (msg.at(letter) == 'b'||msg.at(letter) == 'B'){
            glVertex2f(1, 0);//top
            glVertex2f(2, 0);
            glVertex2f(2, 1);
            glVertex2f(1, 1);
            glVertex2f(1, 2);//bridge
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(1, 3);
            glVertex2f(1, 4);//bottom
            glVertex2f(2, 4);
            glVertex2f(2, 5);
            glVertex2f(1, 5);
            glVertex2f(0, 0);//left
            glVertex2f(1, 0);
            glVertex2f(1, 5);
            glVertex2f(0, 5);
            glVertex2f(2, 1);//right top
            glVertex2f(3, 1);
            glVertex2f(3, 2);
            glVertex2f(2, 2);
            glVertex2f(2, 3);//right bottom
            glVertex2f(3, 3);
            glVertex2f(3, 4);
            glVertex2f(2, 4);
        }
        if (msg.at(letter) == 'c' || msg.at(letter) == 'C'){
            glVertex2f(1, 0);//top
            glVertex2f(3, 0);
            glVertex2f(3, 1);
            glVertex2f(1, 1);
            glVertex2f(0, 1);//left
            glVertex2f(1, 1);
            glVertex2f(1, 4);
            glVertex2f(0, 4);
            glVertex2f(1, 4);//bottom
            glVertex2f(3, 4);
            glVertex2f(3, 5);
            glVertex2f(1, 5);
        }
        if (msg.at(letter) == 'd' || msg.at(letter) == 'D'){
            glVertex2f(1, 0);//top
            glVertex2f(2, 0);
            glVertex2f(2, 1);
            glVertex2f(1, 1);
            glVertex2f(1, 4);//bottom
            glVertex2f(2, 4);
            glVertex2f(2, 5);
            glVertex2f(1, 5);
            glVertex2f(0, 0);//left
            glVertex2f(1, 0);
            glVertex2f(1, 5);
            glVertex2f(0, 5);
            glVertex2f(2, 1);//right top
            glVertex2f(3, 1);
            glVertex2f(3, 4);
            glVertex2f(2, 4);
        }
        if (msg.at(letter) == 'e' || msg.at(letter) == 'E'){
            glVertex2f(1, 0);//top
            glVertex2f(3, 0);
            glVertex2f(3, 1);
            glVertex2f(1, 1);
            glVertex2f(1, 2);//bridge
            glVertex2f(3, 2);
            glVertex2f(3, 3);
            glVertex2f(1, 3);
            glVertex2f(1, 4);//bottom
            glVertex2f(3, 4);
            glVertex2f(3, 5);
            glVertex2f(1, 5);
            glVertex2f(0, 0);//left
            glVertex2f(1, 0);
            glVertex2f(1, 5);
            glVertex2f(0, 5);
        }
        if (msg.at(letter) == 'f' || msg.at(letter) == 'F'){
            glVertex2f(1, 0);//top
            glVertex2f(3, 0);
            glVertex2f(3, 1);
            glVertex2f(1, 1);
            glVertex2f(1, 2);//bridge
            glVertex2f(3, 2);
            glVertex2f(3, 3);
            glVertex2f(1, 3);
            glVertex2f(0, 0);//left
            glVertex2f(1, 0);
            glVertex2f(1, 5);
            glVertex2f(0, 5);
        }
        if (msg.at(letter) == 'g' || msg.at(letter) == 'G'){
            glVertex2f(1, 0);//top
            glVertex2f(3, 0);
            glVertex2f(3, 1);
            glVertex2f(1, 1);
            glVertex2f(0, 1);//left
            glVertex2f(1, 1);
            glVertex2f(1, 4);
            glVertex2f(0, 4);
            glVertex2f(1, 4);//bottom
            glVertex2f(3, 4);
            glVertex2f(3, 5);
            glVertex2f(1, 5);
            glVertex2f(2, 2);//right
            glVertex2f(3, 2);
            glVertex2f(3, 4);
            glVertex2f(2, 4);
        }
        if (msg.at(letter) == 'h' || msg.at(letter) == 'H'){
            glVertex2f(0, 0);//left
            glVertex2f(1, 0);
            glVertex2f(1, 5);
            glVertex2f(0, 5);
            glVertex2f(1, 2);//bridge
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(1, 3);
            glVertex2f(2, 0);//right
            glVertex2f(3, 0);
            glVertex2f(3, 5);
            glVertex2f(2, 5);
        }
        if (msg.at(letter) == 'i' || msg.at(letter) == 'I'){
            glVertex2f(0, 0);//top
            glVertex2f(3, 0);
            glVertex2f(3, 1);
            glVertex2f(0, 1);
            
            glVertex2f(1, 1);//middle
            glVertex2f(2, 1);
            glVertex2f(2, 4);
            glVertex2f(1, 4);
            
            glVertex2f(0, 4);//bottom
            glVertex2f(3, 4);
            glVertex2f(3, 5);
            glVertex2f(0, 5);
        }
        if (msg.at(letter) == 'j'||msg.at(letter) == 'J'){
            glVertex2f(0, 0);//top
            glVertex2f(3, 0);
            glVertex2f(3, 1);
            glVertex2f(0, 1);
            
            glVertex2f(2, 0);//right
            glVertex2f(3, 0);
            glVertex2f(3, 4);
            glVertex2f(2, 4);
        
            glVertex2f(0, 4);//bottom
            glVertex2f(2, 4);
            glVertex2f(2, 5);
            glVertex2f(0, 5);
        }
        if (msg.at(letter) == 'k' || msg.at(letter) == 'K'){
            glVertex2f(0, 0);//left
            glVertex2f(1, 0);
            glVertex2f(1, 5);
            glVertex2f(0, 5);
            
            glVertex2f(1, 2);//bridge
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(1, 3);
            
            glVertex2f(2, 0);//topright
            glVertex2f(3, 0);
            glVertex2f(3, 2);
            glVertex2f(2, 2);
            
            glVertex2f(2, 3);//botright
            glVertex2f(3, 3);
            glVertex2f(3, 5);
            glVertex2f(2, 5);
        }
        if (msg.at(letter) == 'l' || msg.at(letter) == 'L'){
            glVertex2f(0, 0);//left
            glVertex2f(1, 0);
            glVertex2f(1, 5);
            glVertex2f(0, 5);
            glVertex2f(1, 4);//bottom
            glVertex2f(3, 4);
            glVertex2f(3, 5);
            glVertex2f(1, 5);
        }
        if (msg.at(letter) == 'm' || msg.at(letter) == 'M'){
            glVertex2f(0, 0);//left
            glVertex2f(1, 0);
            glVertex2f(1, 5);
            glVertex2f(0, 5);
            glVertex2f(1, 1);//bridge
            glVertex2f(2, 1);
            glVertex2f(2, 2);
            glVertex2f(1, 2);
            glVertex2f(2, 0);//right
            glVertex2f(3, 0);
            glVertex2f(3, 5);
            glVertex2f(2, 5);
        }
        if (msg.at(letter) == 'n' || msg.at(letter) == 'N'){
            glVertex2f(0, 1);//left
            glVertex2f(1, 1);
            glVertex2f(1, 5);
            glVertex2f(0, 5);
            glVertex2f(1, 2);//bridge
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(1, 3);
            glVertex2f(2, 0);//right
            glVertex2f(3, 0);
            glVertex2f(3, 4);
            glVertex2f(2, 4);
        }
        if (msg.at(letter) == 'o' || msg.at(letter) == 'O'){
            glVertex2f(0, 0);//top
            glVertex2f(3, 0);
            glVertex2f(3, 1);
            glVertex2f(0, 1);
            glVertex2f(2, 1);//right
            glVertex2f(3, 1);
            glVertex2f(3, 4);
            glVertex2f(2, 4);
            glVertex2f(0, 4);//bottom
            glVertex2f(3, 4);
            glVertex2f(3, 5);
            glVertex2f(0, 5);
            glVertex2f(0, 1);//left
            glVertex2f(1, 1);
            glVertex2f(1, 4);
            glVertex2f(0, 4);
        }
        if (msg.at(letter) == 'p' || msg.at(letter) == 'P'){
            glVertex2f(1, 0);//top
            glVertex2f(2, 0);
            glVertex2f(2, 1);
            glVertex2f(1, 1);
            glVertex2f(2, 1);//right
            glVertex2f(3, 1);
            glVertex2f(3, 2);
            glVertex2f(2, 2);
            glVertex2f(1, 2);//bottom
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(1, 3);
            glVertex2f(0, 0);//left
            glVertex2f(1, 0);
            glVertex2f(1, 5);
            glVertex2f(0, 5);
        }
        if (msg.at(letter) == 'q' || msg.at(letter) == 'Q'){
            glVertex2f(1, 0);//top
            glVertex2f(2, 0);
            glVertex2f(2, 1);
            glVertex2f(1, 1);
            glVertex2f(2, 1);//right
            glVertex2f(3, 1);
            glVertex2f(3, 5);
            glVertex2f(2, 5);
            glVertex2f(1, 3);//bottom
            glVertex2f(2, 3);
            glVertex2f(2, 5);
            glVertex2f(1, 5);
            glVertex2f(0, 1);//left
            glVertex2f(1, 1);
            glVertex2f(1, 4);
            glVertex2f(0, 4);
        }
        if (msg.at(letter) == 'r' || msg.at(letter) == 'R'){
            glVertex2f(1, 0);//top
            glVertex2f(2, 0);
            glVertex2f(2, 1);
            glVertex2f(1, 1);
            glVertex2f(2, 1);//right
            glVertex2f(3, 1);
            glVertex2f(3, 2);
            glVertex2f(2, 2);
            glVertex2f(1, 2);//bottom
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(1, 3);
            glVertex2f(0, 0);//left
            glVertex2f(1, 0);
            glVertex2f(1, 5);
            glVertex2f(0, 5);
            glVertex2f(2, 3);//botright
            glVertex2f(3, 3);
            glVertex2f(3, 5);
            glVertex2f(2, 5);
        }
        if (msg.at(letter) == 's' || msg.at(letter) == 'S'){
            glVertex2f(0, 0);//top
            glVertex2f(3, 0);
            glVertex2f(3, 1);
            glVertex2f(0, 1);
            glVertex2f(0, 1);//left
            glVertex2f(1, 1);
            glVertex2f(1, 2);
            glVertex2f(0, 2);
            glVertex2f(1, 2);//middle
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(1, 3);
            glVertex2f(2, 3);//right
            glVertex2f(3, 3);
            glVertex2f(3, 4);
            glVertex2f(2, 4);
            glVertex2f(0, 4);//bottom
            glVertex2f(3, 4);
            glVertex2f(3, 5);
            glVertex2f(0, 5);
            
        }
        if (msg.at(letter) == 't' || msg.at(letter) == 'T'){
            glVertex2f(0, 0);//top
            glVertex2f(3, 0);
            glVertex2f(3, 1);
            glVertex2f(0, 1);
            glVertex2f(1, 1);//middle
            glVertex2f(2, 1);
            glVertex2f(2, 5);
            glVertex2f(1, 5);
        }
        if (msg.at(letter) == 'u' || msg.at(letter) == 'U'){
            glVertex2f(2, 0);//right
            glVertex2f(3, 0);
            glVertex2f(3, 5);
            glVertex2f(2, 5);
            glVertex2f(1, 4);//bottom
            glVertex2f(2, 4);
            glVertex2f(2, 5);
            glVertex2f(1, 5);
            glVertex2f(0, 0);//left
            glVertex2f(1, 0);
            glVertex2f(1, 4);
            glVertex2f(0, 4);
        }
        if (msg.at(letter) == 'v' || msg.at(letter) == 'V'){
            glVertex2f(2, 0);//right
            glVertex2f(3, 0);
            glVertex2f(3, 4);
            glVertex2f(2, 4);
            glVertex2f(1, 4);//bottom
            glVertex2f(2, 4);
            glVertex2f(2, 5);
            glVertex2f(1, 5);
            glVertex2f(0, 0);//left
            glVertex2f(1, 0);
            glVertex2f(1, 4);
            glVertex2f(0, 4);
        }
        if (msg.at(letter) == 'w' || msg.at(letter) == 'W'){
            glVertex2f(0, 0);//left
            glVertex2f(1, 0);
            glVertex2f(1, 5);
            glVertex2f(0, 5);
            glVertex2f(1, 3);//bridge
            glVertex2f(2, 3);
            glVertex2f(2, 4);
            glVertex2f(1, 4);
            glVertex2f(2, 0);//right
            glVertex2f(3, 0);
            glVertex2f(3, 5);
            glVertex2f(2, 5);
        }
        if (msg.at(letter) == 'x' || msg.at(letter) == 'X'){
            glVertex2f(0, 0);//tl
            glVertex2f(1, 0);
            glVertex2f(1, 2);
            glVertex2f(0, 2);
            glVertex2f(2, 0);//tr
            glVertex2f(3, 0);
            glVertex2f(3, 2);
            glVertex2f(2, 2);
            glVertex2f(1, 2);//middle
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(1, 3);
            glVertex2f(0, 3);//bl
            glVertex2f(1, 3);
            glVertex2f(1, 5);
            glVertex2f(0, 5);
            glVertex2f(2, 3);//br
            glVertex2f(3, 3);
            glVertex2f(3, 5);
            glVertex2f(2, 5);
        }
        if (msg.at(letter) == 'y' || msg.at(letter) == 'Y'){
            glVertex2f(0, 0);//tl
            glVertex2f(1, 0);
            glVertex2f(1, 2);
            glVertex2f(0, 2);
            glVertex2f(2, 0);//tr
            glVertex2f(3, 0);
            glVertex2f(3, 2);
            glVertex2f(2, 2);
            glVertex2f(1, 2);//middle
            glVertex2f(2, 2);
            glVertex2f(2, 5);
            glVertex2f(1, 5);
        }
        if (msg.at(letter) == 'z' || msg.at(letter) == 'Z'){
            glVertex2f(0, 0);//top
            glVertex2f(3, 0);
            glVertex2f(3, 1);
            glVertex2f(0, 1);
            glVertex2f(0, 3);//left
            glVertex2f(1, 3);
            glVertex2f(1, 4);
            glVertex2f(0, 4);
            glVertex2f(1, 2);//middle
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(1, 3);
            glVertex2f(2, 3);//right
            glVertex2f(3, 1);
            glVertex2f(3, 2);
            glVertex2f(2, 2);
            glVertex2f(0, 4);//bottom
            glVertex2f(3, 4);
            glVertex2f(3, 5);
            glVertex2f(0, 5);
        }
        
        
        if (msg.at(letter) == '0'){
            glVertex2f(1, 0);//top
            glVertex2f(2, 0);
            glVertex2f(2, 1);
            glVertex2f(1, 1);
            glVertex2f(2, 1);//right
            glVertex2f(3, 1);
            glVertex2f(3, 4);
            glVertex2f(2, 4);
            glVertex2f(1, 4);//bottom
            glVertex2f(2, 4);
            glVertex2f(2, 5);
            glVertex2f(1, 5);
            glVertex2f(0, 1);//left
            glVertex2f(1, 1);
            glVertex2f(1, 4);
            glVertex2f(0, 4);
        }
        if (msg.at(letter) == '1'){
            glVertex2f(0, 1);//top
            glVertex2f(1, 1);
            glVertex2f(1, 2);
            glVertex2f(0, 2);
            
            glVertex2f(1, 0);//middle
            glVertex2f(2, 0);
            glVertex2f(2, 4);
            glVertex2f(1, 4);
            
            glVertex2f(0, 4);//bottom
            glVertex2f(3, 4);
            glVertex2f(3, 5);
            glVertex2f(0, 5);
        }
        if (msg.at(letter) == '2'){
            glVertex2f(0, 0);//top
            glVertex2f(2, 0);
            glVertex2f(2, 1);
            glVertex2f(0, 1);
            glVertex2f(0, 3);//left
            glVertex2f(1, 3);
            glVertex2f(1, 4);
            glVertex2f(0, 4);
            glVertex2f(1, 2);//middle
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(1, 3);
            glVertex2f(2, 1);//right
            glVertex2f(3, 1);
            glVertex2f(3, 2);
            glVertex2f(2, 2);
            glVertex2f(0, 4);//bottom
            glVertex2f(3, 4);
            glVertex2f(3, 5);
            glVertex2f(0, 5);
        }
        if (msg.at(letter) == '3'){
            glVertex2f(0, 0);//top
            glVertex2f(2, 0);
            glVertex2f(2, 1);
            glVertex2f(0, 1);
            glVertex2f(0, 2);//bridge
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(0, 3);
            glVertex2f(0, 4);//bottom
            glVertex2f(2, 4);
            glVertex2f(2, 5);
            glVertex2f(0, 5);
            glVertex2f(2, 0);//right
            glVertex2f(3, 0);
            glVertex2f(3, 5);
            glVertex2f(2, 5);
        }
        if (msg.at(letter) == '4'){
            glVertex2f(0, 0);//left
            glVertex2f(1, 0);
            glVertex2f(1, 3);
            glVertex2f(0, 3);
            glVertex2f(1, 2);//middle
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(1, 3);
            glVertex2f(2, 0);//right
            glVertex2f(3, 0);
            glVertex2f(3, 5);
            glVertex2f(2, 5);
        }
        if (msg.at(letter) == '5'){
            glVertex2f(0, 0);//top
            glVertex2f(3, 0);
            glVertex2f(3, 1);
            glVertex2f(0, 1);
            glVertex2f(0, 1);//left
            glVertex2f(1, 1);
            glVertex2f(1, 2);
            glVertex2f(0, 2);
            glVertex2f(1, 2);//middle
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(1, 3);
            glVertex2f(2, 3);//right
            glVertex2f(3, 3);
            glVertex2f(3, 4);
            glVertex2f(2, 4);
            glVertex2f(0, 4);//bottom
            glVertex2f(2, 4);
            glVertex2f(2, 5);
            glVertex2f(0, 5);
        }
        if (msg.at(letter) == '6'){
            glVertex2f(1, 2);//top
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(1, 3);
            glVertex2f(2, 2);//right
            glVertex2f(3, 2);
            glVertex2f(3, 4);
            glVertex2f(2, 4);
            glVertex2f(1, 4);//bottom
            glVertex2f(3, 4);
            glVertex2f(3, 5);
            glVertex2f(1, 5);
            glVertex2f(0, 0);//left
            glVertex2f(1, 0);
            glVertex2f(1, 5);
            glVertex2f(0, 5);
        }
        if (msg.at(letter) == '7'){
            glVertex2f(2, 0);//right
            glVertex2f(3, 0);
            glVertex2f(3, 5);
            glVertex2f(2, 5);
            glVertex2f(0, 0);//top
            glVertex2f(2, 0);
            glVertex2f(2, 1);
            glVertex2f(0, 1);
        }
        if (msg.at(letter) == '8'){
            glVertex2f(1, 0);//top
            glVertex2f(2, 0);
            glVertex2f(2, 1);
            glVertex2f(1, 1);
            glVertex2f(1, 2);//bridge
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(1, 3);
            glVertex2f(1, 4);//bottom
            glVertex2f(2, 4);
            glVertex2f(2, 5);
            glVertex2f(1, 5);
            glVertex2f(0, 1);//tleft
            glVertex2f(1, 1);
            glVertex2f(1, 2);
            glVertex2f(0, 2);
            glVertex2f(0, 3);//bleft
            glVertex2f(1, 3);
            glVertex2f(1, 4);
            glVertex2f(0, 4);
            glVertex2f(2, 1);//tright
            glVertex2f(3, 1);
            glVertex2f(3, 2);
            glVertex2f(2, 2);
            glVertex2f(2, 3);//bright
            glVertex2f(3, 3);
            glVertex2f(3, 4);
            glVertex2f(2, 4);
        }
        if (msg.at(letter) == '9'){
            glVertex2f(1, 0);//top
            glVertex2f(2, 0);
            glVertex2f(2, 1);
            glVertex2f(1, 1);
            glVertex2f(1, 0);//left
            glVertex2f(0, 0);
            glVertex2f(0, 3);
            glVertex2f(1, 3);
            glVertex2f(1, 2);//bottom
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(1, 3);
            glVertex2f(2, 0);//right
            glVertex2f(3, 0);
            glVertex2f(3, 5);
            glVertex2f(2, 5);
        }
        
        
        if (msg.at(letter) == '$'){// FLAT
            glVertex2f(1, 2);//top
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(1, 3);
            glVertex2f(2, 3);//right
            glVertex2f(3, 3);
            glVertex2f(3, 4);
            glVertex2f(2, 4);
            glVertex2f(1, 4);//bottom
            glVertex2f(2, 4);
            glVertex2f(2, 5);
            glVertex2f(1, 5);
            glVertex2f(0, 0);//left
            glVertex2f(1, 0);
            glVertex2f(1, 4);
            glVertex2f(0, 4);
        }
        if (msg.at(letter) == '#'){ // SHARP dur
            glVertex2f(0, 0);//left
            glVertex2f(1, 0);
            glVertex2f(1, 5);
            glVertex2f(0, 5);
            glVertex2f(1, 1);//tbridge
            glVertex2f(4, 1);
            glVertex2f(4, 2);
            glVertex2f(1, 2);
            glVertex2f(1, 3);//bbridge
            glVertex2f(4, 3);
            glVertex2f(4, 4);
            glVertex2f(1, 4);
            glVertex2f(2, 0);//right
            glVertex2f(3, 0);
            glVertex2f(3, 5);
            glVertex2f(2, 5);
         }
         
         
        if (msg.at(letter) == '.'){ // fullstop!
            glVertex2f(0, 4);
            glVertex2f(1, 4);
            glVertex2f(1, 5);
            glVertex2f(0, 5);
        }
        
        if (msg.at(letter) == '\''){ // '
            glVertex2f(0, 0);
            glVertex2f(1, 0);
            glVertex2f(1, 2);
            glVertex2f(0, 2);
        }
        
        if (msg.at(letter) == '-'){
            glVertex2f(0, 2);
            glVertex2f(3, 2);
            glVertex2f(3, 3);
            glVertex2f(0, 3);
        }
        
        if (msg.at(letter) == '*'){
            glVertex2f(1, 0);//t
            glVertex2f(2, 0);
            glVertex2f(2, 1);
            glVertex2f(1, 1);
            glVertex2f(1, 2);//b
            glVertex2f(2, 2);
            glVertex2f(2, 3);
            glVertex2f(1, 3);
            glVertex2f(0, 1);//l
            glVertex2f(1, 1);
            glVertex2f(1, 2);
            glVertex2f(0, 2);
            glVertex2f(2, 1);//r
            glVertex2f(3, 1);
            glVertex2f(3, 2);
            glVertex2f(2, 2);
            
        }if (msg.at(letter) == ':'){ // fullstop!
            glVertex2f(0, 4);
            glVertex2f(1, 4);
            glVertex2f(1, 5);
            glVertex2f(0, 5);
            glVertex2f(0, 2);
            glVertex2f(1, 2);
            glVertex2f(1, 3);
            glVertex2f(0, 3);
        }
        
        
        glEnd();
        
        if (msg.at(letter) == '.' || msg.at(letter)== '\''){
            glTranslated(2, 0, 0);
        } else {
            glTranslated(4,0,0);
        }
    }
    glPopMatrix();
}

double TextHeight(int lineheight){
    return lineheight/5;
}
