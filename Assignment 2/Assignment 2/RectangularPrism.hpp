
#include "Shape.hpp"

class RectangularPrism : public Shape {

public:

	RectangularPrism();
	RectangularPrism(double xLength, double yLength, double zLength);
	void draw();

private:
	double xLength;
	double yLength;
	double zLength;

};