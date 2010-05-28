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
    theparts = Particles();
    nextdown = Tileinfo();
    oldnextdown = Tileinfo();
    currentpage = 0;
    location = glocation;
    active = true;//oh look an inventory, guess I move my mouse over there to get it.
    
    hitstodie = 0;
    collides = 1;
    note = "C";
    octave = 4;
    instrument[10] = "Steel Drums";
    instrument[13] = "Xylophone";
    instrument[1] = "Piano";
    theinstrument = 13;
    ballevery = 2.0;
    
    
    black[0]=0; black[1]=0; black[2]=0; black[3]=1;
    white[0]=1; white[1]=1; white[2]=1; white[3]=1;
    linecolour[0]=0; linecolour[1]=1; linecolour[2]=0; linecolour[3]=1;
    blockcolour[0]=1; blockcolour[1]=0; blockcolour[2]=0; blockcolour[3]=1;
    adarkblue[0]=0.03; adarkblue[1]=0.15; adarkblue[2]=0.53; adarkblue[3]=1;
    alightblue[0]=0.37; alightblue[1]=0.65; alightblue[2]=0.94; alightblue[3]=1;
    
    
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
    things[3].push_back(23);//collides checkbox 23
    //things[3].push_back(22);//static block lul 22
    
    things.push_back(thing);//modifier block menu
    things[4].push_back(2);//back
    things[4].push_back(19);//hitstodie down 19
    things[4].push_back(21);//hitsdie display 21
    things[4].push_back(20);//hitstodie up 20
    things[4].push_back(23);//collides checkbox 23
    things[4].push_back(24);// display note 24
    things[4].push_back(25);//note up 25
    things[4].push_back(26);//note down 26
    things[4].push_back(27);// display octave 27
    things[4].push_back(28);//octave up 28
    things[4].push_back(29);//octave down 29
    things[4].push_back(30);// instrument display 30 <- give a limited choice for now. Glock, xy, pinano, drum?
    things[4].push_back(31);//instr up 31
    things[4].push_back(32);//instr down 32
    //things[4].push_back(33);// modifier block lul 33
    
    things.push_back(thing);//creator block menu
    things[5].push_back(2);//back
    things[5].push_back(19);//hitstodie down 19
    things[5].push_back(21);//hitsdie display 21
    things[5].push_back(20);//hitstodie up 20
    things[5].push_back(23);//collides checkbox 23
    things[5].push_back(24);// display note 24
    things[5].push_back(25);//note up 25
    things[5].push_back(26);//note down 26
    things[5].push_back(27);// display octave 27
    things[5].push_back(28);//octave up 28
    things[5].push_back(29);//octave down 29
    things[5].push_back(30);// instrument display 30 <- give a limited choice for now. Glock, xy, pinano, drum?
    things[5].push_back(31);//instr up 31
    things[5].push_back(32);//instr down 32
    things[5].push_back(34);//emits display 34 <- scale should be 2s default. down to 0.5s, up to 5s.
    things[5].push_back(35);//emits up 35
    things[5].push_back(36);//emits down 36
    //things[5].push_back(37);//creator block lul 37
    
    things.push_back(thing);//destroyer block menu
    things[6].push_back(2);//back
    things[6].push_back(19);//hitstodie down 19
    things[6].push_back(21);//hitsdie display 21
    things[6].push_back(20);//hitstodie up 20
    things[6].push_back(23);//collides checkbox 23
    //things[6].push_back(38);// destroyer block lul 38
    
    
    /*for (int i = 2; i < 50; i++){
        pages[0][i] = -1;
    }*/
    
    width = 150;
    //balls to it, pass W_HEIGHT to this somewhere I guess, for top or bottom. But later.
    
}

