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



#include "Wheel.hpp"
#include "RectangularPrism.hpp"
#include "Cylinder.hpp"



#include <math.h>

#define DEFAULT_SLICES 64

Wheel::Wheel() : Shape() {
	addShape(new Cylinder());
	addShape(new RectangularPrism());
	dynamic_cast<Cylinder*>(shapes[0])->setRadius(0.4);
	dynamic_cast<Cylinder*>(shapes[0])->setY(0.1);
	dynamic_cast<RectangularPrism*>(shapes[1])->setX(0.1);
	dynamic_cast<RectangularPrism*>(shapes[1])->setY(0.4);
	dynamic_cast<RectangularPrism*>(shapes[1])->setZ(0.2);
	wheel_rotation = 0;
};

Wheel::Wheel(double x_, double y_, double z_) : Shape(x_, y_, z_) {
	addShape(new Cylinder());
	addShape(new RectangularPrism());
	dynamic_cast<Cylinder*>(shapes[0])->setRadius(0.4);
	dynamic_cast<Cylinder*>(shapes[0])->setY(0.1);
	dynamic_cast<RectangularPrism*>(shapes[1])->setX(0.1);
	dynamic_cast<RectangularPrism*>(shapes[1])->setY(0.6);
	dynamic_cast<RectangularPrism*>(shapes[1])->setZ(0.2);
	shapes[0]->setColor(1.0, 0, 0);
	shapes[1]->setColor(0, 0, 1.0);
	wheel_rotation = 0;
};

Wheel::Wheel(double x_, double y_, double z_, bool custom) : Shape(x_, y_, z_) {
	wheel_rotation = 0;
};

Wheel::Wheel(double x_, double y_, double z_, double rotation_) :
	Shape(x_, y_, z_, rotation_) {
	addShape(new Cylinder());
	addShape(new RectangularPrism());
	dynamic_cast<Cylinder*>(shapes[0])->setRadius(0.4);
	dynamic_cast<Cylinder*>(shapes[0])->setY(0.1);
	dynamic_cast<RectangularPrism*>(shapes[1])->setX(0.1);
	dynamic_cast<RectangularPrism*>(shapes[1])->setY(0.4);
	dynamic_cast<RectangularPrism*>(shapes[1])->setZ(0.2);

	shapes[0]->setColor(1.0, 0, 0);
	shapes[1]->setColor(0, 0, 1.0);
	wheel_rotation = 0;
};
void Wheel::draw() {

	glPushMatrix();
	glTranslated(x, y + 0.4, z);
	glRotated(rotation, 0, 1, 0);
	glRotated(-wheel_rotation, 0, 0, 1);
	glTranslated(0, -0.4, 0);

	for (int i = 0; i < shapes.size(); i++) {
		shapes[i]->draw();
	}
	glPopMatrix();

};

double Wheel::get_wheel_rotation() {
	return wheel_rotation;
};

void Wheel::set_wheel_rotation(double new_wheel_rotation) {
	wheel_rotation = new_wheel_rotation;
};

Wheel::~Wheel() {

};

void Wheel::addShape(Shape * shape)
{
	shapes.push_back(shape);
}
