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

void MyVehicle::draw()
{
	glPushMatrix();
	positionInGL();

	RectangularPrism Body;

	Body.setLength(3, 1, 2);
	Body.setPosition(0, 0.4, 0);
	Body.setColor(0, 0, 1);
	Body.draw();

	TrapezoidalPrism Roof;

	Roof.setDepth(2);
	Roof.setSides(2, 1, 1, 0.5);
	Roof.setPosition(0, 1.4, 0);
	Roof.draw();

	Cylinder SmallWheel;
	

	//size of the wheels
	SmallWheel.setRadius(0.4);
	SmallWheel.setDepth(0.1);
	//back left
	SmallWheel.setPosition(-1.1, 0, -1.1);
	SmallWheel.setColor(1, 0, 0);
	SmallWheel.draw();
	//back right
	SmallWheel.setPosition(-1.1, 0, 1.1);
	SmallWheel.setColor(1, 0, 1);
	SmallWheel.draw();
	//front right
	SmallWheel.setPosition(1.1, 0, 1.1);
	SmallWheel.setColor(0, 1, 0);
	SmallWheel.setRotation(-getSteering());
	SmallWheel.draw();
	//front left
	SmallWheel.setPosition(1.1, 0, -1.1);
	SmallWheel.setColor(0, 1, 1);
	SmallWheel.setRotation(-getSteering());
	SmallWheel.draw();

	TriangularPrism Spoiler;
	Spoiler.setDepth(3);
	Spoiler.setColor(1, 1, 0);
	Spoiler.setSides(1, 0.4, 120);
	Spoiler.setPosition(-1.5, 1.4, 0);
	Spoiler.draw();

	glPopMatrix();

}