void Inventory::update(string action, int x, int y, int &W_WIDTH, int &W_HEIGHT, int xmod, int ymod, int &TILESIZE){
            //update with clicks and actions
            
    
        int relx = x - W_WIDTH + width;
        if (action == "click"){
            for (int i = 0; i < (int)things[currentpage].size(); i++){
                //for thing in this page
                //cout << "KLIKU"<<things[currentpage][i]<<"\n";
                
                //
                /*cout << relx << ", " << y << " to " <<
                buttonarea(things[currentpage][i], 0, W_WIDTH, W_HEIGHT, xmod, ymod) <<", "<<
                buttonarea(things[currentpage][i], 1, W_WIDTH, W_HEIGHT, xmod, ymod) <<", "<<
                buttonarea(things[currentpage][i], 2, W_WIDTH, W_HEIGHT, xmod, ymod) <<", "<<
                buttonarea(things[currentpage][i], 3, W_WIDTH, W_HEIGHT, xmod, ymod) <<"\n";*/
                
                if (relx-xmod >= buttonarea(things[currentpage][i], 0, W_WIDTH, W_HEIGHT, xmod, ymod) &&
                    relx-xmod <= buttonarea(things[currentpage][i], 2, W_WIDTH, W_HEIGHT, xmod, ymod) &&
                    y-ymod >= buttonarea(things[currentpage][i], 1, W_WIDTH, W_HEIGHT, xmod, ymod) &&
                    y-ymod <= buttonarea(things[currentpage][i], 3, W_WIDTH, W_HEIGHT, xmod, ymod)){
                    
                    buttonfunction(things[currentpage][i]);
                    /*if ((things[currentpage][i] >= 15 && things[currentpage][i] <= 18) || things[currentpage][i] == 37 || things[currentpage][i] == 38){
                        theparts.add("burst", 20/TILESIZE, (W_HEIGHT-20)/TILESIZE, 0, 0, 1.0, 0.6, 0.6);
                    }
                    if (things[currentpage][i] >= 3 && things[currentpage][i] <=14){
                        theparts.add("burst", 20/TILESIZE, (W_HEIGHT-20)/TILESIZE, 0, 0, 0.6, 1.0, 0.6);
                    }*/
                    break;
                    
                }
                
                
            }
            
        } else  if (action == "drag"){
        
        } else if (action == "rightclick"){
        
        } // I dunno
    
}

void Inventory::particlesdraw(int &elapsed_time, int &TILESIZE, float &gravity){
    int lol = 10;
    if (theparts.getSize() != 0){
        theparts.draw(elapsed_time, lol, gravity);
    }
}

