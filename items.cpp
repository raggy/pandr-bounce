/*
 *  items.cpp
 *  BallDrop
 *
 *  Created by Robin Hayes on 08/05/2010.
 *  Copyright 2010 Propellor and Ratchet Games. All rights reserved.
 *
 */
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include <string>
#include "items.h"
#include "text.h"



void ballTexture(){

    int wrap = 1;

    GLuint texture;
    int width, height;
    BYTE * data;
    FILE * file;

    // open texture data
    file = fopen( "test.raw", "rb" );
    //if ( file == NULL ) return 0;

    // allocate buffer
    width = 256;
    height = 256;
    data = malloc( width * height * 3 );

    // read texture data
    fread( data, width * height * 3, 1, file );
    fclose( file );

    // allocate a texture name
    glGenTextures( 1, &texture );

    // select our current texture
    glBindTexture( GL_TEXTURE_2D, texture );

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                     wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                     wrap ? GL_REPEAT : GL_CLAMP );

    // build our texture mipmaps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
                       GL_RGB, GL_UNSIGNED_BYTE, data );

    // free buffer
    free( data );

    textures.push_back(texture);
    
}


void drawBall(double x, double y, int TILESIZE, string textnote){
    glPushMatrix();
        glTranslated(x*TILESIZE-(TILESIZE/2), y*TILESIZE-(TILESIZE/2), 0);
        //GLfloat temp[] = {1, 1, 0, 1.0f};
        //glMaterialfv(GL_FRONT, GL_DIFFUSE, temp);
        
        /*glBegin(GL_QUADS);
            glVertex2f(-(TILESIZE/2),  (TILESIZE/2));
            glVertex2f( (TILESIZE/2),  (TILESIZE/2));
            glVertex2f( (TILESIZE/2), -(TILESIZE/2));
            glVertex2f(-(TILESIZE/2), -(TILESIZE/2));
        glEnd();*/
        
        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, textures[0]);
        
        
        glBegin( GL_QUADS );
        glTexCoord2d(0.0,0.0); glVertex2f(-(TILESIZE/2),  (TILESIZE/2));
        glTexCoord2d(1.0,0.0); glVertex2f( (TILESIZE/2),  (TILESIZE/2));
        glTexCoord2d(1.0,1.0); glVertex2f( (TILESIZE/2), -(TILESIZE/2));
        glTexCoord2d(0.0,1.0); glVertex2f(-(TILESIZE/2), -(TILESIZE/2));
        glEnd();
        
        Text(textnote, -4*TILESIZE/10.0, -3*TILESIZE/10.0, TILESIZE/10.0, 0,0,0);
        
        /*glBegin(GL_TRIANGLE_FAN);
            glVertex2f(0, 0);
            int radius = TILESIZE/2;
            for (int angle = 0; angle <= 360; angle +=5){
                glVertex2f(0 + sin(angle) * radius, 0 + cos(angle) * radius);
            }
        glEnd();*/
        
        //triangle fan isn't smooth, so back to quad with round ball textures I think.

    glPopMatrix();
}



void drawLine(int theTILESIZE, GLfloat colour[], double x1, double y1, double x2, double y2){
    drawLine(theTILESIZE, colour, x1, y1, x2, y2, 0, 0);
}
void drawLine(int theTILESIZE, GLfloat colour[], double x1, double y1, double x2, double y2, int thisx, int thisy){
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colour);
    glBegin(GL_LINES);
        //glColor4f(r,g,b, 1);
        if (y1 == y2){
            y1 +=0.5/theTILESIZE;
            y2 +=0.5/theTILESIZE;
        }
        if (x1 == x2){
            x1 +=0.5/theTILESIZE;
            x2 +=0.5/theTILESIZE;
        }
        glVertex2f(x1*theTILESIZE+thisx, y1*theTILESIZE+thisy);
        glVertex2f(x2*theTILESIZE+thisx, y2*theTILESIZE+thisy);
    glEnd();

}


void drawBlock(int theTILESIZE, GLfloat colour[], int func){
    drawBlock(theTILESIZE, colour, func, 0, 0);
}
void drawBlock(int theTILESIZE, GLfloat colour[], int func, int x, int y){
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colour);
    glBegin(GL_QUADS);
        glVertex3f(0+x,  0+y,  0.0);
        glVertex3f(theTILESIZE-1+x, 0+y,  0.0);
        glVertex3f(theTILESIZE-1+x, theTILESIZE-1+y,  0.0);
        glVertex3f(0+x, theTILESIZE-1+y,  0.0);
    glEnd();
    if (func != 0){
        Text("E4", theTILESIZE/10.0+x, theTILESIZE/10.0+y, theTILESIZE/10.0);
    }
}


void drawSomething(int theTILESIZE, GLfloat colour[]){
    drawSomething(theTILESIZE, colour, 0, 0);
}
void drawSomething(int theTILESIZE, GLfloat colour[], int x, int y){
//I think this ight be the clear tile thing? :/

    glMaterialfv(GL_FRONT, GL_DIFFUSE, colour);
    glBegin(GL_LINE_LOOP);
        glVertex3f(0+x,  0+y,  0.0);
        glVertex3f(theTILESIZE-1+x, 0+y,  0.0);
        glVertex3f(theTILESIZE-1+x, theTILESIZE-1+y,  0.0);
        glVertex3f(0+x, theTILESIZE-1+y,  0.0);
    glEnd();
}