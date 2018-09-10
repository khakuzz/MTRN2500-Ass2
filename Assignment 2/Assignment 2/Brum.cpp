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

	Shape * Body = new RectangularPrism(3, 1, 2);
	RectangularPrism * rect = dynamic_cast<RectangularPrism *>(Body);

	rect->setPosition(0, 0.4, 0);
	rect->setColor(0, 0, 1);
	addingS(rect);
	//Body.draw();

	Shape * Roof = new TrapezoidalPrism(2, 1, 1, 0.5, 2);
	TrapezoidalPrism * Roofe = dynamic_cast<TrapezoidalPrism *>(Roof);

	Roofe->setPosition(0, 1.4, 0);
	Roofe->setColor(1, 1, 1);
	addingS(Roofe);
	//Roof.draw();

	Shape * BLWheel = new Cylinder(0.4, 0.1);
	Cylinder * backLeft = dynamic_cast<Cylinder *>(BLWheel);

	backLeft->setPosition(-1.1, 0, -1.1);
	backLeft->setColor(1, 0, 0);
	addingS(BLWheel);
	//backLeft.draw();

	Shape * BRWheel = new Cylinder(0.4, 0.1);
	Cylinder * backRight = dynamic_cast<Cylinder *>(BRWheel);

	backRight->setPosition(-1.1, 0, 1.1); // back right
	backRight->setColor(1, 0, 1);
	addingS(backRight);
	//backRight.draw();

	Shape * FRWheel = new Cylinder(0.4, 0.1);
	Cylinder * frontRight = dynamic_cast<Cylinder *>(FRWheel);

	// minus the get steering to allow wheels to follow key arrows
	frontRight->setPosition(1.1, 0, 1.1);
	frontRight->setColor(0, 1, 0);
	//frontRight->setRotation(-getSteering());
	addingS(frontRight);

	Shape * FLWheel = new Cylinder(0.4, 0.1);
	Cylinder * frontLeft = dynamic_cast<Cylinder *>(FLWheel);

	// minus the get steering to allow wheels to follow key arrows
	frontLeft->setPosition(1.1, 0, -1.1);
	frontLeft->setColor(1, 1, 0);
	//frontLeft->setRotation(-getSteering());
	addingS(frontLeft);

	Shape * Spoil = new TriangularPrism(1, 0.4, 120, 3);
	TriangularPrism * Spoiler = dynamic_cast<TriangularPrism *>(Spoil);

	Spoiler->setPosition(-1.5, 1.4, 0);
	Spoiler->setColor(1, 1, 0);
	addingS(Spoiler);
	//Spoiler.draw();
	

	std::vector<Shape *>::iterator it;
	for (it = shapes.begin(); it != shapes.end(); ++it) {
		if(dynamic_cast<Cylinder *>(*it)){
			(*it)->setRotation(-getSteering());
		}
		(*it)->draw();
	}

	glPopMatrix();

}