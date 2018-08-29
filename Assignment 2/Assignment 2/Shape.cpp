
#include "Shape.hpp"

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


Shape::Shape() {
	x = y = z = 0.0;
	rotation = 0.0;
	red = green = blue = 1.0;
};

Shape::Shape(double x_, double y_, double z_) {
	x = x_;
	y = y_;
	z = z_;

	rotation = 0.0;
	red = green = blue = 1.0;
};

Shape::Shape(double x_, double y_, double z_, double rotation_) {

	x = x_;
	y = y_;
	z = z_;

	rotation = rotation_;
	red = green = blue = 1.0;
};

Shape::~Shape() {
}

double Shape::getX() {
	return x;
};

double Shape::getY() {
	return y;
};

double Shape::getZ() {
	return z;
};

double Shape::getRotation() {
	return rotation;
};

void Shape::setX(double x_) {
	x = x_;
};

void Shape::setY(double y_) {
	y = y_;
};

void Shape::setZ(double z_) {
	z = z_;
};

void Shape::setRotation(double rotation_) {
	rotation = rotation_;
};


void Shape::setPosition(double x_, double y_, double z_) {
	x = x_;
	y = y_;
	z = z_;
};

void Shape::positionInGL() {
	glTranslated(x, y, z);
	glRotated(-rotation, 0, 1, 0);
};

void Shape::setColorInGL() {
	glColor3f(red, green, blue);
};

double Shape::getRed() {
	return red;
};

double Shape::getGreen() {
	return green;
};

double Shape::getBlue() {
	return blue;
};

void Shape::setColor(float red_, float green_, float blue_) {
	red = red_;
	green = green_;
	blue = blue_;
};

void RectangularPrism::draw()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3d(1, 0, 0);
	glVertex3d((xLength / 2) + x, (yLength / 2) + y, (-zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, (yLength / 2) + y, (-zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, (-yLength / 2) + y, (-zLength / 2) + z);
	glVertex3d((xLength / 2) + x, (-yLength / 2) + y, (-zLength / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(1, 1, 0);
	glVertex3d((xLength / 2) + x, (yLength / 2) + y, (zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, (yLength / 2) + y, (zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, (-yLength / 2) + y, (zLength / 2) + z);
	glVertex3d((xLength / 2) + x, (-yLength / 2) + y, (zLength / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(1, 1, 1);
	glVertex3d((xLength / 2) + x, (yLength / 2) + y, (-zLength / 2) + z);
	glVertex3d((xLength / 2) + x, (yLength / 2) + y, (zLength / 2) + z);
	glVertex3d((xLength / 2) + x, (-yLength / 2) + y, (zLength / 2) + z);
	glVertex3d((xLength / 2) + x, (-yLength / 2) + y, (-zLength / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(1, 0, 1);
	glVertex3d((-xLength / 2) + x, (yLength / 2) + y, (-zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, (yLength / 2) + y, (zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, (-yLength / 2) + y, (zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, (-yLength / 2) + y, (-zLength / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(0, 1, 0);
	glVertex3d((xLength / 2) + x, (yLength / 2) + y, (-zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, (yLength / 2) + y, (-zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, (yLength / 2) + y, (zLength / 2) + z);
	glVertex3d((xLength / 2) + x, (yLength / 2) + y, (zLength / 2) + z);
	glEnd();

	glBegin(GL_QUADS);
	glBegin(GL_QUADS);
	glColor3d(0, 1, 1);
	glVertex3d((xLength / 2) + x, (-yLength / 2) + y, (-zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, (-yLength / 2) + y, (-zLength / 2) + z);
	glVertex3d((-xLength / 2) + x, (-yLength / 2) + y, (zLength / 2) + z);
	glVertex3d((xLength / 2) + x, (-yLength / 2) + y, (zLength / 2) + z);
	glEnd();
	glPopMatrix();

}

void RectangularPrism::setLength(double xLength, double yLength, double zLength)
{
	this->xLength = xLength;
	this->yLength = yLength;
	this->zLength = zLength;

}

void TriangularPrism::draw()
{
	x = getX();
	y = getY();
	z = getZ();
	rotation = getRotation();
	red = getRed();
	green = getGreen();
	blue = getBlue();

}

void TrapezoidalPrism::draw()
{
	x = getX();
	y = getY();
	z = getZ();
	rotation = getRotation();
	red = getRed();
	green = getGreen();
	blue = getBlue();

}

void Cylinder::draw()
{
	x = getX();
	y = getY();
	z = getZ();
	rotation = getRotation();
	red = getRed();
	green = getGreen();
	blue = getBlue();

}

void MyVehicle::draw()
{
	x = getX();
	y = getY();
	z = getZ();
	rotation = getRotation();
	red = getRed();
	green = getGreen();
	blue = getBlue();

}
