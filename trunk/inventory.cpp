/*
 *  inventory.cpp
 *  BallDrop
 *
 *  Created by Robin Hayes on 09/05/2010.
 *  Copyright 2010 Propellor and Ratchet Games. All rights reserved.
 *
 */
#include <string>
#include <sstream>
#include <map>
#include <list>
#include <iostream>

#include "inventory.h"
#include "text.h"
#include "items.h"
using namespace std;


string tostring(int number){
    string s;
    stringstream out;
    out << number;
    return out.str();
}



Inventory::Inventory(int glocation){
    nextdown = Tileinfo();
    currentpage = 0;
    location = glocation;
    active = true;//oh look an inventory, guess I move my mouse over there to get it.
    
    hitstodie = 0;
    
    things.push_back(thing);//initial menu.
    
    things[0].push_back(0);//big line
    things[0].push_back(1);//big block
    
    things.push_back(thing);//line menu.
    things[1].push_back(2);// back button
    for (int i = 3; i < 15; i++){ 
        things[1].push_back(i);//line shapes
    }
    
    things.push_back(thing);//block menu
    things[2].push_back(2);//back
    things[2].push_back(15);//static 15
    things[2].push_back(16);//modifier 16
    things[2].push_back(17);//creator 17
    things[2].push_back(18);//destroyer 18
    
    things.push_back(thing);//static block menu
    things[3].push_back(2);//back
    things[3].push_back(19);//hitstodie down 19
    things[3].push_back(21);//hitsdie display 21
    things[3].push_back(20);//hitstodie up 20
    things[3].push_back(22);//static block lul 22
    
    things.push_back(thing);//modifier block menu
    things[4].push_back(2);//back
    //hitstodie down 19
    //hitsdie display 21
    //hitstodie up 20
    //collides checkbox 23
    // change note to 24
    //note up 25
    //note down 26
    // change octave 27
    //octave up 28
    //octave down 29
    // change instrument 30 <- give a limited choice for now. Glock, xy, pinano, drum?
    //instr up 31
    //instr down 32
    // modifier block lul 33
    
    things.push_back(thing);//modifier block menu
    things[5].push_back(2);//back
    //hitstodie down 19
    //hitsdie display 21
    //hitstodie up 20
    //collides checkbox 23
    //emits display 34
    //emits up 35
    //emits down 36
    //creator block lul 37
    
    things.push_back(thing);//modifier block menu
    things[6].push_back(2);//back
    //hitstodie down 19
    //hitsdie display 21
    //hitstodie up 20
    //collides checkbox 23
    // destroyer block lul 38
    
    
    /*for (int i = 2; i < 50; i++){
        pages[0][i] = -1;
    }*/
    
    width = 150;
    //balls to it, pass W_HEIGHT to this somewhere I guess, for top or bottom. But later.
    
}

void Inventory::update(string action, int x, int y, int W_WIDTH, int W_HEIGHT, int xmod = 0, int ymod = 0){
            //update with clicks and actions
    int relx = x - W_WIDTH + width;
    
    if (action == "click"){
        for (int i = 0; i < (int)things[currentpage].size(); i++){
            //for thing in this page
            //cout << "KLIKU"<<things[currentpage][i]<<"\n";
            
            //
            cout << relx << ", " << y << " to " <<
            buttonarea(things[currentpage][i], 0, W_WIDTH, W_HEIGHT, xmod, ymod) <<", "<<
            buttonarea(things[currentpage][i], 1, W_WIDTH, W_HEIGHT, xmod, ymod) <<", "<<
            buttonarea(things[currentpage][i], 2, W_WIDTH, W_HEIGHT, xmod, ymod) <<", "<<
            buttonarea(things[currentpage][i], 3, W_WIDTH, W_HEIGHT, xmod, ymod) <<"\n";
            
            if (relx-xmod >= buttonarea(things[currentpage][i], 0, W_WIDTH, W_HEIGHT, xmod, ymod) &&
                relx-xmod <= buttonarea(things[currentpage][i], 2, W_WIDTH, W_HEIGHT, xmod, ymod) &&
                y-ymod >= buttonarea(things[currentpage][i], 1, W_WIDTH, W_HEIGHT, xmod, ymod) &&
                y-ymod <= buttonarea(things[currentpage][i], 3, W_WIDTH, W_HEIGHT, xmod, ymod)){
                
                buttonfunction(things[currentpage][i]);
                
            }
            
            
        }
        
    } else  if (action == "drag"){
    
    } else if (action == "rightclick"){
    
    } // I dunno
}

