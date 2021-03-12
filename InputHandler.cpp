#include "InputHandler.h"

LeftRight InputHandler::leftRightInput = LeftRight::NONE;
ForwardBack InputHandler::forwardBackInput = ForwardBack::NONE;
bool InputHandler::shoot = false;
bool InputHandler::restart = false;

void InputHandler::UpdateKeyboardState()
{
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	if (keyboardState[SDL_SCANCODE_A])
	{
		leftRightInput = LeftRight::LEFT;
	}
	else if (keyboardState[SDL_SCANCODE_D])
	{
		leftRightInput = LeftRight::RIGHT;
	}
	else
	{
		leftRightInput = LeftRight::NONE;
	}

	if (keyboardState[SDL_SCANCODE_W])
	{
		forwardBackInput = ForwardBack::FORWARD;
	}
	else if (keyboardState[SDL_SCANCODE_S])
	{
		forwardBackInput = ForwardBack::BACK;
	}
	else
	{
		forwardBackInput = ForwardBack::NONE;
	}

	shoot = keyboardState[SDL_SCANCODE_SPACE];
	restart = keyboardState[SDL_SCANCODE_R];
}
