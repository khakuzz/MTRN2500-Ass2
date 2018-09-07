
#ifndef MTRN3500_TRI_PRISM_H
#define MTRN3500_TRI_PRISM_H

#include "Shape.hpp"

class TriangularPrism : public Shape {
public:

	void draw();
	void setSides(double aLength, double bLength, double theta);
	void setDepth(double depth);

private:
	double aLength;
	double bLength;
	double theta;
	double depth;
};


#endif

