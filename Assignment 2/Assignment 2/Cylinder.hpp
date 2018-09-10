#include "Shape.hpp"

class Cylinder : public Shape {
public:
	Cylinder();
	Cylinder(double radius, double depth);
	void draw();

private:
	double radius;
	double depth;
};