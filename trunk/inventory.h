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
class Inventory {
    public:
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