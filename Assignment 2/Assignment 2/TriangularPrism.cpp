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

TriangularPrism::TriangularPrism()
{
	aLength = bLength = theta = depth = 0;
}

TriangularPrism::TriangularPrism(double aLength, double bLength, double theta, double depth)
{
	this->aLength = aLength;
	this->bLength = bLength;
	this->theta = theta;
	this->depth = depth;

}

double TriangularPrism::getaLength()
{
	return aLength;
}

void TriangularPrism::setaLength(double aLength)
{
	this->aLength = aLength;
}

double TriangularPrism::getbLength()
{
	return bLength;
}

void TriangularPrism::setbLength(double bLength)
{
	this->bLength = bLength;
}

double TriangularPrism::getTheta()
{
	return theta;
}

void TriangularPrism::setTheta(double theta)
{
	this->theta = theta;
}

double TriangularPrism::getDepth()
{
	return depth;
}

void TriangularPrism::setDepth(double depth)
{
	this->depth = depth;
}

void TriangularPrism::draw() // draw method for triangular prism
{
	double xDistance = bLength * cos(theta * PI / 180);
	double yDistance = bLength * sin(theta * PI / 180);

	glPushMatrix();

	glColor3d(red, green, blue);

	glRotated(rotation, 0, 1, 0);

	glBegin(GL_TRIANGLES);
	glColor3d(red, green, blue);
	glVertex3d(-((-aLength / 2) + x), y, (-depth / 2) + z);
	glVertex3d(-((aLength / 2) + x), y, (-depth / 2) + z);
	glVertex3d(-((aLength / 2) + x - xDistance), yDistance + y, (-depth / 2) + z);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3d(red, green, blue);
	glVertex3d(-((-aLength / 2) + x), y, (depth / 2) + z);
	glVertex3d(-((aLength / 2) + x), y, (depth / 2) + z);
	glVertex3d(-((aLength / 2) + x - xDistance), yDistance + y, (depth / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue);
	glVertex3d(-((aLength / 2) + x - xDistance), yDistance + y, (-depth / 2) + z);
	glVertex3d(-((aLength / 2) + x - xDistance), yDistance + y, (depth / 2) + z);
	glVertex3d(-((-aLength / 2) + x), y, (depth / 2) + z);
	glVertex3d(-((-aLength / 2) + x), y, (-depth / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue);
	glVertex3d(-((aLength / 2) + x - xDistance), yDistance + y, (-depth / 2) + z);
	glVertex3d(-((aLength / 2) + x - xDistance), yDistance + y, (depth / 2) + z);
	glVertex3d(-((aLength / 2) + x), y, (depth / 2) + z);
	glVertex3d(-((aLength / 2) + x), y, (-depth / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue);
	glVertex3d(-((-aLength / 2) + x), y, (-depth / 2) + z);
	glVertex3d(-((-aLength / 2) + x), y, (depth / 2) + z);
	glVertex3d(-((aLength / 2) + x), y, (depth / 2) + z);
	glVertex3d(-((aLength / 2) + x), y, (-depth / 2) + z);
	glEnd();

	glPopMatrix();

}