void Inventory::draw(int &W_WIDTH, int &W_HEIGHT, int xmod, int ymod, int stuff){
            // draw the G and the buttons.
    
    
    //the next display
    if ((oldnextdown.type != nextdown.type) || (oldnextdown.func != nextdown.func)
    || (oldnextdown.extra != nextdown.extra) || (oldnextdown.hitstodestroy != nextdown.hitstodestroy)){
        oldnextdown = nextdown;
        if (nextdown.type == 1){
            theparts.add("burst", 20/10+xmod, (W_HEIGHT-20)/10+ymod, 0, 0, 0.6, 1.0, 0.6);
        } else {
            theparts.add("burst", 20/10+xmod, (W_HEIGHT-20)/10+ymod, 0, 0, 1.0, 0.6, 0.6);
        }
    }
    
    glPushMatrix();
        glTranslated(0+xmod, W_HEIGHT-60+ymod, 0);// 0 or 1 for z? or what?
            
        glBegin(GL_QUADS);
        glColor4f(adarkblue[0], adarkblue[1], adarkblue[2], adarkblue[3]);
            glVertex2f(0,0);
            glVertex2f(120,0);
            glVertex2f(120,60);
            glVertex2f(0,60);
        glColor4f(0,0,0,1);
            glVertex2f(2,22);
            glVertex2f(38,22);
            glVertex2f(38,58);
            glVertex2f(2,58);
        glEnd();
    
    glPopMatrix();
    
    if (nextdown.type == 1){   
        drawLine(30, linecolour, atoi(nextdown.extra.c_str()), 5+xmod, W_HEIGHT-35+ymod);
    } else {
        
        if (nextdown.hitstodestroy != 0){
            drawBlockGlow(30, 0, 1, 0, 5+xmod, W_HEIGHT-35+ymod);
        }
        if ((nextdown.func == 2 || nextdown.func == 0) && nextdown.hitstodestroy != 0){
            drawBlock(30, blockcolour, nextdown.func, 5+xmod, W_HEIGHT-35+ymod, itostring(nextdown.hitstodestroy));
        } else if (nextdown.func == 1 || nextdown.func == 3){
            drawBlock(30, blockcolour, nextdown.func, 5+xmod, W_HEIGHT-35+ymod, note+itostring(octave));
        } else {
            drawBlock(30, blockcolour, nextdown.func, 5+xmod, W_HEIGHT-35+ymod);
        }
        
        if (!collides){
            drawBlockGhost(30, 5+xmod, W_HEIGHT-35+ymod);
        }
    }
    

    Text("Next:", 2+xmod, W_HEIGHT-58+ymod, 2, white);
    if (nextdown.type == 1){
        Text("Line", 40+xmod, W_HEIGHT-58+ymod, 2, linecolour);
        Text("Angle: ", 42+xmod, W_HEIGHT-35+ymod, 2, white);
        Text(nextdown.extra+"*", 60+xmod, W_HEIGHT-20+ymod, 2, white);
    } else if (nextdown.type == 2){
        if (nextdown.func == 0){
            Text("Block", 40+xmod, W_HEIGHT-58+ymod, 2, blockcolour);
        } else if (nextdown.func == 3){
            Text("Changer", 40+xmod, W_HEIGHT-58+ymod, 2, blockcolour);
            Text("Instrument:", 45+xmod, W_HEIGHT-40+ymod, 1, white);
            Text(instrument[theinstrument], 45+xmod, W_HEIGHT-32+ymod, 1, white);
            
        } else if (nextdown.func == 1){
            Text("Creator", 40+xmod, W_HEIGHT-58+ymod, 2, blockcolour);
            
            Text("Instrument:", 45+xmod, W_HEIGHT-40+ymod, 1, white);
            Text(instrument[theinstrument], 45+xmod, W_HEIGHT-32+ymod, 1, white);
            
            Text("Interval:", 45+xmod, W_HEIGHT-22+ymod, 1, white);
            Text(ftostring(ballevery)+" seconds", 45+xmod, W_HEIGHT-14+ymod, 1, white);
            
        } else if (nextdown.func == 2){
            Text("Detroyer", 45+xmod, W_HEIGHT-58+ymod, 2, blockcolour);
        }
            
            
    
    }
    
    
    
    
    
    
    
    //the inventory itself
    
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
        
        /*if (stuff==0){
            glTranslated(W_WIDTH-150+xmod, 0+ymod, 0);
        }*/
        
        
        
        for (int i = 0; i < things[currentpage].size(); i ++){
            buttonGet(things[currentpage][i], W_WIDTH, W_HEIGHT, xmod, ymod);
        }
    }
    
    
    glPopMatrix();
}


void Inventory::buttonGet(int &num, int &W_WIDTH, int &W_HEIGHT, int xmod, int ymod){
            // display the button with the details from its area func.
    buttondisplay(num, buttonarea(num, 0, W_WIDTH, W_HEIGHT, xmod, ymod), buttonarea(num, 1, W_WIDTH, W_HEIGHT, xmod, ymod));
}

