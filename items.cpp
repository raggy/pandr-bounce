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
#include <iostream>
#include <math.h>

#include "items.h"
#include "text.h"

#define PI 3.14159265

void itemsInit(){
    /*cout <<"1: " << fuckingtexture << "\n";
    fuckingtexture = ballTexture();
    cout <<"2: " << fuckingtexture << "\n";*/
    //ballTexture();
}

int ballTexture(){

    //int wrap = 1;

    GLuint texture;
    int width, height;
    char * data;
    FILE * file;

    // open texture data
    file = fopen( "test.raw", "rb" );
    //if ( file == NULL ) return 0;

    // allocate buffer
    width = 256;
    height = 256;
    data = (char*) malloc( width * height * 3 );

    // read texture data
    fread( data, width * height * 3, 1, file );
    fclose( file );

    // allocate a texture name
    //glGenTextures( 1, &texture );

    // select our current texture
    glBindTexture( GL_TEXTURE_2D, texture );

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );

    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    
    // when texture area is large, bilinear filter the first mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    /*glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                     wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                     wrap ? GL_REPEAT : GL_CLAMP );*/
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    //gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
    // build our texture mipmaps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );

    // free buffer
    free( data );

    return texture;
    
}



void drawBall(double x, double y, int TILESIZE, string textnote){
    glPushMatrix();
        glTranslated(x*TILESIZE-(TILESIZE/2), y*TILESIZE-(TILESIZE/2), 0);
        GLfloat colour[] = {1, 1, 0, 1.0f};
        //glMaterialfv(GL_FRONT, GL_DIFFUSE, temp);
        
        /*glBegin(GL_QUADS);
            glVertex2f(-(TILESIZE/2),  (TILESIZE/2));
            glVertex2f( (TILESIZE/2),  (TILESIZE/2));
            glVertex2f( (TILESIZE/2), -(TILESIZE/2));
            glVertex2f(-(TILESIZE/2), -(TILESIZE/2));
        glEnd();*/
        
        /*glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, fuckingtexture);
        
        glBegin( GL_QUADS );
        glTexCoord2d(0.0,0.0); glVertex2f(-(TILESIZE/2),  (TILESIZE/2));
        glTexCoord2d(1.0,0.0); glVertex2f( (TILESIZE/2),  (TILESIZE/2));
        glTexCoord2d(1.0,1.0); glVertex2f( (TILESIZE/2), -(TILESIZE/2));
        glTexCoord2d(0.0,1.0); glVertex2f(-(TILESIZE/2), -(TILESIZE/2));
        glEnd();*/
        
               
        
        
        glBegin(GL_TRIANGLE_FAN);
            
            glColor4f(colour[0], colour[1], colour[2], colour[3]);
            glVertex2f(0, 0);
            int radius = TILESIZE/2;
            for (int angle = 0; angle <= 360; angle +=1){
                glVertex2f(0 + sin(angle) * radius, 0 + cos(angle) * radius);
            }
        glEnd();
        
        //triangle fan isn't smooth, so back to quad with round ball textures I think.
        
        Text(textnote, -4*TILESIZE/10.0, -3*TILESIZE/10.0, TILESIZE/10.0, 0,0,0);


    glPopMatrix();
}



