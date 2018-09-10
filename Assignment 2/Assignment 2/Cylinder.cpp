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
	radius = depth = 0;
}

Cylinder::Cylinder(double radius, double depth)
{
	this->radius = radius;
	this->depth = depth;
}

void Cylinder::draw()
{
	glPushMatrix();

	GLUquadric * Cyl;
	Cyl = gluNewQuadric();

	glColor3d(red, green, blue);

	glTranslated(x, y + radius, z - depth / 2);
	glRotated(rotation, 0, 1, 0);
	gluCylinder(Cyl, radius, radius, depth, 5, 1);

	glTranslated(0, 0, depth);
	gluDisk(Cyl, 0, radius, 5, 1);

	glTranslated(0, 0, -depth);
	gluDisk(Cyl, 0, radius, 5, 1);

	glPopMatrix();
}

