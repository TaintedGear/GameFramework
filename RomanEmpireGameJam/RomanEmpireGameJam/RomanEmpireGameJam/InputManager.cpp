#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::AddAxis(const InputAxis& pInputAxis)
{
	mInputAxes[pInputAxis.axisName] = pInputAxis;
}

InputAxis InputManager::GetAxisInfo(const std::string& pAxisName)
{
	return mInputAxes.at(pAxisName);
}

float InputManager::GetAxis(const std::string& pAxisName)
{
	return (float)CheckAxisPressed(pAxisName);
}

int InputManager::CheckAxisPressed(const std::string& pAxisName)
{
	const Uint8* state = 0;
	state = SDL_GetKeyboardState(NULL);

	const InputAxis axes = mInputAxes.at(pAxisName);

	//Positive keys was pressed
	if (state[axes.positiveKey] || state[axes.altPositiveKey])
	{
		return 1;
	}

	//Negative key was pressed
	if (state[axes.negativeKey] || state[axes.altNegativeKey])
	{
		return -1;
	}

	//No key was pressed
	return 0;
}