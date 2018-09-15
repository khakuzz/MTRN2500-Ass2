
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <map>


#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
	#include <unistd.h>
	#include <sys/time.h>
#elif defined(WIN32)
	#include <Windows.h>
	#include <tchar.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
	#include <unistd.h>
	#include <sys/time.h>
#endif

#include <Xinput.h>
#include "XBoxController.h"
#include "XInputWrapper.h"

#include "Camera.hpp"
#include "Ground.hpp"
#include "KeyManager.hpp"

#include "Shape.hpp"
#include "TriangularPrism.hpp"
#include "TrapeziodalPrism.h"
#include "RectangularPrism.hpp"
#include "Cylinder.hpp"
#include "Vehicle.hpp"
#include "Brum.hpp"
#include "OtherCar.h"

#include "RemoteDataManager.hpp"
#include "Messages.hpp"
#include "HUD.hpp"
#include "ObstacleManager.hpp"


void display();
void reshape(int width, int height);
void idle();

void keydown(unsigned char key, int x, int y);
void keyup(unsigned char key, int x, int y);
void special_keydown(int keycode, int x, int y);
void special_keyup(int keycode, int x, int y);

void mouse(int button, int state, int x, int y);
void dragged(int x, int y);
void motion(int x, int y);

using namespace std;
using namespace scos;

// Used to store the previous mouse location so we
//   can calculate relative mouse movement.
int prev_mouse_x = -1;
int prev_mouse_y = -1;

// vehicle control related variables
Vehicle * vehicle = NULL;
double speed = 0;
double steering = 0;

// default goal location
std::deque<GoalState> goals;

std::map<int, Vehicle *> otherVehicles;

int frameCounter = 0;

