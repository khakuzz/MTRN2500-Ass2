#include "XBoxController.h"
#include <Windows.h>
#include <iostream>

GamePad::XBoxController::XBoxController(XInputWrapper * xinput, DWORD id) // Imports the xbox inputs through the xinputwrapper
{
	this->xinput = xinput;
	UserID = id;

}

DWORD GamePad::XBoxController::GetControllerId() // Obtains the ID of the controller and returns it as UserID
{
	return UserID;
}

bool GamePad::XBoxController::IsConnected() // Checks if controller is connected
{
	if (xinput->XInputGetState(UserID, &State) == ERROR_DEVICE_NOT_CONNECTED) {
		return false;
	}
	return true;
}

bool GamePad::XBoxController::PressedA() // Performs bitwise AND with the value of bitmask for A
{
	xinput->XInputGetState(UserID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedB() // Performs bitwise AND with the value of bitmask for B
{
	xinput->XInputGetState(UserID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedX() // Performs bitwise AND with the value of bitmask for X
{
	xinput->XInputGetState(UserID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedY() // Performs bitwise AND with the value of bitmask for Y
{
	xinput->XInputGetState(UserID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedLeftShoulder() // Performs bitwise AND with the value of bitmask for Left Shoulder
{
	xinput->XInputGetState(UserID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedRightShoulder() // Performs bitwise AND with the value of bitmask for Right Shoulder
{
	xinput->XInputGetState(UserID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedLeftDpad() // Performs bitwise AND with the value of bitmask for Left D Pad
{
	xinput->XInputGetState(UserID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedRightDpad() // Performs bitwise AND with the value of bitmask for Right D Pad
{
	xinput->XInputGetState(UserID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedUpDpad() // Performs bitwise AND with the value of bitmask for Up D Pad
{
	xinput->XInputGetState(UserID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedDownDpad() // Performs bitwise AND with the value of bitmask for Down D Pad
{
	xinput->XInputGetState(UserID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedStart() // Performs bitwise AND with the value of bitmask for Start
{
	xinput->XInputGetState(UserID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_START) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedBack() // Performs bitwise AND with the value of bitmask for Back
{
	xinput->XInputGetState(UserID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedLeftThumb() // Performs bitwise AND with the value of bitmask for Left Thumb
{
	xinput->XInputGetState(UserID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) {
		return true;
	}
	return false;
}

bool GamePad::XBoxController::PressedRightThumb() // Performs bitwise AND with the value of bitmask for Right Thumb
{
	xinput->XInputGetState(UserID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) {
		return true;
	}
	return false;
}

BYTE GamePad::XBoxController::LeftTriggerLocation() // Returns byte value of the Left Trigger
{
	xinput->XInputGetState(UserID, &State);
	return State.Gamepad.bLeftTrigger;
}

BYTE GamePad::XBoxController::RightTriggerLocation() // Returns byte value of the Right Trigger
{
	xinput->XInputGetState(UserID, &State);
	return State.Gamepad.bRightTrigger;
}

GamePad::Coordinate GamePad::XBoxController::LeftThumbLocation() // Returns the value of the Left Thumb Location
{
	xinput->XInputGetState(UserID, &State);
	GamePad::Coordinate LeftThumb(State.Gamepad.sThumbLX, State.Gamepad.sThumbLY); // Imports the values of the coordinates for Left Thumb and creates an object LeftThumb

	float LX = LeftThumb.GetX(); // Get value of X and Y Coordinates and sets them to a float value
	float LY = LeftThumb.GetY();

	float magnitude = sqrt(LX * LX + LY * LY); // Finds the magnitude of the position of X and Y coordinates

	float normalisedMagnitude = 0;

	if (magnitude > Deadzone) { // Checks if the magnitude is greater than the set dead zone
		if (magnitude > 32767) {
			magnitude = 32767; // limits the magnitude to the max value if it exceeds the max value
		}

		magnitude = magnitude - Deadzone;

		normalisedMagnitude = ((magnitude) / (32767 - Deadzone)); // adds a scale factor of 0 - 1 to allow the coordinates to be mapped to the new magnitudes

		LeftThumb.SetX(normalisedMagnitude * LeftThumb.GetX()); // Replace the existing magnitudes for X and Y with their respective new magnitudes
		LeftThumb.SetY(normalisedMagnitude * LeftThumb.GetY());

	}
	else {
		LeftThumb.SetX(0); // If the magnitude is inside the dead zone, set the X and Y coordinates to 0
		LeftThumb.SetY(0);
		magnitude = 0.0;
		normalisedMagnitude = 0.0;
	}

	return LeftThumb;
}

GamePad::Coordinate GamePad::XBoxController::RightThumbLocation() // Returns the value of the Right Thumb Location
{
	xinput->XInputGetState(UserID, &State);
	GamePad::Coordinate RightThumb(State.Gamepad.sThumbRX, State.Gamepad.sThumbRY);// Imports the values of the coordinates for Right Thumb and creates an object RightThumb

	float RX = RightThumb.GetX(); // Get value of X and Y Coordinates and sets them to a float value
	float RY = RightThumb.GetY();

	float magnitude = sqrt(RX * RX + RY * RY); // Finds the magnitude of the position of X and Y coordinates

	float normalisedMagnitude = 0;

	if (magnitude > Deadzone) { // Checks if the magnitude is greater than the set dead zone
		if (magnitude > 32767) {
			magnitude = 32767; // limits the magnitude to the max value if it exceeds the max value
		}

		magnitude = magnitude - Deadzone;

		normalisedMagnitude = ((magnitude) / (32767 - Deadzone)); // adds a scale factor of 0 - 1 to allow the coordinates to be mapped to the new magnitudes

		RightThumb.SetX(normalisedMagnitude * RightThumb.GetX()); // Replace the existing magnitudes for X and Y with their respective new magnitudes
		RightThumb.SetY(normalisedMagnitude * RightThumb.GetY());

	}
	else {
		RightThumb.SetX(0); // If the magnitude is inside the dead zone, set the X and Y coordinates to 0
		RightThumb.SetY(0);
		magnitude = 0.0;
		normalisedMagnitude = 0.0;
	}

	return RightThumb;
}

void GamePad::XBoxController::Vibrate(WORD left, WORD right) // Sets the vibration settings for the controller
{
	xinput->XInputSetState(UserID, &Vibration);
	Vibration.wLeftMotorSpeed = left; // The left and right motor values are set to the inputs 'left' and 'right'
	Vibration.wRightMotorSpeed = right;

	return;
}

void GamePad::XBoxController::SetDeadzone(unsigned int radius) // Sets the deadzone for the controller
{
	Deadzone = radius;
}
