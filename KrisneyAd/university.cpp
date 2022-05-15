// #include loads up library files, the order can matter
// generally load glut.h last
#include <stdio.h>  // this library is for standard input and output
#include <stdlib.h>
#include <math.h> //for rotation and math-y stuff
#include "krisneyAd.h"
#include "glut.h"// this library is for glut the OpenGL Utility Toolkit

/*Anything to do with the university scene*/

/*UNI SCENE*/
//BUILDING
//TREES
//PATHWAY
//CLOUDS; STARS
//SUN; MOON
//BACKGROUND

int count = 0;

//day or night?
bool night = false;

//RGB array for colours going day->night  float dayToNight[][sky || ground || uni || clouds][single set of RGB values]
float dayToNightSky[][3] = { {0.51, 0.79, 0.98}, {0.47, 0.75, 0.94}, {0.43, 0.71, 0.9}, {0.39, 0.67, 0.86}, {0.35, 0.63, 0.82}, {0.31, 0.59, 0.78},
	{0.27, 0.55, 0.74}, {0.23, 0.51, 0.7}, {0.19, 0.47, 0.66}, {0.15, 0.43, 0.62}, {0.11, 0.39, 0.58}, {0.07, 0.35, 0.54}, {0.03, 0.31, 0.5}, {0.0, 0.27, 0.46},
	{0.0, 0.23, 0.42}, {0.0, 0.19, 0.38}, {0.0, 0.15, 0.34} };


//colour change for sky
float skyR = 0.51;
float skyG = 0.79;
float skyB = 0.98;

//colour change for ground
float groundR = 0.25;
float groundG = 0.59;
float groundB = 0.13;

//colour change for uni
float uniR = 0.36;
float uniG = 0.13;
float uniB = 0.04;

//colour change for clouds
float cloudR = 1.0;
float cloudG = 1.0;
float cloudB = 1.0;

//cloud movement
float cloudMove1 = -20.0;
float cloudSpeed1 = 0.1;
float cloudMove2 = -200.0;
float cloudSpeed2 = 0.05;

//stars shining
float starShine[5] = { 0.7, 0.5, 0.8, 0.5, 0.3 };
bool shining[5] = { true, true, true, true, true };
float starMove[5] = { starShine[0], starShine[1], starShine[2], starShine[3], starShine[4] };

//sun frame positions

//moon frame positions

//drawing star points
float star[10][2] = {
	{ 9.510565163, 3.090169944 },
	{ 2.938926261, 4.045084972 },
	{ 0.0, 10.0 },
	{ -2.938926261, 4.045084972 },
	{ -9.510565163, 3.090169944 },
	{ -4.755282581, -1.545084972 },
	{ -5.877852523, -8.090169944 },
	{ 0.0, -5.0 },
	{ 5.877852523, -8.090169944 },
	{ 4.755282581, -1.545084972 }
};

void drawSun(float tx, float ty) {
	glPushMatrix();
	glTranslatef(tx, ty, 0.0);
	glColor3f(1.0, 1.0, 0.6);
	drawFilledCircle(0.0, 0.0, 25.0, 20);

	glColor4f(1.0, 1.0, 0.6, 0.9);
	drawFilledCircle(0.0, 0.0, 30.0, 20);
	glPopMatrix();

}

float thetaSun = 0.0;
void drawSunFrames() {
	glPushMatrix();
	glRotatef(thetaSun, 0.0, 0.0, 1.0);
	drawSun(-200.0, 50.0);
	glPopMatrix();
	thetaSun -= 1.0;

	if (thetaSun <= -220.0) {
		thetaSun = -220.0;
	}
}

void drawMoon(float tx, float ty) {
	glPushMatrix();
	glTranslatef(tx, ty, 0.0);
	glColor3f(0.98, 0.98, 0.98);
	drawFilledCircle(0.0, 0.0, 25.0, 20);

	glColor4f(0.98, 0.98, 0.98, 0.9);
	drawFilledCircle(0.0, 0.0, 28.0, 20);
	glPopMatrix();
}

float thetaMoon = 0.0;
void drawMoonFrames() {
	glPushMatrix();
	glRotatef(thetaMoon, 0.0, 0.0, 1.0);
	drawMoon(-200.0, -100.0);
	glPopMatrix();
	thetaMoon -= 1.0;

	if (thetaMoon <= -80.0) {
		thetaMoon = -80.0;
	}
}

