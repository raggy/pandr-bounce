#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>

#include <iostream>
#include <string>
#include <list>
#include <math.h>
#include <map>
#include <time.h>
#include <iomanip>
#include <sstream>


#include "RtMidi.h"
#include "text.h"
#ifndef ITEMS_H
#include "items.h"
#endif
#include "inventory.h"

#define PI 3.14159265

using namespace std;

int fps = 0;
int fullscreen = 0;

int TILESIZE = 10;

int WIDTH = 80;
int HEIGHT = 60;

int W_WIDTH = 800;
int W_HEIGHT= 600;

int cameraxmod = 0;
int cameraymod = 0;
int scrollamount = TILESIZE/2;

RtMidiOut::RtMidiOut *midiout = new RtMidiOut::RtMidiOut();


int gameplz = 0;
int ballz = 0;
//0 for menu, 1 for game, simplolcity
int maxmod = 150;
//100 is slowish, 200 is fastish? I don't know any more.
float gravity = 0.01;



GLfloat white[] = {1,1,1,1};
GLfloat black[] = {0,0,0,1};

map <string, int> note;



/*string tostring(int number){
    string s;
    stringstream out;
    out << number;
    return out.str();
}*/
string ftostring(float number){
    string s;
    stringstream out;
    out << number;
    return out.str();
}
float deg(float rads){
    return rads * 180/PI;
}
float rad(float degs){
    return degs * PI/180;
}
float spd(float x, float y){
    return sqrt((x*x +y*y));
}
void notesinit(){
    string notes[12] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
    //we'll go up to 9, shall we?
    int midnum = 24;
    string nbuffer;
    string otherbuffer;
    
    for (int octave = 0; octave < 10; octave++){
        for (int anote=0; anote < 12; anote++){
            //8 lines of code for something I could do in about three in python. I LUV U C++
            stringstream obuffer;
            nbuffer = notes[anote];
            obuffer << octave;
            otherbuffer = obuffer.str();
            nbuffer += otherbuffer;
            note[nbuffer] = midnum;
            nbuffer = "";
            otherbuffer="";
            midnum++;
            
            cout << notes[anote] << ":" << note[notes[anote]] << ", ";
        }
    }
    cout << "\nMiddle C = " << note["C4"] << "\n";
}

//Logix plz

class Ball {
    //maybe variables are mapped public by default?
    public:
        float x;
        float y;
        float xv;
        float yv;
        int width;
        int height;
        int bid;
        int timer;
        int hittimer;
        bool justhit;
        int timednote;
        int bouncecount;
        int hitcycle;
        int myinstrument;
        int mynote;
        string textnote;
        int velocity;
    
        int ded;
        
        int balltype;//a C# or a *?
        //ints probably need to be mapped to a dictionary, for sanity
        vector<unsigned char> message;
        
        Ball(int bx, int by, int instrument=9, int thenote=60){
            //x, y, instrument, thenote
            x = bx;
            y = by;
            xv = 0.0;
            yv = 0.0;
            
            ded = 0;
            
            width=TILESIZE;
            height=TILESIZE;
            
            myinstrument = instrument;
            mynote = thenote;
            textnote = "C3";
            velocity = 90;
            timednote = mynote;
            
            // whee!
            cout << "My id is "<< ballz << "\n";
            bid = ballz;
            ballz ++;
            hitcycle = 0;//I can't remember what this is for. First hit only?
            
            timer = 0;
            hittimer = 0;
            justhit = false;
            
            midiout->openPort(bid);
            // this is drop, duh.
            //unsigned int nPorts = midiout->getPortCount();
            //std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";
            
            //@TODO:
            //if (bid == 16 || bid == 32){//etc
                //add a new output lol
            //]
            //hit();
        }
        
        int getID(){
            return bid;
        }
        
        
        //Need to remove ball from storage when it's caught - that should just be for the in=play stuff.
        //just add again at a new height, simple, I suppose.
        
        
        void update(){
            if (timer > 0){
                if (timer == 1){
                    stopnoise();
                }
                timer --;
            }
            if (hittimer > 0){
                if (hittimer == 1){
                    justhit = false;
                }
                hittimer --;
            }
            yv += gravity;
            //xv += gravity;
            //cout << yv << "\n";
            
            x += xv;
            y += yv;
            
            //cout << bid << ": " << xv << "/" << yv << "\n";
            
            //to collision check here or in a block..?
            
            if (y > HEIGHT+TILESIZE || x < 0-TILESIZE || x > WIDTH+TILESIZE){
                //cout << bid << " becomes ded...\n";
                ded = 1;
                ballz --;
            } else {
                //cout << bid << " not ded!" << "\n";
            }
                
        }
        
        void kill(){
            ded = 1;
            ballz --;
        }
        
        bool isded(){
            if (ded == 1){
                return true;
            } else {
                return false;
            }
        }
        
