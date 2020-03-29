#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <gl/freeglut.h>
#include <string.h>
#include <stdio.h>

GLint winWidth = 600, winHeight = 600;
GLint winLeftMargin = 0, winBottomMargin = 0;

GLint roadCenter = winWidth / 2;
GLint roadWidth = winWidth / 2;

GLint centerLinesWidth = 5;
GLint centerLinesHeight = 30;
GLint centerLinesDistancing = 40;

GLint numberOfCenterLines = winHeight / (centerLinesHeight + centerLinesDistancing);

GLint roadMarginWidth = 30;
GLint roadMarginLinesDistancing = 60;
GLint numberOfRoadMarginLines = winHeight / roadMarginLinesDistancing;

GLint carWidth = 60;
GLint carHeight = 120;

GLint carBehindInitialXmin = roadCenter + roadWidth / 10;
GLint carBehindInitialYmax = winBottomMargin + winHeight / 2 + carHeight / 2 - winHeight;
GLint carBehindNowXmin;
GLint carBehindNowYmax;
GLint carBehindYTranslate;
GLint carBehindXTranslate;

GLint enableBehindCarTransform = 1;

GLdouble movementQuantity = 0.0;
GLdouble movementQuantityCar = 0.0;
int mousePressed = 0;


double percent = 0.0;
int enableTranslate = 0;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare
	glMatrixMode(GL_PROJECTION); // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	glOrtho(winLeftMargin, winLeftMargin + winWidth, winBottomMargin, winBottomMargin + winHeight, 21, -1);
	//gluOrtho2D(GLdouble(winLeftMargin),GLdouble(winLeftMargin + winWidth),GLdouble( winBottomMargin),GLdouble( winBottomMargin + winHeight)); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(winLeftMargin + winWidth + 2, winBottomMargin + winHeight / 2, 20, winLeftMargin + winWidth + 2, winBottomMargin + winHeight / 2, 0, 0, 0, 1);
	glLoadIdentity();
	//left green part
	glColor3f(0.0, 1.0, 0.5);
	glBegin(GL_QUADS);
	glVertex3i(winLeftMargin, winBottomMargin, 0);
	glVertex3i(winLeftMargin + roadCenter - roadWidth / 2 - roadMarginWidth, winBottomMargin, 0);
	glVertex3i(winLeftMargin + roadCenter - roadWidth / 2 - roadMarginWidth, winBottomMargin + winHeight, 0);
	glVertex3i(winLeftMargin, winBottomMargin + winHeight, 0);
	glEnd();
	//right green part
	glBegin(GL_QUADS);
	glVertex3i(winLeftMargin + roadCenter + roadWidth/2 + roadMarginWidth, winBottomMargin, 0);
	glVertex3i(winLeftMargin + winWidth, winBottomMargin, 0);
	glVertex3i(winLeftMargin + winWidth, winBottomMargin + winHeight, 0);
	glVertex3i(winLeftMargin + roadCenter + roadWidth / 2 + roadMarginWidth, winBottomMargin + winHeight, 0);
	glEnd();
	//road margin left
	glColor3f(220.0 / 255.0, 220.0 / 255.0, 220.0 / 255.0);
	glBegin(GL_QUADS);
	glVertex3i(winLeftMargin + roadCenter - roadWidth / 2 - roadMarginWidth, winBottomMargin, 0);
	glVertex3i(winLeftMargin + roadCenter - roadWidth / 2, winBottomMargin, 0);
	glVertex3i(winLeftMargin + roadCenter - roadWidth / 2, winBottomMargin + winHeight, 0);
	glVertex3i(winLeftMargin + roadCenter - roadWidth / 2 - roadMarginWidth, winBottomMargin + winHeight, 0);
	glEnd();
	//road margin right
	glBegin(GL_QUADS);
	glVertex3i(winLeftMargin + roadCenter + roadWidth / 2, winBottomMargin, 0);
	glVertex3i(winLeftMargin + roadCenter + roadWidth / 2 + roadMarginWidth, winBottomMargin, 0);
	glVertex3i(winLeftMargin + roadCenter + roadWidth / 2 + roadMarginWidth, winBottomMargin + winHeight, 0);
	glVertex3i(winLeftMargin + roadCenter + roadWidth / 2, winBottomMargin + winHeight, 0);
	glEnd();
	// road
	glColor3f(169.0 / 255.0, 169.0 / 255.0, 169.0 / 255.0);
	glBegin(GL_QUADS);
	glVertex3i(winLeftMargin + roadCenter - roadWidth / 2, winBottomMargin, 0);
	glVertex3i(winLeftMargin + roadCenter + roadWidth / 2 , winBottomMargin, 0);
	glVertex3i(winLeftMargin + roadCenter + roadWidth / 2 , winBottomMargin + winHeight, 0);
	glVertex3i(winLeftMargin + roadCenter - roadWidth / 2, winBottomMargin + winHeight, 0);
	glEnd();

	//the car
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3i(roadCenter + roadWidth / 10, winBottomMargin + winHeight / 2 - carHeight / 2, 0);
	glVertex3i(roadCenter + roadWidth / 10 + carWidth, winBottomMargin + winHeight / 2 - carHeight / 2, 0);
	glVertex3i(roadCenter + roadWidth / 10 + carWidth, winBottomMargin + winHeight / 2 + carHeight / 2, 0);
	glVertex3i(roadCenter + roadWidth / 10, winBottomMargin + winHeight / 2 + carHeight / 2, 0);
	glEnd();

	

	glPushMatrix();
	glTranslated(0.0, GLint(movementQuantity) % (centerLinesHeight + centerLinesDistancing), 0.0);
	// center lines
	glColor3f(255, 255, 255);
	for (int i = -1; i <= numberOfCenterLines + 5; i++)
	{
		glBegin(GL_QUADS);
		glVertex3i(winLeftMargin + roadCenter - centerLinesWidth / 2, i * (centerLinesHeight + centerLinesDistancing), 0);
		glVertex3i(winLeftMargin + roadCenter + centerLinesWidth / 2, i * (centerLinesHeight + centerLinesDistancing), 0);
		glVertex3i(winLeftMargin + roadCenter + centerLinesWidth / 2, i * (centerLinesHeight + centerLinesDistancing) + centerLinesHeight, 0);
		glVertex3i(winLeftMargin + roadCenter - centerLinesWidth / 2, i * (centerLinesHeight + centerLinesDistancing) + centerLinesHeight, 0);
		glEnd();
	}
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.0, GLint(movementQuantity) % (roadMarginLinesDistancing), 0.0);
	//road margin lines
	glColor3f(169.0 / 255.0, 169.0 / 255.0, 169.0 / 255.0);
	for (int i = 0;i <= numberOfRoadMarginLines + 5; i++)
	{
		glBegin(GL_LINES);
		glVertex3i(winLeftMargin + roadCenter - roadWidth / 2 - roadMarginWidth * 9 / 10, i * roadMarginLinesDistancing, 0);
		glVertex3i(winLeftMargin + roadCenter - roadWidth / 2 - roadMarginWidth * 1 / 10, i * roadMarginLinesDistancing, 0);
		glEnd();

		glBegin(GL_LINES);
		glVertex3i(winLeftMargin + roadCenter + roadWidth / 2 + roadMarginWidth * 9 / 10, i * roadMarginLinesDistancing, 0);
		glVertex3i(winLeftMargin + roadCenter + roadWidth / 2 + roadMarginWidth * 1 / 10, i * roadMarginLinesDistancing, 0);
		glEnd();
	}
	
	glPopMatrix();

	glPushMatrix();
	glTranslated(carBehindXTranslate, carBehindYTranslate, 0.0);
	glTranslated((carBehindNowXmin - winLeftMargin + carWidth / 2), (winBottomMargin + winHeight / 2 - carHeight / 2 - winHeight + carHeight / 2), 0);
	glRotated(percent * 70.0, 0, 0, 1);
	glTranslated(-(carBehindNowXmin - winLeftMargin + carWidth / 2), -(winBottomMargin + winHeight / 2 - carHeight / 2 - winHeight + carHeight / 2), 0);

	//car behind
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3i(roadCenter + roadWidth / 10, winBottomMargin + winHeight / 2 - carHeight / 2 - winHeight , 1);
	glVertex3i(roadCenter + roadWidth / 10 + carWidth, winBottomMargin + winHeight / 2 - carHeight / 2 - winHeight , 1);
	glVertex3i(roadCenter + roadWidth / 10 + carWidth, winBottomMargin + winHeight / 2 + carHeight / 2 - winHeight , 1);
	glVertex3i(roadCenter + roadWidth / 10, winBottomMargin + winHeight / 2 + carHeight / 2 - winHeight , 1);
	glEnd();

	glPopMatrix();
	
	glutSwapBuffers();
	glFlush();
}