void drawLine(int theTILESIZE, GLfloat colour[], int angle, int thisx, int thisy){
    double x1, x2, y1, y2;
    if (angle >= 180){
        angle -= 180;
    }//only need to define half.

    if (angle == 0){
        x1 = 0.0;
        y1 = 0.5;
        x2 = 1.0;
        y2 = 0.5;
    } else if (angle == 45){
        x1 = 0.0;
        y1 = 0.0;
        x2 = 1.0;
        y2 = 1.0;
    } else if (angle == 90){
        x1 = 0.5;
        y1 = 0.0;
        x2 = 0.5;
        y2 = 1.0;
    } else if (angle == 135){
        x1 = 1.0;
        y1 = 0.0;
        x2 = 0.0;
        y2 = 1.0;
        
    //that's the easy ones...    
    } else if (angle < 45){
        x1 = 0.0;
        y1 = 0.5-(0.5 * (tan(angle*PI/180)));
        x2 = 1.0;
        y2 = 0.5+(0.5 * (tan(angle*PI/180)));
    } else if (angle > 45 && angle < 90){
        x1 = 0.5-(0.5* (tan((90-angle)*PI/180)));
        y1 = 0.0;
        x2 = 0.5+(0.5* (tan((90-angle)*PI/180)));
        y2 = 1.0;
    } else if (angle > 90 && angle < 135){
        x1 = 0.5+(0.5* (tan((angle-90)*PI/180)));
        y1 = 0.0;
        x2 = 0.5-(0.5* (tan((angle-90)*PI/180)));
        y2 = 1.0;
    } else if (angle > 135 && angle < 180){
        x1 = 0.0;
        y1 = 0.5-(0.5 * (tan((angle)*PI/180)));
        x2 = 1.0;
        y2 = 0.5+(0.5 * (tan((angle)*PI/180)));
    }
    drawLine(theTILESIZE, colour, x1, y1, x2, y2, thisx, thisy);
}
void drawLine(int theTILESIZE, GLfloat colour[], double x1, double y1, double x2, double y2){
    drawLine(theTILESIZE, colour, x1, y1, x2, y2, 0, 0);
}
void drawLine(int theTILESIZE, GLfloat colour[], double x1, double y1, double x2, double y2, int thisx, int thisy){
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, colour);
    glBegin(GL_LINES);
        glColor4f(colour[0], colour[1], colour[2], colour[3]);
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
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, colour);
    glBegin(GL_QUADS);
        glColor4f(colour[0], colour[1], colour[2], colour[3]);
        glVertex2f(0+x,  0+y);
        
        //glColor4f(0,0,1,1);
        glVertex2f(theTILESIZE-1+x, 0+y);
        glVertex2f(theTILESIZE-1+x, theTILESIZE-1+y);
        
        //glColor4f(0,1,0,1);
        glVertex2f(0+x, theTILESIZE-1+y);
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

    //glMaterialfv(GL_FRONT, GL_DIFFUSE, colour);
    glBegin(GL_LINE_LOOP);
        glColor4f(colour[0], colour[1], colour[2], 0.5);
        glVertex2f(0+x,  0+y);
        glVertex2f(theTILESIZE-1+x, 0+y);
        glVertex2f(theTILESIZE-1+x, theTILESIZE-1+y);
        glVertex2f(0+x, theTILESIZE-1+y);
    glEnd();
}



/*void drawLineGlow(int theTILESIZE, float r, float g, float b, double x1, double y1, double x2, double y2){//, int thisx, int thisy
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colour);
    glBegin(GL_QUADS);
    
        glColor4f(r, g, b, 1);
        glVertex2f(x1*theTILESIZE, y1*theTILESIZE);
        glVertex2f(x2*theTILESIZE, y2*theTILESIZE);
        
        
    glEnd();
}*/

void drawBlockGlow(int theTILESIZE, float r, float g, float b){
    float amnt = theTILESIZE/3;
    float TILESIZE = theTILESIZE-1.1;
    glBegin(GL_QUADS);
        
        //glMaterialfv(GL_FRONT, GL_DIFFUSE, inwhite);
        glColor4f(r, g, b, 0);
        glVertex2f(0, 0-amnt);// top
        glVertex2f(TILESIZE, 0-amnt);
        //glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
        glColor4f(r, g, b, 1);
        glVertex2f(TILESIZE, 0);
        glVertex2f(0, 0);
        
        glColor4f(r, g, b, 1);
        glVertex2f(TILESIZE, 0);//right
        glColor4f(r, g, b, 0);
        glVertex2f(TILESIZE+amnt, 0);
        glVertex2f(TILESIZE+amnt, TILESIZE);
        glColor4f(r, g, b, 1);
        glVertex2f(TILESIZE, TILESIZE);
        
        
        glVertex2f(0, TILESIZE);//bottom
        glVertex2f(TILESIZE, TILESIZE);
        glColor4f(r, g, b, 0);
        glVertex2f(TILESIZE, TILESIZE+amnt);
        glVertex2f(0, TILESIZE+amnt);
        
        glColor4f(r, g, b, 0);
        glVertex2f(0-amnt, 0);//left
        glColor4f(r, g, b, 1);
        glVertex2f(0, 0);
        glVertex2f(0, TILESIZE);
        glColor4f(r, g, b, 0);
        glVertex2f(0-amnt, TILESIZE);
    glEnd();
    
    glBegin(GL_TRIANGLES);
        glColor4f(r, g, b, 0);
        glVertex2f(0, 0-amnt);//tl
        glVertex2f(0-amnt, 0);
        glColor4f(r, g, b, 1);
        glVertex2f(0, 0);
        
        glColor4f(r, g, b, 0);
        glVertex2f(TILESIZE, 0-amnt);//tr
        glVertex2f(TILESIZE+amnt, 0);
        glColor4f(r, g, b, 1);
        glVertex2f(TILESIZE, 0);
        
        glVertex2f(TILESIZE, TILESIZE);//br
        glColor4f(r, g, b, 0);
        glVertex2f(TILESIZE+amnt, TILESIZE);
        glVertex2f(TILESIZE, TILESIZE+amnt);
        
        glVertex2f(0-amnt, TILESIZE);
        glVertex2f(0, TILESIZE+amnt);
        glColor4f(r, g, b, 1);
        glVertex2f(0, TILESIZE);//bl
    glEnd();
    //let's see what this does
        
}