        void changenote(string thenote, int thevelocity = -1){
            textnote = thenote;
            mynote = note[thenote];
            if (thevelocity != -1){
                velocity = thevelocity;
            }
            cout << thenote << "/" << mynote << "\n";
            cout << note["C4"] << "c4\n";
            cout << note["G8"] << "g8\n";
            cout << note["F#2"] << "f#2\n";
        }
        
        void hit(){
            //cout << "Told to hit! " << bid << "\n";
            //play the relevant note
            //cout << "BOING\n";
            //sound lol = sound(); //Not declared in this scope whut, error with sdl?
            //lol.playWAV("Snare.wav");
            hitcycle = 1;
            
            stopnoise();
                    //MIDI STUFF
            // Send out a series of MIDI messages.
            //cout << "program change";
            // Program change: 192, 5 //instrument
            message.push_back( 192 );
            message.push_back( myinstrument );
            midiout->sendMessage( &message );

            //cout << "control change";
            // Control Change: 176, 7, 100 (volume)
            message[0] = 176;
            message[1] = 07;
            message.push_back( 100 );
            midiout->sendMessage( &message );

            //cout << "note on";
            // Note On: 144, 64, 90
            message[0] = 144;
            message[1] = mynote;
            message[2] = velocity;
            midiout->sendMessage( &message );

            message.clear(); //otherwise errors about sysex.
            timer = 60;//remember 60fps.
            hittimer = 5;
            justhit = true;
            
            timednote = mynote;

//            ded = 1;
        }
        
        void stopnoise(){
        //doesn't seem to actually work? :/
        //OH because of hit at the end. Ok.
            message.clear();
            //cout << "note off";
            // Note Off: 128, 64, 40
            message.push_back(128);
            message.push_back(timednote);// == note
            message.push_back(velocity);// == dynamics
            midiout->sendMessage( &message );
            message.clear();
            //hit();
        }
        
        
        void die(){
            //do stuff about dying here like kill midi connection and reopen the slot maybe.
            
            stopnoise();
            //midiout->closePort(bid);//??
        }
        
        double getX(){
            return x;
        }
        double getY(){
            return y;
        }
        double getXV(){
            return xv;
        }
        double getYV(){
            return yv;
        }
        
        void setPos(double sx, double sy, double sxv, double syv){
            x = sx;
            y = sy;
            xv = sxv;
            yv = syv;
        }
        
        void draw(){
            //cout << "Balls\n";
            
            drawBall(x, y, TILESIZE, textnote); //instrument and stuff later.å
            
            /*glPushMatrix();
                glTranslated(x*TILESIZE-(TILESIZE/2), y*TILESIZE-(TILESIZE/2), 0);
                GLfloat temp[] = {1, 1, 0, 1.0f};
                glMaterialfv(GL_FRONT, GL_DIFFUSE, temp);
                
                glBegin(GL_QUADS);
                    glVertex2f(-(TILESIZE/2),  (TILESIZE/2));
                    glVertex2f( (TILESIZE/2),  (TILESIZE/2));
                    glVertex2f( (TILESIZE/2), -(TILESIZE/2));
                    glVertex2f(-(TILESIZE/2), -(TILESIZE/2));
                glEnd();
                
                Text(textnote, -4*TILESIZE/10.0, -3*TILESIZE/10.0, TILESIZE/10.0, 0,0,0);*/
                
                /*glBegin(GL_TRIANGLE_FAN);
                    glVertex2f(0, 0);
                    int radius = TILESIZE/2;
                    for (int angle = 0; angle <= 360; angle +=5){
                        glVertex2f(0 + sin(angle) * radius, 0 + cos(angle) * radius);
                    }
                glEnd();*/
                
                //triangle fan isn't smooth, so back to quad with round ball textures I think.

            //glPopMatrix();
            if (hitcycle){
                hitcycle = 0;
                //cout << "Hi: [" << x << ", "<<  y  << "]\n";
            }
        }
        
    
};


list<Ball> ball_list;