void idleFunc() {
	movementQuantity -= 0.1;
	if (enableTranslate == 1) movementQuantityCar -= 0.3;
	carBehindYTranslate = ((-GLint(movementQuantityCar)) % (winHeight * 2));
	if (carBehindYTranslate == winHeight * 2 - 1)
	{
		enableTranslate = 0;
		movementQuantityCar = 0.0;
	}
	if (mousePressed == 1 && enableTranslate == 0)
	{
		enableTranslate = 1;
		mousePressed = 0;
	}
	carBehindNowYmax = carBehindInitialYmax + carBehindYTranslate;
	carBehindNowXmin = roadCenter + roadWidth / 10;
	if (carBehindInitialYmax + carBehindYTranslate  < winHeight / 4) {
		
		carBehindXTranslate = 0;
		percent = 0.0;
	}
	else 
	if(carBehindInitialYmax + carBehindYTranslate >= winHeight/4 &&
		carBehindInitialYmax + carBehindYTranslate <= winHeight /2 - carHeight / 4)
	{
		percent = (GLdouble(carBehindNowYmax - winHeight / 4) / GLdouble(winHeight / 4 - carHeight / 4));
		if (percent > 0.5) percent = 1.0 - percent;
		carBehindXTranslate = GLdouble((-roadWidth / 2 + roadWidth/8)) * (GLdouble(carBehindNowYmax - winHeight/4) / GLdouble(winHeight /4 - carHeight / 4));
	}
	else
	if (carBehindInitialYmax + carBehindYTranslate > winHeight / 2 - carHeight / 4 &&
		carBehindInitialYmax + carBehindYTranslate <= winHeight / 2 + carHeight / 4 + carHeight)
	{
		percent = 0;
		carBehindXTranslate = GLdouble((-roadWidth / 2 + roadWidth / 8));
	}
	else
	if (carBehindNowYmax > winHeight / 2 + carHeight / 4 + carHeight &&
		carBehindNowYmax <= winHeight * 3 / 4 +  carHeight)
	{
		percent = (GLdouble(winHeight * 3 / 4 - carBehindNowYmax) / GLdouble(winHeight / 4 - carHeight / 4));
		if (percent < -0.5) percent = -1 - percent;
		carBehindXTranslate = GLdouble((-roadWidth / 2 + roadWidth / 8)) * (GLdouble(winHeight * 3 / 4 - carBehindNowYmax) / GLdouble(winHeight / 4 - carHeight / 4)) - GLdouble((roadWidth / 2 - roadWidth / 8));
	}
	else
	{
		percent = 0;
		carBehindXTranslate = 0;
	}
	glutPostRedisplay();
}


void mouseFunc(int button, int state, int x, int y)
{
	if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		mousePressed = 1;
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // initializare GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition(100, 50); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize(int(winWidth), int(winHeight)); // dimensiunile ferestrei
	glutCreateWindow("Trafic");
	init();
	glutDisplayFunc(draw);
	glutIdleFunc(idleFunc);
	glutMouseFunc(mouseFunc);
	glutMainLoop();
}


