// #include loads up library files, the order can matter
// generally load glut.h last
#include <stdio.h>  // this library is for standard input and output
#include <stdlib.h>
#include <math.h> //for rotation and math-y stuff
#include "krisneyAd.h"
#include "glut.h"// this library is for glut the OpenGL Utility Toolkit


/*Anything to do with the Krissy Poo scene*/

int walkCount = 0; //counter for walking

//hair
void drawHair() {
	//face front
	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -18.0, 0.0);
	glScalef(1.0, 0.8, 1.0);
	drawFilledSemiCircle(0, 0, 50, 80);
	glPopMatrix();

	float triangles[3][3][2] = { { { -55.0, 0.0 },{ -50.0, 24.0 },{ -15.0, 24.0 } },
	{ { 50.0, 24.0 },{ 15.0, 24.0 },{ 55.0, 0.0 } },
	{ { -15.0, 24.0 },{ 0.0, 0.0 },{ 15.0, 24.0 } }
	};
	for (int j = 0; j < 3; j++) {
		glBegin(GL_TRIANGLES);
		for (int k = 0; k < 3; k++) {
			glVertex2fv(triangles[j][k]);
		} glEnd();
	}

	float side[4][2] = { { -60.0, 43.0 },{ -68.0, 38.0 },{ -72.0, 13.0 },{ -60.0, 23.0 } };

	//face side
	glBegin(GL_POLYGON);
	for (int a = 0; a < 4; a++) {
		glVertex2fv(side[a]);
	} glEnd();
	glBegin(GL_POLYGON);
	for (int a = 0; a < 4; a++) {
		glVertex2f(-(side[a][0]), side[a][1]);
	} glEnd();

}

//bow
void drawBow() {
	float bowL[11][2] = { { -12.0, 37.0 },{ -20.0, 35.0 },{ -60.0, 30.0 },{ -65.0, 35.0 },
	{ -65.0, 50.0 },{ -60.0, 53.0 },{ -65.0, 59.0 },{ -65.0, 100.0 },{ -60.0, 105.0 },
	{ -55.0, 103.0 },{ -12.0, 55.0 } };
	float bowM[8][2] = { { -18.0, 42.0 },{ -18.0, 54.0 },{ -12.0, 60.0 },
	{ 12.0, 60.0 },{ 18.0, 54.0 },{ 18.0, 42.0 },{ 12.0, 33.0 },{ -12.0, 33.0 } };

	//OUTLINE
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);//left
	for (int i = 0; i < 11; i++) {
		glVertex2fv(bowL[i]);
	} glEnd();
	glBegin(GL_LINE_LOOP);//right
	for (int i = 0; i < 11; i++) {
		glVertex2f(-(bowL[i][0]), bowL[i][1]);
	} glEnd();

	//bow
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);//left
	for (int i = 0; i < 11; i++) {
		glVertex2fv(bowL[i]);
	} glEnd();
	glBegin(GL_POLYGON);//right
	for (int i = 0; i < 11; i++) {
		glVertex2f(-(bowL[i][0]), bowL[i][1]);
	} glEnd();

	glColor3f(0.0, 0.0, 0.0); //middle outline
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 8; i++) {
		glVertex2fv(bowM[i]);
	} glEnd();

	glColor3f(1.0, 0.0, 0.0); //middle
	glBegin(GL_POLYGON);
	for (int i = 0; i < 8; i++) {
		glVertex2fv(bowM[i]);
	} glEnd();
}

