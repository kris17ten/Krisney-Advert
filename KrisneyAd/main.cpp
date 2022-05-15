// #include loads up library files, the order can matter
// generally load glut.h last
#include <stdio.h>  // this library is for standard input and output
#include <stdlib.h>
#include <math.h> //for rotation and math-y stuff
#include "krisneyAd.h"
#include "glut.h"// this library is for glut the OpenGL Utility Toolkit


int counter = 0;
int sceneCount = 0;
double zoom = 0.0;
double krissyWalkForward = -1200.0;
double moveOut = 0.0;

// init 3d  Viewing with perpective viewing as in real life
void init3DPerspectiveProjection()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	/* define the projection transformation */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//field of view in y axis (degrees), aspect = ratio between height and width
	//znear & zfar should be > 0
	gluPerspective(60.0, 1.3, 1.0, 10000.0);

	/* define the viewing transformation */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//up vector (0,1,0) means up is aligned with the y axis
	//camera[x, y, z], view[x, y, z], upAlign[x, y, z]
	gluLookAt(0.0, 0.0, 400.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


void krissyPooScene() {
	if (counter <= 20) {
		//put character at back
		glPushMatrix();
		glTranslatef(0.0, 0.0, krissyWalkForward);
		drawKrissy();
		glPopMatrix();
	}
	//character walking to front, and then draw character
	if (krissyWalkForward <= -50 && counter > 20) {
		glPushMatrix();
		glTranslatef(0.0, 0.0, krissyWalkForward);
		animateKrissy();
		glPopMatrix();
		krissyWalkForward += 2.8;
	} else if (counter > 20 && counter <= 560) {
		drawKrissy();
	}
	//character gets surprised
	if (counter > 560 && counter <= 780) {
		drawSurprisedKrissy();
	}
	//pan scene to left
	if (counter > 780) {
		glPushMatrix();
		glTranslatef(moveOut, 0.0, 0.0);
		drawSurprisedKrissy();
		glPopMatrix();
		moveOut -= 5.0;
	}

	//switch to next scene
	if (counter == 1100) {
		counter = 0;
		sceneCount++;
	}
}

void screenScene() {
	//draw screen with mouse, then animate
	if (counter <= 100) {
		drawScreenScene();
	} else {
		animateScreenScene();
	}

	//switch to next scene
	if (counter == 290) {
		counter = 0;
		zoom = 0;
		sceneCount++;
	}
}

void brainScene() {
	//draw the classroom
	if (counter <= 5) {
		drawClassScene();
	}
	else {
		//zoom in to get to brain
		glPushMatrix();
		glTranslatef(0.0, 0.0, zoom);
		drawClassScene();
		glPopMatrix();
		if (zoom >= 400.0) {
			zoom = 400.0;
			drawTiredBrainScene();
		}
		else {
			zoom += 4.0;
		}
	}

	//switch to next scene
	if (counter == 450) {
		counter = 0;
		zoom = 0;
		sceneCount++;
	}
}

void uniScene() {
	//draw uni scene (day to night animation)
	if (counter <= 480) {
		drawUniScene();
	} else { //pan in to classroom
		glPushMatrix();
		glTranslatef(0.0, 0.0, zoom);
		drawUniScene();
		glPopMatrix();
		if (zoom >= 400.0) {
			zoom = 400.0;
			drawClassScene();
		}
		else {
			zoom += 4.0;
		}
	}

	//switch to next scene
	if (counter == 620) {
		counter = 0;
		zoom = 0;
		sceneCount++;
	}
}

void krisneyScene() {
	//draw board and write
	if (counter <= 120) {
		animateKrisneyScene();
	} else {
		drawKrisneyScene();
	}
	//static
	if (counter > 1500) {
		shortCircuit();
	}

	//switch to next scene
	if (counter == 1700) {
		counter = 0;
		zoom = 0;
		sceneCount++;
	}
}

void endTransmissionScene() {
	//draw end transmission
	if (counter > 5) {
		drawEndTransmission();
	}

	//switch to next scene
	if (counter == 280) {
		counter = 0;
		zoom = 0;
		sceneCount++;
	}
}

void endCreditsScene() {
	//end ad screen
	drawEndCredits();

	//switch to next scene
	if (counter == 1200) {
		counter = 0;
		zoom = 0;
		sceneCount++;
	}
}

//outline for second viewport
void drawOutline() {
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(300.0, -230.0);
	glVertex2f(300.0, 230.0);
	glVertex2f(-300.0, 230.0);
	glVertex2f(-300.0, -230.0);
	glEnd();
}

//second viewport to show the brain scene thing; works on scene count
void secondViewPort() {
	glViewport(668, 400, 130, 100);
	if (sceneCount > 1 && sceneCount <= 3) {
		drawOutline();
		drawTiredBrainScene();
	} else if (sceneCount == 4) {
		drawOutline();
		drawHappyBrainScene();
	} else if (sceneCount > 4 && sceneCount <= 5) {
		drawOutline();
		drawExtBrainScene();
	}
}

//function that runs the animation by scene
void runAnimation() {
	secondViewPort();

	//main screen animation
	glViewport(0.0, 0.0, 800, 500);
	switch (sceneCount) {
	case 0: uniScene();
		break;
	case 1: brainScene();
		break;
	case 2: screenScene();
		break;
	case 3: krissyPooScene();
		break;
	case 4: krisneyScene();
		break;
	case 5: endTransmissionScene();
		break;
	case 6: endCreditsScene();
		break;
	case 7: end();
		break;
	}
}

//display function
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	runAnimation();

	glFlush(); // force all drawing to finish
	glutSwapBuffers();
	counter++;
}

//timer
void Timer(int value) {
	if (value) glutPostRedisplay();
	glutTimerFunc(20, Timer, value);
}

//visibility function
void visibility(int state) {
	switch (state) {
	case GLUT_VISIBLE:
		Timer(1);
		break;
	case GLUT_NOT_VISIBLE:
		Timer(0);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);  //perform the GLUT initialization
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // more initialisation
	glutInitWindowSize(800, 500); // set window size
	glutInitWindowPosition(200, 100); // set window position
	glutCreateWindow("Krisney!!"); // create a display with a given caption for the title bar
	glEnable(GL_BLEND); //Enable blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.
	init3DPerspectiveProjection();
	glutDisplayFunc(display);
	glutVisibilityFunc(visibility);

	glEnable(GL_DEPTH_TEST); //depth

	glutMainLoop();

	// this line exits the program
	return 0;
}