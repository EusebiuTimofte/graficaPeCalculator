#include<stdio.h>
#include<stdlib.h>
#include<iostream>

int* produs_vectorial(int v1x, int v1y, int v1z, int v2x, int v2y, int v2z)
{
	int* vector = (int*)malloc(3 * sizeof(int));
	vector[0] = v1y * v2z - v2y * v1z;
	vector[1] = v2x * v1z - v1x * v2z;
	vector[2] = v1x * v2y - v2x * v1x;
	return vector;
}

/*Hearn & Baker */
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <gl/freeglut.h>
#include <string.h>

GLsizei winWidth = 600, winHeight = 600;
int x[100];
int y[100];
int k[100]; // k[i] = coordonata k a produsului vectorial in punctul i
int nrofPoints;
int indexOfMostLeftPoint;
class scrPt
{
public:
	GLint x, y;
};

static void init(void)
{
	x[0] = -100;
	y[0] = 0;
	x[1] = -50;
	y[1] = 50;
	x[2] = 0;
	y[2] = 0;
	x[3] = 100;
	y[3] = 250;
	x[4] = -120;
	y[4] = 150;
	nrofPoints = 5;
	indexOfMostLeftPoint = 4;
	k[0] = produs_vectorial(x[0] - x[4], y[0] - y[4], 0, x[1] - x[0], y[1] - y[0], 0)[2];
	for (int i = 1; i < nrofPoints; i++)
	{
		k[i] = produs_vectorial(x[i] - x[i-1], y[i] - y[i-1], 0, x[(i + 1) % nrofPoints] - x[i], y[(i + 1) % nrofPoints] - y[i], 0)[2];
	}
}
void display(void)
{
	glPointSize(2.0);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	for (int i = 0; i < nrofPoints; i++)
	{
		glVertex2i(x[i], y[i]);
		glVertex2i(x[(i + 1) % nrofPoints], y[(i + 1) % nrofPoints]);
	}
	glEnd();
	glPointSize(5.0);
	for (int i = 0; i < nrofPoints; i++)
	{
		if (k[i] * k[indexOfMostLeftPoint] >= 0) {
			glColor3f(0.0, 0.0, 1.0);
		}
		else
		{
			glColor3f(1.0, 0.0, 0.0);
		}
		glBegin(GL_POINTS);
		glVertex2i(x[i], y[i]);
		glEnd();
	}
	glFlush();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv); // initializare GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition(0, 0); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize(500, 500); // dimensiunile ferestrei 
	glutCreateWindow("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(-250.0, 500.0, -250.0, 500.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
	

	init();
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}