void Inventory::draw(int W_WIDTH, int W_HEIGHT, int xmod, int ymod){
            // draw the G and the buttons.
    GLfloat adarkblue[]  = {0.03, 0.15, 0.53, 1};
    GLfloat alightblue[] = {0.37, 0.65, 0.94, 1};
    glPushMatrix();
    if (active == false){
       
            glTranslated(W_WIDTH-20+xmod, 0+ymod, 0);// 0 or 1 for z? or what?
            
            glBegin(GL_QUADS);
            glColor4f(adarkblue[0], adarkblue[1], adarkblue[2], adarkblue[3]);
                glVertex2f(0,0);
                glVertex2f(20,0);
                glVertex2f(20,W_HEIGHT);
                glVertex2f(0,W_HEIGHT);
            glEnd();
            
            glBegin(GL_LINE_LOOP);
            glColor4f(alightblue[0], alightblue[1], alightblue[2], alightblue[3]);
                glVertex2f(7,W_HEIGHT/2-5);
                glVertex2f(14,W_HEIGHT/2+1);
                glVertex2f(7,W_HEIGHT/2+7);
            glEnd();
            
    } else {
    
        glTranslated(W_WIDTH-150+xmod, 0+ymod, 0);
    
        glBegin(GL_QUADS);
            glColor4f(adarkblue[0], adarkblue[1], adarkblue[2], adarkblue[3]);
            glVertex2f(0,0);
            glVertex2f(150,0);
            glVertex2f(150,W_HEIGHT);
            glVertex2f(0,W_HEIGHT);
        glEnd();
        
    
        glBegin(GL_LINE_LOOP);
            glColor4f(alightblue[0], alightblue[1], alightblue[2], alightblue[3]);
            glVertex2f(14,W_HEIGHT/2-5);
            glVertex2f(7,W_HEIGHT/2+1);
            glVertex2f(14,W_HEIGHT/2+7);
        glEnd();

        Text("Inventory", 4, 4, 3, 1,1,1);
        
        
        for (int i = 0; i < (int)things[currentpage].size(); i ++){
            buttonGet(things[currentpage][i], W_WIDTH, W_HEIGHT, xmod, ymod);
        }
        
    }
    
    
    glPopMatrix();
}


void Inventory::buttonGet(int num, int W_WIDTH, int W_HEIGHT, int xmod = 0, int ymod = 0){
            // display the button with the details from its area func.
    buttondisplay(num, buttonarea(num, 0, W_WIDTH, W_HEIGHT, xmod, ymod), buttonarea(num, 1, W_WIDTH, W_HEIGHT, xmod, ymod));
}

void Inventory::buttondisplay(int num, int xoff, int yoff){
            //display the button
    GLfloat black[]      = {0,0,0, 1};
    GLfloat linecolour[] = {0,1,0, 1};
    GLfloat blockcolour[] = {1,0,0, 1};
    GLfloat adarkblue[]  = {0.03, 0.15, 0.53, 1};
    GLfloat alightblue[] = {0.37, 0.65, 0.94, 1};
    int angle;
    if (num==0){
        //big line
        //glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
        glBegin(GL_QUADS);
        glColor4f(black[0], black[1], black[2], black[3]);
            glVertex2f(xoff+0,yoff+0);
            glVertex2f(xoff+100,yoff+0);
            glVertex2f(xoff+100,yoff+100);
            glVertex2f(xoff+0,yoff+100);
        glEnd();
        Text("Line", xoff, yoff, TextHeight(10));
        drawLine(80, linecolour, 0, 1, 1, 0, 10+xoff, yoff+10);  
    } else if (num == 1){
        //big block
        //glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
        glBegin(GL_QUADS);
        glColor4f(black[0], black[1], black[2], black[3]);
            glVertex2f(xoff+0,yoff+0);
            glVertex2f(xoff+100,yoff+0);
            glVertex2f(xoff+100,yoff+100);
            glVertex2f(xoff+0,yoff+100);
        glEnd();
        Text("Block", xoff, yoff, TextHeight(10));
        drawBlock(80, blockcolour, 0, 10+xoff, yoff+10);
    } else if (num == 2){
        //back button
        //glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
        glBegin(GL_QUADS);
            glColor4f(black[0], black[1], black[2], black[3]);
            glVertex2f(xoff,yoff+0);
            glVertex2f(xoff+50,yoff+0);
            glVertex2f(xoff+50,yoff+30);
            glVertex2f(xoff,yoff+30);
        glEnd();
        //glMaterialfv(GL_FRONT, GL_DIFFUSE, alightblue);
        glBegin(GL_LINE_LOOP);
            glColor4f(alightblue[0], alightblue[1], alightblue[2], alightblue[3]);
            glVertex2f(xoff+15,yoff+2);
            glVertex2f(xoff+15,yoff+28);
            glVertex2f(xoff+3,yoff+15);
        glEnd();
            Text("Back", xoff+16, yoff+15-5, TextHeight(10));
        
        switch (currentpage){
            case 1:
                Text("Lines", xoff, yoff+38, 3);
                break;
            case 2:
                Text("Blocks", xoff-10, yoff+38, 3);
                break;
            case 3:
                Text("Normal", xoff-10, yoff+38, 3);
                break;
            case 4:
                Text("Changer", xoff-16, yoff+38, 3);
                break;
            case 5:
                Text("Creator", xoff-16, yoff+38, 3);
                break;
            case 6:
                Text("Destroyer", xoff-28, yoff+38, 3);
                break;
        }
                
        
            
    } else if (num >= 3 && num <=14){
        glBegin(GL_QUADS);
        glColor4f(black[0], black[1], black[2], black[3]);
            glVertex2f(xoff-2,yoff-2);
            glVertex2f(xoff+52,yoff-2);
            glVertex2f(xoff+52,yoff+52);
            glVertex2f(xoff-2,yoff+52);
        glEnd();
        angle = 0+ ((num-3)*15);
        drawLine(50, linecolour, angle, xoff, yoff);
    } else if (num >= 15 && num <= 18){
        glBegin(GL_QUADS);
        glColor4f(black[0], black[1], black[2], black[3]);
            glVertex2f(xoff-0,yoff-0);
            glVertex2f(xoff+80,yoff-0);
            glVertex2f(xoff+80,yoff+80);
            glVertex2f(xoff-0,yoff+80);
        glEnd();
        drawBlock(60, blockcolour, 0, xoff+10, yoff+10);
        if (num == 15){
            Text("Normal", xoff+16, yoff, TextHeight(10));
        } else if (num == 16){
            Text("Changer", xoff+12, yoff, TextHeight(10));
        } else if (num == 17){
            Text("Creator", xoff+12, yoff, TextHeight(10));
        } else if (num == 18){
            Text("Destroyer", xoff+4, yoff, TextHeight(10));
        }
    }
}