class Storage {
    //when you add a ball to the stage, it comes in here.
    //it also acts as a bridge to let us do thigns to balls.
    //there's probably a more elegant way to do this.
    public:
        void add(Ball lol){
            //cout << "A BALL\n";
            ball_list.push_back( lol );
        }
//        void remove (int bid){
//            int tbid = bid;
//            cout << "DIE YOU HIDEOUS FIEND (" << ball_list[tbid].getID() << ")\n";
//            ball_list[tbid].die();
//            
//            vector<Ball>::iterator  the_iterator;

//            the_iterator = ball_list.begin();
//            bool done = false;
//            while(done == false && (the_iterator != ball_list.end() || ball_list.begin() == ball_list.end())) {
//                if (the_iterator->getID() == tbid){
//                    if (the_iterator->isded()){
//                        cout << "\t" << ball_list[tbid].getID() << " has been erased.\n";
//                        ball_list.erase(the_iterator);
//                        ballz--;
//                    } else {
//                        cout << "\t" << "Mistaken identity! "<< ball_list[tbid].getID() << " is innocent!\n";
//                    }
//                    done = true;
//                    break;
//                        
//                }
//                the_iterator++;
//            }
//            if (done == false){
//                cout << "\t" << "No change made! ("<< tbid << ")\n";
//            } else {
//                cout << "\t" << "Ballz: "<< ballz<< "\n";
//                if (ballz <= 0){
//                    clear();
//                }
//            }
//            cout << "phew.\n";
//        }
        
//        void checkded(int bid){
//            if (ball_list[bid].ded == 1){
//                cout << "I DIE (" << ball_list[bid].getID() << ")\n";
//                remove(bid);
//            }
//        }
        
        void clear (){
            ball_list.clear();
            cout << "Poof\n";
        }
        
        /*double getX(int bid){
            double toreturn = ball_list[bid].getX();
            return toreturn;
        }
        double getY(int bid){
            double toreturn = ball_list[bid].getY();
            return toreturn;
        }
        double getXV(int bid){
            double toreturn = ball_list[bid].getXV();
            return toreturn;
        }
        double getYV(int bid){
            double toreturn = ball_list[bid].getYV();
            return toreturn;
        }
        
        void setPos(int bid, int sx, int sy, int sxv, int syv){
            ball_list[bid].setPos(sx, sy, sxv,syv);
        }*/
        
        void changenote(list<Ball>::iterator &ball, string thenote, int velocity = -1){
            ball->changenote(thenote, velocity);
        }

};
Storage storage = Storage();


/*struct Background {
    //lol hi
    public:
        void draw(){
            //cout << "background\n";
            glPushMatrix();
                glTranslated(0,0,0);
                GLfloat temp[] = {0, 0, 0.01, 1.0f};
                glMaterialfv(GL_FRONT, GL_DIFFUSE, temp);
                        glBegin(GL_QUADS);
                            glVertex2f(0.0,  0.0);
                            glVertex2f( W_WIDTH,  0.0);
                            glVertex2f( W_WIDTH, W_HEIGHT);
                            glVertex2f(0, W_HEIGHT);
                        glEnd();
            glPopMatrix();
        }
};
Background background = Background();*/







// TILE CLASS. --------------------------------------------------------
class Tile {
    public:
        int x;
        int y;
        
        int type;
        //maybe 0 for clear if I need to define that
        // 1 for line
        // 2 for block
        
        int func;
        //depends on type
        //LINE - all need vector
        //0 = bounce 
        //1 = filter (needs what to block/accept)
        //2 = modifier (needs what to change to
        //~3= silent bounce?
        
        //BLOCK - no vector, size is tilesize.
        //0 = static block.
        //1 = emitter (needs ball to emit, frequency, number, trigger)
        //2 = destroyer
        //3 = modifier
        
        //let's give them all a unique ID.
        //maps should be read froma  file one day too plz.
        
        int uid;
        
        int angle;
        string filter;
        string modifier;
        //let's just store it in sodding strings.
        string emitter;
        int hitstodestroy;
        int maxhitstodestroy;
        bool ghost;
        
        float glow[3];
        
        string extra;
        
        vector<float> coords;

        float r, g, b;
        
