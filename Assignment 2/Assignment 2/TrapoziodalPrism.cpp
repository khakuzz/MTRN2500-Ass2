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
#include "TrapeziodalPrism.h"



TrapezoidalPrism::TrapezoidalPrism()
{
	aLength = bLength = height = aOffset = depth = 0;
}

TrapezoidalPrism::TrapezoidalPrism(double aLength, double bLength, double height, double aOffset, double depth)
{
	this->aLength = aLength;
	this->bLength = bLength;
	this->height = height;
	this->aOffset = aOffset;
	this->depth = depth;

}

void TrapezoidalPrism::draw()
{
	glPushMatrix();

	glColor3d(red, green, blue);

	glRotated(rotation, 0, 1, 0);

	glBegin(GL_QUADS);
	glColor3d(red, green, blue);
	glVertex3d((aLength / 2) + x, y, (-depth / 2) + z);
	glVertex3d((-aLength / 2) + x, y, (-depth / 2) + z);
	glVertex3d((aLength / 2) + x - aOffset - bLength, height + y, (-depth / 2) + z);
	glVertex3d((aLength / 2) + x - aOffset, height + y, (-depth / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue);
	glVertex3d((aLength / 2) + x, y, (depth / 2) + z);
	glVertex3d((-aLength / 2) + x, y, (depth / 2) + z);
	glVertex3d((aLength / 2) + x - aOffset - bLength, height + y, (depth / 2) + z);
	glVertex3d((aLength / 2) + x - aOffset, height + y, (depth / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue);
	glVertex3d((aLength / 2) + x - aOffset, height + y, (-depth / 2) + z);
	glVertex3d((aLength / 2) + x - aOffset, height + y, (depth / 2) + z);
	glVertex3d((aLength / 2) + x - aOffset - bLength, height + y, (depth / 2) + z);
	glVertex3d((aLength / 2) + x - aOffset - bLength, height + y, (-depth / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue);
	glVertex3d((aLength / 2) + x - aOffset - bLength, height + y, (-depth / 2) + z);
	glVertex3d((aLength / 2) + x - aOffset - bLength, height + y, (depth / 2) + z);
	glVertex3d((-aLength / 2) + x, y, (depth / 2) + z);
	glVertex3d((-aLength / 2) + x, y, (-depth / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue);
	glVertex3d((-aLength / 2) + x, y, (-depth / 2) + z);
	glVertex3d((-aLength / 2) + x, y, (depth / 2) + z);
	glVertex3d((aLength / 2) + x, y, (depth / 2) + z);
	glVertex3d((aLength / 2) + x, y, (-depth / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue);
	glVertex3d((aLength / 2) + x, y, (-depth / 2) + z);
	glVertex3d((aLength / 2) + x, y, (depth / 2) + z);
	glVertex3d((aLength / 2) + x - aOffset, height + y, (depth / 2) + z);
	glVertex3d((aLength / 2) + x - aOffset, height + y, (-depth / 2) + z);
	glEnd();

	glPopMatrix();

}
