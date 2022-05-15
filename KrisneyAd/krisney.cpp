// #include loads up library files, the order can matter
// generally load glut.h last
#include <stdio.h>  // this library is for standard input and output
#include <stdlib.h>
#include <math.h> //for rotation and math-y stuff
#include "krisneyAd.h"
#include "glut.h"// this library is for glut the OpenGL Utility Toolkit

/*Anything to do with the krisney scene*/

int lineCount = 0; //for drawing the lines
int lightCount = 0; //for lighting the lights

//tweening
float proportion = 0.0;
float tweenPoly[4][2];

//lights on the sign
struct showlight {
	float x;
	float y;
	bool on = false;
};

    //////////////////////////
   //    FIREWORK BACK     //
  //////////////////////////

#define FIREWORKSIZE 500

// the gravity vector
float gx = 0;
float gy = -0.0025;

float fireworkCenterX, fireworkCenterY;
//variables for firework colour, set once per firework
float fr = 1; float fg = 1;  float fb = 1;

//struct for the firework 
struct lineParticle {
	float x = 0; // position in x
	float y = 0; // position in y
	float inc = 0.8;
	float radius;
	float xd = 0; //direction in x
	float yd = 0; //direction in y
	float fa = 1.0;
};

lineParticle firework[FIREWORKSIZE]; //array of firework

void normalise(int i) {
	float mag;
	mag = sqrt((firework[i].xd*firework[i].xd) + (firework[i].yd*firework[i].yd));
	firework[i].xd = firework[i].xd / mag;
	firework[i].yd = firework[i].yd / mag;
}

void setDirectionVector(int i) {
	firework[i].xd = (float)((rand() % 1000) + 1) / 1000.0;
	firework[i].yd = sqrt(1.0 - (firework[i].xd*firework[i].xd));
	if (rand() % 1000 < 500) firework[i].xd = -firework[i].xd;
	if (rand() % 1000 < 500) firework[i].yd = -firework[i].yd;
}

//initialize the fireworks
void initFirework() {
	for (int i = 0; i < FIREWORKSIZE; i++) {

		firework[i].x = fireworkCenterX;
		firework[i].y = fireworkCenterY;
		firework[i].inc = 0.01 + (float)(rand() % 150) / 1000.0;
		firework[i].radius = (float)(rand() % 15);
		firework[i].fa = 1.0;
		setDirectionVector(i);
	}
	// set fireowrk centre
	fireworkCenterX = -300 + (rand() % 600);
	fireworkCenterY = -220 + (rand() % 440);
	//set firework color
	fr = (float)(rand() % 1000) / 1000.0;
	fg = (float)(rand() % 1000) / 1000.0;
	fb = (float)(rand() % 1000) / 1000.0;
}

//draw the particles
void drawParticleShape(int i) {
	glBegin(GL_LINES);
	glVertex2d(firework[i].x, firework[i].y);
	glVertex2d(firework[i].x + firework[i].xd * 20, firework[i].y + firework[i].yd * 20);
	glEnd();
}

void drawFireParticle(int i)
{
	glColor4f(fr, fg, fb, firework[i].fa);
	glLineWidth(2);

	drawParticleShape(i);
	// update partcile movement based on its speed (inc) and its direction vector
	firework[i].x = firework[i].x + (firework[i].xd*firework[i].inc);
	firework[i].y = firework[i].y + (firework[i].yd*firework[i].inc);
	// add gravity
		// this then  produces a direction vector that is a little longer than 1
	firework[i].yd = firework[i].yd + gy;
	// so the normalise the vector to make length 1
	normalise(i);
	// reduce transparency
	firework[i].fa -= 0.0015;
}

void drawFirework()
{
	// draw each fire particle	
	for (int i = 0; i < FIREWORKSIZE; i++)
	{
		drawFireParticle(i);
	}
	//start a firework in a new position every so often randomly
	if (lightCount % 800 == 0) {
		fireworkCenterX = -300 + (rand() % 600);
		fireworkCenterY = -220 + (rand() % 440);
		initFirework();
	}
}



    //////////////////////////
   //        KRISNEY       //
  //////////////////////////