        Tile(int& sid, int& sx, int& sy, int stype = 0, int sfunc = 0, string sextra="0", int shits = 0, bool sghost = false){
            uid = sid;
            x = sx;
            y = sy;
            type = stype;
            func = sfunc;
            
            extra = sextra;
            
            hitstodestroy = shits;
            maxhitstodestroy = shits;
            
            if (hitstodestroy != 0){
                glow[0] = 0.0;
                glow[1] = 1.0;
                glow[2] = 0.0;
            }
            
            ghost = sghost;
            
            //decided by type and shit later
            if (type == 1){
                r = 0;
                g = 1;
                b = 0;
            } else if (type == 2){
                r = 1;
                g = 0;
                b = 0;
            }
            
            if (type == 1){
                angle = atoi(extra.c_str());
                //coords for 1 then * tilesize!)
                if (angle >= 180){
                    angle -= 180;
                }//only need to define half.
                
                if (angle == 0){
                    coords.push_back(0.0);
                    coords.push_back(0.5);
                    coords.push_back(1.0);
                    coords.push_back(0.5);
                } else if (angle == 45){
                    coords.push_back(0.0);
                    coords.push_back(0.0);
                    coords.push_back(1.0);
                    coords.push_back(1.0);
                } else if (angle == 90){
                    coords.push_back(0.5);
                    coords.push_back(0.0);
                    coords.push_back(0.5);
                    coords.push_back(1.0);
                } else if (angle == 135){
                    coords.push_back(1.0);
                    coords.push_back(0.0);
                    coords.push_back(0.0);
                    coords.push_back(1.0);
                    
                //that's the easy ones...    
                } else if (angle < 45){
                    coords.push_back(0.0);
                    coords.push_back(0.5-(0.5 * (tan(angle*PI/180))));
                    coords.push_back(1.0);
                    coords.push_back(0.5+(0.5 * (tan(angle*PI/180))));
                } else if (angle > 45 && angle < 90){
                    coords.push_back(0.5-(0.5* (tan((90-angle)*PI/180))));
                    coords.push_back(0.0);
                    coords.push_back(0.5+(0.5* (tan((90-angle)*PI/180))));
                    coords.push_back(1.0);
                } else if (angle > 90 && angle < 135){
                    coords.push_back(0.5+(0.5* (tan((angle-90)*PI/180))));
                    coords.push_back(0.0);
                    coords.push_back(0.5-(0.5* (tan((angle-90)*PI/180))));
                    coords.push_back(1.0);
                } else if (angle > 135 && angle < 180){
                    coords.push_back(0.0);
                    coords.push_back(0.5-(0.5 * (tan((angle)*PI/180))));
                    coords.push_back(1.0);
                    coords.push_back(0.5+(0.5 * (tan((angle)*PI/180))));
                }
                
                //cout << "Angle: " << angle << "/"<< angle*PI/180 << ", coords: ";
                
                /*for (int i=0; i < 4; i ++){
                    cout << coords[i] << ", ";
                }
                cout << "\n";*/
            }
        }
        
        void checkDestroy(){
            if (hitstodestroy != 0){
                if (hitstodestroy == 1){
                    type = 0;
                    func = 0;
                    extra = "";
                } else {
                    hitstodestroy--;
                }
            }
        }
        
        void hitGlow(){
            float hit = (hitstodestroy+0.0)/(maxhitstodestroy+0.0);
            
            if (hit == 0.5){
                glow[0] = 1;
                glow[1] = 1;
            } else if (hit > 0.5){
                glow[1] = 1;
                glow[0] = ((1-hit)*2);
            } else {
                glow[0] = 1;
                glow[1] = hit*2 -0.2;
            }
        }
        
        void checkCollision(){
            if (type != 0 || ghost == false){
                float hyp=0.0;
                vector<float> ballpos;
                float ang=0.0;
                float pbang=0.0;
                float newxv=0.0;
                float newyv=0.0;
                float lineangle=0.0;
                float speed = 0.0;
                
                list<Ball>::iterator ball;
                for (ball = ball_list.begin(); ball != ball_list.end(); ball++) {
                    hyp = 0;
                    ballpos.clear();
                    ballpos.push_back(ball->getX());
                    ballpos.push_back(ball->getY());
                    ballpos.push_back(ball->getXV());
                    ballpos.push_back(ball->getYV());
                    
                    if (type == 1){ //if we're a line..
                        if (ballpos[0]*TILESIZE > (x)*TILESIZE &&\
                         ballpos[0]*TILESIZE <= (x+1)*TILESIZE &&\
                         ballpos[1]*TILESIZE > (y)*TILESIZE &&\
                         ballpos[1]*TILESIZE <= (y+1)*TILESIZE \
                         && !(ball->justhit)){
                            lineangle = rad(angle-45);
                            /*if (lineangle > 90){
                                lineangle -=360;
                            }*/
                            ang=0.0;//initial angle
                            pbang=0.0;//postbounce angle
                            newxv=0.0;// x and
                            newyv=0.0;// y velocities
                            
                            //cout << "pung (" << ball->getID() << ")\n";
                            ball->hit();
                            //cout << "speed: "<< ball->yv <<"\n";
                            
                            
                            //BEN WAY:
                            //working now, hooray.
                            ang = atan2(ballpos[2], ballpos[3]);
                            speed = spd(ballpos[2], ballpos[3])+0.01;
                            pbang = ang-lineangle;
                            pbang = -pbang;
                            pbang += lineangle;
                            
                            /*if (ang-rad(lineangle) > 0.5){
                                pbang += rad(45);
                            }
                            if (ang-rad(lineangle) < -0.5){
                                pbang -= rad(45);
                            }*/
                            
                            newxv= cos(pbang)*speed;
                            newyv= sin(pbang)*speed;
                            
                           // cout << "speed: " << speed << "\n";
                            /*
                            //MY WAY:
                            //Accurate mostly from above. Fails at sides and below.
                            
                            cout << ballpos[0] << ", " << ballpos[1] << ", " << ballpos[2] << ", " << ballpos[3] << "; " ;
                            hyp = sqrt(ballpos[2]*ballpos[2] + ballpos[3]*ballpos[3])+0.01;//the 0.01 means it doesn't decay.
                            ang = atan(ballpos[3]/ballpos[2]) *180/PI +180;
                            //ang = floor((asin(ballpos[3]/hyp)+90)/10)*10;
                            cout << ang << "\n";
                            
                            
                            if (ang <0){
                                ang += 360;
                            } else if (ang > 359){
                                ang -= 360;
                            }
                            pbang = lineangle-ang-180+lineangle;
                            //pbang = angle-ang;
                            if (pbang < 0){
                                pbang += 360;
                            } else if (pbang > 359){
                                pbang -= 360;
                            }
                            newxv = cos((pbang)*PI/180)*hyp;
                            newyv = sin((pbang)*PI/180)*hyp;
                            */
                            
                            /*cout << cos(rad(60)) << ", "<<cos(60*PI/180) << "\n";
                            cout << "Ball's angle: "<<ang<<", line's angle: "<<rad(lineangle)<<", difference: "<<(ang-rad(lineangle))<<", ball's new angle: "<<pbang<<"\n";
                            cout << "Vectors: "<<newxv<<" and "<<newyv<<"\n";*/
                            ball->setPos(ballpos[0], ballpos[1],   newxv, newyv );
                            
                            checkDestroy();
                            //angle = pbang;
                        }
                    }
                    
                    
                    if (type == 2){
                        if (ballpos[0]*TILESIZE > (x)*TILESIZE && \
                        ballpos[0]*TILESIZE <= (x+1)*TILESIZE && \
                        ballpos[1]*TILESIZE > (y)*TILESIZE && \
                        ballpos[1]*TILESIZE <= (y+1)*TILESIZE \
                        && !(ball->justhit)){
                            //cout << "thock (" << ball->getID() << ")\n"; 
                            
                            if (func == 3){
                                ball->changenote(extra);
                                cout << "NOTE CHANGE: " << extra << "\n";
                            }
                            
                            if (!ghost){
                                ball->hit();
                                hitGlow();
                                if (ballpos[3] >= ballpos[2]){//going faster in y than x
                                //NOTE: can probably do this better somehow, what if it's flying sideways..?
                                    ball->setPos(ballpos[0], ballpos[1],   ballpos[2], -(ballpos[3]+0.01) );
                                } else {
                                    ball->setPos(ballpos[0], ballpos[1],   -(ballpos[2]+0.01), ballpos[3] );
                                }  
                                
                                if (func == 2){
                                    ball->kill();
                                }
                            }
                            
                            
                            checkDestroy();
                        }
                    }
                }
                
            }//if !0
        }
        