void Inventory::buttondisplay(int &num, int xoff, int yoff){
            //display the button
   
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
    } else if ((num >= 15 && num <= 18)){// || num == 22 || num == 33 || num == 37 || num == 38){
        glBegin(GL_QUADS);
        glColor4f(black[0], black[1], black[2], black[3]);
            glVertex2f(xoff-0,yoff-0);
            glVertex2f(xoff+80,yoff-0);
            glVertex2f(xoff+80,yoff+80);
            glVertex2f(xoff-0,yoff+80);
        glEnd();
        if (num == 15){
            drawBlock(60, blockcolour, 0, xoff+10, yoff+10);
            Text("Normal", xoff+16, yoff, TextHeight(10));
        } else if (num == 16){
            drawBlock(60, blockcolour, 3, xoff+10, yoff+10);   
            Text("Changer", xoff+12, yoff, TextHeight(10));
        } else if (num == 17){
            drawBlock(60, blockcolour, 1, xoff+10, yoff+10);
            Text("Creator", xoff+12, yoff, TextHeight(10));
        } else if (num == 18){
            drawBlock(60, blockcolour, 2, xoff+10, yoff+10);    
            Text("Destroyer", xoff+4, yoff, TextHeight(10));
        }/* else if (num == 22 || num == 33 || num == 37 || num == 38){
            Text("Finalise", xoff+8, yoff, TextHeight(10));
        }*/
    } else if (num == 19 || num == 20 || num == 35 || num == 36){ //minus and plus signs
        glBegin(GL_QUADS);
        glColor4f(black[0], black[1], black[2], black[3]);
            glVertex2f(xoff+0,yoff+0);
            glVertex2f(xoff+20,yoff+0);
            glVertex2f(xoff+20,yoff+30);
            glVertex2f(xoff+0,yoff+30);
        glColor4f(alightblue[0], alightblue[1], alightblue[2], alightblue[3]);
            glVertex2f(xoff+3,yoff+13);
            glVertex2f(xoff+17,yoff+13);
            glVertex2f(xoff+17,yoff+17);
            glVertex2f(xoff+3,yoff+17);
        if (num == 20 || num == 35){
            glVertex2f(xoff+8,yoff+8);
            glVertex2f(xoff+12,yoff+8);
            glVertex2f(xoff+12,yoff+22);
            glVertex2f(xoff+8,yoff+22);
        }
        glEnd();
    } else if (num == 21){
        glBegin(GL_QUADS);
        glColor4f(black[0], black[1], black[2], black[3]);
            glVertex2f(xoff+0,yoff+0);
            glVertex2f(xoff+40,yoff+0);
            glVertex2f(xoff+40,yoff+30);
            glVertex2f(xoff+0,yoff+30);
        glEnd();
        
        Text("Hits to destroy", xoff-10, yoff-10);
        
        if (hitstodie>=10){
            Text(itostring(hitstodie), xoff+6
            , yoff+5, 4);
        } else if (hitstodie>0){
            Text(itostring(hitstodie), xoff+14, yoff+5, 4);
        } else {
            Text(itostring(hitstodie), xoff+14, yoff+5, 4, alightblue);
        }
        
    } else if (num == 23){//collides checkbox
        if (collides){
            Text("Balls hit this", xoff-7, yoff-10);
        } else {
            Text("Balls don't hit this", xoff-19, yoff-10);
        }
        glBegin(GL_QUADS);
        glColor4f(black[0], black[1], black[2], black[3]);
            glVertex2f(xoff+0,yoff+0);
            glVertex2f(xoff+40,yoff+0);
            glVertex2f(xoff+40,yoff+40);
            glVertex2f(xoff+0,yoff+40);
            
        if (collides){
            glColor4f(alightblue[0], alightblue[1], alightblue[2], alightblue[3]);
            glVertex2f(xoff+40,yoff);
            glVertex2f(xoff+40,yoff+10);
            glVertex2f(xoff+15,yoff+40);
            glVertex2f(xoff+15,yoff+30);
            
            glVertex2f(xoff,yoff+20);
            glVertex2f(xoff+15,yoff+30);
            glVertex2f(xoff+15,yoff+40);
            glVertex2f(xoff,yoff+28);
            
            
        } else {
            glColor4f(1,1,1,1);
            glVertex2f(xoff+8,yoff+2);
            glVertex2f(xoff+40-2,yoff+40-8);
            glVertex2f(xoff+40-8,yoff+40-2);
            glVertex2f(xoff+2,yoff+8);
            
            glVertex2f(xoff+40-2,yoff+8);
            glVertex2f(xoff+8,yoff+40-2);
            glVertex2f(xoff+2,yoff+40-8);
            glVertex2f(xoff+40-8,yoff+2);
        }
        
        glEnd();
        
    } else if (num == 24){ // display note
        //NOTE TO FUTURE SELF
        //commented stuff on #24 is for accidentals.
    
        glBegin(GL_QUADS);
        glColor4f(black[0], black[1], black[2], black[3]);
            glVertex2f(xoff+0,yoff+0);
            /*glVertex2f(xoff+40,yoff+0);
            glVertex2f(xoff+40,yoff+30);*/
            glVertex2f(xoff+20,yoff+0);
            glVertex2f(xoff+20,yoff+30);
            glVertex2f(xoff+0,yoff+30);
        glEnd();
        Text("note", xoff-18, yoff+12);
        //if (note.size() == 2){
            Text(note, xoff+6, yoff+5, 4, white);
        /*} else {
            Text(note, xoff+26, yoff+5, 4, white);
        }*/
    } else if (num == 27){ // display octave
        glBegin(GL_QUADS);
        glColor4f(black[0], black[1], black[2], black[3]);
            glVertex2f(xoff+0,yoff+0);
            glVertex2f(xoff+20,yoff+0);
            glVertex2f(xoff+20,yoff+30);
            glVertex2f(xoff+0,yoff+30);
        glEnd();
        Text("octave", xoff+22, yoff+12);
        Text(itostring(octave), xoff+4, yoff+5, 4);
        
    } else if (num == 25 || num == 26 || num == 28 || num == 29){ // UP
        glBegin(GL_QUADS);
        glColor4f(black[0], black[1], black[2], black[3]);
            glVertex2f(xoff+0,yoff+0);
            glVertex2f(xoff+20,yoff+0);
            glVertex2f(xoff+20,yoff+10);
            glVertex2f(xoff+0,yoff+10);
        glEnd();
        glBegin(GL_TRIANGLES);
        glColor4f(1,1,1,1);
            if (num == 25 || num == 28){
            glVertex2f(xoff+10,yoff+2);
            glVertex2f(xoff+18,yoff+8);
            glVertex2f(xoff+2,yoff+8);
            } else {
            glVertex2f(xoff+10,yoff+8);
            glVertex2f(xoff+18,yoff+2);
            glVertex2f(xoff+2,yoff+2);
            }
        glEnd();
    } else if (num == 30){ // instrument display
        glBegin(GL_QUADS);
        glColor4f(black[0], black[1], black[2], black[3]);
            glVertex2f(xoff+0,yoff+0);
            glVertex2f(xoff+130,yoff+0);
            glVertex2f(xoff+130,yoff+30);
            glVertex2f(xoff+0,yoff+30);
        glEnd();
        Text("Sound:", xoff, yoff-6);
        Text( instrument[theinstrument] , xoff+5, yoff+5, 2);
        //instrument[theinstrument]
    } else if (num == 31 || num == 32){
        glBegin(GL_QUADS);
            glColor4f(black[0], black[1], black[2], black[3]);
                glVertex2f(xoff+0,yoff+0);
                glVertex2f(xoff+60,yoff+0);
                glVertex2f(xoff+60,yoff+20);
                glVertex2f(xoff+0,yoff+20);
            glEnd();
            glBegin(GL_TRIANGLES);
            glColor4f(1,1,1,1);
                if (num == 31){
                    glVertex2f(xoff+45,yoff+2);
                    glVertex2f(xoff+45,yoff+18);
                    glVertex2f(xoff+15,yoff+10);
                } else {
                    glVertex2f(xoff+15,yoff+2);
                    glVertex2f(xoff+15,yoff+18);
                    glVertex2f(xoff+45,yoff+10);
                }
        glEnd();
    } else if (num == 34){// emits display
    
        glBegin(GL_QUADS);
        glColor4f(black[0], black[1], black[2], black[3]);
            glVertex2f(xoff+0,yoff+0);
            glVertex2f(xoff+40,yoff+0);
            glVertex2f(xoff+40,yoff+30);
            glVertex2f(xoff+0,yoff+30);
        glEnd();
        Text("Make a ball every", xoff-12, yoff-10);
        Text("seconds", xoff+5, yoff+32);
        if (ftostring(ballevery).size() == 3){
            Text(ftostring(ballevery), xoff+1, yoff+5, 4, white);
        } else {
            Text(ftostring(ballevery), xoff+14, yoff+5, 4, white);
        }
        

    }
}

