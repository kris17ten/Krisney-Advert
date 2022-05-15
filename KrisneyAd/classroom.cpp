// #include loads up library files, the order can matter
// generally load glut.h last
#include <stdio.h>  // this library is for standard input and output
#include <stdlib.h>
#include <math.h> //for rotation and math-y stuff
#include "krisneyAd.h"
#include "glut.h"// this library is for glut the OpenGL Utility Toolkit

/*Anything to do with the classroom scene*/

//draw a table
void drawTable() {
	glPushMatrix();
	glTranslatef(0.0, 0.0, 10.0);
	//top
	glColor3f(0.58, 0.43, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(-300.0, -50.0);
	glVertex2f(100.0, -50.0);
	glVertex2f(110.0, -90.0);
	glVertex2f(-290.0, -90.0);
	glEnd();

	glColor3f(0.48, 0.33, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(-300.0, -50.0);
	glVertex2f(100.0, -50.0);
	glVertex2f(100.0, -210.0);
	glVertex2f(-300.0, -210.0);
	glEnd();
	glPopMatrix();
}

//lines on the clock
void drawNumbers() {
	const int NUMBEROFPOINTS = 12;
	//initialize point array
	double ptAX[NUMBEROFPOINTS] = { 20 };
	double ptAY[NUMBEROFPOINTS] = { 0 };

	//degree of rotation
	double degree = ((360.0 / NUMBEROFPOINTS) / 180.0) * 3.1415926;

	//find other points
	for (int i = 1; i < NUMBEROFPOINTS; i++) {
		double pt[2] = {
			(ptAX[i - 1] * cos(degree)) - (ptAY[i - 1] * sin(degree)),
			(ptAX[i - 1] * sin(degree)) + (ptAY[i - 1] * cos(degree))
		};
		ptAX[i] = pt[0];
		ptAY[i] = pt[1];
	}

	//drawing
	glPointSize(3.0);
	glBegin(GL_POINTS);
	for (int a = 0; a < NUMBEROFPOINTS; a++) {
		glVertex2d(ptAX[a], ptAY[a]);
	}
	glEnd();
}

//hands on the clock
void drawHourHand() {
	glLineWidth(3.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 8.0);
	glEnd();
}

void drawMinuteHand() {
	glLineWidth(3.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 16.0);
	glEnd();
}

//actual clock
void drawClock() {
	//outline
	glPushMatrix();
	glTranslatef(200.0, 150.0, 0.0);
	glColor3f(0.8, 0.0, 0.0);
	drawCircle(0.0, 0.0, 25.0, 50);

	//hands
	glColor3f(0.0, 1.0, 0.0);
	drawHourHand();
	glColor3f(0.0, 0.0, 1.0);
	drawMinuteHand();

	//number points
	glColor3f(0.0, 0.0, 0.0);
	drawNumbers();

	//body
	glColor3f(0.9, 0.9, 0.9);
	drawFilledCircle(0.0, 0.0, 25.0, 30);
	glPopMatrix();
}

//draw PC screen
void drawPC() {
	glPushMatrix();
	glTranslatef(0.0, 0.0, 10.5);
	//grey outline
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-50.0, 35.0);
	glVertex2f(50.0, 35.0);
	glVertex2f(50.0, -45.0);
	glVertex2f(-50.0, -45.0);
	glEnd();

	//black square - screen
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(-50.0, 35.0);
	glVertex2f(50.0, 35.0);
	glVertex2f(50.0, -45.0);
	glVertex2f(-50.0, -45.0);
	glEnd();
	glPopMatrix();
}

//draw person sitting in front of the screen
void drawPerson() {
	//head
	glPushMatrix();
	glTranslatef(0.0, 0.0, 15.0);
	glColor3f(0.39, 0.17, 0.06);
	drawFilledCircle(0.0, 0.0, 40.0, 40);
	glBegin(GL_POLYGON);
	glVertex2f(0.0, 40.0);
	glVertex2f(2.0, 45.0);
	glVertex2f(-3.0, 38.0);
	glEnd();

	//legs
	glColor3f(0.08, 0.11, 0.55);
	glBegin(GL_POLYGON);
	glVertex2f(-40.0, -190.0);
	glVertex2f(40.0, -190.0);
	glVertex2f(40.0, -240.0);
	glVertex2f(-40.0, -240.0);
	glEnd();
	glPopMatrix();
}

//draw chair
void drawChair() {
	glPushMatrix();
	glTranslatef(0.0, 0.0, 17.0);
	//back
	glColor3f(0.1, 0.0, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(-60.0, -20.0);
	glVertex2f(-50.0, -10.0);
	glVertex2f(50.0, -10.0);
	glVertex2f(60.0, -20.0);
	glVertex2f(50.0, -160.0);
	glVertex2f(-50.0, -160.0);
	glEnd();

	//seat
	glBegin(GL_POLYGON);
	glVertex2f(50.0, -160.0);
	glVertex2f(60.0, -170.0);
	glVertex2f(60.0, -190.0);
	glVertex2f(-60.0, -190.0);
	glVertex2f(-60.0, -170.0);
	glVertex2f(-50.0, -160.0);
	glEnd();

	//leg
	glBegin(GL_POLYGON);
	glVertex2f(-10.0, -190.0);
	glVertex2f(10.0, -190.0);
	glVertex2f(10.0, -240.0);
	glVertex2f(-10.0, -240.0);
	glEnd();
	glPopMatrix();
}

//draw classroom background
void drawClassBackground() {
	//wall
	glColor3f(0.8, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(300.0, 300.0);
	glVertex2f(300.0, -90.0);
	glVertex2f(-300.0, -90.0);
	glVertex2f(-300.0, 300.0);
	glEnd();

	//floor
	glColor3f(0.20, 0.10, 0.35);
	glBegin(GL_POLYGON);
	glVertex2f(300.0, -90.0);
	glVertex2f(300.0, -300.0);
	glVertex2f(-300.0, -300.0);
	glVertex2f(-300.0, -90.0);
	glEnd();
}

//draw on the white board
void drawCS() {
	float CS[][4][2] = { { {-70.0, 100.0}, {-70.0, 90.0}, {-120.0, 90.0}, {-120.0, 100.0} },
	{ {-130.0, 90.0}, {-120.0, 90.0}, {-120.0, 10.0}, {-130.0, 10.0} },
	{ {-70.0, 10.0}, {-70.0, 0.0}, {-120.0, 0.0}, {-120.0, 10.0} },

	{ {-50.0, 100.0}, {-50.0, 90.0}, {0.0, 90.0}, {0.0, 100.0} },
	{ {-60.0, 90.0}, {-50.0, 90.0}, {-50.0, 60.0}, {-60.0, 60.0} },
	{ {0.0, 60.0}, {0.0, 50.0}, {-50.0, 50.0}, {-50.0, 60.0} },
	{ {0.0, 50.0}, {10.0, 50.0}, {10.0, 10.0}, {0.0, 10.0} },
	{ {-50.0, 10.0}, {-50.0, 0.0}, {0.0, 0.0}, {0.0, 10.0} }
	};

	for (int i = 0; i < 8; i++) {
		glBegin(GL_POLYGON);
		for (int j = 0; j < 4; j++) {
			glVertex2fv(CS[i][j]);
		} glEnd();
	}

}

//draw board on the wall
void drawBoard() {
	//writing on board
	glPushMatrix();
	glTranslatef(-80.0, 50.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	drawCS();
	glPopMatrix();

	//border
	glColor3f(0.5, 0.5, 0.5);
	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-250.0, 200.0);
	glVertex2f(30.0, 200.0);
	glVertex2f(30.0, 20.0);
	glVertex2f(-250.0, 20.0);
	glEnd();

	glColor3f(0.8, 0.8, 0.8);
	glLineWidth(5.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-250.0, 200.0);
	glVertex2f(30.0, 200.0);
	glVertex2f(30.0, 20.0);
	glVertex2f(-250.0, 20.0);
	glEnd();

	//actual board
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-250.0, 200.0);
	glVertex2f(30.0, 200.0);
	glVertex2f(30.0, 20.0);
	glVertex2f(-250.0, 20.0);
	glEnd();

	//shadow
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_POLYGON);
	glVertex2f(-245.0, 195.0);
	glVertex2f(33.0, 195.0);
	glVertex2f(33.0, 15.0);
	glVertex2f(-245.0, 15.0);
	glEnd();
}

//draw the classroom scene
void drawClassScene() {
	drawChair();
	drawPerson();
	drawPC();
	drawTable();
	drawClock();
	drawBoard();
	drawClassBackground();
}