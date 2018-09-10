
#include "Shape.hpp"

class RectangularPrism : public Shape {

public:

	RectangularPrism();
	RectangularPrism(double xLength, double yLength, double zLength);

	double getxLength();
	void setxLength(double xLength);
	double getyLength();
	void setyLength(double yLength);
	double getzLength();
	void setzLength(double zLength);

	void draw();

private:
	double xLength;
	double yLength;
	double zLength;

};