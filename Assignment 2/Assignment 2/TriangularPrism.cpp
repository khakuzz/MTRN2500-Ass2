#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#elif defined(WIN32)
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <math.h>
#define PI 3.14159265358979

#include "TriangularPrism.hpp"

void TriangularPrism::draw()
{
	double xDistance = bLength * cos(theta * PI / 180);
	double yDistance = bLength * sin(theta * PI / 180);

	glPushMatrix();

	glColor3d(red, green, blue);

	glRotated(rotation, 0, 1, 0);

	glBegin(GL_TRIANGLES);
	glColor3d(red, green, blue);
	glVertex3d((-aLength / 2) + x, y, (-depth / 2) + z);
	glVertex3d((aLength / 2) + x, y, (-depth / 2) + z);
	glVertex3d((aLength / 2) + x - xDistance, yDistance + y, (-depth / 2) + z);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3d(red, green, blue);
	glVertex3d((-aLength / 2) + x, y, (depth / 2) + z);
	glVertex3d((aLength / 2) + x, y, (depth / 2) + z);
	glVertex3d((aLength / 2) + x - xDistance, yDistance + y, (depth / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue);
	glVertex3d((aLength / 2) + x - xDistance, yDistance + y, (-depth / 2) + z);
	glVertex3d((aLength / 2) + x - xDistance, yDistance + y, (depth / 2) + z);
	glVertex3d((-aLength / 2) + x, y, (depth / 2) + z);
	glVertex3d((-aLength / 2) + x, y, (-depth / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue);
	glVertex3d((aLength / 2) + x - xDistance, yDistance + y, (-depth / 2) + z);
	glVertex3d((aLength / 2) + x - xDistance, yDistance + y, (depth / 2) + z);
	glVertex3d((aLength / 2) + x, y, (depth / 2) + z);
	glVertex3d((aLength / 2) + x, y, (-depth / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue);
	glVertex3d((-aLength / 2) + x, y, (-depth / 2) + z);
	glVertex3d((-aLength / 2) + x, y, (depth / 2) + z);
	glVertex3d((aLength / 2) + x, y, (depth / 2) + z);
	glVertex3d((aLength / 2) + x, y, (-depth / 2) + z);
	glEnd();

	glPopMatrix();

}

void TriangularPrism::setSides(double aLength, double bLength, double theta)
{
	this->aLength = aLength;
	this->bLength = bLength;
	this->theta = theta;

}

void TriangularPrism::setDepth(double depth)
{
	this->depth = depth;

}