void drawSky(float r, float g, float b) {
	//sky
	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
	glVertex2f(300.0, 300.0);
	glVertex2f(300.0, -90.0);
	glVertex2f(-300.0, -90.0);
	glVertex2f(-300.0, 300.0);
	glEnd();
}

void drawGround(float r, float g, float b) {
	//ground
	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
	glVertex2f(300.0, -90.0);
	glVertex2f(300.0, -300.0);
	glVertex2f(-300.0, -300.0);
	glVertex2f(-300.0, -90.0);
	glEnd();
}

void drawWindow() {
	glColor3f(0.8, 0.8, 0.8);
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-20.0, 20.0);
	glVertex2f(20.0, 20.0);
	glVertex2f(20.0, -20.0);
	glVertex2f(-20.0, -20.0);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(0.0, 20.0);
	glVertex2f(0.0, -20.0);

	glVertex2f(-20.0, 0.0);
	glVertex2f(20.0, 0.0);
	glEnd();

	glColor3f(0.8, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-20.0, 20.0);
	glVertex2f(20.0, 20.0);
	glVertex2f(20.0, -20.0);
	glVertex2f(-20.0, -20.0);
	glEnd();
}

void drawCloud(float tx, float ty) {
	glPushMatrix();
	glTranslatef(tx, ty, 0.0);
	glColor3f(cloudR, cloudG, cloudB);
	drawFilledCircle(-8.0, 6.0, 15.0, 80); //TL
	drawFilledCircle(8.0, 6.0, 15.0, 80); //TR
	drawFilledCircle(-14.0, -4.0, 15.0, 80); //BL
	drawFilledCircle(0.0, -4.0, 15.0, 80); //BM
	drawFilledCircle(14.0, -4.0, 15.0, 80); //BR
	glPopMatrix();
}

void drawCloudsOnScene() {
	drawCloud(cloudMove1, 130.0); //cloud1
	cloudMove1 += cloudSpeed1;

	drawCloud(cloudMove2, 110.0); //cloud2
	cloudMove2 += cloudSpeed2;

	if (cloudMove1 >= 340.0) {
		cloudMove1 = -350.0;
	}

	if (cloudMove2 >= 340.0) {
		cloudMove2 = -350.0;
	}
}

void drawStar(float xc, float yc, float scale) {
	glPushMatrix();
	glScalef(scale, scale, 1.0);
	glColor3f(skyR, skyG, skyB);
	glBegin(GL_POLYGON);
	for (int i = 1; i < 4; i++) {
		glVertex2d(xc + star[i][0], yc + star[i][1]);
	} glEnd();

	glBegin(GL_POLYGON);
	for (int i = 3; i < 6; i++) {
		glVertex2d(xc + star[i][0], yc + star[i][1]);
	} glEnd();

	glBegin(GL_POLYGON);
	for (int i = 5; i < 8; i++) {
		glVertex2d(xc + star[i][0], yc + star[i][1]);
	} glEnd();

	glBegin(GL_POLYGON);
	for (int i = 7; i < 10; i++) {
		glVertex2d(xc + star[i][0], yc + star[i][1]);
	} glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(xc + star[9][0], yc + star[9][1]);
	glVertex2d(xc + star[0][0], yc + star[0][1]);
	glVertex2d(xc + star[1][0], yc + star[1][1]);
	glEnd();

	// middle
	glColor3f(1.0, 1.0, 0.6);
	glBegin(GL_POLYGON);
	glVertex2d(xc + star[9][0], yc + star[9][1]);
	glVertex2d(xc + star[1][0], yc + star[1][1]);
	glVertex2d(xc + star[3][0], yc + star[3][1]);
	glVertex2d(xc + star[5][0], yc + star[5][1]);
	glVertex2d(xc + star[7][0], yc + star[7][1]);
	glEnd();
	glPopMatrix();
}

//animate single star
void animateStar(float x, float y, int starNumber) {
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	drawStar(0.0, 0.0, starMove[starNumber]);
	glPopMatrix();

	//grow and shrink
	if (shining[starNumber] == true) {
		starMove[starNumber] += 0.05;
	}
	else {
		starMove[starNumber] -= 0.05;
	}

	//if grown to max, shirnk
	if (starMove[starNumber] >= starShine[starNumber] + 0.3) {
		shining[starNumber] = false;
	} //if shrunk to min, grow
	else if (starMove[starNumber] <= starShine[starNumber] - 0.4) {
		shining[starNumber] = true;
	}
}

