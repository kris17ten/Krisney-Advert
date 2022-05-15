// #include loads up library files, the order can matter
// generally load glut.h last
#include <stdio.h>  // this library is for standard input and output
#include <stdlib.h>
#include <math.h> //for rotation and math-y stuff
#include "krisneyAd.h"
#include "glut.h"// this library is for glut the OpenGL Utility Toolkit

/*Anything to do with the brain scene*/

//circle points to draw brain
float brain[31][2] = { {0.0, 60.0}, {40.0, 60.0}, {80.0, 40.0}, {110.0, 30.0}, {120.0, 0.0}, {110.0, 20.0}, {110.0, -20.0}, {100.0, -30.0}, {100.0, -40.0},
{80.0, -40.0}, {70.0, -50.0}, {50.0, -60.0}, {40.0, -60.0}, {20.0, -50.0}, {0.0, -50.0}, {-20.0, -60.0}, {-40.0, -50.0}, {-70.0, -50.0}, {-120.0, -50.0},
{-100.0, -60.0}, {-140.0, -40.0}, {-140.0, -20.0}, {-120.0, -10.0}, {-120.0, 20.0}, {-100.0, 40.0}, {-90.0, 50.0}, {-80.0, 50.0}, {-60.0, 60.0}, {-20.0, 70.0},
{-40.0, 70.0}, {0.0, 70.0} };

//to animate the pupils of the eye
int eyeCount = 0;

//wave arms
float waveLeft = -60.0; bool cLeft = true;
float waveRight = 0.0; bool cRight = false;

//drawing of the brain
void drawPart(float tx, float ty) {
	glPushMatrix();
	glTranslatef(tx, ty, 0.0);
	glColor3f(1.0, 0.70, 0.75);
	drawFilledCircle(0.0, 0.0, 30.0, 30);
	glLineWidth(4.0);
	glColor3f(0.55, 0.30, 0.35);
	drawCircle(0.0, 0.0, 30.0, 30);
	glPopMatrix();
}

void drawNonOutPart(float tx, float ty) {
	glPushMatrix();
	glTranslatef(tx, ty, 0.0);
	glColor3f(1.0, 0.70, 0.75);
	drawFilledCircle(0.0, 0.0, 20.0, 30);
	glPopMatrix();
}

void drawOutArc(float theta, float tx, float ty, float rad) {
	glPushMatrix();//1
	glRotatef(theta, 0.0, 0.0, 1.0);
	glTranslatef(tx, ty, 0.0);
	glLineWidth(3.0);
	glColor3f(0.55, 0.30, 0.35);
	drawArc(0.0, 0.0, 20.0, rad, 30);
	glPopMatrix();
}

void drawSingleBrainEye(float tx) {
	//red lines for eye
	glLineWidth(2.0);
	glColor4f(1.0, 0.1, 0.1, 0.4);
	glBegin(GL_LINES);
	glVertex2f(tx + 6.0, 6.0);
	glVertex2f(tx + 10.0, 10.0);

	glVertex2f(tx + 6.0, 2.0);
	glVertex2f(tx + 10.0, 4.0);

	glVertex2f(tx + 3.0, -13.0);
	glVertex2f(tx + 7.0, -17.0);

	glVertex2f(tx + -8.0, 0.0);
	glVertex2f(tx + -12.0, -1.0);
	glEnd();

	glPushMatrix();
	glTranslatef(tx, 0.0, 0.0);
	//translucent red to show tired
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 0.5, 0.5, 0.9);
	drawFilledCircle(0.0, 0.0, 18.0, 30);
	glDisable(GL_BLEND);

	//under the eye
	glColor3f(0.4, 0.2, 0.25);
	glLineWidth(2.0);
	drawSemiArc(0.0, 0.0, 20.0, 30);

	//outer eye
	glColor3f(1.0, 1.0, 1.0);
	drawFilledCircle(0.0, 0.0, 20.0, 30);
	glPopMatrix();
}

