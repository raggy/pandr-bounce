/*
 *  particles.h
 *  BallDrop
 *
 *  Created by Robin Hayes on 19/05/2010.
 *  Copyright 2010 Propellor and Ratchet Games. All rights reserved.
 *
 */
#ifdef __APPLE__
#   include <OpenGL/OpenGL.h>
#else
#   include <GL/gl.h>
#endif
#include <vector>
#include <string>

using namespace std;

#ifndef PARTICLES_H
#define PARTICLES_H

struct Particle{
    public:
        float x, y, xv, yv;
        string type, action;
        GLfloat colour[4];
        int life, lifemax;
};

typedef vector<Particle> PSystem;
    

class Particles {
    public:
        vector <PSystem> particle_list;
        Particles();
        void draw(int elapsed_time, int &TILESIZE, float &gravity);
        float getR(int max, int min);
        float getR(int max){
            getR(max, 0.0);
        }
        void update(PSystem &system, int elapsed_time, float &gravity);
        //void add(string type, float x, float y, float &r, float &g, float &b);
        void add(string psystem_type, float x, float y, float xv, float yv, float r, float g, float b);
        
        int getSize();
};
#endif