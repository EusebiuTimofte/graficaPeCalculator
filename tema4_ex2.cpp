/*Hearn & Baker */
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <gl/freeglut.h>
#include <string.h>
const double TWO_PI = 6.2831853;
double distancex = 0;
double distancey = 0;
GLsizei winWidth = 600, winHeight = 600;
GLuint regHex;
static GLfloat rotTheta = 0.0;
int unghi = 0;
class scrPt
{
public:
	GLint x, y;
};

static void init(void)
{
	scrPt hexVertex;
	GLdouble hexTheta;
	GLint k;

	glClearColor(1.0, 1.0, 1.0, 1.0);
	regHex = glGenLists(1);
	glNewList(regHex, GL_COMPILE);
	glPointSize(3);
	//deseneaza primul poligon
	glBegin(GL_POLYGON);
	for (k = 0; k < 10; k++)
	{
		hexTheta = TWO_PI * double(k) / 10;
		hexVertex.x = 0 + 100 * cos(hexTheta);
		hexVertex.y = 0 + 100 * sin(hexTheta);
		glColor3f(double(k)/10.0, double(k)/10.0, double(k)/10.0);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glEndList();

}
void displayHex(void)
{
	unghi = (unghi + 1) % 360;
	distancex += 0.1;
	distancey += 0.1;


	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glTranslated(distancex, distancey, 0);
	glPushMatrix();
	glRotated(unghi, 0, 0, 1);
	glCallList(regHex);
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
	glFlush();
}

void mouse(int button, int state, int x, int y)
{
	distancex = 0.0;
	distancey = 0.0;
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-300, 300.0, -300.0, 300.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Hexagon - utilizarea listelor de display");

	init();
	glutDisplayFunc(displayHex);
	glutIdleFunc(displayHex);
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}