//All line arrays
float allLine[][4][2] = {
	//K
	{ {-250.0, 100.0}, {-240.0, 100.0}, {-240.0, 100.0}, {-250.0, 100.0} },
	{ {-200.0, 100.0}, {-190.0, 100.0}, {-190.0, 100.0}, {-200.0, 100.0} },
	{ {-250.0, 50.0}, {-240.0, 50.0}, {-240.0, 50.0}, {-250.0, 50.0} },

	//R
	{ {-180.0, 100.0}, {-170.0, 100.0}, {-170.0, 100.0}, {-180.0, 100.0} },
	{ {-180.0, 100.0}, {-180.0, 90.0}, {-180.0, 90.0}, {-180.0, 100.0} },
	{ {-130.0, 90.0}, {-120.0, 90.0}, {-120.0, 90.0}, {-130.0, 90.0} },
	{ {-130.0, 50.0}, {-130.0, 40.0}, {-130.0, 40.0}, {-130.0, 50.0} },
	{ {-180.0, 50.0}, {-170.0, 50.0}, {-170.0, 50.0}, {-180.0, 50.0} },

	//I
	{ {-100.0, 50.0}, {-90.0, 50.0}, {-90.0, 50.0}, {-100.0, 50.0} },
	{ {-100.0, 80.0}, {-90.0, 80.0}, {-90.0, 80.0}, {-100.0, 80.0} },

	//S
	{ {0.0, 100.0}, {0.0, 90.0}, {0.0, 90.0}, {0.0, 100.0} },
	{ {-60.0, 90.0}, {-50.0, 90.0}, {-50.0, 90.0}, {-60.0, 90.0} },
	{ {-50.0, 60.0}, {-50.0, 50.0}, {-50.0, 50.0}, {-50.0, 60.0} },
	{ {0.0, 50.0}, {10.0, 50.0}, {10.0, 50.0}, {0.0, 50.0} },
	{ {0.0, 10.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 10.0} },

	//N
	{ {30.0, 100.0}, {40.0, 100.0}, {40.0, 100.0}, {30.0, 100.0} },
	{ {30.0, 100.0}, {40.0, 100.0}, {40.0, 100.0}, {30.0, 100.0} },
	{ {80.0, 0.0}, {90.0, 0.0}, {90.0, 0.0}, {80.0, 0.0} },

	//E
	{ {110.0, 100.0}, {120.0, 100.0}, {120.0, 100.0}, {110.0, 100.0} },
	{ {110.0, 10.0}, {110.0, 0.0}, {110.0, 0.0}, {110.0, 10.0} },
	{ {110.0, 100.0}, {110.0, 90.0}, {110.0, 90.0}, {110.0, 100.0} },
	{ {110.0, 55.0}, {110.0, 45.0}, {110.0, 45.0}, {110.0, 55.0} },

	//Y
	{ {170.0, 100.0}, {180.0, 100.0}, {180.0, 100.0}, {170.0, 100.0} },
	{ {230.0, 100.0}, {240.0, 100.0}, {240.0, 100.0}, {230.0, 100.0} },
	{ {200.0, 50.0}, {210.0, 50.0}, {210.0, 50.0}, {200.0, 50.0} }
};

