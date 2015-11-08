#pragma once

#include "Scene.h"

//Default scene to be used for starting projects

class DefaultScene : public Scene
{
public:
	DefaultScene();
	virtual ~DefaultScene();

	virtual bool InitializeScene();
};

