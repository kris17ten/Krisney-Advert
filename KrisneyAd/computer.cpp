// #include loads up library files, the order can matter
// generally load glut.h last
#include <stdio.h>  // this library is for standard input and output
#include <stdlib.h>
#include <math.h> //for rotation and math-y stuff
#include "krisneyAd.h"
#include "glut.h"// this library is for glut the OpenGL Utility Toolkit

/*Anything to do with the computer scene*/

//animate mouse over the screen
float moveMouseX = 240.0;
float moveMouseY = -180.0;

//click animation
float zoomClick = 0.0;
bool clicked = false;
bool clickd = false;

//draw mouse / cursor
void drawMouse() {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(4.0, -13.8);
	glVertex2f(6.0, -13.2);
	glVertex2f(7.0, -19.4);
	glVertex2f(5.0, -20.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, -15.0);
	glVertex2f(10.0, -12.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(4.0, -13.8);
	glVertex2f(6.0, -13.2);
	glVertex2f(7.0, -19.4);
	glVertex2f(5.0, -20.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, -15.0);
	glVertex2f(10.0, -12.0);
	glEnd();
}

//draw the clicking animation
void drawClick() {
	//circle animation
	glColor3f(0.0, 0.0, 1.0);
	drawCircle(0.0, 0.0, 10.0, 40);
}

//draw the play button
void drawPlayButton() {
	//play
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-105.0, 10.0);
	glVertex2f(-81.5, -3.5);
	glVertex2f(-105.0, -17.0);
	glEnd();

	//red rectangle
	//mouse hover
	if (moveMouseX <= -80.0 || moveMouseY >= -15.0) {
		glColor3f(0.7, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(-119.0, 17.0);
		glVertex2f(-72.0, 17.0);
		glVertex2f(-72.0, -24.0);
		glVertex2f(-119.0, -24.0);
		glEnd();
	}
	else {
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(-117.0, 15.0);
		glVertex2f(-70.0, 15.0);
		glVertex2f(-70.0, -22.0);
		glVertex2f(-117.0, -22.0);
		glEnd();
	}
}

//draw video
void drawVideoArea() {
	//play button
	drawPlayButton();

	//black viewing area
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(-295.0, 130.0);
	glVertex2f(100.0, 130.0);
	glVertex2f(100.0, -150.0);
	glVertex2f(-295.0, -150.0);
	glEnd();
}

//draw minimize, fullscreen, close buttons
void drawMFCButtons() {
	//minimize
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex2f(245.0, 210.0);
	glVertex2f(251.0, 210.0);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(240.0, 220.0);
	glVertex2f(255.0, 220.0);
	glVertex2f(255.0, 200.0);
	glVertex2f(240.0, 200.0);
	glEnd();

	//fullscreen
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(265.0, 213.0);
	glVertex2f(270.0, 213.0);
	glVertex2f(270.0, 207.0);
	glVertex2f(265.0, 207.0);
	glEnd();

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(260.0, 220.0);
	glVertex2f(275.0, 220.0);
	glVertex2f(275.0, 200.0);
	glVertex2f(260.0, 200.0);
	glEnd();

	//close
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(3.0);
	glBegin(GL_LINES);
	glVertex2f(285.0, 215.0);
	glVertex2f(290.0, 205.0);

	glVertex2f(290.0, 215.0);
	glVertex2f(285.0, 205.0);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(280.0, 220.0);
	glVertex2f(295.0, 220.0);
	glVertex2f(295.0, 200.0);
	glVertex2f(280.0, 200.0);
	glEnd();
}

//draw the rest of the screen
void drawScreenElements() {
	//mfc
	drawMFCButtons();

	//rectangle on top
	glColor3f(0.68, 0.85, 0.9);
	glBegin(GL_POLYGON);
	glVertex2f(-295.0, 220.0);
	glVertex2f(235.0, 220.0);
	glVertex2f(235.0, 200.0);
	glVertex2f(-295.0, 200.0);
	glEnd();

	//second rectangle
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_POLYGON);
	glVertex2f(-295.0, 190.0);
	glVertex2f(290.0, 190.0);
	glVertex2f(290.0, 170.0);
	glVertex2f(-295.0, 170.0);
	glEnd();

	//third rectangle
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2f(-295.0, 160.0);
	glVertex2f(100.0, 160.0);
	glVertex2f(100.0, 140.0);
	glVertex2f(-295.0, 140.0);
	glEnd();

	//rectangle under video
	glColor3f(0.8, 0.3, 0.8);
	glBegin(GL_POLYGON);
	glVertex2f(-295.0, -160.0);
	glVertex2f(100.0, -160.0);
	glVertex2f(100.0, -220.0);
	glVertex2f(-295.0, -220.0);
	glEnd();

	//square at side
	glColor3f(0.2, 0.8, 0.8);
	glBegin(GL_POLYGON);
	glVertex2f(110.0, 160.0);
	glVertex2f(295.0, 160.0);
	glVertex2f(295.0, -25.0);
	glVertex2f(110.0, -25.0);
	glEnd();

	//rectangle under square
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_POLYGON);
	glVertex2f(110.0, -40.0);
	glVertex2f(200.0, -40.0);
	glVertex2f(200.0, -220.0);
	glVertex2f(110.0, -220.0);
	glEnd();

	//series of rectangles under square
	float colors[][3] = { {1.0, 0.0, 0.0}, {1.0, 0.65, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {0.5, 0.0, 0.5} };
	float space = 0.0;
	for (int i = 0; i < 5; i++) {
		glColor3fv(colors[i]);
		glBegin(GL_POLYGON);
		glVertex2f(205.0, -40.0 + space);
		glVertex2f(295.0, -40.0 + space);
		glVertex2f(295.0, -70.0 + space);
		glVertex2f(205.0, -70.0 + space);
		glEnd();
		space -= 37.0;
	}
}

