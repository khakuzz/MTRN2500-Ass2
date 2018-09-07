#include "Shape.hpp"

class Cylinder : public Shape {
public:
	void draw();
	void setRadius(double radius);
	void setDepth(double depth);

private:
	double radius;
	double depth;
};