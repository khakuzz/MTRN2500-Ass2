
#ifndef MTRN3500_TRI_PRISM_H
#define MTRN3500_TRI_PRISM_H

#include "Shape.hpp"

class TriangularPrism : public Shape {
public:

	TriangularPrism();
	TriangularPrism(double aLength, double bLength, double theta, double depth);

	double getaLength();
	void setaLength(double aLength);
	double getbLength();
	void setbLength(double bLength);
	double getTheta();
	void setTheta(double theta);
	double getDepth();
	void setDepth(double depth);

	void draw();

private:
	double aLength;
	double bLength;
	double theta;
	double depth;
};


#endif

