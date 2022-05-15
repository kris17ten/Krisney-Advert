#pragma once
// #include loads up library files, the order can matter
// generally load glut.h last
#include <stdio.h>  // this library is for standard input and output
#include <stdlib.h>
#include <math.h> //for rotation and math-y stuff
#include "glut.h"// this library is for glut the OpenGL Utility Toolkit

/*Header file that includes non-body functions. The functions are defined in their respective files. 
To share the functions across the file, this file is required.*/

//UTILITYFUNCTIONS
void drawCircle(float cx, float cy, float r, int num_segments);
void drawSemiCircle(float cx, float cy, float r, int num_segments);
void drawSemiArc(float cx, float cy, float r, int num_segments);
void drawArc(float cx, float cy, float r, float rad, int num_segments);
void drawFilledCircle(float cx, float cy, float r, int num_segments);
void drawFilledSemiCircle(float cx, float cy, float r, int num_segments);
void drawChangeYtb(float x, float yS, float yE);
void drawChangeYbt(float x, float yS, float yE);
void drawChangeXlr(float xS, float xE, float y);
void drawChangeXrl(float xS, float xE, float y);
void drawChangeXYrl(float x, float yS, float yE);
void drawChangeXYlr(float x, float yS, float yE);
void krisneyTween(float source[][2], float destination[][2], int numPoints, double proportion, float tweenPoly[][2]);
void renderSpacedBitmapString(float x, float y, void *font, char *string);


//ALPHABET
void drawAlphabet(char letter, float tx, float ty);


//COMPUTER
void drawScreenScene();
void animateScreenScene();
void goBlank();
void drawEndTransmission();
void end();
void drawEndCredits();


//UNIVERSITY
void drawUniScene();


//CLASSROOM
void drawClassScene();


//BRAIN
void drawTiredBrainScene();
void drawHappyBrainScene();
void drawExtBrainScene();


//KRISNEY
void drawKrisney();
void writeKrisneyLine();
void drawKrisneyScene();
void animateKrisneyScene();
void shortCircuit();


//KRISSYPOO
void drawKrissy();
void animateKrissy();
void drawSurprisedKrissy();