int Inventory::buttonarea(int &num, int part, int &W_WIDTH, int &W_HEIGHT, int xmod=0, int ymod=0){
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
    
    //HITSTODIE stuff
    if (num >= 19 && num <= 21){
        adjusty += 120;
        adjustx += 35;
        if (num==21) adjustx+=23;
        if (num==20) adjustx+=66;
    }
    
    //NOTE CHANGE stuff
    if (num == 25 || num == 26 || num == 28 || num == 29){
        adjustx += 60;
        adjusty += 245;
        if (num == 28 || num == 29) adjustx += 25;
        if (num == 26 || num == 29) adjusty +=50;
    }
    
    //INSTRUMENT stuff
    if (num == 31 || num == 32){
        adjustx += 10;
        adjusty += 362;
        adjustx += (num-31)*70;
    }
    
    //EMIT TIME stuff
    if (num >= 34 && num <= 36){
        adjusty += 400;
        adjustx += 35;
        if (num==34) adjustx+=23;
        if (num==35) adjustx+=66;
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
    } else if (num == 19 || num == 20 || num == 35 || num == 36){
        arraytoreturn[0] = adjustx;
        arraytoreturn[1] = adjusty;
        arraytoreturn[2] = adjustx+20;
        arraytoreturn[3] = adjusty+30;
    } else if (num == 21 || num == 34){
        arraytoreturn[0] = adjustx;
        arraytoreturn[1] = adjusty;
        arraytoreturn[2] = adjustx+40;
        arraytoreturn[3] = adjusty+30;
    /*} else if (num == 22){
        arraytoreturn[0] = 40;
        arraytoreturn[1] = 250;
        arraytoreturn[2] = 40+80;
        arraytoreturn[3] = 250+80;*/
    } else if (num == 23){
        arraytoreturn[0] = 60;
        arraytoreturn[1] = 180;
        arraytoreturn[2] = 60+40;
        arraytoreturn[3] = 180+40;
    } else if (num == 24){
        arraytoreturn[0] = 60;//40;
        arraytoreturn[1] = 260;
        arraytoreturn[2] = 60+40;//40+40;
        arraytoreturn[3] = 260+30;
    } else if (num == 25 || num == 26 || num == 28 || num == 29){
        arraytoreturn[0] = adjustx;
        arraytoreturn[1] = adjusty;
        arraytoreturn[2] = adjustx+20;
        arraytoreturn[3] = adjusty+10;
    } else if (num == 27){
        arraytoreturn[0] = 85;
        arraytoreturn[1] = 260;
        arraytoreturn[2] = 85+20;
        arraytoreturn[3] = 260+30;
    } else if (num == 30){
        arraytoreturn[0] = 10;
        arraytoreturn[1] = 330;
        arraytoreturn[2] = 10+130;
        arraytoreturn[3] = 330+30;
    } else if (num == 31 || num == 32){
        arraytoreturn[0] = adjustx;
        arraytoreturn[1] = adjusty;
        arraytoreturn[2] = adjustx+60;
        arraytoreturn[3] = adjusty+20;
    }/* else if (num == 33){
        arraytoreturn[0] = 40;
        arraytoreturn[1] = 400;
        arraytoreturn[2] = 40+80;
        arraytoreturn[3] = 400+80;
    } else if (num == 38){
        arraytoreturn[0] = 40;
        arraytoreturn[1] = 300;
        arraytoreturn[2] = 40+80;
        arraytoreturn[3] = 300+80;
    } else if (num == 37){
        arraytoreturn[0] = 40;
        arraytoreturn[1] = 500;
        arraytoreturn[2] = 40+80;
        arraytoreturn[3] = 500+80;
    }*/
    
    
    /*glBegin(GL_LINE_LOOP);
        glColor4f(1,0,0,1);
        glVertex2f(arraytoreturn[0], arraytoreturn[1]);
        glVertex2f(arraytoreturn[2], arraytoreturn[1]);
        glVertex2f(arraytoreturn[2], arraytoreturn[3]);
        glVertex2f(arraytoreturn[0], arraytoreturn[3]);
    glEnd();*/
    
    return arraytoreturn[part];
}

