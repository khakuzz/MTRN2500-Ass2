
#include "Vehicle.hpp"

Vehicle::Vehicle() {
	speed = steering = 0;
};

Vehicle::~Vehicle()
{ 
	// clean-up added shapes
	for(int i = 0; i < shapes.size(); i++) {
		delete shapes[i];
	}
}

void Vehicle::update(double dt)
{
	speed = clamp(MAX_BACKWARD_SPEED_MPS, speed, MAX_FORWARD_SPEED_MPS);
	steering = clamp(MAX_LEFT_STEERING_DEGS, steering, MAX_RIGHT_STEERING_DEGS);

	// update position by integrating the speed
	x += speed * dt * cos(rotation * 3.1415926535 / 180.0);
	z += speed * dt * sin(rotation * 3.1415926535 / 180.0);

	// update heading
	rotation += dt * steering * speed;

	while (rotation > 360) rotation -= 360;
	while (rotation < 0) rotation += 360;


	if(fabs(speed) < .1)
		speed = 0;
	if(fabs(steering) < .1)
		steering = 0;

}

void Vehicle::update(double speed_, double steering_, double dt) 
{
	speed = speed + ((speed_) - speed)*dt*4;
	steering = steering + (steering_ - steering)*dt * 6;

	update(dt);
}

void Vehicle::addShape(Shape * shape) 
{
	shapes.push_back(shape);
}

double clamp(double a, double n, double b) {

	if (a < b) {
		if (n < a) n = a;
		if (n > b) n = b;
	} else {
		if (n < b) n = b;
		if (n > a) n = a;
	}

	return n;

};

void MyVehicle::draw()
{
	glPushMatrix();
	positionInGL();

	RectangularPrism body;

	body.setLength(3, 1, 2);
	body.setPosition(0, 0.4, 0);
	body.setColor(0, 0, 1);
	body.draw();

	Cylinder SmallWheel;

	SmallWheel.setRadius(0.4);
	SmallWheel.setDepth(0.1);
	SmallWheel.setPosition(1.1, 0, 1.1);
	SmallWheel.setColor(0, 1, 0);
	SmallWheel.draw();
	SmallWheel.setPosition(1.1, 0, -1.1);
	SmallWheel.setColor(0, 1, 1);
	SmallWheel.draw();

	Cylinder BigWheel;

	BigWheel.setRadius(0.8);
	BigWheel.setDepth(0.1);
	BigWheel.setPosition(-1.1, 0, 1.1);
	BigWheel.setColor(1, 0, 0);
	BigWheel.draw();
	BigWheel.setPosition(-1.1, 0, -1.1);
	BigWheel.setColor(1, 0, 1);
	BigWheel.draw();

	glPopMatrix();

}
