#pragma once

#include "Application.h"
#include "World.h"

class BasicApp :
	public Application
{
public:
	BasicApp();
	virtual ~BasicApp();

	virtual bool Initialize();
	virtual void Shutdown();

protected: 
	virtual void MessagingLoop() override;
	virtual void Update() override;
	virtual void Draw() override;

	//World object
	std::shared_ptr<class THWorld> mWorld;
};

