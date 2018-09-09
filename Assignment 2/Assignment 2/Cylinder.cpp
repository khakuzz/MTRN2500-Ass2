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


void Cylinder::draw()
{
	glPushMatrix();

	GLUquadric * Cyl;
	Cyl = gluNewQuadric();

	glColor3d(red, green, blue);

	glTranslated(x, y + radius, z - depth / 2);
	glRotated(rotation, 0, 1, 0);
	gluCylinder(Cyl, radius, radius, depth, 20, 1);

	glTranslated(0, 0, depth);
	gluDisk(Cyl, 0, radius, 20, 100);

	glTranslated(0, 0, -depth);
	gluDisk(Cyl, 0, radius, 20, 100);

	glPopMatrix();
}

void Cylinder::setRadius(double radius)
{
	this->radius = radius;
}

void Cylinder::setDepth(double depth)
{
	this->depth = depth;
}