//face
void drawFace() {
	//face
	glPushMatrix();
	glScalef(1.1, 1.0, 1.0);
	glTranslatef(0.0, -10.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	drawCircle(0, 0, 70, 100);
	glColor3f(1.0, 1.0, 1.0);
	drawFilledCircle(0, 0, 70, 100);
	glPopMatrix();

	//eyes
	glPushMatrix();//left
	glColor3f(0.0, 0.0, 0.0);
	glScalef(1.0, 3.0, 1.0);
	glTranslatef(20.0, -10.0, 0.1);
	drawFilledCircle(0, 0, 3, 80);
	glPopMatrix();

	glPushMatrix();//right
	glColor3f(0.0, 0.0, 0.0);
	glScalef(1.0, 3.0, 1.0);
	glTranslatef(-20.0, -10.0, 0.1);
	drawFilledCircle(0, 0, 3, 80);
	glPopMatrix();

	//mouth
	glPushMatrix();
	glTranslatef(0.0, -50.0, 0.1);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	drawSemiCircle(0, 0, 6, 50);
	glColor3f(1.0, 0.0, 0.0);
	drawFilledSemiCircle(0, 0, 6, 50);
	glPopMatrix();
}

//head
void drawHead() {
	glPushMatrix();
	glScalef(0.8, 0.8, 1.0);
	glTranslatef(0.0, 80.0, 0.0);
	drawBow();
	drawHair();
	drawFace();
	glPopMatrix();
}

//dress for character
void drawDress() {
	//outline
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0, 60.0);
	glVertex2f(-58.0, -50.0);
	glVertex2f(-60.0, -55.0);
	glVertex2f(-80.0, -120.0);
	glVertex2f(80.0, -120.0);
	glVertex2f(60.0, -55.0);
	glEnd();

	glColor3f(0.9, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.0, 60.0);
	glVertex2f(-58.0, -50.0);
	glVertex2f(-58.0, -70.0);
	glVertex2f(58.0, -70.0);
	glVertex2f(58.0, -50.0);
	glEnd();

	glPushMatrix();
	glTranslatef(0.0, -60.0, 0.0);
	drawFilledCircle(0.0, 0.0, 55.0, 80);
	glPopMatrix();

	glBegin(GL_POLYGON);
	glVertex2f(-60.0, -55.0);
	glVertex2f(-80.0, -120.0);
	glVertex2f(80.0, -120.0);
	glVertex2f(60.0, -55.0);
	glEnd();
}

//draw arms
//upper arm array
float upperArm[][2] = { {-30.0, -30.0}, {-30.0, -70.0}, {-55.0, -70.0}, {-55.0, -30.0} };
//lower arm array
float lowerArm[][2] = { {-18.0, -70.0}, {-18.0, -110.0}, {-43.0, -110.0}, {-43.0, -70.0} };

void drawRightUpperArm() {
	//outline right upper arm
	glPushMatrix();
	glRotatef(25.0, 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	for (int i = 0; i < 4; i += 2) {
		glVertex2f(-(upperArm[i][0]), upperArm[i][1]);
		glVertex2f(-(upperArm[i + 1][0]), upperArm[i + 1][1]);
	} glEnd();

	//right upper arm
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);//right
	for (int i = 0; i < 4; i++) {
		glVertex2f(-(upperArm[i][0]), upperArm[i][1]);
	} glEnd();
	glPopMatrix();
}