//background
void drawBack() {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(300.0, -300.0);
	glVertex2f(300.0, 300.0);
	glVertex2f(-300.0, 300.0);
	glVertex2f(-300.0, -300.0);
	glEnd();
}

//animate the click
void click() {
	if (clicked && (!clickd)) {
		glPushMatrix();
		glTranslatef(-100.0, 0.0, 0.0);
		glScalef(zoomClick, zoomClick, 1.0);
		drawClick();
		glPopMatrix();
		zoomClick += 0.1;

		if (zoomClick >= 1.0) {
			zoomClick = 0.0;
			clickd = true;
		}
	}
}

//initialPosition  240.0, -180.0
//finalPosition   -100.0,    0.0
//duration         340.0,  180.0
//ratio              9  :  17

//move mouse
void animateMouse() {
	glPushMatrix();
	glTranslatef(moveMouseX, moveMouseY, 0.0);
	drawMouse();
	glPopMatrix();

	if (moveMouseX <= -100.0 || moveMouseY >= 0.0) {
		moveMouseX = -100.0;
		moveMouseY = 0.0;
		clicked = true;
		click();
	}
	else {
		moveMouseX -= 3.0;
		moveMouseY += 1.59;
	}
}

//run the scene
void animateScreenScene() {
	animateMouse();
	drawVideoArea();
	drawScreenElements();
	drawBack();
}

//draw scene
void drawScreenScene() {
	glPushMatrix();
	glTranslatef(240.0, -180.0, 0.0);
	drawMouse();
	glPopMatrix();

	drawVideoArea();
	drawScreenElements();
	drawBack();
}



    //////////////////////////
   //     VIDEO END +      //
  //////////////////////////

float zoomWhite = 0.0; //to make the screen white
float turnOff = 1.0; //end of animation
int sec = 0; //run animation
float xMove = 0.0; //for drawing coloured bars

//make the screen go white
void goBlank() {
	glPushMatrix();
	glScalef(zoomWhite, zoomWhite, 1.0);
	drawBack();
	glPopMatrix();
	zoomWhite += 0.05;
}

//turn off effect
void end() {
	glPushMatrix();
	glScalef(turnOff, turnOff, 1.0);
	drawBack();
	glPopMatrix();
	turnOff -= 0.07;

	if (turnOff <= 0.0) {
		turnOff = 0.0;
	}

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(300.0, -300.0);
	glVertex2f(300.0, 300.0);
	glVertex2f(-300.0, 300.0);
	glVertex2f(-300.0, -300.0);
	glEnd();
}

//draw end of transmission bars
void drawBar(float xL) {
	glBegin(GL_POLYGON);
	glVertex2f(xL, -300.0);
	glVertex2f(xL, 300.0);
	glVertex2f(xL + 75.0, 300.0);
	glVertex2f(xL + 75.0, -300.0);
	glEnd();
}

