#pragma once

#include "PCH.h"
#include "InputKeys.h"

struct InputAxis
{
	std::string axisName;
	InputKeys positiveKey = KEY_NULL,
		negativeKey = KEY_NULL,
		altPositiveKey = KEY_NULL,
		altNegativeKey = KEY_NULL;
};

class InputManager
{
public:
	InputManager();
	~InputManager();

	void AddAxis(const InputAxis& pInputAxis);
	InputAxis GetAxisInfo(const std::string& pAxisName);
	float GetAxis(const std::string& pAxisName);

private:

	int CheckAxisPressed(const std::string& pAxisName);

	std::map<std::string, InputAxis> mInputAxes;
};

