/*
 *  text.h
 *  BallDrop
 *
 *  Created by Robin Hayes on 04/05/2010.
 *  Copyright 2010 Propellor and Ratchet Games. All rights reserved.
 *
 */

#ifdef __APPLE__
#   include <OpenGL/OpenGL.h>
#else
#   include <GL/gl.h>
#endif

#include <string>

using namespace std;

#ifndef TEXT_H
#define TEXT_H
string itostring(int number);
string ftostring(float number);

void Text(string msg, int x, int y);
void Text(string msg, int x, int y, float size);
void Text(string msg, int x, int y, float size, GLfloat colour[]);
void Text(string msg, int x, int y, float size, double r, double g, double b);

double TextHeight(int lineheight);

#endif