//draw "END OF TRANSMISSION"
void drawErrText() {
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.4, 0.4, 1.0);
	drawAlphabet('E', -600.0, 0.0);
	drawAlphabet('N', -540.0, 0.0);
	drawAlphabet('D', -470.0, 0.0);

	drawAlphabet('O', -380.0, 0.0);
	drawAlphabet('F', -310.0, 0.0);

	drawAlphabet('T', -220.0, 0.0);
	drawAlphabet('R', -180.0, 0.0);
	drawAlphabet('A', -90.0, 0.0);
	drawAlphabet('N', -40.0, 0.0);
	drawAlphabet('S', 40.0, 0.0);
	drawAlphabet('M', 110.0, 0.0);
	drawAlphabet('I', 200.0, 0.0);
	drawAlphabet('S', 240.0, 0.0);
	drawAlphabet('S', 320.0, 0.0);
	drawAlphabet('I', 400.0, 0.0);
	drawAlphabet('O', 430.0, 0.0);
	drawAlphabet('N', 500.0, 0.0);
	glPopMatrix();
}

//different versions to disrupt
void drawErrTextLoss1() {
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.4, 0.4, 1.0);
	drawAlphabet('E', -600.0, 0.0);
	drawAlphabet('D', -470.0, 0.0);

	drawAlphabet('O', -380.0, 0.0);
	drawAlphabet('F', -310.0, 0.0);

	drawAlphabet('T', -220.0, 0.0);
	drawAlphabet('R', -180.0, 0.0);
	drawAlphabet('N', -40.0, 0.0);
	drawAlphabet('M', 110.0, 0.0);
	drawAlphabet('I', 200.0, 0.0);
	drawAlphabet('S', 240.0, 0.0);
	drawAlphabet('O', 430.0, 0.0);
	drawAlphabet('N', 500.0, 0.0);
	glPopMatrix();

	drawChangeXlr(20.0, 40.0, 80.0);
	drawChangeYbt(-30.0, 230.0, 250.0);
	drawChangeXlr(100.0, 110.0, -180.0);
}

void drawErrTextLoss2() {
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.4, 0.4, 1.0);
	drawAlphabet('E', -600.0, 0.0);
	drawAlphabet('N', -540.0, 0.0);

	drawAlphabet('O', -380.0, 0.0);

	drawAlphabet('T', -220.0, 0.0);
	drawAlphabet('N', -40.0, 0.0);
	drawAlphabet('S', 40.0, 0.0);
	drawAlphabet('M', 110.0, 0.0);
	drawAlphabet('I', 200.0, 0.0);
	drawAlphabet('S', 240.0, 0.0);
	drawAlphabet('S', 320.0, 0.0);
	drawAlphabet('I', 400.0, 0.0);
	drawAlphabet('O', 430.0, 0.0);
	glPopMatrix();

	drawChangeXlr(0.0, 80.0, 120.0);
	drawChangeXlr(-180.0, -170.0, -150.0);
	drawChangeYtb(-120.0, 45.0, 60.0);
}

//draw screen
void drawEndTransmission() {
	sec++;
	if ((sec >= 40 && sec <= 70) || (sec >= 150 && sec <= 180)) {
		drawErrTextLoss1();
	}
	else if (sec >= 85 && sec <= 120) {
		drawErrTextLoss2();
	}
	else {
		drawErrText();
	}

	float colours[][3] = { {1.0, 1.0, 1.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 0.0} };
	for (int i = 0; i < 8; i++) {
		glColor3fv(colours[i]);
		drawBar(-300.0 + xMove);
		xMove += 75.0;
	}
	xMove = 0.0;
}



    //////////////////////////
   //      AD SCREEN       //
  //////////////////////////

//krissy poo bit character
float KPl[][4][2] = { { {-40.0, 60.0}, {-30.0, 60.0}, {-30.0, 10.0}, {-40.0, 10.0} },
	{ {40.0, 60.0}, {30.0, 60.0}, {30.0, 10.0}, {40.0, 10.0} },
	{ {-30.0, 70.0}, {30.0, 70.0}, {30.0, 60.0}, {-30.0, 60.0} },
	{ {-30.0, 10.0}, {30.0, 10.0}, {30.0, 0.0}, {-30.0, 0.0} },
	{ {25.0, 100.0}, {20.0, 100.0}, {20.0, 70.0}, {25.0, 70.0} }, //right bow
	{ {25.0, 100.0}, {20.0, 100.0}, {0.0, 70.0}, {5.0, 70.0} },
	{ {-25.0, 100.0}, {-20.0, 100.0}, {-20.0, 70.0}, {-25.0, 70.0} }, //left bow
	{ {-25.0, 100.0}, {-20.0, 100.0}, {0.0, 70.0}, {-5.0, 70.0} },
	{ {-5.0, 80.0}, {5.0, 80.0}, {5.0, 70.0}, {-5.0, 70.0} }, //middle
	{ {8.0, 38.0}, {5.0, 38.0}, {5.0, 30.0}, {8.0, 30.0} }, //eyes
	{ {-8.0, 38.0}, {-5.0, 38.0}, {-5.0, 30.0}, {-8.0, 30.0} }
};

