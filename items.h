/*
 *  items.h
 *  BallDrop
 *
 *  Created by Robin Hayes on 08/05/2010.
 *  Copyright 2010 Propellor and Ratchet Games. All rights reserved.
 *
 */

#include <OpenGL/OpenGL.h>
#include <string>
#include <vector>
using namespace std;
#ifndef ITEMS_H
#define ITEMS_H

typedef void BYTE;
vector <GLuint> textures;
void ballTexture();

void drawBall(double x, double y, int TILESIZE, string textnote);

void drawLine(int theTILESIZE, GLfloat colour[], double x1, double y1, double x2, double y2);
void drawLine(int theTILESIZE, GLfloat colour[], double x1, double y1, double x2, double y2, int thix, int thisy);

void drawBlock(int theTILESIZE, GLfloat colour[], int func);
void drawBlock(int theTILESIZE, GLfloat colour[], int func, int x, int y);

void drawSomething(int theTILESIZE, GLfloat colour[]);
void drawSomething(int theTILESIZE, GLfloat colour[], int x, int y);
#endif