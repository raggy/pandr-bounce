/*
 *  text.h
 *  BallDrop
 *
 *  Created by Robin Hayes on 04/05/2010.
 *  Copyright 2010 Propellor and Ratchet Games. All rights reserved.
 *
 */

#include <OpenGL/OpenGL.h>
#include <string>

using namespace std;

#ifndef TEXT_H
#define TEXT_H

void Text(string msg, int x, int y);
void Text(string msg, int x, int y, float size);
void Text(string msg, int x, int y, float size, double r, double g, double b);

double TextHeight(int lineheight);

#endif