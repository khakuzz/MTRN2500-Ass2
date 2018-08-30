
#ifndef MTRN3500_SHAPE_H
#define MTRN3500_SHAPE_H

// Abstract class
class Shape {

public:
	Shape();
	Shape(double x_, double y_, double z_);
	Shape(double x_, double y_, double z_, double rotation_);
	virtual ~Shape();

	virtual void draw() = 0;

	double getX();
	double getY();
	double getZ();
	double getRotation();

	void setX(double x_);
	void setY(double y_);
	void setZ(double z_);
	void setRotation(double rotation_);

	void setPosition(double x_, double y_, double z_);

	void positionInGL();
	void setColorInGL();

	double getRed();
	double getGreen();
	double getBlue();
	void setColor(float red_, float green_, float blue_);

protected:
	double x, y, z;               // position
	double rotation;              // heading of the object in the horizontal plane (degrees)
	float red, green, blue;       // colour of object

};

class RectangularPrism : public Shape {
	
public:
	void draw();
	void setLength(double xLength, double yLength, double zLength);

private:
	double xLength;
	double yLength;
	double zLength;

};

class TriangularPrism : public Shape {
public:
//	void draw();
	void setSides(double FirstSide, double SecondSide, double angle);
	void setLength(double length);

private:
	double FirstSide;
	double SecondSide;
	double angle;
	double length;
};

class TrapezoidalPrism : public Shape {
public:
	void draw();
};

class Cylinder : public Shape {
public:
	void draw();
	void setRadius(double radius);
	void setHeight(double height);

private:
	double radius;
	double height;
};

class MyVehicle : public Shape {
public:
	void draw();
};

#endif // for MTRN3500_SHAPE_H
