#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)
#include <iostream>
float x[100];
float y[100];
int nr_puncte;
int se_intersecteaza = 1;
void desen(void) // procedura desenare  
{
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare

	glColor3f(0.0, 0.0, 1.0); // culoarea punctelor: albastru
	glPointSize(5);
	glLineWidth(5);

	int i;
	glBegin(GL_LINES);
	for (i = 0; i < 2; i++)
		glVertex2i(x[i], y[i]);
	glEnd();

	glBegin(GL_LINES);
	glVertex2i(x[2], y[2]);
	glVertex2i(x[3], y[3]);
	glEnd();

	if (se_intersecteaza == 1)
	{
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(5);
		glBegin(GL_POINTS);
		glVertex2i(x[5], y[5]);
		glEnd();
	}



	glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}


int collinear(float x1, float y1, float x2,
	float y2, float x3, float y3)
{
	// Calculation the area of  
	// triangle. We have skipped  
	// multiplication with 0.5  
	// to avoid floating point  
	// computations  
	float a = x1 * (y2 - y3) +
		x2 * (y3 - y1) +
		x3 * (y1 - y2);

	if (a == 0)
		return 1;
	else
		return 0;
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // initializare GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition(0, 0); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize(1200, 700); // dimensiunile ferestrei 
	glutCreateWindow("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara
	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(0.0, 1200.0, 0.0, 700.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare

	glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare


	x[0] = 700.0;
	y[0] = 400.0;
	x[1] = 400.0;
	y[1] = 401.0;
	nr_puncte = 2;
	x[3] = 300.0;
	y[3] = 301.0;
	x[2] = 800.0;
	y[2] = 500.0;
	nr_puncte = 4;

	//verifica daca A,B,C,D sunt necoliniare
	if ( collinear(x[0],y[0],x[1], y[1], x[2], y[2]) && collinear(x[0], y[0], x[1], y[1], x[3], y[3]) )
	{
		printf("Punctele sunt coliniare!");
		exit(1);
	}

	//verifica daca [AB] se intersecteaza cu [CD]

	float ABx = x[1] - x[0];
	float ABy = y[1] - y[0];
	float pantaAB = ABy / ABx;
	float ctAB = float(y[1]) - pantaAB * float(x[1]);

	float CDx = x[3] - x[2];
	float CDy = y[3] - y[2];
	float pantaCD = CDy / CDx;
	float ctCD = float(y[3]) - pantaCD * float(y[3]);

	int se_intersecteaza = 1;

	// -y + panta*x + c = 0
	//verifica daca A si B sunt pe parti diferite ale lui CD
	if ((-float(y[0]) + pantaCD * float(x[0])+ ctCD) * (-float(y[1]) + pantaCD * float(x[1]) + ctCD) > 0)
	{
		printf("A si B sunt pe aceeasi parte a segmentului CD\n");
		se_intersecteaza = 0;
	}

	//verifica daca C si D sunt pe parti diferite ale lui AB
	if ((-float(y[2]) + pantaAB * float(x[2]) + ctAB) * (-float(y[3]) + pantaAB * float(x[3]) + ctAB) > 0)
	{
		printf("C si D sunt pe aceeasi parte a segmentului AB\n");
		se_intersecteaza = 0;
	}

	if (se_intersecteaza == 1)
	{
		//calculeaza punctul de intersectie
		/* s0(xC −xD) + t0(xB −xA) = xC−xA 
		s0(yC −yD) + t0(yB −yA) = yC −yA*/

		//primul coeficient al lui s0 : (xC- xD)
		float s0c1 = x[2] - x[3];
		float s0c2 = y[2] - y[3];

		float t0c1 = x[1] - x[0];
		float t0c2 = y[1] - y[0];
		//termenul din dreapta egalului
		float td1 = x[2] - x[0];
		float td2 = y[2] - y[0];

		//coeficientul cu care trb impartia a doua ecuatie pt a elimina t0
		float coef = -(t0c1 / t0c2);

		float s0 = (td1 + td2 * coef) / (s0c1 + s0c2 * coef);

		//din prima ecuatie obtinem t0 stiind pe s0
		float t0 = (td1 - s0c1 * s0) / t0c1;

		float x_intersectie = t0 * x[1] + (float(1) - t0) * x[0];
		float y_intersectie = t0 * y[1] + (float(1) - t0) * y[0];

		x[5] = x_intersectie;
		y[5] = y_intersectie;

		printf("Intersectia este in punctul (%.6f, %.6f)\n", x_intersectie, y_intersectie);
	}



	glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie

	glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
}