void drawRightElbow() {
	//right elbow
	glPushMatrix();
	glTranslatef(65.0, -40.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	drawFilledCircle(0.0, 0.0, 12.0, 50);
	glPopMatrix();
}

void drawRightLowerArm() {
	//outline right lower arm
	glPushMatrix();
	glRotatef(35.0, 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	for (int i = 0; i < 4; i += 2) {
		glVertex2f(-(lowerArm[i][0]), lowerArm[i][1]);
		glVertex2f(-(lowerArm[i + 1][0]), lowerArm[i + 1][1]);
	} glEnd();

	//right lower arm
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);//right
	for (int i = 0; i < 4; i++) {
		glVertex2f(-(lowerArm[i][0]), lowerArm[i][1]);
	} glEnd();
	glPopMatrix();
}

void drawRightWrist() {
	//right wrist outline
	glPushMatrix();
	glRotatef(35.0, 0.0, 0.0, 1.0);
	glTranslatef(30.0, -110.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	drawSemiArc(0.0, 0.0, 12.0, 50);

	//right wrist
	glColor3f(1.0, 1.0, 1.0);
	drawFilledCircle(0.0, 0.0, 12.0, 50);
	glPopMatrix();
}

void drawRightSleeve() {
	glPushMatrix();//right
	glTranslatef(48.0, -2.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	drawCircle(0.0, 0.0, 20.0, 60);
	glColor3f(0.9, 0.0, 0.0);
	drawFilledCircle(0.0, 0.0, 20.0, 60);
	glPopMatrix();
}

void drawRightArm() {
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.3);
	drawRightSleeve();
	glPopMatrix();
	drawRightWrist();
	drawRightLowerArm();
	drawRightElbow();
	drawRightUpperArm();
}

void drawLeftUpperArm() {
	//outline left upper arm
	glPushMatrix();
	glRotatef(-25.0, 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	for (int i = 0; i < 4; i += 2) {
		glVertex2f(upperArm[i][0], upperArm[i][1]);
		glVertex2f(upperArm[i + 1][0], upperArm[i + 1][1]);
	} glEnd();

	//left upper arm
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);//right
	for (int i = 0; i < 4; i++) {
		glVertex2f(upperArm[i][0], upperArm[i][1]);
	} glEnd();
	glPopMatrix();
}

void drawLeftElbow() {
	//left elbow
	glPushMatrix();
	glTranslatef(-65.0, -40.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	drawFilledCircle(0.0, 0.0, 12.0, 50);
	glPopMatrix();
}

void drawLeftLowerArm() {
	//outline left lower arm
	glPushMatrix();
	glRotatef(-35.0, 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	for (int i = 0; i < 4; i += 2) {
		glVertex2f(lowerArm[i][0], lowerArm[i][1]);
		glVertex2f(lowerArm[i + 1][0], lowerArm[i + 1][1]);
	} glEnd();

	//left lower arm
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);//right
	for (int i = 0; i < 4; i++) {
		glVertex2f(lowerArm[i][0], lowerArm[i][1]);
	} glEnd();
	glPopMatrix();
}

void drawLeftWrist() {
	//left wrist outline
	glPushMatrix();
	glRotatef(-35.0, 0.0, 0.0, 1.0);
	glTranslatef(-30.0, -110.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	drawSemiArc(0.0, 0.0, 12.0, 50);

	//left wrist
	glColor3f(1.0, 1.0, 1.0);
	drawFilledCircle(0.0, 0.0, 12.0, 50);
	glPopMatrix();
}

void drawLeftSleeve() {
	glPushMatrix();//left
	glTranslatef(-48.0, -2.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	drawCircle(0.0, 0.0, 20.0, 60);
	glColor3f(0.9, 0.0, 0.0);
	drawFilledCircle(0.0, 0.0, 20.0, 60);
	glPopMatrix();
}

void drawLeftArm() {
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.3);
	drawLeftSleeve();
	glPopMatrix();
	drawLeftWrist();
	drawLeftLowerArm();
	drawLeftElbow();
	drawLeftUpperArm();
}

//draw legs
float aboveKnee[][2] = { {0.0, -110.0}, {0.0, -140.0}, {-45.0, -140.0}, {-45.0, -110.0} };

float knee[][2] = { {0.0, -130.0}, {0.0, -150.0}, {-45.0, -150.0}, {-45.0, -130.0} };

float belowKnee[][2] = { {0.0, -140.0}, {0.0, -168.0}, {-3.0, -170.0}, {-42.0, -170.0}, {-45.0, -168.0}, {-45.0, -140.0} };

float outline[][2] = { {0.0, -110.0}, {0.0, -168.0}, {-3.0, -170.0}, {-42.0, -170.0}, {-45.0, -168.0}, {-45.0, -110.0} };

void drawRightThigh() {
	//right above knee
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++) {
		glVertex2f(-(aboveKnee[i][0]), aboveKnee[i][1]);
	} glEnd();
}

void drawRightKnee() {
	//right knee
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++) {
		glVertex2f(-(knee[i][0]), knee[i][1]);
	} glEnd();
}

void drawRightShin() {
	//right below knee
	glBegin(GL_POLYGON);
	for (int i = 0; i < 6; i++) {
		glVertex2f(-(belowKnee[i][0]), belowKnee[i][1]);
	} glEnd();
}

void drawRightLeg() {
	//right outline
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 6; i++) {
		glVertex2f(-(outline[i][0]), outline[i][1]);
	} glEnd();

	drawRightThigh();
	drawRightShin();
	drawRightKnee();
}

void drawLeftThigh() {
	//left above knee
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++) {
		glVertex2f(aboveKnee[i][0], aboveKnee[i][1]);
	} glEnd();
}

