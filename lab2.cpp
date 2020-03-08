#include <windows.h> //  sunt mentionate fisiere (biblioteci) care urmeaza sa fie incluse
#include <gl/freeglut.h> //freeglut.h
int X[6];
int Y[6];
void init(void)   //initializare fereastra de vizualizare
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  //precizeaza culoarea de fond a ferestrei de vizualizare

    glMatrixMode(GL_PROJECTION);   //se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
    gluOrtho2D(0.0, 1200.0, 0.0, 700.0);  //sunt indicate coordonatele extreme ale ferestrei de vizualizare

    X[0] = 400;
    Y[0] = 400;

    X[1] = 500;
    Y[1] = 350;

    X[2] = 500;
    Y[2] = 200;

    X[3] = 415;
    Y[3] = 150;

    X[4] = 300;
    Y[4] = 200;

    X[5] = 300;
    Y[5] = 335;
}
void desen(void) // procedura desenare
{

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(0, 1, 0);
    glVertex2i(X[0], Y[0]);
    glColor3f(0, 1, 1);
    glVertex2i(X[1], Y[1]);
    glColor3f(0, 0, 1);
    glVertex2i(X[2], Y[2]);
    glColor3f(1, 0, 1);
    glVertex2i(X[3], Y[3]);
    glColor3f(1, 0, 0);
    glVertex2i(X[4], Y[4]);
    glColor3f(1, 1, 0);
    glVertex2i(X[5], Y[5]);
    glEnd();
    glFlush();  //proceseaza procedurile OpenGL cat mai rapid
}
void main(int argc, char** argv)
{
    glutInit(&argc, argv); // initializare GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//  se utilizeaza un singur buffer  modul de colorare RedGreenBlue(= default)
    glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei de vizualizare(in coordonate ecran)
    glutInitWindowSize(1200, 700); // dimensiunile ferestrei
    glutCreateWindow("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

    init(); // executa procedura de initializare
    glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
    glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie
    glutMainLoop(); // ultima instructiune a programului, asteapta(eventuale) noi date de intrare
}