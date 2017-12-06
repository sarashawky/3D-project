//header
#include <stdlib.h>
#include<GLFW\glfw3.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<stdio.h>
#include <random>
#include <ctime>
#include <math.h>
using namespace std;
#include<iostream>
//globals

int WindowHeight = 1000;
int WindowWidth = 1000;
GLuint elephant;
float elephantrot;
char ch = '1';
int x=0, y=-40, z=-105;
//other functions and main

//.obj loader code begins

// Set lighting intensity and color
GLfloat qaAmbientLight[] = { 1.2, .2, 1.2, 1.0 };
GLfloat qaDiffuseLight[] = { 1.8, 1.8, .8, 1.0 };
GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat emitLight[] = { 0.9, 0.9, 0.9, 0.01 };
GLfloat Noemit[] = { 0.0, 0.0, 0.0, 1.0 };
// Light source position
GLfloat qaLightPosition[] = { 0.5, 0, -3.5, 0.5 };

void display(void);
void reshape(int x, int y);


void initLighting()
{

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Set lighting intensity and color
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	// Set the light position
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

}

void printtext(int x, int y, string String)
{
	//(x,y) is from the bottom left of the window
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, WindowWidth, 0, WindowHeight, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	glRasterPos2i(x, y);
	for (int i = 0; i<String.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
	}
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}



void loadObj(char *fname)
{
	FILE *fp;
	int read;
	GLfloat x, y, z;
	char ch;
	elephant = glGenLists(1);
	fp = fopen(fname, "r");
	if (!fp)
	{
		printf("can't open file %s\n", fname);
		exit(1);
	}
	glPointSize(20.0);
	glNewList(elephant, GL_COMPILE);
	{
		glPushMatrix();
		glBegin(GL_POINTS);
		while (!(feof(fp)))
		{
			read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
			if (read == 4 && ch == 'v')
			{
				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}
	glPopMatrix();
	glEndList();
	fclose(fp);
}

//.obj loader code ends here

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
	//glOrtho(-25,25,-2,2,0.1,100);	
	glMatrixMode(GL_MODELVIEW);
}

void keyboard_callback(int key, int, int)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		y += 5;
		break;
	case GLUT_KEY_DOWN:
		y-=5;
		break;
	case GLUT_KEY_RIGHT:
		x+=5;
		break;
	case GLUT_KEY_LEFT:
		x-=5;
		break;
	}
}
void drawCar()
{
	
	int min = 1;
	srand(time(NULL));
	//x = 0 + rand() % 100;
	//y = -40 + rand() % 10;
	//z = -105 + rand() % 100;
	glPushMatrix();
	glutSpecialFunc(keyboard_callback);
	glTranslatef(x, y, z);

	glColor3f(0.7, 1.0, 0.5);
	glScalef(1, 1, 1);
	glRotatef(elephantrot, 0, 1, 0);
	glCallList(elephant);
	glPopMatrix();
	elephantrot = elephantrot + 0.6;
	if (elephantrot>360)elephantrot = elephantrot - 360;
}


void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_TEST);

	char string[64];
	sprintf(string, "Hello it is Pony");
	glColor3f(1, 1, 0);
	printtext(150, 200, string);
	sprintf(string, "Sara");
	glColor3f(1, 1, 0);
	printtext(700, 600, string);
	glLoadIdentity();
	drawCar();
	glutSwapBuffers(); //swap the buffers

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 450);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("ObjLoader");
	initLighting();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	loadObj("data/pony.obj");

	//replace porsche.obj with radar.obj or any other .obj to display it
	glutMainLoop();
	return 0;
}