char alphaArray[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

int letterCounter = 0; //counter to animate

float yVal = -350.0; //for drawing on screen

//for animating the caption
char capArr[] = { 'B', 'E', 'L', 'I', 'E', 'V', 'E', 'T', 'H', 'E', 'I', 'M', 'P', 'O', 'S', 'S', 'I', 'B', 'L', 'E' };
float txArr[] = { -630.0, -560.0, -500.0, -430.0, -400.0, -320.0, -270.0, -160.0, -120.0, -50.0, 50.0, 80.0, 160.0, 230.0, 310.0, 390.0, 470.0, 500.0, 570.0, 630.0 };

int switchLetters = 0; //for going through animating the letters

//draw the character
void drawKrissyPooLine() {
	for (int o = 0; o < 11; o++) {
		glBegin(GL_POLYGON);
		for (int i = 0; i < 4; i++)
			glVertex2fv(KPl[o][i]);
		glEnd();
	}
}

//animates the single letter
void animateSingleLetter(char endLetter, float tx, float ty) {
	letterCounter++;
	//goes through random alphabets
	if (letterCounter % 2 == 0 && letterCounter < 10) {
		drawAlphabet(alphaArray[(int)(rand() % 26)], tx, ty);
	}
	//displays actual letter
	if (letterCounter >= 10) {
		drawAlphabet(endLetter, tx, ty);
	}
}

//draw caption on screen
void drawCaption() {
	glPushMatrix();
	glScalef(0.4, 0.4, 1.0);

	drawAlphabet('B', -630.0, yVal);
	drawAlphabet('E', -560.0, yVal);
	drawAlphabet('L', -500.0, yVal);
	drawAlphabet('I', -430.0, yVal);
	drawAlphabet('E', -400.0, yVal);
	drawAlphabet('V', -320.0, yVal);
	drawAlphabet('E', -270.0, yVal);

	drawAlphabet('T', -160.0, yVal);
	drawAlphabet('H', -120.0, yVal);
	drawAlphabet('E', -50.0, yVal);

	drawAlphabet('I', 50.0, yVal);
	drawAlphabet('M', 80.0, yVal);
	drawAlphabet('P', 160.0, yVal);
	drawAlphabet('O', 230.0, yVal);
	drawAlphabet('S', 310.0, yVal);
	drawAlphabet('S', 390.0, yVal);
	drawAlphabet('I', 470.0, yVal);
	drawAlphabet('B', 500.0, yVal);
	drawAlphabet('L', 570.0, yVal);
	drawAlphabet('E', 630.0, yVal);

	glPopMatrix();
}

//runs through a letter
void runLetter(int pos) {
	//draw all letters
	for (int i = 0; i < pos; i++) {
		drawAlphabet(capArr[i], txArr[i], yVal);
	}
	//animate the current letter
	animateSingleLetter(capArr[pos], txArr[pos], yVal);
}

//animating the caption
void animateCaption() {
	float yVal = -350.0;

	if (letterCounter > 40) {
		letterCounter = 0;
		switchLetters++;
	}

	if (switchLetters < 20) {
		glPushMatrix();
		glScalef(0.4, 0.4, 1.0);
		runLetter(switchLetters);
		glPopMatrix();
	}
	else {
		glPushMatrix();
		glScalef(1.0, 1.0, 1.0);
		drawCaption();
		glPopMatrix();
	}
}

//draw end scene
void drawEndCredits() {
	glColor3f(1.0, 1.0, 1.0);

	glPushMatrix();
	glTranslatef(0.0, 80.0, 0.0);
	animateCaption();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 80.0, 0.0);
	drawKrissyPooLine();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.5, 0.5, 1.0);
	glTranslatef(15.0, 0.0, 0.0);
	drawKrisney();
	glPopMatrix();
}