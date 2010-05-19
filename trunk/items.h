/*
 *  items.h
 *  BallDrop
 *
 *  Created by Robin Hayes on 08/05/2010.
 *  Copyright 2010 Propellor and Ratchet Games. All rights reserved.
 *
 */

#ifdef __APPLE__
#   include <OpenGL/OpenGL.h>
#   include <OpenGL/glu.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <stdio.h>
#   include <stdlib.h>
#endif

#include <string>
#include <vector>
using namespace std;
#ifndef ITEMS_H
#define ITEMS_H




void itemsInit();

int ballTexture();


#ifndef THETEXTURESLOL
//vector <GLuint> thetextures;
//static int fuckingtexture = ballTexture();
#define THETEXTURESLOL
#endif


void drawBall(double x, double y, int TILESIZE, string textnote);

void drawLine(int theTILESIZE, GLfloat colour[], int angle, int thisx, int thisy);
void drawLine(int theTILESIZE, GLfloat colour[], double x1, double y1, double x2, double y2);
void drawLine(int theTILESIZE, GLfloat colour[], double x1, double y1, double x2, double y2, int thix, int thisy);

void drawBlock(int theTILESIZE, GLfloat colour[], int func);
void drawBlock(int theTILESIZE, GLfloat colour[], int func, string writing);
void drawBlock(int theTILESIZE, GLfloat colour[], int func, int x, int y);
void drawBlock(int theTILESIZE, GLfloat colour[], int func, int x, int y, string writing);

void drawSomething(int theTILESIZE, GLfloat colour[]);
void drawSomething(int theTILESIZE, GLfloat colour[], int x, int y);


void drawBlockGlow(int theTILESIZE, float r, float g, float b);

#endif