//draw the stars in position
void drawStarsOnScene() {
	animateStar(0.0, 200.0, 0);
	animateStar(-100.0, 100.0, 1);
	animateStar(-230.0, 0.0, 2);
	animateStar(150.0, 220.0, 3);
	animateStar(200.0, 140.0, 4);
	animateStar(250.0, -50.0, 2);
	animateStar(-200.0, 160.0, 4);
}

//building
void drawBuilding() {
	//door
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex2f(-30.0, -80.0);
	glVertex2f(-1.0, -80.0);
	glVertex2f(-1.0, -120.0);
	glVertex2f(-30.0, -120.0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(1.0, -80.0);
	glVertex2f(30.0, -80.0);
	glVertex2f(30.0, -120.0);
	glVertex2f(1.0, -120.0);
	glEnd();

	//window 1
	glPushMatrix();
	glTranslatef(-100.0, 0.0, 0.0);
	drawWindow();
	glPopMatrix();


	//window 2
	drawWindow();

	//window 3
	glPushMatrix();
	glTranslatef(100.0, 0.0, 0.0);
	drawWindow();
	glPopMatrix();

	//name
	glColor3f(1.0, 0.4, 0.4);
	char uniName[11] = "UNIVERSITY";
	renderSpacedBitmapString(-70, 50, GLUT_BITMAP_TIMES_ROMAN_24, uniName);

	//building
	glColor3f(uniR, uniG, uniB);
	glBegin(GL_POLYGON);
	glVertex2f(-150.0, 80.0);
	glVertex2f(150.0, 80.0);
	glVertex2f(150.0, -120.0);
	glVertex2f(-150.0, -120.0);
	glEnd();
}

//sun
void drawSunOnScene() {
	if (count <= 80) {
		drawSun(-200.0, 50.0);
	}
	else {
		drawSunFrames();
	}
}

//moon
void drawMoonOnScene() {
	if (count <= 280) {
		drawMoon(-200.0, -120.0);
	}
	else {
		drawMoonFrames();
	}
}

//lighting effects
void changeSky() {
	drawSky(skyR, skyG, skyB);
	if (count >= 230) {
		if (skyR >= 0.0 && skyG >= 0.15 && skyB >= 0.34) {
			skyR -= 0.005;
			skyG -= 0.005;
			skyB -= 0.005;
		}
		else {
			skyR = 0.0;
			skyG = 0.15;
			skyB = 0.34;
		}
	}
}

void changeGround() {
	drawGround(groundR, groundG, groundB);
	if (count >= 230) {
		if (groundR >= 0.0 && groundG >= 0.27 && groundB >= 0.0) {
			groundR -= 0.002;
			groundG -= 0.002;
			groundB -= 0.002;
		}
		else {
			groundR = 0.0;
			groundG = 0.27;
			groundB = 0.0;
		}
	}
}

void changeClouds() {
	if (count >= 82 && count <= 362) {
		cloudSpeed1 = 0.9;
		cloudSpeed2 = 0.7;
	}
	else {
		cloudSpeed1 = 0.1;
		cloudSpeed2 = 0.05;
	}

	if (count >= 250) {
		if (cloudR >= 0.4 && cloudG >= 0.4 && cloudB >= 0.4) {
			cloudR -= 0.005;
			cloudG -= 0.005;
			cloudB -= 0.005;
		}
		else {
			cloudR = 0.4;
			cloudG = 0.4;
			cloudB = 0.4;
		}
	}
}

void changeBuilding() {
	drawBuilding();
	if (count >= 230) {
		if (uniR >= 0.26 && uniG >= 0.03 && uniB >= 0.0) {
			uniR -= 0.005;
			uniG -= 0.005;
			uniB -= 0.005;
		}
		else {
			uniR = 0.26;
			uniG = 0.03;
			uniB = 0.0;
		}
	}
}

//day or night
void animateScene() {
	if (count >= 280) {
		night = true;
	}
	drawCloudsOnScene();
	drawSunOnScene();
	changeClouds();

	if (night) {
		drawStarsOnScene();
		drawMoonOnScene();
	}
}

//display the scene
void drawUniScene() {
	count++;
	changeBuilding();
	changeGround();
	animateScene();
	changeSky();
}