//All block arrays
float allBlock[][4][2] = {
	//K
	{ {-250.0, 100.0}, {-240.0, 100.0}, {-240.0, 0.0}, {-250.0, 0.0} },
	{ {-200.0, 100.0}, {-190.0, 100.0}, {-240.0, 50.0}, {-250.0, 50.0} },
	{ {-250.0, 50.0}, {-240.0, 50.0}, {-190.0, 0.0}, {-200.0, 0.0} },

	//R
	{ {-180.0, 100.0}, {-170.0, 100.0}, {-170.0, 0.0}, {-180.0, 0.0} },
	{ {-130.0, 100.0}, {-130.0, 90.0}, {-180.0, 90.0}, {-180.0, 100.0} },
	{ {-130.0, 90.0}, {-120.0, 90.0}, {-120.0, 50.0}, {-130.0, 50.0} },
	{ {-180.0, 50.0}, {-180.0, 40.0}, {-130.0, 40.0}, {-130.0, 50.0} },
	{ {-180.0, 50.0}, {-170.0, 50.0}, {-120.0, 0.0}, {-130.0, 0.0} },

	//I
	{ {-100.0, 50.0}, {-90.0, 50.0}, {-90.0, 0.0}, {-100.0, 0.0} },
	{ {-100.0, 80.0}, {-90.0, 80.0}, {-90.0, 70.0}, {-100.0, 70.0} },

	//S
	{ {-50.0, 100.0}, {-50.0, 90.0}, {0.0, 90.0}, {0.0, 100.0} },
	{ {-60.0, 90.0}, {-50.0, 90.0}, {-50.0, 60.0}, {-60.0, 60.0} },
	{ {0.0, 60.0}, {0.0, 50.0}, {-50.0, 50.0}, {-50.0, 60.0} },
	{ {0.0, 50.0}, {10.0, 50.0}, {10.0, 10.0}, {0.0, 10.0} },
	{ {-50.0, 10.0}, {-50.0, 0.0}, {0.0, 0.0}, {0.0, 10.0} },

	//N
	{ {30.0, 100.0}, {40.0, 100.0}, {40.0, 0.0}, {30.0, 0.0} },
	{ {30.0, 100.0}, {40.0, 100.0}, {90.0, 0.0}, {80.0, 0.0} },
	{ {80.0, 0.0}, {90.0, 0.0}, {90.0, 100.0}, {80.0, 100.0} },

	//E
	{ {110.0, 100.0}, {120.0, 100.0}, {120.0, 0.0}, {110.0, 0.0} },
	{ {160.0, 10.0}, {160.0, 0.0}, {110.0, 0.0}, {110.0, 10.0} },
	{ {160.0, 100.0}, {160.0, 90.0}, {110.0, 90.0}, {110.0, 100.0} },
	{ {140.0, 55.0}, {140.0, 45.0}, {110.0, 45.0}, {110.0, 55.0} },

	//Y
	{ {170.0, 100.0}, {180.0, 100.0}, {210.0, 50.0}, {200.0, 50.0} },
	{ {230.0, 100.0}, {240.0, 100.0}, {210.0, 50.0}, {200.0, 50.0} },
	{ {200.0, 50.0}, {210.0, 50.0}, {210.0, 0.0}, {200.0, 0.0} }
};

//draw each block
void drawBlock(float blockArray[][2]) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
		glVertex2fv(blockArray[i]);
	glEnd();
}

//draw outline
void drawOutlineBlock(float blockArray[][2]) {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++)
		glVertex2fv(blockArray[i]);
	glEnd();
}

//go from single line to block
void writeBlock(float lineArray[][2], float blockArray[][2]) {
	krisneyTween(lineArray, blockArray, 4, proportion, tweenPoly);

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
		glVertex2f(tweenPoly[i][0], tweenPoly[i][1]);	//morphing from line to block
	glEnd();

	proportion += 0.03;

	if (proportion > 1.0) {
		proportion = 0.0;
		lineCount += 1;
	}
}

//draw out Krisney
void drawKrisney() {
	for (int i = 0; i < 25; i++) {
		drawBlock(allBlock[i]);
	}
}

//draw out Krisney
void drawOutlineKrisney() {
	for (int i = 0; i < 25; i++) {
		drawOutlineBlock(allBlock[i]);
	}
}

//runs the step for the switch case; n = position in array
void runStep(int n) {
	for (int i = 0; i < n; i++) {
		drawBlock(allBlock[i]);
	}
	writeBlock(allLine[n], allBlock[n]);
}

//krisney writing - lines
void writeKrisneyLine() {
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(4.0);

	if (lineCount < 25) {
		runStep(lineCount);
	}
	else {
		drawKrisney();
	}
}

//LIGHTS

showlight lightArray[28];

