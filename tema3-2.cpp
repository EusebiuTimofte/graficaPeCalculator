#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)
int x[100];
int y[100];
int z[100];
int nr_puncte;
void desen(void) // procedura desenare  
{
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare

	glColor3f(0.0, 0.0, 1.0); // culoarea punctelor: albastru
	glPointSize(2);
	glLineWidth(2);

	int i;
	glBegin(GL_POINTS);
	for (i = 0; i < 3; i++)
		glVertex3i(x[i], y[i], z[i]);
	glEnd();

	glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // initializare GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition(0, 0); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize(1200, 700); // dimensiunile ferestrei 
	glutCreateWindow("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara
	
	glMatrixMode(GL_PROJECTION);// se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(0.0, 1200.0, 0.0, 700.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare

	glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

	//A
	x[0] = 300;
	y[0] = 300;
	z[0] = 100;
	//B
	x[1] = 700;
	y[1] = 400;
	z[1] = 100;
	//C
	x[2] = 400;
	y[2] = 400;
	z[2] = 100;
	nr_puncte = 3;

	glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
}