        int lolhi(){
            if (type > 0){
                return type;
            }
        }
        
        // draw the damn tile.
        int draw(){
        
            //check balls for collision here.
            checkCollision();
            
            glPushMatrix();
                glTranslated(x*TILESIZE, y*TILESIZE, 0);
                //glColor4f(1,1,1, 1);
                GLfloat temp[] = {r, g, b, 1};

                
                GLfloat drk[] = {0, 0, 0.3, 1};
                //glMaterialfv(GL_FRONT, GL_DIFFUSE, temp);
                switch (type) {
                    case 1:
                        //line
                        drawLine(TILESIZE, temp, coords[0], coords[1], coords[2], coords[3]);
                        //if (hitstodestroy != 0){
                            //drawLineGlow(TILESIZE, 1,1,1, coords[0], coords[1], coords[2], coords[3]);
                        //}
                        break;
                    case 2:
                        //block
                        if (hitstodestroy != 0){
                            drawBlockGlow(TILESIZE, glow[0], glow[1], glow[2]);
                        }
                        drawBlock(TILESIZE, temp, func);
                        
                        //Text(ftostring(glow[0])+" "+ftostring(glow[1]), 0, 0);
                        break;
                    default:
                        drawSomething(TILESIZE, drk);
                        break;
                }
            glPopMatrix();
            return 0;
        }
};


// MAP CLASS --------------------------------------------------------
class Map {
    public:
    
        

    
        int width, height; // set in constructor.
        int uid;
        
        vector < vector<Tile> > tiles;
        
        Map(int w, int h){
            //Tile * tiles;
        
            //int i;
            //int * p;
            //i = 2;
            //p= new (nothrow) int[i];
            
        
            width = w;
            height = h;
            uid = 0;
            vector<Tile> dummy;
            for (int i = 0; i < width; i++) {
            
                tiles.push_back(dummy);
                for (int j = 0; j < height; j++) {
                    if (i == 10 && j == 20){
                        tiles[i].push_back(Tile(uid, i, j, 1, 0, "0", 0, false)); //static line
                    } else if (i == 4 && j == 20){
                        tiles[i].push_back(Tile(uid, i, j, 2, 0, "0", 20, false)); //static block
                    } else if (i == 10 && j == 25){
                        tiles[i].push_back(Tile(uid, i, j, 2, 3, "E4", 0, true));// changer block
            
                    } else {
                        tiles[i].push_back(Tile(uid, i, j, 0, 0, "0", 0, true));// bg/ghost
                    }
                    uid ++;
                }
            }
            /*for (int i = 0; i < 50; i++) {
                for (int j = 0; j < 50; j++) {
                    if (tiles[i][j].type != 0){
                        cout << "***";
                    }
                    cout << tiles[i][j].type<<"|";
                }
                cout << "\n";
            }*/
                
        }
        