void Inventory::buttonfunction(int &num){
        // what happens when you click a button.
        
    cout << num << "\n";
    
    
        
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
        /*for (int i = 0; i < things[currentpage].size(); i++){
            cout << "Thing: " << things[currentpage][i] << "\n";
        }*/
        nextdown.type = 2;
        nextdown.hitstodestroy = hitstodie;
        nextdown.extra = "";
        switch (num){
            case 15:
                nextdown.func=0;
                break;
            case 16:
                nextdown.func=3;
                break;
            case 17:
                nextdown.func=1;
                nextdown.extra+="createpattern:1;patterncycle:"+ftostring(ballevery)+";";
                break;
            case 18:
                nextdown.func=2;
                break;
        }
        if (num != 15){ nextdown.extra += "collides:"+itostring(collides)+";";}
        
        if (num == 16 || num == 17){
            nextdown.extra+="note:"+note+itostring(octave)+";";
            nextdown.extra+="instrument:"+itostring(theinstrument)+";";
        }
        
    } else if (num == 19){// hitstodie down
        if (hitstodie > 0){
            hitstodie --;
        }
        nextdown.hitstodestroy = hitstodie;
        
    } else if (num == 20){// hitstodie up
        hitstodie++;
        nextdown.hitstodestroy = hitstodie;
        
    // 21: hitstodie display has no click function, yet.
    /*
    } else if (num == 22 || num == 33 || num == 37 || num == 38){ // put down a block.
        
        
        if (num != 22){ nextdown.extra += "collides:"+itostring(collides)+";";}
        
        if (num == 33 || num == 37){
            nextdown.extra+="note:"+note+itostring(octave)+";";
            nextdown.extra+="instrument:"+itostring(theinstrument)+";";
        }
        
        if (num == 22){//static
            nextdown.func = 0;
        } else if (num == 33){
            nextdown.func=3;
        } else if (num == 37){
            nextdown.func=1;
            nextdown.extra+="createpattern:1;patterncycle:"+ftostring(ballevery)+";";
        } else if (num == 38){
            nextdown.func=2;
        }*/
        
    } else if (num == 23){
        collides = !collides;
        if (num != 22){ nextdown.extra += "collides:"+itostring(collides)+";";}
    
    
    } else if (num == 25){
        /*if (note=="C") {note="C#";}
        else if (note=="C#"){note="D";}
        else if (note=="D") {note="D#";}
        else if (note=="D#"){note="E";}
        else if (note=="E") {note="F";}
        else if (note=="F") {note="F#";}
        else if (note=="F#"){note="G";}
        else if (note=="G") {note="G#";}
        else if (note=="G#"){note="A";}
        else if (note=="A") {note="A#";}
        else if (note=="A#"){note="B";}
        else if (note=="B") {note="C";}*/
        if (note=="C") {note="D";}
        else if (note=="D") {note="E";}
        else if (note=="E") {note="F";}
        else if (note=="F") {note="G";}
        else if (note=="G") {note="A";}
        else if (note=="A") {note="B";}
        else if (note=="B") {note="C";}
            nextdown.extra+="note:"+note+itostring(octave)+";";
    } else if (num == 26){
        /*if (note=="C") {note="B";}
        else if (note=="C#"){note="C";}
        else if (note=="D") {note="C#";}
        else if (note=="D#"){note="D";}
        else if (note=="E") {note="D#";}
        else if (note=="F") {note="E";}
        else if (note=="F#"){note="F";}
        else if (note=="G") {note="F#";}
        else if (note=="G#"){note="G";}
        else if (note=="A") {note="G#";}
        else if (note=="A#"){note="A";}
        else if (note=="B") {note="A#";}*/
        if (note=="C") {note="B";}
        else if (note=="D") {note="C";}
        else if (note=="E") {note="D";}
        else if (note=="F") {note="E";}
        else if (note=="G") {note="F";}
        else if (note=="A") {note="G";}
        else if (note=="B") {note="A";}
            nextdown.extra+="note:"+note+itostring(octave)+";";
    } else if (num == 28){
        if (octave < 9) octave++;
        nextdown.extra+="note:"+note+itostring(octave)+";";
    } else if (num == 29){
        if (octave >3) octave--;
        nextdown.extra+="note:"+note+itostring(octave)+";";
    } else if (num == 31){
        if (theinstrument==10) {theinstrument=13;}
        else if (theinstrument==13) {theinstrument=1;}
        else if (theinstrument==1) {theinstrument=10;}
            nextdown.extra+="instrument:"+itostring(theinstrument)+";";
    } else if (num == 32){
        if (theinstrument==10) {theinstrument=1;}
        else if (theinstrument==1) {theinstrument=13;}
        else if (theinstrument==13) {theinstrument=10;}
            nextdown.extra+="instrument:"+itostring(theinstrument)+";";
    } else if (num == 35){
        if (ballevery < 5){
           ballevery += 0.5;
            nextdown.extra+="createpattern:1;patterncycle:"+ftostring(ballevery)+";";
        }
    } else if (num == 36){
        if (ballevery >=1){
            ballevery -= 0.5;
            nextdown.extra+="createpattern:1;patterncycle:"+ftostring(ballevery)+";";
        }
        
    }
}
