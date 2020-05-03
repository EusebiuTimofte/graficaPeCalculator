//SURSA:  lighthouse3D:  http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/

#include<gl/freeglut.h>
#include<math.h>
// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;

enum {
    WINTER, SPRING
};

int rendermode = WINTER;

void menu(int selection)
{
  rendermode = selection;
  glutPostRedisplay();
}

void changeSize(int w, int h)
{

// Prevent a divide by zero, when window is too short
// (you cant make a window of zero width).
if (h == 0)
h = 1;
float ratio = w * 1.0 / h;

glClearColor(0.0, 1.0, 0.9, 0.0);

// Use the Projection Matrix
glMatrixMode(GL_PROJECTION);

// Reset Matrix
glLoadIdentity();

// Set the viewport to be the entire window
glViewport(0, 0, w, h);

// Set the correct perspective.
gluPerspective(45.0f, ratio, 0.1f, 100.0f);

// Get Back to the Modelview
glMatrixMode(GL_MODELVIEW);
}


void drawSnowMan() {

	glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	
	glutSolidSphere(0.25f,20,20);

// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glutSolidCone(0.08f,0.5f,10,2);
}

void drawTree() {

// Draw Trunk
    glColor3f(0.4f, 0.15f, 0.0f);
    GLUquadricObj *trunk;

    glRotatef(90, -1, 0, 0);
   // glTranslatef(0.0f, 2.0f, 0.0f);
    trunk = gluNewQuadric();
    gluQuadricDrawStyle(trunk, GLU_FILL);
    gluCylinder (trunk, 0.3f, 0.05f, 3.0f, 40, 20);

// Draw Crown
    glColor3f(0.0f, 0.95f, 0.0f);
    glTranslatef(0.0f, 0.0f, 3.0f);
    glutSolidSphere(1.0f, 20, 20);

}

void drawFlower() {
    glColor3f(0.0f, 0.4f, 0.0f);
    glTranslatef(-1.5f, 0.3f, -3.0f);

	//flower trunk
	GLUquadricObj* trunk;
	trunk = gluNewQuadric();
	gluQuadricDrawStyle(trunk, GLU_FILL);
	gluCylinder(trunk, 0.03f, 0.03f, 0.4f, 40, 20);
	
	//flower petals
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 0.4f);
	GLUquadricObj* trunk2;
	trunk2 = gluNewQuadric();
	gluQuadricDrawStyle(trunk2, GLU_FILL);
	gluCylinder(trunk2, 0.06f, 0.06f, 0.2f, 40, 20);

}


void renderScene(void) {

	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	x, 1.0f, z,
			x+lx, 1.0f,  z+lz,
			0.0f, 1.0f,  0.0f);
	
	//colours
	GLfloat pozitial0[] = { -100.0, 100.0, 100.0, 1.0 };
	GLfloat albastru[] = { 0.0, 0.0, 0.8, 0.5 };
	GLfloat alb[] = { 0.8, 0.8, 0.8, 0.1 };

    /// GROUND

    switch(rendermode) {

    case WINTER:
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
    for(int i = -3; i < 3; i++)
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0,0,j * 10.0);
			drawSnowMan();
			glPopMatrix();
		}
	
	//lightning
	
	glLightfv(GL_LIGHT0, GL_POSITION, pozitial0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, albastru);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_BLEND);
    break;


    case SPRING:
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
	glColor3f(0.0f, 0.8f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
	for(int i = -3; i < 3; i++)
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0,0,j * 10.0);
			
			drawTree();
			
			drawFlower();
			glPopMatrix();
		}
	glDisable(GL_BLEND);
        break;
    }
	
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy)
{

	float fraction = 0.2f;

	switch (key) {
		case 'a' :
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case 'd' :
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case 'w' :
			x += lx * fraction;
			z += lz * fraction;
			break;
		case 's' :
			x -= lx * fraction;
			z -= lz * fraction;
			break;
	}

	if(key == 27)
        exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {



}


int main(int argc, char **argv) {

	// init GLUT and create window

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Scena 3D");
	
	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	glutCreateMenu(menu);
    glutAddMenuEntry("WINTER", WINTER);
    glutAddMenuEntry("SPRING", SPRING);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	
	// enter GLUT event processing cycle
	glutMainLoop();

	
	
	return 1;
}