//draw set position for lights
//pos = the position in array; random +/- to find right order for lights
void initLights() {
	int pos = 0;

	float spaceA = -170.0;
	glColor3f(1.0, 1.0, 0.0);
	for (int i = 0; i < 9; i++) {
		lightArray[pos].x = spaceA;
		lightArray[pos].y = 110.0;
		spaceA += 40.0;
		pos++;
	}
	pos += 4;
	spaceA = -80.0;
	for (int i = 0; i < 5; i++) {
		lightArray[pos].x = 180.0;
		lightArray[pos].y = spaceA;
		spaceA += 40.0;
		pos--;
	}
	spaceA = -170.0;
	pos += 14;
	for (int i = 0; i < 9; i++) {
		lightArray[pos].x = spaceA;
		lightArray[pos].y = -110.0;
		spaceA += 40.0;
		pos--;
	}
	pos += 10;
	spaceA = -80.0;
	for (int i = 0; i < 5; i++) {
		lightArray[pos].x = -180.0;
		lightArray[pos].y = spaceA;
		spaceA += 40.0;
		pos++;
	}
}

//draw lights on sign
void drawLight(showlight light) {
	glColor3f(0.9, 0.9, 0.0);
	glPushMatrix();
	glTranslatef(light.x, light.y, 0.0);
	drawFilledCircle(0.0, 0.0, 5.0, 30);

	//if the light is on, draw light
	if (light.on) {
		glLineWidth(4.0);
		glColor3f(1.0, 1.0, 0.5);
		drawCircle(0.0, 0.0, 5.0, 50);
	}
	glPopMatrix();
}

void drawLightsOnScreen() {
	initLights();
	for (int i = 0; i < 28; i++) {
		drawLight(lightArray[i]);
	}
}

//turn off all lights
void turnOffLights() {
	for (int i = 0; i < 28; i++) {
		lightArray[i].on = false;
	}
}


int lightsOn = 0; //how many lights are on?
//run light sequence
void animateLights() {
	lightCount++;
	for (int i = 0; i < lightsOn; i++) {
		lightArray[i].on = true;
	}

	if (lightsOn > 28) {
		turnOffLights();
		lightsOn = 0;
	}

	if (lightCount % 15 == 0) {
		lightsOn++;
	}
	drawLightsOnScreen();
}

//draw sign
void drawLinesOnSign() {
	float spaceB = 0.0;
	glColor3f(0.7, 0.7, 0.7);

	for (int i = 0; i < 5; i++) {
		glBegin(GL_LINES);
		glVertex2f(-170.0, -80.0 + spaceB);
		glVertex2f(170.0, -80.0 + spaceB);
		glEnd();
		spaceB += 40.0;
	}
}

void drawSign() {
	animateLights();
	drawLinesOnSign();

	//white
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-170.0, 100.0);
	glVertex2f(170.0, 100.0);
	glVertex2f(170.0, -100.0);
	glVertex2f(-170.0, -100.0);
	glEnd();

	//red outline
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(-180.0, 120.0);
	glVertex2f(-190.0, 110.0);

	glVertex2f(-190.0, -110.0);
	glVertex2f(-180.0, -120.0);

	glVertex2f(180.0, -120.0);
	glVertex2f(190.0, -110.0);

	glVertex2f(190.0, 110.0);
	glVertex2f(180.0, 120.0);
	glEnd();
}

//draw scene
void drawKrisneyScene() {
	glPushMatrix();
	glScalef(0.8, 0.8, 1.0);
	glTranslatef(10.0, -40.0, 0.0);
	writeKrisneyLine();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.2, 1.2, 1.0);
	drawSign();
	glPopMatrix();

	drawFirework();
}


//move the sign down
float moveSign = 300.0;
void animateKrisneyScene() {
	glPushMatrix();
	glTranslatef(0.0, moveSign, 0.35);
	glScalef(1.2, 1.2, 1.0);
	drawSign();
	glPopMatrix();

	moveSign -= 4.0;

	if (moveSign <= 0.0) {
		moveSign = 0.0;
	}
}

int numberOfDots = 0;
void shortCircuit() {
	for (int i = 0; i < numberOfDots; i++) {
		glColor3f(1.0, 1.0, 1.0);
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glVertex3f((-300.0 + (float)(rand() % 600)), (-300.0 + (float)(rand() % 600)), 1.0);
		glEnd();
	}
	numberOfDots += 50;
}