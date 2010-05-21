/*
 *  particles.cpp
 *  BallDrop
 *
 *  Created by Robin Hayes on 19/05/2010.
 *  Copyright 2010 Propellor and Ratchet Games. All rights reserved.
 *
 */

#include "particles.h"
#include <iostream>
#include <time.h>

Particles::Particles(){
    //does this need to do anything?
    //probably not.
    srand ( time(NULL) );
};


void Particles::update(PSystem &system, int elapsed_time, float &gravity){
    vector <int> topop;
        //cout << "PARTICLE UPDATE\n";
    for (int i = 0; i < system.size(); i++){
        //cout << "Life: "<< i << "," <<system[i].life<<"\n";
        if (system[i].action != "burstglow"){
            system[i].yv += gravity*elapsed_time;
        }
        system[i].x += system[i].xv*elapsed_time;
        system[i].y += system[i].yv*elapsed_time;
        system[i].life--;
        
        if (system[i].action == "schlupglow" && system[i].life == (system[i].lifemax/2)){
            system[i].xv = -(system[i].xv);
            system[i].yv = -(system[i].yv);
            system[i].colour[1] = 1;
        }
        
        if (system[i].life < (system[i].lifemax/3.0)){
            if (system[i].life <= 0){
                topop.push_back(i);
            } else {
                system[i].colour[3] = system[i].life/(system[i].lifemax/3.0); //fade
                //cout << system[i].life/10.0 << "\n";
            }
        }
    }
    for (int i = 0; i < topop.size(); i++){
        system.erase(system.begin()+topop[i]);
        topop.erase(topop.begin()+i);
    }
}

/*void add(string type, float x, float y, float &r, float &g, float &b){
    add(type, x,y, 0, 0, r,g,b);
}*/
float Particles::getR(int max, int min){
    return (rand() % max + min)+0.0;
}

void Particles::add(string psystem_type, float x, float y, float xv, float yv, float r, float g, float b){
    //cout << "Adding a particlol "<< x<<", "<< y<<"\n";
    PSystem newsys = PSystem();
    float xrand= 0.0;
    float yrand= 0.0;
    float xvrand= 0.0;
    float yvrand= 0.0;
    //cout << psystem_type << "\n";
    if (psystem_type == "disintegrate"){
        for (int i =0; i < 100; i++){
            xrand = (rand() % 8);
            yrand = (rand() % 8);
            xvrand = (rand() % 16);
            yvrand = (rand() % 16);
            //cout << xrand << ", "<< yrand << "\n";
            Particle particlol = Particle();
            particlol.type = "dot";
            particlol.action="disindot";
            particlol.x = x +0.1+ (xrand/10); //vary for tilesize for a good starting spread.
            particlol.y = y +0.1+ (yrand/10);
            //cout << particlol.x << ", "<< particlol.y << "\n";
            particlol.xv = xv-0.008+(xvrand/1000);//add some variation here. maybe +-10% but remember 0,0 as well.
            particlol.yv = yv-0.008+(yvrand/1000);
            particlol.colour[0] = r;//maybe some variation here too
            particlol.colour[1] = g;
            particlol.colour[2] = b;
            particlol.colour[3] = 1.0;
            particlol.life = 30; // and here.
            particlol.lifemax = 30;
            newsys.push_back(particlol);
            //cout << "newsyssize: " << newsys.size()<< "\n";
        }
    } else if (psystem_type == "burst"){
        for (int i = 0; i < 70; i++){
            xrand = (rand() % 8);
            yrand = (rand() % 8);
            xvrand = (rand() % 16);
            yvrand = (rand() % 16);
            //cout << xrand << ", "<< yrand << "\n";
            Particle particlol = Particle();
            particlol.type = "dot";
            particlol.action="burstdot";
            particlol.x = x +0.1+ (xrand/10); //vary for tilesize for a good starting spread.
            particlol.y = y +0.1+ (yrand/10);
            //cout << particlol.x << ", "<< particlol.y << "\n";
            particlol.xv = xv-0.008+(xvrand/1000);//add some variation here. maybe +-10% but remember 0,0 as well.
            particlol.yv = yv-0.008+(yvrand/1000);
            particlol.colour[0] = r+0.7;//maybe some variation here too
            particlol.colour[1] = g+0.7;
            particlol.colour[2] = b+0.7;
            
            for (int c= 0; c <3; c++){
                if (particlol.colour[c]>1.0){
                    particlol.colour[c]=1.0;;
                }
            }
            
            particlol.colour[3] = 1.0;
            particlol.life = 30; // and here.
            newsys.push_back(particlol);
            //cout << "newsyssize: " << newsys.size()<< "\n";
        }
        
        for (int i=0; i < 60; i++){
            xvrand = (rand() % 16);
            yvrand = (rand() % 16);
            Particle particlol = Particle();
            particlol.type = "glow";
            particlol.action="burstglow";
            particlol.x = x +0.1; //vary for tilesize for a good starting spread.
            particlol.y = y +0.1;
            //cout << particlol.x << ", "<< particlol.y << "\n";
            particlol.xv = xv-0.008+(xvrand/1000);//add some variation here. maybe +-10% but remember 0,0 as well.
            particlol.yv = yv-0.008+(yvrand/1000);
            particlol.colour[0] = r;//+0.7;//maybe some variation here too
            particlol.colour[1] = g;//+0.7;
            particlol.colour[2] = b;//+0.7;
            
            /*for (int c= 0; c <3; c++){
                if (particlol.colour[c]>1.0){
                    particlol.colour[c]=1.0;;
                }
            }*/
            particlol.colour[3] = 1.0;
            particlol.lifemax = 30; // and here.
            particlol.life = 30;
            newsys.push_back(particlol);
        }
    } else if (psystem_type == "poof"){
        for (int i=0; i < 30; i++){
            xvrand = (rand() % 16);
            yvrand = (rand() % 8);
            Particle particlol = Particle();
            particlol.type = "glow";
            particlol.action = "poofglow";
            particlol.x = x +0.5; //vary for tilesize for a good starting spread.
            particlol.y = y +0.5;
            //cout << particlol.x << ", "<< particlol.y << "\n";
            particlol.xv = xv-0.008+(xvrand/1000);//add some variation here. maybe +-10% but remember 0,0 as well.
            particlol.yv = yv-0.004+(yvrand/1000);
            particlol.colour[0] = r;//+0.7;//maybe some variation here too
            particlol.colour[1] = g;//+0.7;
            particlol.colour[2] = b;//+0.7;
            
            /*for (int c= 0; c <3; c++){
                if (particlol.colour[c]>1.0){
                    particlol.colour[c]=1.0;;
                }
            }*/
            particlol.colour[3] = 1.0;
            particlol.lifemax = 10; // and here.
            particlol.life = 10;
            newsys.push_back(particlol);
        }
    } else if (psystem_type == "schlup"){
        for (int i=0; i < 30; i++){
            xvrand = (rand() % 16);
            yvrand = (rand() % 16);
            Particle particlol = Particle();
            particlol.type = "glow";
            particlol.action = "schlupglow";
            particlol.x = x +0.5; //vary for tilesize for a good starting spread.
            particlol.y = y +0.5;
            //cout << particlol.x << ", "<< particlol.y << "\n";
            particlol.xv = xv-0.008+(xvrand/1000);//add some variation here. maybe +-10% but remember 0,0 as well.
            particlol.yv = yv-0.008+(yvrand/1000);
            particlol.colour[0] = r;//+0.7;//maybe some variation here too
            particlol.colour[1] = g;//+0.7;
            particlol.colour[2] = b;//+0.7;
            
            /*for (int c= 0; c <3; c++){
                if (particlol.colour[c]>1.0){
                    particlol.colour[c]=1.0;;
                }
            }*/
            particlol.colour[3] = 1.0;
            particlol.lifemax = 20; // and here.
            particlol.life = 20;
            newsys.push_back(particlol);
        }
    }
    
    //disintegrate for blocks and balls
    //burst for finalised things (make it whiter, remember)
    //poof for putting something down
    //t:whatever for some text
    
    particle_list.push_back(newsys);
    cout << "PL size: " <<particle_list.size() << "\n";
}

