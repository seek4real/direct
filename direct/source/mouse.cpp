/**
** mouse
** suport mouse device input
*/

#include "../include/mouse.h"
#include "../include/log.h"
#include <string>

using direct::MouseInput;
using direct::Logger;

MouseInput::MouseInput() {}
MouseInput::~MouseInput() {}

// Singleton Lazy
MouseInput& MouseInput::single()
{
	static MouseInput instance;
	return instance;
}

void MouseInput::onLeftKeyDown(float x, float y)
{
	Logger::get()->log("left mouse key down position =" + std::to_string(x) + "," + std::to_string(y));

}
void MouseInput::onLeftKeyUp(float x, float y){}

void MouseInput::onRightKeyDown(float x, float y){}
void MouseInput::onRightKeyUp(float x, float y){}

void MouseInput::onMove(float x, float y){}