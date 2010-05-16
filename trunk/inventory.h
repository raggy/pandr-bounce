/*
 *  inventory.h
 *  BallDrop
 *
 *  Created by Robin Hayes on 09/05/2010.
 *  Copyright 2010 Propellor and Ratchet Games. All rights reserved.
 *
 */
#include <OpenGL/OpenGL.h>
#include <string>
#include <vector>
using namespace std;

#ifndef INVENTLOL
#define INVENTLOL

struct Tileinfo{
    public:
        int type;
        int func;
        string extra;
        Tileinfo(){
            type=1;
            func=0;
            extra="0";
        }
};

string tostring(int number);

class Inventory {
    public:
        Tileinfo nextdown;
        bool active;
        int currentpage;
        int location; //0123 = t r b l
        int width;
        GLfloat black[];
        GLfloat adarkblue[];
        GLfloat alightblue[];
        GLfloat linecolour[];
        GLfloat blockcolour[];
        
        vector <int> thing;
        
        vector < vector <int> > things;
        
        Inventory(int glocation);
        
        void update(string action, int x, int y, int W_WIDTH, int W_HEIGHT);
        
        void draw(int W_WIDTH, int W_HEIGHT);
        
        void buttonGet(int num, int W_WIDTH, int W_HEIGHT);
        
        void buttondisplay(int num, int xoff, int yoff);
        int buttonarea(int num, int part, int W_WIDTH, int W_HEIGHT);
        void buttonfunction(int num);
};
#endif