        void change (int x, int y, int type = 0, int func = 0, string extra = "0"){
            tiles[x][y] = Tile(tiles[x][y].uid, x, y, type, func, extra);
        }
};




/*NOTES LOL
tiles can be 10*10
the line will be around the centre * style.
should report it's angle to ball on collision

ball will use that to give itself a new velocity x/y
something like um.. if it hits at 45+ it goes away at 45-.
minus the degrees from 90 I suppose.

obviously also triggers hit().

different line types:
solid, normal
modifier, changes note/velocity/instrument
destroyer, makes ball go poof
filter, only let certain notes/instruments through.

maybe also blocks for:
emitter, set balltype, regularity, number, they just drop out
a different way to change direction?
queuing or time slowing?
black holes that curve its path?
etc.
prolly destroyer should go here.
*/



/*----------------------------------------------------------


------------   BIG GAP TWIXT THIS AND GLCODE YAY __________

___________________________________________________________*/









int camerax = 0;
int cameray = 0;
int cameraz = 0;

string stringlol = "Hello!";

//--------------------------------------------------------


Map themap = Map(WIDTH, HEIGHT);
Inventory invent = Inventory(1);//location, 0123 = t r b l;



// Draw function void
void draw() {

//cout << "-----------------------------------------------------\n"
//cout << "----- DRAW START -------------------------------------\n";
    
    // Clears the color buffer bit and depth buffer bit
    glClear (GL_COLOR_BUFFER_BIT);

    // Push the current matrix stack
    glPushMatrix();
    // Defines a viewing transformation
    gluLookAt (camerax+cameraxmod, cameray+cameraymod, cameraz,
               camerax+cameraxmod, cameray+cameraymod, cameraz - 20,
               0.0, 1.0, 0.0);


    //GLfloat whitelight[] = {0,0,0,0.0};



    //glLightfv(GL_LIGHT0, GL_AMBIENT, whitelight);
    //glEnable(GL_LIGHTING);

    // Push the current matrix stack
    glPushMatrix();


    
    for (int x = 0; x < WIDTH; x ++){
        for (int y = 0; y < HEIGHT; y++){
            themap.tiles[x][y].draw();
            //cout << themap.tiles[x][y].lolhi();
        }
    }
    //cout << "\n";
    
    // Create a new iterator for the ball_list
    list<Ball>::iterator ball;
    // Loop through all balls in the list
    for (ball = ball_list.begin(); ball != ball_list.end(); ) {
        // Update current ball
        ball->update();
        // If it dies
        if (ball->ded)
        {
            // Remove it from the list and increment iterator
            ball_list.erase(ball++);
            // Debug
            //cout << ball_list.size() << " balls left" << endl;
        }
        // If it doesn't die
        else
        {
            // Draw it
            ball->draw();
            // Increment iterator
            ++ball;
        }
    }
    
    invent.draw(W_WIDTH, W_HEIGHT, cameraxmod, cameraymod);
    
    Text("abcdefghijklmnopqrstuvwxyz 1234567890 # $", 0+cameraxmod,0+cameraymod, TILESIZE/10.0); // $ = flat, maybe could use unicode I guess
    
    string textfps = "fps ";
    stringstream out;
    out << fps;
    textfps+= out.str();
    //cout << textfps<< fps<< "\n";
    Text(textfps, 0+cameraxmod, (W_HEIGHT-20+cameraymod), 2);
    //Text(textfps, 0, 20, 2);
    
    /*// none of this works.
    // Create a pixmap font from a TrueType file.
    FTGLPixmapFont font("/home/user/Arial.ttf");

    // If something went wrong, bail out.
    if(!font.Error()){
        font.FaceSize(72);
        font.Render("Hello World!");
    }*/

    glPopMatrix();
    //cout << "pop!\n";
    // Swaps the buffers
    glutSwapBuffers();
}




// Reshapes the window
void reshape(int w, int h) {

    W_WIDTH = w;
    W_HEIGHT = h;
    
    glDisable(GL_DEPTH_TEST);
    // Sets the viewport
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    // Applies matrix operations to the projection matrix stack
    glMatrixMode(GL_PROJECTION);
    // Replaces the current matrix with the identity matrix
    glLoadIdentity();
    // Sets up a perspective projection matrix
    //gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 60.0);
    glOrtho (0, w, h, 0, -10, 10);
    
    //gluOrtho2D(0, 800, 600, 0);
    glDisable(GL_DEPTH_TEST);
    // Applies matrix operations to the modelview matrix stack
    //glMatrixMode(GL_MODELVIEW);
    //glOrtho (0, (GLfloat)w, (GLfloat)h, 0, 0, 1);
    // Replaces the current matrix with the identity matrix=
    //glLoadIdentity();
    //glTranslatef(0.375, 0.375, 0);

    glutPostRedisplay();
    
}