void drawLeftKnee() {
	//left knee
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++) {
		glVertex2f(knee[i][0], knee[i][1]);
	} glEnd();
}

void drawLeftShin() {
	//left below knee
	glBegin(GL_POLYGON);
	for (int i = 0; i < 6; i++) {
		glVertex2f(belowKnee[i][0], belowKnee[i][1]);
	} glEnd();
}

void drawLeftLeg() {
	//left outline
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 6; i++) {
		glVertex2f(outline[i][0], outline[i][1]);
	}glEnd();

	drawLeftThigh();
	drawLeftShin();
	drawLeftKnee();
}

//walking poses
void drawPose1() {
	glPushMatrix();
	glScalef(0.9, 1.0, 1.0);
	drawLeftArm();

	glPushMatrix();
	glRotatef(10.0, 1.0, 0.0, 0.0);
	drawRightArm();
	glPopMatrix();

	drawHead();
	drawDress();

	glPushMatrix();
	glRotatef(10.0, 1.0, 0.0, 0.0);
	drawLeftLeg();
	glPopMatrix();

	drawRightLeg();
	glPopMatrix();
}

void drawPose2() {
	glPushMatrix();
	glScalef(0.9, 1.0, 1.0);

	glPushMatrix();
	glRotatef(10.0, 1.0, 0.0, 0.0);
	drawLeftArm();
	glPopMatrix();

	drawRightArm();
	drawHead();
	drawDress();
	drawLeftLeg();

	glPushMatrix();
	glRotatef(10.0, 1.0, 0.0, 0.0);
	drawRightLeg();
	glPopMatrix();
	glPopMatrix();
}

//draw blink
void drawBlinkEyes() {
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.1);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-23.0, 51.0);
	glVertex2f(23.0, 51.0);
	glVertex2f(23.0, 35.0);
	glVertex2f(-23.0, 35.0);
	glEnd();
	glPopMatrix();
}

//blink
void blink() {
	if (walkCount % 150 < 20) {
		drawBlinkEyes();
	}
}

//walk
void animateKrissy() {
	walkCount++;

	blink();

	if (walkCount % 40 > 20) {
		drawPose2();
	}
	else {
		drawPose1();
	}
}

//draw exclaimation marks
float scaleExclaim = 0.0;
void drawExclaim() {
	glColor3f(1.0, 1.0, 0.0);
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex2f(25.0, 50.0);
	glVertex2f(25.0, 30.0);
	glEnd();

	glPushMatrix();
	glTranslatef(25.0, 20.0, 0.0);
	drawCircle(0.0, 0.0, 2.0, 10);
	glPopMatrix();
}

void animateExclaim(float tx, float ty) {
	glPushMatrix();
	glScalef(scaleExclaim, scaleExclaim, 1.0);
	glTranslatef(tx, ty, 0.0);
	drawExclaim();
	glPopMatrix();
	scaleExclaim += 0.1;

	if (scaleExclaim > 1.2) {
		scaleExclaim = 1.2;
	}
}

//draw character
void drawKrissy() {
	blink();
	glPushMatrix();
	glScalef(0.9, 1.0, 1.0);
	drawLeftArm();
	drawRightArm();
	drawHead();
	drawDress();
	drawLeftLeg();
	drawRightLeg();
	glPopMatrix();
}

//draw surprised character
void drawSurprisedKrissy() {
	//mouth
	glPushMatrix();
	glTranslatef(0.0, 20.0, 0.2);
	glColor3f(0.0, 0.0, 0.0);
	drawFilledCircle(0.0, 0.0, 6.0, 50);
	glPopMatrix();

	blink();
	drawKrissy();

	animateExclaim(60.0, 80.0);
	animateExclaim(70.0, 80.0);
}