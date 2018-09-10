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
#include "RectangularPrism.hpp"


RectangularPrism::RectangularPrism()
{
	xLength = yLength = zLength = 0;
}

RectangularPrism::RectangularPrism(double xLength, double yLength, double zLength)
{
	this->xLength = xLength;
	this->yLength = yLength;
	this->zLength = zLength;

}

double RectangularPrism::getxLength()
{
	return xLength;
}

void RectangularPrism::setxLength(double xLength)
{
	this->xLength = xLength;
}

double RectangularPrism::getyLength()
{
	return yLength;
}

void RectangularPrism::setyLength(double yLength)
{
	this->yLength = yLength;
}

double RectangularPrism::getzLength()
{
	return zLength;
}

void RectangularPrism::setzLength(double zLength)
{
	this->zLength = zLength;
}

void RectangularPrism::draw() // origin of shape needs to be at the base and not at the centre of the shape
{
	glPushMatrix();

	glColor3d(red, green, blue);

	glRotated(rotation, 0, 1, 0);

	glBegin(GL_QUADS);
	glColor3d(red, green, blue);
	glVertex3d((xLength / 2) + x, y, (-zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, y, (-zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, yLength + y, (-zLength / 2) + z);
	glVertex3d((xLength / 2) + x, yLength + y, (-zLength / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue);
	glVertex3d((xLength / 2) + x, y, (zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, y, (zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, yLength + y, (zLength / 2) + z);
	glVertex3d((xLength / 2) + x, yLength + y, (zLength / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue);
	glVertex3d((xLength / 2) + x, y, (-zLength / 2) + z);
	glVertex3d((xLength / 2) + x, y, (zLength / 2) + z);
	glVertex3d((xLength / 2) + x, yLength + y, (zLength / 2) + z);
	glVertex3d((xLength / 2) + x, yLength + y, (-zLength / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue);
	glVertex3d((-xLength / 2) + x, y, (-zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, y, (zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, yLength + y, (zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, yLength + y, (-zLength / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue);
	glVertex3d((xLength / 2) + x, yLength + y, (-zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, yLength + y, (-zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, yLength + y, (zLength / 2) + z);
	glVertex3d((xLength / 2) + x, yLength + y, (zLength / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue);
	glVertex3d((xLength / 2) + x, y, (-zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, y, (-zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, y, (zLength / 2) + z);
	glVertex3d((xLength / 2) + x, y, (zLength / 2) + z);
	glEnd();

	glPopMatrix();

}