float lastclock = 0.0;
int frame=0,timebase=0;
int thetime;

void idler(void) {
    if (clock() > lastclock){
        glutPostRedisplay();
        lastclock = clock() + (CLOCKS_PER_SEC/60);
        
        
        frame++;
        thetime=glutGet(GLUT_ELAPSED_TIME);
        if (thetime - timebase > 1000) {
            fps = frame * 1000.0/(thetime-timebase);
            timebase = thetime;		
            frame = 0;
            cout << ballz << " balls\n";
        }
    }
}


void quit(){
    cout << "Bye!\n";
    list<Ball>::iterator ball;
    for (ball = ball_list.begin(); ball != ball_list.end(); ball++)
        ball->stopnoise();
    
    //storage.clear();
    //RtMidiOut::~RtMidiOut();
    exit(0);
}


void Mouse(int button, int state, int x, int y){
    cout << "Button " << button << " " << state << " at "<< x << "/" << y << "\n";
    //0 is leftclick, 2 is rightclick, side buttons not recognised. guessing 1 uis scrollclick.
    //0 is down, 1 is up
    
    //if x and y are within the stage, do stage stuff
    //if they're within the inventory, do inventory stuff.
    
    
    //nurr this only works on button press...
    
    
    switch (button){
        case 0:
            switch (state){
                case 1:
                    if (!invent.active){
                        
                        if (((x+cameraxmod)>= 0 && (x+cameraxmod) < W_WIDTH) && ((y+cameraymod)>= 0 && (y+cameraymod) < W_HEIGHT)){
                            themap.change((x+cameraxmod)/TILESIZE,(y+cameraymod)/TILESIZE, invent.nextdown.type, invent.nextdown.func, invent.nextdown.extra);
                        }
                    } else {
                        invent.update("click", x+cameraxmod, y+cameraymod, W_WIDTH, W_HEIGHT, cameraxmod, cameraymod);
                    }
                    break;
            }
            break;
        case 2:
            switch (state){
                case 1:
                    if (((x+cameraxmod)>= 0 && (x+cameraxmod) < W_WIDTH) && ((y+cameraymod)>= 0 && (y+cameraymod) < W_HEIGHT)){
                        themap.change((x+cameraxmod)/TILESIZE,(y+cameraymod)/TILESIZE, 0);
                    }
                    break;
            }
            break;
    }
}


void MouseMove(int x, int y){
    //if options.invonright == True
    if (x > (W_WIDTH/10*9)){
        if (invent.active == false){
            invent.active = true;
        }
    } else if (x < (W_WIDTH-150)){
        if (invent.active == true){
            invent.active = false;
        }
    }
}

