/*
 *  inventory.cpp
 *  BallDrop
 *
 *  Created by Robin Hayes on 09/05/2010.
 *  Copyright 2010 Propellor and Ratchet Games. All rights reserved.
 *
 */
#include <OpenGL/OpenGL.h>
#include <string>
#include <map>
#include <list>
#include <iostream>

#include "inventory.h"
#include "text.h"
#include "items.h"
using namespace std;


Inventory::Inventory(int glocation){
    currentpage = 0;
    location = glocation;
    active = true;//oh look an inventory, guess I move my mouse over there to get it.
    
    
    things.push_back(thing);
    
    things[0].push_back(0);//big line
    things[0].push_back(1);//big block
    
    things.push_back(thing);
    things[1].push_back(2);// back to main
    
    things.push_back(thing);
    things[2].push_back(2);
    
    
    /*for (int i = 2; i < 50; i++){
        pages[0][i] = -1;
    }*/
    
    width = 150;
    //balls to it, pass W_HEIGHT to this somewhere I guess, for top or bottom. But later.
    
}

void Inventory::update(string action, int x, int y, int W_WIDTH, int W_HEIGHT){
    int relx = x - W_WIDTH + width;
    
    if (action == "click"){
        for (int i = 0; i < (int)things[currentpage].size(); i++){
            //for thing in this page
            //cout << "KLIKU"<<things[currentpage][i]<<"\n";
            
            //
            cout << relx << ", " << y << " to " <<
            buttonarea(things[currentpage][i], 0, W_WIDTH, W_HEIGHT) <<", "<<
            buttonarea(things[currentpage][i], 1, W_WIDTH, W_HEIGHT) <<", "<<
            buttonarea(things[currentpage][i], 2, W_WIDTH, W_HEIGHT) <<", "<<
            buttonarea(things[currentpage][i], 3, W_WIDTH, W_HEIGHT) <<"\n";
            
            if (relx >= buttonarea(things[currentpage][i], 0, W_WIDTH, W_HEIGHT) &&
                relx <= buttonarea(things[currentpage][i], 2, W_WIDTH, W_HEIGHT) &&
                y >= buttonarea(things[currentpage][i], 1, W_WIDTH, W_HEIGHT) &&
                y <= buttonarea(things[currentpage][i], 3, W_WIDTH, W_HEIGHT)){
                
                buttonfunction(things[currentpage][i]);
                
            }
            
            
        }
        
    } else  if (action == "drag"){
    
    } else if (action == "rightclick"){
    
    } // I dunno
}

void Inventory::draw(int W_WIDTH, int W_HEIGHT){
    GLfloat adarkblue[]  = {0.03, 0.15, 0.53, 1};
    GLfloat alightblue[] = {0.37, 0.65, 0.94, 1};
    glPushMatrix();
    if (active == false){
       
            glTranslated(W_WIDTH-20, 0, 0);// 0 or 1 for z? or what?
            
            glMaterialfv(GL_FRONT, GL_DIFFUSE, adarkblue);
            glBegin(GL_QUADS);
                glVertex2f(0,0);
                glVertex2f(20,0);
                glVertex2f(20,W_HEIGHT);
                glVertex2f(0,W_HEIGHT);
            glEnd();
            
            glMaterialfv(GL_FRONT, GL_DIFFUSE, alightblue);
            glBegin(GL_LINE_LOOP);
                glVertex2f(7,W_HEIGHT/2-5);
                glVertex2f(14,W_HEIGHT/2+1);
                glVertex2f(7,W_HEIGHT/2+7);
            glEnd();
            
    } else {
    
        glTranslated(W_WIDTH-150, 0, 0);
    
        glMaterialfv(GL_FRONT, GL_DIFFUSE, adarkblue);
        glBegin(GL_QUADS);
            glVertex2f(0,0);
            glVertex2f(150,0);
            glVertex2f(150,W_HEIGHT);
            glVertex2f(0,W_HEIGHT);
        glEnd();
        
    
        glMaterialfv(GL_FRONT, GL_DIFFUSE, alightblue);
        glBegin(GL_LINE_LOOP);
            glVertex2f(14,W_HEIGHT/2-5);
            glVertex2f(7,W_HEIGHT/2+1);
            glVertex2f(14,W_HEIGHT/2+7);
        glEnd();

        Text("Inventory", 4, 4, 3, 1,1,1);
        
        
        //cout <<"draw "<< W_WIDTH<< ", "<< W_HEIGHT << "\n";
        
        for (int i = 0; i < (int)things[currentpage].size(); i ++){
            //cout << i << "\n";
            buttonGet(things[currentpage][i], W_WIDTH, W_HEIGHT);
        }
        
    }
    
    
    glPopMatrix();
}