//int _tmain(int argc, _TCHAR* argv[]) {
int main(int argc, char ** argv) {

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	glutInit(&argc, (char**)(argv));
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("MTRN3500 - GL");

	Camera::get()->setWindowDimensions(WINDOW_WIDTH, WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutKeyboardFunc(keydown);
	glutKeyboardUpFunc(keyup);
	glutSpecialFunc(special_keydown);
	glutSpecialUpFunc(special_keyup);

	glutMouseFunc(mouse);
	glutMotionFunc(dragged);
	glutPassiveMotionFunc(motion);

	// -------------------------------------------------------------------------
	// Please uncomment the following line of code and replace 'MyVehicle'
	//   with the name of the class you want to show as the current 
	//   custom vehicle.
	// -------------------------------------------------------------------------

	vehicle = new MyVehicle();


	// add test obstacles
	ObstacleManager::get()->addObstacle(Obstacle(10,10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(10,-10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10,10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10,-10, 1));

	// add test goal
	GoalState g;
	g.x = 25;
	g.z = 0;
	goals.push_back(g);


	glutMainLoop();

	if (vehicle != NULL) {
		delete vehicle;
	}

	return 0;
}

void drawGoals()
{
	for (int i = 0; i < goals.size(); ++i) {
		GoalState goal = goals[i];

		glPushMatrix();
		glTranslatef(goal.x, 0, goal.z);
		glRotated(90, -1, 0, 0);
		static GLUquadric * quad = gluNewQuadric();

		// make first goal purple
		if (i == 0)
			glColor3f(1, .3, 1);
		else
			glColor3f(1, 1, 1);

		gluCylinder(quad, .5, .5, 10, 5, 1);
		glPopMatrix();
	}
}

void testing() {

	RectangularPrism Rec(10, 5, 10);
	Rec.setPosition(25, 0, 25);
	Rec.setRotation(0);
	Rec.setColor(0, 0, 1);
	Rec.draw();

	TriangularPrism Tri(3, 40, 90, 30);
	Tri.setDepth(5);
	Tri.setPosition(-25, 0, 25);
	Tri.setColor(0, 1, 0);
	Tri.draw();

	TrapezoidalPrism Tra(10, 10, 10, 2, 10);
	Tra.setDepth(15);
	Tra.setPosition(-25, 0, -25);
	Tra.setColor(0, 1, 1);
	Tra.draw();

	Cylinder Cyl;
	Cyl.setPosition(25, 0, -25);
	Cyl.setRotation(0);
	Cyl.setRadius(5);
	Cyl.setDepth(10);
	Cyl.setColor(1, 0, 0);
	Cyl.draw();

	MyVehicle Veh;
	Veh.setPosition(0, 0, 0);
	//Veh.draw();

}

void display() {
	frameCounter++;
	// -------------------------------------------------------------------------
	//  This method is the main draw routine. 
	// -------------------------------------------------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(Camera::get()->isPursuitMode() && vehicle != NULL) {
		double x = vehicle->getX(), y = vehicle->getY(), z = vehicle->getZ();
		double dx = cos(vehicle->getRotation() * 3.141592765 / 180.0);
		double dy = sin(vehicle->getRotation() * 3.141592765 / 180.0);
		Camera::get()->setDestPos(x + (-20 * dx), y + 15, z + (-20 * dy));
		Camera::get()->setDestDir(dx, -0.25, dy);
	}
	Camera::get()->updateLocation();
	Camera::get()->setLookAt();

	Ground::draw();
	
	// draw other vehicles
	for(std::map<int, Vehicle *>::iterator iter = otherVehicles.begin(); iter != otherVehicles.end(); ++iter) 
		iter->second->draw();

	// draw my vehicle
	if (vehicle != NULL) {
		vehicle->draw();

	}

	// draw obstacles
	ObstacleManager::get()->drawAll();

	// draw goals
	drawGoals();

	// draw HUD
	HUD::Draw();

	//testing();

	glutSwapBuffers();
};

void reshape(int width, int height) {

	Camera::get()->setWindowDimensions(width, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
};

void remoteDriver(Vehicle * vehicle, double x, double z, double r, double speed_, double steering_)
{
	// filter 
	const double kSmoothingFactor = 0.5;
	vehicle->setX(vehicle->getX() * kSmoothingFactor + x * (1 - kSmoothingFactor));
	vehicle->setZ(vehicle->getZ() * kSmoothingFactor + z * (1 - kSmoothingFactor));

	vehicle->setRotation(r);
	vehicle->steering = steering_;
	vehicle->speed = speed_;
}

double getTime()
{
#if defined(WIN32)
	LARGE_INTEGER freqli;
	LARGE_INTEGER li;
	if(QueryPerformanceCounter(&li) && QueryPerformanceFrequency(&freqli)) {
		return double(li.QuadPart) / double(freqli.QuadPart);
	}
	else {
		static ULONGLONG start = GetTickCount64();
		return (GetTickCount64() - start) / 1000.0;
	}
#else
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + (t.tv_usec / 1000000.0);
#endif
}

void idle() {

	XInputWrapper xinput;
	GamePad::XBoxController controller(&xinput, 0);


	if (KeyManager::get()->isAsciiKeyPressed('a')) {
		Camera::get()->strafeLeft();
	}

	if (KeyManager::get()->isAsciiKeyPressed('c')) {
		Camera::get()->strafeDown();
	}

	if (KeyManager::get()->isAsciiKeyPressed('d')) {
		Camera::get()->strafeRight();
	}

	if (KeyManager::get()->isAsciiKeyPressed('s')) {
		Camera::get()->moveBackward();
	}

	if (KeyManager::get()->isAsciiKeyPressed('w')) {
		Camera::get()->moveForward();
	}

	if (KeyManager::get()->isAsciiKeyPressed(' ')) {
		Camera::get()->strafeUp();
	}

	speed = 0;
	steering = 0;

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_LEFT)) {
		steering = Vehicle::MAX_LEFT_STEERING_DEGS * -1;   
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
		steering = Vehicle::MAX_RIGHT_STEERING_DEGS * -1;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_UP)) {
		speed = Vehicle::MAX_FORWARD_SPEED_MPS;
	}

	float magnitude = 0;

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_DOWN)) {
		speed = Vehicle::MAX_BACKWARD_SPEED_MPS;
	}
	if (controller.LeftThumbLocation().GetX() < 0) {
		magnitude = (float)controller.LeftThumbLocation().GetX() / 32767;
		steering = Vehicle::MAX_LEFT_STEERING_DEGS * magnitude;
	}

	if (controller.LeftThumbLocation().GetX() > 0) {
		magnitude = (float)controller.LeftThumbLocation().GetX() / 32767;
		steering = Vehicle::MAX_RIGHT_STEERING_DEGS * -magnitude;
	}
	
	float LeftTriggerMagnitude = 0;
	float RightTriggerMagnitude = 0;

	if (controller.RightTriggerLocation() > 0) {
		RightTriggerMagnitude = (float)controller.RightTriggerLocation() / 255;
		speed = RightTriggerMagnitude * 10;
	}

	if (controller.LeftTriggerLocation() > 0) {
		LeftTriggerMagnitude = (float)controller.LeftTriggerLocation() / 255;
		speed = LeftTriggerMagnitude * -4;
	}
	

	if (controller.PressedRightShoulder()) { // try to map this to left and right trigger instead of left and right shoulder!
		speed = Vehicle::MAX_FORWARD_SPEED_MPS;
	}

	if (controller.PressedLeftShoulder()) {
		speed = Vehicle::MAX_BACKWARD_SPEED_MPS;
	}

	// attempt to do data communications every 4 frames if we've created a local vehicle
	if(frameCounter % 4 == 0 && vehicle != NULL) {

		// if not connected, attempt to connect every 2 seconds
		if(!RemoteDataManager::IsConnected()) {
			if(frameCounter % 120 == 0) {
		
				// erase other vehicles
				for(std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter  != otherVehicles.end(); ++iter) {
					delete iter->second;
				}
				otherVehicles.clear();

				// uncomment this line to connect to the robotics server.
				RemoteDataManager::Connect("www.robotics.unsw.edu.au","18081");

				// on connect, let's tell the server what we look like
				if (RemoteDataManager::IsConnected()) {
					ObstacleManager::get()->removeAll();

					VehicleModel vm;
					vm.remoteID = 0;
					
					//
					// student code goes here
					//


					std::vector<Shape *> shapeVector = dynamic_cast<MyVehicle *>(vehicle)->getShapes();
					std::vector<Shape *>::iterator itera;

					for (itera = shapeVector.begin(); itera != shapeVector.end(); ++itera) {

						ShapeInit tempShape = {};

						tempShape.xyz[0] = (*itera)->getX(); // stores the colour, location and rotation of MyVehicle
						tempShape.xyz[1] = (*itera)->getY();
						tempShape.xyz[2] = (*itera)->getZ();
						tempShape.rgb[0] = (*itera)->getRed();
						tempShape.rgb[1] = (*itera)->getGreen();
						tempShape.rgb[2] = (*itera)->getBlue();
						tempShape.rotation = (*itera)->getRotation();

						if (dynamic_cast<RectangularPrism *>(*itera)) { // checks what type (*itera) is and stores the parameters of the shape
							tempShape.type = RECTANGULAR_PRISM;
							tempShape.params.rect.xlen = (float)dynamic_cast<RectangularPrism *>(*itera)->getxLength();
							tempShape.params.rect.ylen = (float)dynamic_cast<RectangularPrism *>(*itera)->getyLength();
							tempShape.params.rect.zlen = (float)dynamic_cast<RectangularPrism *>(*itera)->getzLength();
							vm.shapes.push_back(tempShape);
						}
						else if (dynamic_cast<TriangularPrism *>(*itera)) {
							tempShape.type = TRIANGULAR_PRISM;
							tempShape.params.tri.alen = (float)dynamic_cast<TriangularPrism *>(*itera)->getaLength();
							tempShape.params.tri.blen = (float)dynamic_cast<TriangularPrism *>(*itera)->getbLength();
							tempShape.params.tri.angle = (float)dynamic_cast<TriangularPrism *>(*itera)->getTheta();
							tempShape.params.tri.depth = (float)dynamic_cast<TriangularPrism *>(*itera)->getDepth();
							vm.shapes.push_back(tempShape);
						}
						else if (dynamic_cast<TrapezoidalPrism *>(*itera)) {
							tempShape.type = TRAPEZOIDAL_PRISM;
							tempShape.params.trap.alen = (float)dynamic_cast<TrapezoidalPrism *>(*itera)->getaLength();
							tempShape.params.trap.blen = (float)dynamic_cast<TrapezoidalPrism *>(*itera)->getbLength();
							tempShape.params.trap.height = (float)dynamic_cast<TrapezoidalPrism *>(*itera)->getHeight();
							tempShape.params.trap.aoff = (float)dynamic_cast<TrapezoidalPrism *>(*itera)->getaOffset();
							tempShape.params.trap.depth = (float)dynamic_cast<TrapezoidalPrism *>(*itera)->getDepth();
							vm.shapes.push_back(tempShape);
						}
						else if (dynamic_cast<Cylinder *>(*itera)) {
							tempShape.type = CYLINDER;
							tempShape.params.cyl.radius = (float)dynamic_cast<Cylinder *>(*itera)->getRadius();
							tempShape.params.cyl.depth = (float)dynamic_cast<Cylinder *>(*itera)->getDepth();
							tempShape.params.cyl.isRolling = (float)dynamic_cast<Cylinder *>(*itera)->getisRolling();
							tempShape.params.cyl.isSteering = (float)dynamic_cast<Cylinder *>(*itera)->getisSteering();
							vm.shapes.push_back(tempShape);
						}
					}

					RemoteDataManager::Write(GetVehicleModelStr(vm));
				}
			}
		}

		// if we're connected, send our vehicle state to the server
		if (RemoteDataManager::IsConnected()) {
			VehicleState vs;
			vs.remoteID = 0;
			vs.x = vehicle->getX();
			vs.z = vehicle->getZ();
			vs.rotation = vehicle->getRotation();
			vs.speed = vehicle->getSpeed();
			vs.steering = vehicle->getSteering();
			RemoteDataManager::Write(GetVehicleStateStr(vs));
		}

		// if we're still connected, receive and handle response messages from the server
		if (RemoteDataManager::IsConnected()) {
			std::vector<RemoteMessage> msgs = RemoteDataManager::Read();
			for(unsigned int i = 0; i < msgs.size(); i++ ) {

				RemoteMessage msg = msgs[i];
				//cout << msg.payload << endl;

				switch(msg.type) {
					// new models
					case 'M':
						{
							std::vector<VehicleModel> models = GetVehicleModels(msg.payload);
							for(unsigned int i = 0; i < models.size(); i++) {
								VehicleModel vm = models[i];
								
								// uncomment the line below to create remote vehicles
								otherVehicles[vm.remoteID] = new OtherCar();

								//
								// more student code goes here
								//

								std::vector<ShapeInit>::iterator itera;

								for (itera = vm.shapes.begin(); itera != vm.shapes.end(); ++itera) {

									double x = (double)(*itera).xyz[0];
									double y = (double)(*itera).xyz[1];
									double z = (double)(*itera).xyz[2];
									double rotation = (double)(*itera).rotation;
									double red = (double)(*itera).rgb[0];
									double green = (double)(*itera).rgb[1];
									double blue = (double)(*itera).rgb[2];

									if ((*itera).type == RECTANGULAR_PRISM) {

										RectangularPrism * Rect = new RectangularPrism((*itera).params.rect.xlen, (*itera).params.rect.ylen, (*itera).params.rect.zlen);
										Rect->setRotation((*itera).rotation);
										Rect->setPosition(x, y, z);
										Rect->setColor(red, green, blue);
										otherVehicles[vm.remoteID]->addShape(Rect);
									}
									else if ((*itera).type == TRIANGULAR_PRISM) {

										TriangularPrism * Tria = new TriangularPrism((*itera).params.tri.alen, (*itera).params.tri.blen, (*itera).params.tri.angle, (*itera).params.tri.depth);
										Tria->setRotation((*itera).rotation);
										Tria->setPosition(x, y, z);
										Tria->setColor(red, green, blue);
										otherVehicles[vm.remoteID]->addShape(Tria);
									}
									else if ((*itera).type == TRAPEZOIDAL_PRISM) {
										
										TrapezoidalPrism * Trap = new TrapezoidalPrism((*itera).params.trap.alen, (*itera).params.trap.blen, (*itera).params.trap.height, (*itera).params.trap.aoff, (*itera).params.trap.depth);
										Trap->setRotation((*itera).rotation);
										Trap->setPosition(x, y, z);
										Trap->setColor(red, green, blue);
										otherVehicles[vm.remoteID]->addShape(Trap);
									}
									else if ((*itera).type == CYLINDER) {

										Cylinder * Cyli = new Cylinder((*itera).params.cyl.radius, (*itera).params.cyl.depth);
										Cyli->setisRolling((*itera).params.cyl.isRolling);
										Cyli->setisSteering((*itera).params.cyl.isSteering);
										Cyli->setRotation((*itera).rotation);
										Cyli->setPosition(x, y, z);
										Cyli->setColor(red, green, blue);
										otherVehicles[vm.remoteID]->addShape(Cyli);
									}
								}
								
							}
							break;
						}

					// vehicle states
					case 'S': 
						{
							std::vector<VehicleState> states = GetVehicleStates(msg.payload);
							for(unsigned int i = 0; i < states.size(); i++) {
								VehicleState vs = states[i];

								std::map<int, Vehicle*>::iterator iter = otherVehicles.find(vs.remoteID);
								if(iter != otherVehicles.end()) {
									Vehicle * veh = iter->second;
									remoteDriver(veh, vs.x, vs.z, vs.rotation, vs.speed, vs.steering);
								}
							}
							break;
						}

					// goal state
					case 'G':
						{
							goals = GetGoals(msg.payload);
							break;
						}

					// obstacle state
					case 'O':
						{
							std::vector<ObstacleState> obs = GetObstacles(msg.payload);
							for(unsigned int i = 0; i < obs.size(); i++) {
								Obstacle o(obs[i].x, obs[i].z, obs[i].radius);
								ObstacleManager::get()->addObstacle(o);
							}
							break;
						}

					// disconnect list
					case 'D':
						{
							std::vector<int> disconnectedIDs = GetVehicleDisconnects(msg.payload);
							for(unsigned int i = 0; i < disconnectedIDs.size(); i++) {
								int id = disconnectedIDs[i];
								std::map<int, Vehicle*>::iterator iter = otherVehicles.find(id);
								if(iter != otherVehicles.end()) {
									delete iter->second;
									otherVehicles.erase(iter);
								}
							}
							break;
						}

					// error message
					case 'E':
						{
							cerr << "Server error: " << msg.payload << endl;
							break;
						}

				}
			} 
		}
	}


	const float sleep_time_between_frames_in_seconds = 0.025;

	static double previousTime = getTime();
	const double currTime = getTime();
	const double elapsedTime = currTime - previousTime;
	previousTime = currTime;

	// do a simulation step
	if (vehicle != NULL) {
		vehicle->update(speed, steering, elapsedTime);
	}
	for(std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter  != otherVehicles.end(); ++iter) {
		iter->second->update(elapsedTime);
	}

	display();

