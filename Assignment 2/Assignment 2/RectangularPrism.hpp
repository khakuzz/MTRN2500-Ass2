
#include "Shape.hpp"

class RectangularPrism : public Shape {

public:
	void draw();
	void setLength(double xLength, double yLength, double zLength);

private:
	double xLength;
	double yLength;
	double zLength;

};