int Inventory::buttonarea(int num, int part, int W_WIDTH, int W_HEIGHT, int xmod=0, int ymod=0){
        //get the button's position and area
    int arraytoreturn[4]; //x1, y1, x2, y2
    
    int adjustx = 0;
    int adjusty = 0;
    
    //LINE MENU stuff
    if (num >= 3 && num <=14){
        adjustx += 25;
        adjusty += 100;
    }
    if (num >= 3 && num <=8){
        adjusty += (num-3)*80;
    }
    if (num >= 9 && num <=14){
        adjusty += (num-9)*80;
        adjustx += 60;
    }
    
    //BLOCK MENU stuff
    if (num >= 15 && num <= 18){
        adjustx += 35;
        adjusty += 120;
        
        adjusty +=(num-15)*100;
    }
    
    if (num == 0){
        arraytoreturn[0] = 25;
        arraytoreturn[1] = W_HEIGHT/2-150;
        arraytoreturn[2] = 25+100;
        arraytoreturn[3] = W_HEIGHT/2-150+100;
    } else if (num == 1){
        arraytoreturn[0] = 25;
        arraytoreturn[1] = W_HEIGHT/2+50;
        arraytoreturn[2] = 25+100;
        arraytoreturn[3] = W_HEIGHT/2+50+100;
    } else if (num == 2){
        arraytoreturn[0] = 75-25;
        arraytoreturn[1] = 30;
        arraytoreturn[2] = 75-25+50;
        arraytoreturn[3] = 30+30;
    } else if (num >= 3 && num <=14){
        arraytoreturn[0] = adjustx;
        arraytoreturn[1] = adjusty;
        arraytoreturn[2] = adjustx+50;
        arraytoreturn[3] = adjusty+50;
    } else if (num >= 15 && num <= 18){
        arraytoreturn[0] = adjustx;
        arraytoreturn[1] = adjusty;
        arraytoreturn[2] = adjustx+80;
        arraytoreturn[3] = adjusty+80;
    }
    return arraytoreturn[part];
}

void Inventory::buttonfunction(int num){
        // what happens when you click a button.
    if (num == 0){
        currentpage = 1;//line menu
        
    }else if (num == 1){
        currentpage = 2;//block menu
        
    } else if (num == 2){
        if (currentpage == 1 || currentpage == 2){
            currentpage = 0; //back button to main
        } else if (currentpage == 3||currentpage == 4||currentpage == 5||currentpage == 6){
            currentpage = 2;
        }
        
    } else if (num >= 3 && num <=14){ // line buttons
        nextdown.type = 1;
        nextdown.func = 0;
        nextdown.extra = tostring(( 0+ ((num-3)*15) ));
        
    } else if (num >=15 && num <=18){ //block buttons -> submenus
        currentpage = num- 12;//? is this right?
        cout << "Going to " << currentpage << "\n";
        
    } else if (num == 19){// hitstodie down
        if (hitstodie > 0){
            hitstodie --;
        }
        
    } else if (num == 20){// hitstodie up
        hitstodie++;
        
    // 21: hitstodie display has no click function, yet.
    
    } else if (num >= 22 && num <= 25){ // put down a static block.
        nextdown.type = 2;
        nextdown.hitstodie = hitstodie;
        if (num == 22){
            nextdown.func = 0;
            nextdown.extra = "0";
        }
    }
    
}