void Inventory::buttonGet(int num, int W_WIDTH, int W_HEIGHT){
    //cout <<"get "<< W_WIDTH<< ", "<< W_HEIGHT << "\n";
    buttondisplay(num, buttonarea(num, 0, W_WIDTH, W_HEIGHT), buttonarea(num, 1, W_WIDTH, W_HEIGHT));
}

void Inventory::buttondisplay(int num, int xoff, int yoff){
    //cout<< "display "<< xoff<< ", "<< yoff << "\n";
    GLfloat black[]      = {0,0,0, 1};
    GLfloat linecolour[] = {0,1,0, 1};
    GLfloat blockcolour[] = {1,0,0, 1};
    GLfloat adarkblue[]  = {0.03, 0.15, 0.53, 1};
    GLfloat alightblue[] = {0.37, 0.65, 0.94, 1};
    if (num==0){
        //big line
        glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
        glBegin(GL_QUADS);
            glVertex2f(xoff+0,yoff+0);
            glVertex2f(xoff+100,yoff+0);
            glVertex2f(xoff+100,yoff+100);
            glVertex2f(xoff+0,yoff+100);
        glEnd();
        Text("Line", xoff, yoff, TextHeight(10));
        drawLine(80, linecolour, 0, 1, 1, 0, 10+xoff, yoff+10);  
    } else if (num == 1){
        //big block
        glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
        glBegin(GL_QUADS);
            glVertex2f(xoff+0,yoff+0);
            glVertex2f(xoff+100,yoff+0);
            glVertex2f(xoff+100,yoff+100);
            glVertex2f(xoff+0,yoff+100);
        glEnd();
        Text("Block", xoff, yoff, TextHeight(10));
        drawBlock(80, blockcolour, 0, 10+xoff, yoff+10);
    } else if (num == 2){
        //back button
        glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
        glBegin(GL_QUADS);
            glVertex2f(xoff,yoff+0);
            glVertex2f(xoff+50,yoff+0);
            glVertex2f(xoff+50,yoff+30);
            glVertex2f(xoff,yoff+30);
        glEnd();
        glMaterialfv(GL_FRONT, GL_DIFFUSE, alightblue);
        glBegin(GL_LINE_LOOP);
            glVertex2f(xoff+15,yoff+2);
            glVertex2f(xoff+15,yoff+28);
            glVertex2f(xoff+3,yoff+15);
        glEnd();
            Text("Back", xoff+16, yoff+15-5, TextHeight(10));
    }
}

int Inventory::buttonarea(int num, int part, int W_WIDTH, int W_HEIGHT){
    int arraytoreturn[4]; //x1, y1, x2, y2
    switch (num){
        case (0):
            arraytoreturn[0] = 25;
            arraytoreturn[1] = W_HEIGHT/2-150;
            arraytoreturn[2] = 25+100;
            arraytoreturn[3] = W_HEIGHT/2-150+100;
            break;
        case (1):
            arraytoreturn[0] = 25;
            arraytoreturn[1] = W_HEIGHT/2+50;
            arraytoreturn[2] = 25+100;
            arraytoreturn[3] = W_HEIGHT/2+50+100;
            break;
        case (2):
            arraytoreturn[0] = 75-25;
            arraytoreturn[1] = 30;
            arraytoreturn[2] = 75-25+50;
            arraytoreturn[3] = 30+30;
            break;
    }
    return arraytoreturn[part];
}

void Inventory::buttonfunction(int num){
    if (num == 0){
        cout << "COCKS\n";
        currentpage = 1;
    }else if (num == 1){
        cout << "DICKS\n";
        currentpage = 2;
    } else if (num == 2){
        currentpage = 0; 
    }
}
