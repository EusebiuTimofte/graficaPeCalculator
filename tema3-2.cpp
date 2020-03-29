#include<math.h>
#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)
GLfloat x[100];
GLfloat y[100];
GLfloat z[100];
int nr_puncte;
GLfloat A;
GLfloat B;
GLfloat C;

GLint winWidth = 600, winHeight = 600;
GLfloat x0 = 0.0, y00 = 0.0, z0 = 0.0;
GLfloat xref = 0.0, yref = 0.0, zref = 400.0;
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0;

GLfloat xwMin = -1000.0, ywMin = -1000.0, xwMax = 1000.0, ywMax = 1000.0;

GLfloat dnear = 0.0, dfar = 1000.0;

void desen(void) // procedura desenare  
{
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare

	glColor3f(0.0, 0.0, 1.0); // culoarea punctelor: albastru
	glPointSize(2);

	int i;
	glLineWidth(4.0);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3f(x[0], y[0], z[0]);
	glVertex3f(x[1], y[1], z[1]);
	glVertex3f(x[3], y[3], z[3]);
	glVertex3f(x[2], y[2], z[2]);
	glEnd();
	glPointSize(4);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex3f(x[4], y[4], z[4]);
	glEnd();
	//deseneaza vector avand aceeasi directie si sens cu ale normalei
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(x[0], y[0], z[0]);
	glVertex3f(x[0] + A, y[0] + B, z[0] + C);
	glEnd();
	glColor3f(1.0, 1.0, 0.0);
	// deseneaza O1
	glBegin(GL_LINES);
	glVertex3f(x[4], y[4], z[4]);
	glVertex3f(x[4] +  A/500, y[4] + B/500, z[4] + C/500);
	glEnd();
	//deseneaza O2
	glBegin(GL_LINES);
	glVertex3f(x[4], y[4], z[4]);
	glVertex3f(x[4] - A/500, y[4] - B/500, z[4] - C/500);
	glEnd();

	glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

void mouse2(int button, int state, int xfunc, int yfunc)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			glMatrixMode(GL_MODELVIEW);
			//x[4] + A / 500, y[4] + B / 500, z[4] + C / 500 sunt coordonatele lui O1
			//x[4], y[4], z[4] sunt coordonatele lui M
			//Vx=0, Vy=1, Vz=0
			gluLookAt(x[4] + A / 10, y[4] + B / 10, z[4] + C / 10, x[4], y[4], z[4], Vx, Vy, Vz);
			glMatrixMode(GL_PROJECTION);
			glOrtho(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
			//desen();
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			glMatrixMode(GL_MODELVIEW);
			//x[4] - A / 500, y[4] - B / 500, z[4] - C / 500 sunt coordonatele lui O2
			//x[4], y[4], z[4] sunt coordonatele lui M
			//Vx=0, Vy=1, Vz=0
			gluLookAt(x[4] - A / 50, y[4] - B / 50, z[4] - C / 50, x[4], y[4], z[4], Vx, Vy, Vz);
			glMatrixMode(GL_PROJECTION);
			glOrtho(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
			//desen();
		}
		break;
	}
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // initializare GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition(0, 0); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize(winWidth, winHeight); // dimensiunile ferestrei 
	glutCreateWindow("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara
	
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(x0, y00, z0, xref, yref, zref, Vx, Vy, Vz);

	glMatrixMode(GL_PROJECTION);
	glOrtho(xwMin, xwMax, ywMin, ywMax, dnear, dfar);

	//A
	x[0] = 300;
	y[0] = 300;
	z[0] = 100;
	//B
	x[1] = 700;
	y[1] = 400;
	z[1] = 50;
	//C
	x[2] = 400;
	y[2] = 400;
	z[2] = 300;
	nr_puncte = 3;
	//M
	x[4] = (x[0] + x[1] + x[2]) /3;
	y[4] = (y[0] + y[1] + y[2]) /3;
	z[4] = (z[0] + z[1] + z[2]) /3;

	// vectorul OD = OA+AC+AB , deci D = A + (C-A) + (B-A) = B + C - A
	x[3] = x[1] + x[2] - x[0];
	y[3] = y[1] + y[2] - y[0];
	z[3] = z[1] + z[2] - z[0];

	//vector perpendicular pe plan: (A,B,C)
	A = y[1] * z[2] + y[3] * z[1] + y[2] * z[3] - y[3] * z[2] - y[2] * z[1] - y[1] * z[3];
	B = x[3] * z[2] + x[2] * z[1] + x[1] * z[3] - x[1] * z[2] - x[3] * z[1] - x[2] * z[3];
	C = x[1] * y[2] + x[3] * y[1] + x[2] * y[3] - x[3] * y[2] - x[2] * y[1] - x[1] * y[3];
	// calculam sqrt(A^2 + B^2 + C^2)
	double radical = sqrt(double(A) * double(A) + double(B) * double(B) + double(C) * double(C));
	//normala este (A/radical, B/radical, C/radical)

	glutMouseFunc(mouse2);
	glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
}