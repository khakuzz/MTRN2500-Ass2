#include "TriangularPrism.hpp"
#include "TrapeziodalPrism.h"
#include "RectangularPrism.hpp"
#include "Cylinder.hpp"
#include "MyVehicle.hpp"
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

MyVehicle::MyVehicle()
{
	glPushMatrix();
	positionInGL();

	Shape * Body = new RectangularPrism(3, 1, 2);
	RectangularPrism * rect = dynamic_cast<RectangularPrism *>(Body);

	rect->setPosition(0, 0.4, 0);
	rect->setColor(0, 0, 1);
	addingS(rect);

	Shape * Roof = new TrapezoidalPrism(2, 1, 1, 0.5, 2);
	TrapezoidalPrism * Roofe = dynamic_cast<TrapezoidalPrism *>(Roof);

	Roofe->setPosition(0, 1.4, 0);
	Roofe->setColor(1, 0, 1);
	addingS(Roofe);

	Shape * BLWheel = new Cylinder(0.4, 0.1);
	Cylinder * backLeft = dynamic_cast<Cylinder *>(BLWheel);

	backLeft->setPosition(-1.1, 0, -1.1);
	backLeft->setColor(1, 0, 0);
	backLeft->setisRolling(true);
	backLeft->setisSteering(false);
	addingS(BLWheel);

	Shape * BRWheel = new Cylinder(0.4, 0.1);
	Cylinder * backRight = dynamic_cast<Cylinder *>(BRWheel);

	backRight->setPosition(-1.1, 0, 1.1); // back right
	backRight->setColor(1, 0, 1);
	backRight->setisRolling(true);
	backRight->setisSteering(false);
	addingS(backRight);

	Shape * FRWheel = new Cylinder(0.4, 0.1);
	Cylinder * frontRight = dynamic_cast<Cylinder *>(FRWheel);

	addingS(frontRight);

	// minus the get steering to allow wheels to follow key arrows
	frontRight->setPosition(1.1, 0, 1.1);
	frontRight->setisSteering(true);
	frontRight->setisRolling(true);
	frontRight->setColor(0, 1, 0);

	Shape * FLWheel = new Cylinder(0.4, 0.1);
	Cylinder * frontLeft = dynamic_cast<Cylinder *>(FLWheel);

	addingS(frontLeft);

	// minus the get steering to allow wheels to follow key arrows
	frontLeft->setPosition(1.1, 0, -1.1);
	frontLeft->setisSteering(true);
	frontLeft->setisRolling(true);
	frontLeft->setColor(1, 1, 0);

	Shape * triangle = new RectangularPrism(3, 3, 3);
	RectangularPrism * TRI = dynamic_cast<RectangularPrism *>(triangle);

	TRI->setPosition(0, 3, 0);
	TRI->setColor(1, 0.5, 0.5);
	//addingS(TRI);

	glPopMatrix();
}

void MyVehicle::addingS(Shape * shape)
{
	addShape(shape);
}

void MyVehicle::draw()
{
	glPushMatrix();
	positionInGL();
	
	std::vector<Shape *>::iterator it;
	for (it = shapes.begin(); it != shapes.end(); ++it) {
		if(dynamic_cast<Cylinder *>(*it)){
			dynamic_cast<Cylinder *>(*it)->setSteering(getSteering());
			dynamic_cast<Cylinder *>(*it)->setRolling(-speed/dynamic_cast<Cylinder *>(*it)->getRadius() + dynamic_cast<Cylinder *>(*it)->getRolling());
		}
		(*it)->draw();
	}

	glPopMatrix();

}

std::vector<Shape*> MyVehicle::getShapes()
{
	return shapes;
}
