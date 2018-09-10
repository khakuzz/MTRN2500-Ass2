#include "Shape.hpp"

class TrapezoidalPrism : public Shape {
public:

	TrapezoidalPrism();
	TrapezoidalPrism(double aLength, double bLength, double height, double aOffset, double depth);

	double getaLength();
	void setaLength(double aLength);
	double getbLength();
	void setbLength(double bLength);
	double getHeight();
	void setHeight(double height);
	double getaOffset();
	void setaOffset(double aOffset);
	double getDepth();
	void setDepth(double depth);

	void draw();

private:
	double aLength;
	double bLength;
	double height;
	double aOffset;
	double depth;
};