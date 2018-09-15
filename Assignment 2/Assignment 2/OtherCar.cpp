#include "OtherCar.h"
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

OtherCar::OtherCar()
{
}

void OtherCar::draw() // draw method of other cars
{
	glPushMatrix();
	positionInGL();

	std::vector<Shape *>::iterator it; // iterator with shape * vector
	for (it = shapes.begin(); it != shapes.end(); ++it) {
		if (dynamic_cast<Cylinder *>(*it)) { // if the Shape vector has a cylinder in it, set the steering and rolling
			dynamic_cast<Cylinder *>(*it)->setSteering(getSteering());
			dynamic_cast<Cylinder *>(*it)->setRolling(-speed / dynamic_cast<Cylinder *>(*it)->getRadius() + dynamic_cast<Cylinder *>(*it)->getRolling());
		}
		(*it)->draw();
	}

	glPopMatrix();
}