void Particles::draw(int elapsed_time, int &TILESIZE, float &gravity){
    for (int i = 0; i < particle_list.size(); i++){
        if (particle_list[i].size() == 0){
            particle_list.erase(particle_list.begin()+i);
            //cout << "ERASURE\n";
        }
    }

    for (int i = 0; i < particle_list.size(); i++){
    
        PSystem &thisys = particle_list[i];
        update(thisys, elapsed_time, gravity);
        float pixel = TILESIZE/10.0;
        
        for (int j = 0; j < thisys.size(); j++){
            
            if (thisys[j].type == "dot"){
                //GL me a dot, with thispart.xy coords, thispar.rgb colour.
                glBegin(GL_QUADS);
                glColor4f(thisys[j].colour[0],thisys[j].colour[1],thisys[j].colour[2],thisys[j].colour[3]);
                    glVertex2f(thisys[j].x*TILESIZE, thisys[j].y*TILESIZE);
                    glVertex2f(thisys[j].x*TILESIZE+pixel, thisys[j].y*TILESIZE);
                    glVertex2f(thisys[j].x*TILESIZE+pixel, thisys[j].y*TILESIZE+pixel);
                    glVertex2f(thisys[j].x*TILESIZE, thisys[j].y*TILESIZE+pixel);
                glEnd();
            } else if (thisys[j].type == "glow"){
           //     /[]\
           //     \[]/
                glBegin(GL_TRIANGLE_FAN);
                glColor4f(thisys[j].colour[0],thisys[j].colour[1],thisys[j].colour[2],thisys[j].colour[3]);
                    glVertex2f(thisys[j].x*TILESIZE, thisys[j].y*TILESIZE);
                glColor4f(thisys[j].colour[0],thisys[j].colour[1],thisys[j].colour[2],0.0);
                    glVertex2f(thisys[j].x*TILESIZE+2*pixel, thisys[j].y*TILESIZE);
                    glVertex2f(thisys[j].x*TILESIZE+1*pixel, thisys[j].y*TILESIZE+2*pixel);
                    glVertex2f(thisys[j].x*TILESIZE-1*pixel, thisys[j].y*TILESIZE+2*pixel);
                    glVertex2f(thisys[j].x*TILESIZE-2*pixel, thisys[j].y*TILESIZE);
                    glVertex2f(thisys[j].x*TILESIZE-1*pixel, thisys[j].y*TILESIZE-2*pixel);
                    glVertex2f(thisys[j].x*TILESIZE+1*pixel, thisys[j].y*TILESIZE-2*pixel);
                    glVertex2f(thisys[j].x*TILESIZE+2*pixel, thisys[j].y*TILESIZE);
                glEnd();
            } //etc
            
            
        }
    }
}
int Particles::getSize(){
    return particle_list.size();
}