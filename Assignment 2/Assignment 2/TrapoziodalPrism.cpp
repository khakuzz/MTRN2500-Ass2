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

double TrapezoidalPrism::getaLength()
{
	return aLength;
}

void TrapezoidalPrism::setaLength(double aLength)
{
	this->aLength = aLength;
}

double TrapezoidalPrism::getbLength()
{
	return bLength;
}

void TrapezoidalPrism::setbLength(double bLength)
{
	this->bLength = bLength;
}

double TrapezoidalPrism::getHeight()
{
	return height;
}

void TrapezoidalPrism::setHeight(double height)
{
	this->height = height;
}

double TrapezoidalPrism::getaOffset()
{
	return aOffset;
}

void TrapezoidalPrism::setaOffset(double aOffset)
{
	this->aOffset = aOffset;
}

double TrapezoidalPrism::getDepth()
{
	return depth;
}

void TrapezoidalPrism::setDepth(double depth)
{
	this->depth = depth;
}

void TrapezoidalPrism::draw() // draw method for trapezoidal prism
{
	glPushMatrix();

	glColor3d(red, green, blue);

	glRotated(rotation, 0, 1, 0);

	glBegin(GL_QUADS);
	glColor3d(red, green, blue); // front face
	glVertex3d(-((aLength / 2) + x), y, (-depth / 2) + z);
	glVertex3d(-((-aLength / 2) + x), y, (-depth / 2) + z);
	glVertex3d(-((aLength / 2) + x - aOffset - bLength), height + y, (-depth / 2) + z);
	glVertex3d(-((aLength / 2) + x - aOffset), height + y, (-depth / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue); // back face
	glVertex3d(-((aLength / 2) + x), y, (depth / 2) + z);
	glVertex3d(-((-aLength / 2) + x), y, (depth / 2) + z);
	glVertex3d(-((aLength / 2) + x - aOffset - bLength), height + y, (depth / 2) + z);
	glVertex3d(-((aLength / 2) + x - aOffset), height + y, (depth / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue); // top face
	glVertex3d(-((aLength / 2) + x - aOffset), height + y, (-depth / 2) + z);
	glVertex3d(-((aLength / 2) + x - aOffset), height + y, (depth / 2) + z);
	glVertex3d(-((aLength / 2) + x - aOffset - bLength), height + y, (depth / 2) + z);
	glVertex3d(-((aLength / 2) + x - aOffset - bLength), height + y, (-depth / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue); // right face
	glVertex3d(-((aLength / 2) + x - aOffset - bLength), height + y, (-depth / 2) + z);
	glVertex3d(-((aLength / 2) + x - aOffset - bLength), height + y, (depth / 2) + z);
	glVertex3d(-((-aLength / 2) + x), y, (depth / 2) + z);
	glVertex3d(-((-aLength / 2) + x), y, (-depth / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue); // bottom face
	glVertex3d(-((-aLength / 2) + x), y, (-depth / 2) + z);
	glVertex3d(-((-aLength / 2) + x), y, (depth / 2) + z);
	glVertex3d(-((aLength / 2) + x), y, (depth / 2) + z);
	glVertex3d(-((aLength / 2) + x), y, (-depth / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(red, green, blue); // left face
	glVertex3d(-((aLength / 2) + x), y, (-depth / 2) + z);
	glVertex3d(-((aLength / 2) + x), y, (depth / 2) + z);
	glVertex3d(-((aLength / 2) + x - aOffset), height + y, (depth / 2) + z);
	glVertex3d(-((aLength / 2) + x - aOffset), height + y, (-depth / 2) + z);
	glEnd();

	glPopMatrix();

}
