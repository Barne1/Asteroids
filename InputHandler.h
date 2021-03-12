#pragma once
#include "SDL.h"
enum class LeftRight
{
	LEFT,
	RIGHT,
	NONE
};

enum class ForwardBack
{
	FORWARD,
	BACK,
	NONE
};

class InputHandler
{
public:
	static void UpdateKeyboardState();
	static const LeftRight GetLeftRight() { return leftRightInput; }
	static const ForwardBack GetForwardBack() { return forwardBackInput; }
	static const bool GetShoot() { return shoot; }
	static const bool GetRestart() { return restart; }
private:
	static LeftRight leftRightInput;
	static ForwardBack forwardBackInput;
	static bool shoot;
	static bool restart;
};

