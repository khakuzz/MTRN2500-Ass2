#include "Vehicle.hpp"

class MyVehicle : public Vehicle {
public:

	MyVehicle();
	void addingS(Shape * shape); // add the shape to the vector using this method
	void draw(); // draws the vehicle
	std::vector<Shape *> getShapes(); // returns the shapes vector
};