void MouseDrag(int x, int y){
    //lul
}
void initialise(void) {

    glClearColor(0.0, 0.0, 0.1, 1);
    //background?

    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //lightplz
    glEnable (GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glAlphaFunc ( GL_GREATER, 0.1 ) ;
    glEnable ( GL_ALPHA_TEST ) ;

    glEnable(GL_COLOR_MATERIAL);
    

    
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho (0, W_WIDTH, W_HEIGHT, 0,-10, 10);
    //gluOrtho2D(0, 800, 600, 0);
    glDisable(GL_DEPTH_TEST);
    //glMatrixMode (GL_MODELVIEW);
    //glLoadIdentity ();
    
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    
    glTranslatef(0.375, 0.375, 0);


// The display function is called each time there is a display callback
    glutDisplayFunc(draw);
    // The reshape function reshapes the scene
    glutReshapeFunc(reshape);
    // Function that reads input from the keyboard
    glutMouseFunc(Mouse);
    glutPassiveMotionFunc(MouseMove);
    glutMotionFunc(MouseDrag);
    // framerate control
    glutIdleFunc(idler);
    glutIgnoreKeyRepeat(0);
    
    
    
    glutPostRedisplay();

    
}


void SpecialKeyboard(int key, int x, int y){
    cout << key << "\n";
    scrollamount = TILESIZE/2;
    switch(key) {
        case GLUT_KEY_LEFT:
            if (cameraxmod >=scrollamount){
                cameraxmod -=scrollamount;
            }
            break;
        case GLUT_KEY_RIGHT:
            cameraxmod +=scrollamount;
            break;
        case GLUT_KEY_UP:
            if (cameraymod >=scrollamount){
                cameraymod -=scrollamount;
            }
            break;
        case GLUT_KEY_DOWN:
            cameraymod +=scrollamount;
            break;
    }
        
}


void Keyboard(unsigned char key, int A, int B) {
    /*string campos = (string) ((char) camerax);
    campos << ", ";
    campos << (cameray+10);
    campos << ", ";
    campos << (cameraz+20);*/
    //camerax, cameray, cameraz
    
    switch(key) {
            // Escapes from the program by pressing 'Esc'
        case 27:
            fullscreen = 0;
            glutLeaveGameMode();
            initialise();
            quit();
            //gameplz=0; // Terminates the program
            break;
        case 'a':
            TILESIZE=10;
            break;
        case 's':
            TILESIZE=20;
            break;
            
        case 'z':
            TILESIZE--;
            break;
        case 'x':
            TILESIZE++;
            break;
            
        case 'q':
            invent.nextdown.type=1;
            invent.nextdown.func=0;
            invent.nextdown.extra = "0";
            break;
        case 'w':
            invent.nextdown.type=1;
            invent.nextdown.func=0;
            invent.nextdown.extra = "15";
            break;
        case 'e':
            invent.nextdown.type=1;
            invent.nextdown.func=0;
            invent.nextdown.extra = "30";
            break;
        case 'r':
            invent.nextdown.type=1;
            invent.nextdown.func=0;
            invent.nextdown.extra = "45";
            break;
        case 't':
            invent.nextdown.type=1;
            invent.nextdown.func=0;
            invent.nextdown.extra = "60";
            break;
        case 'y':
            invent.nextdown.type=1;
            invent.nextdown.func=0;
            invent.nextdown.extra = "75";
            break;
        case 'u':
            invent.nextdown.type=1;
            invent.nextdown.func=0;
            invent.nextdown.extra = "90";
            break;
        case 'i':
            invent.nextdown.type=1;
            invent.nextdown.func=0;
            invent.nextdown.extra = "105";
            break;
        case 'o':
            invent.nextdown.type=1;
            invent.nextdown.func=0;
            invent.nextdown.extra = "120";
            break;
        case 'p':
            invent.nextdown.type=1;
            invent.nextdown.func=0;
            invent.nextdown.extra = "135";
            break;
        case '[':
            invent.nextdown.type=1;
            invent.nextdown.func=0;
            invent.nextdown.extra = "150";
            break;
        case ']':
            invent.nextdown.type=1;
            invent.nextdown.func=0;
            invent.nextdown.extra = "165";
            break;
            
        case 'h':
            //storage.changenote(ball, "E3");
            break;
        case 'n':
            storage.add( Ball(11, 15) );
            break;
        case 'f':
            if (fullscreen){
                fullscreen = 0;
                glutLeaveGameMode();
                initialise();
                glutKeyboardFunc(Keyboard);
                glutSpecialFunc(SpecialKeyboard);

            } else {
                fullscreen = 1;
                glutEnterGameMode();
                initialise();
                glutKeyboardFunc(Keyboard);
                glutSpecialFunc(SpecialKeyboard);
            }
            break;

        
        default:
            break;
    }

    
    //cout << key;
    //cout << "\n";
    //cout << " (" << camerax << ", " << cameray << ", " << cameraz << ")\n\n";
}


int main (int argc, char * argv[]) {
    // this ought to be good for a laugh.
    notesinit();
    
    //start simplesynth because I give up.
    //system("say butts lol");
    //system("~/Documents/XCode/BallDrop/SimpleSynth.app/Contents/MacOS/SimpleSynth", "~/Documents/XCode/BallDrop/SimpleSynth.app/Contents/MacOS/SimpleSynth", NULL);
    //even this doesn't work T-T
    //pauses the program until the process is complete, durr. Neeed to thread.
    
    
    
    itemsInit();

    storage.add( Ball(4, 10) );
    storage.add( Ball(5, 10) );
    storage.add( Ball(6, 10) );
    storage.add( Ball(10, 15) );
    storage.add( Ball(11, 15) );
    storage.add( Ball(12, 15) );
    
    gameplz = 1;
    
    /*while (gameplz == 1){
        
        for (list<Ball>::iterator ball = ball_list.begin(); ball != ball_list.end(); ball++) {
            ball -> update();
        }
    }*/
    
     // Initialise GLUT library
    glutInit(&argc, argv);
    // Initialise the display mode
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    // Initialise the window position
    glutInitWindowPosition(300, 300);
    // Initialise the window size
    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    // Creates a window on the screen
    glutCreateWindow ("BALL DROPPER v0.0");

    // Call the initialise function
    initialise();
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpecialKeyboard);

    
    glutGameModeString("800x600:16@75");
    
    

    
    // Causes the program to enter an event-processing loop
    glutMainLoop();
    
    
    //anything after this is when we die.
    return 0;
}