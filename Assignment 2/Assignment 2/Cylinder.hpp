#include "Shape.hpp"

class Cylinder : public Shape {
public:
	Cylinder();
	Cylinder(double radius, double depth);

	void setRadius(double radius);
	double getRadius();
	void setDepth(double depth);
	double getDepth();

	void draw();

	void setSteering(double steering);
	double getSteering();
	void setRolling(double rolling);
	double getRolling();

	void setisRolling(bool);
	bool getisRolling();
	void setisSteering(bool);
	bool getisSteering();

private:
	double radius;
	double depth;
	double steering;
	double rolling;
	bool isRolling;
	bool isSteering;
};