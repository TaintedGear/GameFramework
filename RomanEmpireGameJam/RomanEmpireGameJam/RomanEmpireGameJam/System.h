#pragma once

class System
{
public:
	System();
	virtual ~System();

	virtual bool StartupSystem();
	virtual void ShutdownSystem();

	//TODO
};

