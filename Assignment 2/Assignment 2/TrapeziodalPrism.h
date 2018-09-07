#include "Shape.hpp"

class TrapezoidalPrism : public Shape {
public:
	void draw();
	void setSides(double aLength, double bLength, double height, double aOffset);
	void setDepth(double depth);

private:
	double aLength;
	double bLength;
	double height;
	double aOffset;
	double depth;
};