#include "Shape.hpp"

class TrapezoidalPrism : public Shape {
public:

	TrapezoidalPrism();
	TrapezoidalPrism(double aLength, double bLength, double height, double aOffset, double depth);
	void draw();

private:
	double aLength;
	double bLength;
	double height;
	double aOffset;
	double depth;
};