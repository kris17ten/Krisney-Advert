// #include loads up library files, the order can matter
// generally load glut.h last
#include <stdio.h>  // this library is for standard input and output
#include <stdlib.h>
#include <math.h> //for rotation and math-y stuff
#include "krisneyAd.h"
#include "glut.h"// this library is for glut the OpenGL Utility Toolkit

/*Any functions that are constantly used throughout across this project.*/

//draw a circle
void drawCircle(float cx, float cy, float r, int num_segments) {
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 

		//printf("%f, %f\n", x + cx, y + cy);
	}
	glEnd();
}

//draw a semi circle; change the theta value to be multiplied by 1.0
void drawSemiCircle(float cx, float cy, float r, int num_segments) {
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = -1.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 

		//printf("%f, %f\n", x + cx, y + cy);
	}
	glEnd();
}

//draw a semi arc; use GL_LINE_STRIP
void drawSemiArc(float cx, float cy, float r, int num_segments) {
	glBegin(GL_LINE_STRIP);
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = -1.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 

		//printf("%f, %f\n", x + cx, y + cy);
	}
	glEnd();
}

//draw an arc; rad = radians to be multipled for theta
void drawArc(float cx, float cy, float r, float rad, int num_segments) {
	glBegin(GL_LINE_STRIP);
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = rad * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 

		//printf("%f, %f\n", x + cx, y + cy);
	}
	glEnd();
}

//draw a filled circle
void drawFilledCircle(float cx, float cy, float r, int num_segments) {
	glBegin(GL_TRIANGLE_FAN);
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 

		//printf("%f, %f\n", x + cx, y + cy);
	}
	glEnd();
}

//draw a filled semi circle
void drawFilledSemiCircle(float cx, float cy, float r, int num_segments) {
	glBegin(GL_TRIANGLE_FAN);
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = -1.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 

		//printf("%f, %f\n", x + cx, y + cy);
	}
	glEnd();
}

//change vertical position; x will always differ by 10 -> top to bottom
void drawChangeYtb(float x, float yS, float yE) {
	int y = (int)(yS - yE); //top to bottom, so yS > yE
	glBegin(GL_LINES);
	for (int i = 0; i < y; i++) {
		glVertex2f(x, yS);
		glVertex2f(x + 10.0, yS);
		yS -= 1.0;
	}
	glEnd();
}

//change vertical position; x will always differ by 10 -> bottom to top
void drawChangeYbt(float x, float yS, float yE) {
	int y = (int)(yE - yS); //bottom to top, so yS < yE
	glBegin(GL_LINES);
	for (int i = 0; i < y; i++) {
		glVertex2f(x, yS);
		glVertex2f(x + 10.0, yS);
		yS += 1.0;
	}
	glEnd();
}

//change horizontal position; y will always differ by 10 -> left to right
void drawChangeXlr(float xS, float xE, float y) {
	int x = (int)(xE - xS); //left to right, so xE > xS
	glBegin(GL_LINES);
	for (int i = 0; i < x; i++) {
		glVertex2f(xS, y);
		glVertex2f(xS, y - 10.0);
		xS += 1.0;
	}
	glEnd();
}

//change horizontal position; y will always differ by 10 -> right to left
void drawChangeXrl(float xS, float xE, float y) {
	int x = (int)(xS - xE); //left to right, so xE < xS
	glBegin(GL_LINES);
	for (int i = 0; i < x; i++) {
		glVertex2f(xS, y);
		glVertex2f(xS, y - 10.0);
		xS -= 1.0;
	}
	glEnd();
}

//change diagonal position; width will always differ by 10 -> /
void drawChangeXYrl(float x, float yS, float yE) {
	int y = (int)(yS - yE); //top to bottom, so yS > yE
	glBegin(GL_LINES);
	for (int i = 0; i < y; i++) {
		glVertex2f(x, yS);
		glVertex2f(x + 10.0, yS);
		yS -= 1.0;
		x -= 1.0;
	}
	glEnd();
}

//change diagonal position; width will always differ by 10 -> "\"
void drawChangeXYlr(float x, float yS, float yE) {
	int y = (int)(yS - yE); //top to bottom, so yS > yE
	glBegin(GL_LINES);
	for (int i = 0; i < y; i++) {
		glVertex2f(x, yS);
		glVertex2f(x + 10.0, yS);
		yS -= 1.0;
		x += 1.0;
	}
	glEnd();
}

//tweening function
void krisneyTween(float source[][2], float destination[][2], int numPoints, double proportion, float tweenPoly[][2]) {
	for (int p = 0; p < numPoints; p++) {
		// get the source point
		double sourceX = source[p][0];
		double sourceY = source[p][1];

		// get the destination point
		double destinationX = destination[p][0];
		double destinationY = destination[p][1];

		// get the difference between source and destination
		double differenceX = (destinationX - sourceX);
		double differenceY = (destinationY - sourceY);

		// tween point is source position + proportion
	 // of distance between source and destination
		double tweenX = sourceX + (differenceX * proportion);
		double tweenY = sourceY + (differenceY * proportion);

		// create point with tween co-ordinates in tween array
		tweenPoly[p][0] = int(tweenX);
		tweenPoly[p][1] = int(tweenY);
	}
}

//renderSpacedBitmapString(50,400,GLUT_BITMAP_HELVETICA_18,"text"); // Add text on the scene
void renderSpacedBitmapString(float x, float y, void *font, char *string) {
	char *c;
	int x1 = x;
	for (c = string; *c != '\0'; c++) {
		glRasterPos2f(x1, y);
		glutBitmapCharacter(font, *c);
		x1 = x1 + glutBitmapWidth(font, *c);
	}
}