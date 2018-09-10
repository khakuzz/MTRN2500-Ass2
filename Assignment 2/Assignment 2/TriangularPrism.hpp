
#ifndef MTRN3500_TRI_PRISM_H
#define MTRN3500_TRI_PRISM_H

#include "Shape.hpp"

class TriangularPrism : public Shape {
public:

	TriangularPrism();
	TriangularPrism(double aLength, double bLength, double theta, double depth);
	void draw();

private:
	double aLength;
	double bLength;
	double theta;
	double depth;
};


#endif