void drawPupils(float tx) {
	//little white dot
	glColor3f(1.0, 1.0, 1.0);
	drawFilledCircle(3.0, 2.0, 1.0, 30);

	glPushMatrix(); //left
	glTranslatef(-40.0 + tx, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	drawFilledCircle(0.0, 0.0, 8.0, 30);

	glPopMatrix();


	//little white dot
	glColor3f(1.0, 1.0, 1.0);
	drawFilledCircle(3.0, 2.0, 1.0, 30);

	glPushMatrix(); //right
	glTranslatef(20.0 + tx, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	drawFilledCircle(0.0, 0.0, 8.0, 30);

	glPopMatrix();
}

void animatePupils() {
	eyeCount++;
	if (eyeCount % 4 > 2) {
		drawPupils(0.5);
	}
	else {
		drawPupils(-0.5);
	}
}

void drawBrainTiredEyes() {
	animatePupils();
	drawSingleBrainEye(-40.0); //left
	drawSingleBrainEye(20.0); //right
}

void drawBrainHappyEyes() {
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(5.0);

	glPushMatrix(); //left
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glScalef(1.0, 1.3, 1.0);
	glTranslatef(-20.0, 0.0, 0.0);
	drawSemiArc(0.0, 0.0, 15.0, 40);
	glPopMatrix();

	glPushMatrix(); //right
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glScalef(1.0, 1.3, 1.0);
	glTranslatef(40.0, 0.0, 0.0);
	drawSemiArc(0.0, 0.0, 15.0, 40);
	glPopMatrix();
}

void drawBrainLeftUpperArm() {
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex2f(-110.0, -10.0);
	glVertex2f(-140.0, -10.0);
	glEnd();
}

void drawBrainLeftLowerArm() {
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex2f(-140.0, -10.0);
	glVertex2f(-170.0, -10.0);
	glEnd();
}

void drawBrainLeftWrist() {
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(-170.0, -10.0);
	glVertex2f(-175.0, -15.0);
	glVertex2f(-185.0, -15.0);
	glVertex2f(-190.0, -12.5);
	glVertex2f(-190.0, -7.5);
	glVertex2f(-185.0, -5.0);
	glVertex2f(-175.0, -5.0);
	glEnd();
}

void drawBrainRightUpperArm() {
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex2f(90.0, -10.0);
	glVertex2f(120.0, -10.0);
	glEnd();
}

void drawBrainRightLowerArm() {
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex2f(120.0, -10.0);
	glVertex2f(150.0, -10.0);
	glEnd();
}

void drawBrainRightWrist() {
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(150.0, -10.0);
	glVertex2f(155.0, -15.0);
	glVertex2f(165.0, -15.0);
	glVertex2f(170.0, -12.5);
	glVertex2f(170.0, -7.5);
	glVertex2f(165.0, -5.0);
	glVertex2f(155.0, -5.0);
	glEnd();
}

void drawBrainLeftThigh() {
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex2f(-40.0, -60.0);
	glVertex2f(-40.0, -90.0);
	glEnd();
}

void drawBrainLeftShin() {
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex2f(-40.0, -90.0);
	glVertex2f(-40.0, -120.0);
	glEnd();
}

void drawBrainLeftFoot() {
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(-40.0, -120.0);
	glVertex2f(-40.0, -130.0);
	glVertex2f(-55.0, -130.0);
	glVertex2f(-50.0, -120.0);
	glEnd();
}

void drawBrainRightThigh() {
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex2f(20.0, -60.0);
	glVertex2f(20.0, -90.0);
	glEnd();
}

void drawBrainRightShin() {
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex2f(20.0, -90.0);
	glVertex2f(20.0, -120.0);
	glEnd();
}

void drawBrainRightFoot() {
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(20.0, -120.0);
	glVertex2f(20.0, -130.0);
	glVertex2f(35.0, -130.0);
	glVertex2f(30.0, -120.0);
	glEnd();
}

void drawBrainBody() {
	//random outlines in middle
	drawOutArc(0.0, 70.0, 0.0, -0.5);
	drawOutArc(-340.0, 50.0, -45.0, -0.4);
	drawOutArc(-80.0, 0.0, -80.0, -0.7);
	drawOutArc(120.0, -50.0, -45.0, 0.4);
	drawOutArc(-45.0, 85.0, 20.0, -0.4);

	glPushMatrix(); //center
	glScalef(3.5, 2.0, 1.0);
	glColor3f(1.0, 0.70, 0.75);
	drawFilledCircle(0.0, 0.0, 40.0, 30);
	glPopMatrix();

	//non-outline circles
	drawNonOutPart(-125.0, -50.0);
	drawNonOutPart(-140.0, -25.0);
	drawNonOutPart(-80.0, 60.0);
	drawNonOutPart(95.0, -48.0);

	//body
	for (int i = 0; i < 31; i++) {
		drawPart(brain[i][0], brain[i][1]);
	}
}



//draw and animate scenes

void drawTiredBrain() {
	//eyes
	drawBrainTiredEyes();

	//hands
	drawBrainLeftUpperArm();
	drawBrainLeftLowerArm();
	drawBrainLeftWrist();
	drawBrainRightUpperArm();
	drawBrainRightLowerArm();
	drawBrainRightWrist();

	//feet
	drawBrainLeftThigh();
	drawBrainLeftShin();
	drawBrainLeftFoot();
	drawBrainRightThigh();
	drawBrainRightShin();
	drawBrainRightFoot();

	//body
	drawBrainBody();
}

void drawHappyBrain() {
	//eyes
	drawBrainHappyEyes();

	//body
	drawBrainBody();
}

void drawBrainBackground() {
	glColor3f(0.6, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(300.0, -300.0);
	glVertex2f(300.0, 300.0);
	glVertex2f(-300.0, 300.0);
	glVertex2f(-300.0, -300.0);
	glEnd();
}

void drawJailCell() {
	float bar = 0.0;

	//top
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_POLYGON);
	glVertex2f(300.0, 230.0);
	glVertex2f(300.0, 200.0);
	glVertex2f(-300.0, 200.0);
	glVertex2f(-300.0, 230.0);
	glEnd();

	glColor3f(0.3, 0.3, 0.3);
	glLineWidth(4.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(300.0, 230.0);
	glVertex2f(300.0, 200.0);
	glVertex2f(-300.0, 200.0);
	glVertex2f(-300.0, 230.0);
	glEnd();

	//bottom
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_POLYGON);
	glVertex2f(300.0, -230.0);
	glVertex2f(300.0, -200.0);
	glVertex2f(-300.0, -200.0);
	glVertex2f(-300.0, -230.0);
	glEnd();

	glColor3f(0.3, 0.3, 0.3);
	glLineWidth(4.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(300.0, -230.0);
	glVertex2f(300.0, -200.0);
	glVertex2f(-300.0, -200.0);
	glVertex2f(-300.0, -230.0);
	glEnd();


	for (int i = 0; i < 5; i++) {
		glColor3f(0.6, 0.6, 0.6);
		glBegin(GL_POLYGON);
		glVertex2f(-280.0 + bar, -300.0);
		glVertex2f(-280.0 + bar, 300.0);
		glVertex2f(-300.0 + bar, 300.0);
		glVertex2f(-300.0 + bar, -300.0);
		glEnd();

		glColor3f(0.3, 0.3, 0.3);
		glLineWidth(4.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(-280.0 + bar, -300.0);
		glVertex2f(-280.0 + bar, 300.0);
		glVertex2f(-300.0 + bar, 300.0);
		glVertex2f(-300.0 + bar, -300.0);
		glEnd();

		bar += 135.0;
	}
}

void drawTiredBrainScene() {
	drawJailCell();
	drawTiredBrain();
	drawBrainBackground();
}

void waveArms() {
	glPushMatrix();
	glTranslatef(-30.0, 0.0, 0.0);
	glRotatef(waveLeft, 0.0, 0.0, 1.0);
	glTranslatef(30.0, 0.0, 0.0);
	drawBrainLeftUpperArm();
	drawBrainLeftLowerArm();
	drawBrainLeftWrist();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(20.0, 0.0, 0.0);
	glRotatef(waveRight, 0.0, 0.0, 1.0);
	glTranslatef(-20.0, 0.0, 0.0);
	drawBrainRightUpperArm();
	drawBrainRightLowerArm();
	drawBrainRightWrist();
	glPopMatrix();

	if (waveLeft >= 0.0) {
		cLeft = false;
	}
	else if (waveLeft <= -60.0) {
		cLeft = true;
	}

	if (waveRight >= 60.0) {
		cRight = true;
	}
	else if (waveRight <= 0.0) {
		cRight = false;
	}

	if (cLeft) {
		waveLeft += 2.0;
	}
	else {
		waveLeft -= 2.0;
	}

	if (cRight) {
		waveRight -= 2.0;
	}
	else {
		waveRight += 2.0;
	}

}

//brain dancing
void drawBrainPose1() {
	glPushMatrix();
	glTranslatef(30.0, -58.0, 0.0);
	glRotatef(-40.0, 0.0, 0.0, 1.0);
	drawBrainLeftThigh();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-85.0, -5.0, 0.0);
	glRotatef(40.0, 0.0, 0.0, 1.0);
	drawBrainLeftShin();
	glPopMatrix();

	drawBrainLeftFoot();

	glPushMatrix();
	glTranslatef(-35.0, -45.0, 0.0);
	glRotatef(40.0, 0.0, 0.0, 1.0);
	drawBrainRightThigh();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(82.0, -17.0, 0.0);
	glRotatef(-40.0, 0.0, 0.0, 1.0);
	drawBrainRightShin();
	glPopMatrix();

	drawBrainRightFoot();

	glPushMatrix();
	glTranslatef(0.0, -10.0, 0.0);
	drawHappyBrain();
	glPopMatrix();
}

void drawBrainPose2() {
	//draw legs
	drawBrainLeftThigh();
	drawBrainLeftShin();
	drawBrainLeftFoot();
	drawBrainRightThigh();
	drawBrainRightShin();
	drawBrainRightFoot();

	drawHappyBrain();
}

void drawExtBrainScene() {
	drawBrainPose2();
	drawBrainBackground();
}

void animateLegs() {
	eyeCount++;
	if (eyeCount % 30 < 15) {
		drawBrainPose1();
	}
	else {
		drawBrainPose2();
	}
}

void drawHappyBrainScene() {
	waveArms();
	animateLegs();
	drawBrainBackground();
}