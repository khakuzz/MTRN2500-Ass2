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


#include "Cylinder.hpp"


Cylinder::Cylinder()
{
	radius = depth = steering = rolling = 0;
}

Cylinder::Cylinder(double radius, double depth)
{
	this->radius = radius;
	this->depth = depth;
	steering = rolling = 0;
}

void Cylinder::setRadius(double radius)
{
	this->radius = radius;
}

double Cylinder::getRadius()
{
	return radius;
}

void Cylinder::setDepth(double depth)
{
	this->depth = depth;
}

double Cylinder::getDepth()
{
	return depth;
}

void Cylinder::draw()
{
	glPushMatrix();

	GLUquadric * Cyl;
	Cyl = gluNewQuadric();

	glColor3d(red, green, blue);

	glTranslated(x, y + radius, z - depth / 2);
	glRotated(-steering, 0, 1, 0);
	glRotated(rolling, 0, 0, 1);
	gluCylinder(Cyl, radius, radius, depth, 5, 1);

	glTranslated(0, 0, depth);
	gluDisk(Cyl, 0, radius, 5, 1);

	glTranslated(0, 0, -depth);
	gluDisk(Cyl, 0, radius, 5, 1);

	glPopMatrix();
}

void Cylinder::setSteering(double steering)
{
	this->steering = steering;
}

double Cylinder::getSteering()
{
	return steering;
}

void Cylinder::setRolling(double rolling)
{
	this->rolling = rolling;
}

double Cylinder::getRolling()
{
	return rolling;
}

