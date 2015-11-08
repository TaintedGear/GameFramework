#pragma once

#include "PCH.h"

class Component
{
public:
	Component();
	virtual ~Component();

	// Accessors
	std::string Tag() const { return mTag; }
	std::string Name() const { return mName; }
	void Name(std::string val) { mName = val; }

	void Update(const float pDeltaTick);

protected:
	std::string mName;
	std::string mTag;

};