#ifdef _WIN32 
	Sleep(sleep_time_between_frames_in_seconds * 1000);
#else
	usleep(sleep_time_between_frames_in_seconds * 1e6);
#endif
};

void keydown(unsigned char key, int x, int y) {

	// keys that will be held down for extended periods of time will be handled
	//   in the idle function
	KeyManager::get()->asciiKeyPressed(key);

	// keys that react ocne when pressed rather than need to be held down
	//   can be handles normally, like this...
	switch (key) {
	case 27: // ESC key
		exit(0);
		break;      
	case '0':
		Camera::get()->jumpToOrigin();
		break;
	case 'p':
		Camera::get()->togglePursuitMode();
		break;
	}

};

void keyup(unsigned char key, int x, int y) {
	KeyManager::get()->asciiKeyReleased(key);
};

void special_keydown(int keycode, int x, int y) {

	KeyManager::get()->specialKeyPressed(keycode);

};

void special_keyup(int keycode, int x, int y) {  
	KeyManager::get()->specialKeyReleased(keycode);  
};

void mouse(int button, int state, int x, int y) {

};

void dragged(int x, int y) {

	if (prev_mouse_x >= 0) {

		int dx = x - prev_mouse_x;
		int dy = y - prev_mouse_y;

		Camera::get()->mouseRotateCamera(dx, dy);
	}

	prev_mouse_x = x;
	prev_mouse_y = y;
};

void motion(int x, int y) {

	prev_mouse_x = x;
	prev_mouse_y = y;
};


