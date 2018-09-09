#include "TriangularPrism.hpp"
#include "TrapeziodalPrism.h"
#include "RectangularPrism.hpp"
#include "Cylinder.hpp"
#include "Brum.hpp"
#include "Vehicle.hpp"

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

void MyVehicle::addingS(Shape * shape)
{
	addShape(shape);
}

void MyVehicle::draw()
{
	glPushMatrix();
	positionInGL();

	RectangularPrism Body;

	Body.setLength(3, 1, 2);
	Body.setPosition(0, 0.4, 0);
	Body.setColor(0, 0, 1);
	addShape(&Body);
	//Body.draw();

	TrapezoidalPrism Roof;

	Roof.setDepth(2);
	Roof.setSides(2, 1, 1, 0.5);
	Roof.setPosition(0, 1.4, 0);
	addShape(&Roof);
	//shapes.push_back(&Roof);
	//Roof.draw();

	Cylinder backLeft;
	
	//size of the wheels
	backLeft.setRadius(0.4);
	backLeft.setDepth(0.1);
	backLeft.setPosition(-1.1, 0, -1.1); // back left
	backLeft.setColor(1, 0, 0);
	//addingS(&backLeft);
	//backLeft.draw();

	Cylinder backRight;

	backRight.setRadius(0.4);
	backRight.setDepth(0.1);
	backRight.setPosition(-1.1, 0, 1.1); // back right
	backRight.setColor(1, 0, 1);
	//addingS(&backRight);
	//backRight.draw();


	Cylinder frontRight;

	// minus the get steering to allow wheels to follow key arrows
	frontRight.setRadius(0.4);
	frontRight.setDepth(0.1);
	frontRight.setPosition(1.1, 0, 1.1); // front right
	frontRight.setColor(0, 1, 0);
	frontRight.setRotation(-getSteering());
	//addingS(&frontRight);
	frontRight.draw();

	Cylinder frontLeft;

	// minus the get steering to allow wheels to follow key arrows
	frontLeft.setRadius(0.4);
	frontLeft.setDepth(0.1);
	frontLeft.setPosition(1.1, 0, -1.1); // front right
	frontLeft.setColor(1, 1, 0);
	frontLeft.setRotation(-getSteering());
	//addingS(&frontLeft);
	frontLeft.draw();

	TriangularPrism Spoiler;
	Spoiler.setDepth(3);
	Spoiler.setColor(1, 1, 0);
	Spoiler.setSides(1, 0.4, 120);
	Spoiler.setPosition(-1.5, 1.4, 0);
	//addingS(&Spoiler);
	Spoiler.draw();

	std::vector<Shape *>::iterator it;
	for (it = shapes.begin(); it != shapes.end(); ++it) {
		(*it)->draw();
	}

	glPopMatrix();

}